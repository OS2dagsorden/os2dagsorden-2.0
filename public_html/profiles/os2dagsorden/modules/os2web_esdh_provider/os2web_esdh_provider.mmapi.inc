<?php

/**
 * @file
 * This file implements the importing functions
 * of the MM functionality and depends on a
 * plugin to do the actual filereads
 */

module_load_include('inc', 'os2web_esdh_provider', 'includes/os2web_esdh_provider.queue');
$PROCESSING_MEETING = 0;
$PROCESSING_BP = 0;

/**
 * Pretty sizes.
 *
 * @param int $size
 *   Size in bytes
 *
 * @return string
 *   Pretty size
 */
function hr_size($size) {
  $unit = array('b', 'kb', 'mb', 'gb', 'tb', 'pb');
  return @round($size / pow(1024, ($i = floor(log($size, 1024)))), 2) . ' ' . $unit[$i];
}

/**
 * Internal logger.
 *
 * @param string $msg
 *   Message to log
 */
function err_debug($msg = FALSE) {
  if (variable_get('os2web_esdh_provider_debug_info')) {
    $mem = hr_size(memory_get_usage());
    $timer = number_format(timer_read('mm_import') / 1000, 2) . "sec.";
    error_log("MM Import - $msg - $mem $timer");
  }
}

/**
 * Imports meeting metadata into a node.
 *
 * @param string $meeting_id
 *   Meeting id
 *
 * @return int
 *   Node id
 */
function _os2web_esdh_provider_import_meeting($meeting_id, $force = FALSE, &$context = NULL) {
  if (!lock_acquire(__FUNCTION__ . $meeting_id['id'])) {
    return;
  }
  timer_start('mm_import');
  global $PROCESSING_MEETING_ID, $PROCESSING_MEETING_NID, $PROCESSING_MEETING_ACCESS;
  $PROCESSING_MEETING_ID = $meeting_id['id'];

  $nid = os2web_esdh_provider_index_meeting_get_nid($meeting_id['id']);
  if ($nid) {
    watchdog('acadre MM', '[XML_ID: !id ] Found existing meeting node nid: !nid', array('!id' => $PROCESSING_MEETING_ID, '!nid' => $nid), WATCHDOG_DEBUG);
    $PROCESSING_MEETING_NID = $nid;
  }

  if (!os2web_esdh_provider_index_meeting_is_manifest_outdated($meeting_id['id'], filemtime(drupal_realpath($meeting_id['uri']))) &&
    !os2web_esdh_provider_index_meeting_has_deleted_agendas($meeting_id['id'])) {
    if ($nid) {
      watchdog('acadre MM', '[XML_ID: !id] Latest meeting version is already imported into nid: !nid. Skipping manifest', array('!id' => $PROCESSING_MEETING_ID, '!nid' => $nid), WATCHDOG_INFO);
    } else {
      watchdog('acadre MM', '[XML_ID: !id] No agendas to import. Skipping manifest', array('!id' => $PROCESSING_MEETING_ID), WATCHDOG_INFO);
    }
    lock_release(__FUNCTION__ . $meeting_id['id']);
    return;
  }

  watchdog('acadre MM', '[XML_ID: !id] Initialized meeting import', array('!id' => $PROCESSING_MEETING_ID), WATCHDOG_NOTICE);

  $meetings = os2web_esdh_provider_invoke('mm', 'import_meeting', $meeting_id);

  $nids = array();

  // Do an initially check on if there are any approved meetings.
  if (count($meetings) === 0) {
    watchdog('acadre MM', '[XML_ID: !id]  There was no meetings to import. See if all manifests are OK? ', array('!id' => $PROCESSING_MEETING_ID), WATCHDOG_WARNING);
    _os2web_esdh_provider_send_statusmail(t('There was no meetings to import for meeting !id. See if all manifests are OK?', array('!id' => $meeting_id['id'])), TRUE);
    lock_release(__FUNCTION__ . $meeting_id['id']);
    return;
  }

  // Run through all meetings. Remove all unpublished.
  // Retrieve nid of already existing node.
  $number_of_meetings = count($meetings);
  watchdog('acadre MM', '[XML_ID: !id] Number of agendas: !number', array('!id' => $PROCESSING_MEETING_ID, '!number' => $number_of_meetings), WATCHDOG_DEBUG);
  for ($i = 0; $i < $number_of_meetings; $i++) {
    os2web_esdh_provider_index_meeting($nid, $meeting_id, $meetings[$i]);

    if ($meetings[$i]['publish'] === FALSE) {
      watchdog('acadre MM', '[XML_ID: !id] Agenda !meeting_sub_id will NOT be published. [publish]=!publish, [access]=!access',
        array('!id' => $PROCESSING_MEETING_ID,
              '!meeting_sub_id' => $meetings[$i]['meeting_sub_id'],
              '!publish' => intval($meetings[$i]['publish']),
              '!access' => $meetings[$i]['agenda_access'],
        ),
        WATCHDOG_INFO);
      unset($meetings[$i]);
    } else {
      watchdog('acadre MM', '[XML_ID: !id] Agenda !meeting_sub_id is allowed be published. [publish]=!publish, [access]=!access',
        array('!id' => $PROCESSING_MEETING_ID,
              '!meeting_sub_id' => $meetings[$i]['meeting_sub_id'],
              '!publish' => intval($meetings[$i]['publish']),
              '!access' => $meetings[$i]['agenda_access'],
        ),
        WATCHDOG_INFO);
    }
  }

  // If any already exist and no one is left to be published,
  // the existing should be unpublished.
  if ($nid && count($meetings) === 0) {
    // Meeting needs to be unpublished.
    watchdog('acadre MM', '[XML_ID: !id] Starting deleting node with nid: !nid', array('!id' => $PROCESSING_MEETING_ID, '!nid' => $nid), WATCHDOG_DEBUG);
    node_delete($nid);
    watchdog('acadre MM', '[XML_ID: !id] Deleted node nid: !nid .', array('!id' => $PROCESSING_MEETING_ID, '!nid' => $nid), WATCHDOG_NOTICE);
    lock_release(__FUNCTION__ . $meeting_id['id']);
    watchdog('acadre MM', '[XML_ID: !id] Finished meeting import', array('!id' => $PROCESSING_MEETING_ID), WATCHDOG_NOTICE);
    return;
  }

   // Ideally $meetings will only have one entry.
  // But can have more if manifest is wrong.
  foreach ($meetings as $meeting) {
    $PROCESSING_MEETING_ACCESS = $meeting['agenda_access'];
    watchdog('acadre MM', '[XML_ID: !id] Start import agenda !meeting_sub_id with !number bullets, force: !force',
        array('!id' => $PROCESSING_MEETING_ID, '!meeting_sub_id' => $meeting['meeting_sub_id'], '!number' => count($meeting['items']), '!force' => intval($force)), WATCHDOG_DEBUG);

    // Meeting already exist.
    // Either update, republish, delete or skip.
    if ($nid) {
      $node = node_load($nid);
      $republish = FALSE;

      // Republish by Force.
      if ($force) {
        $republish = TRUE;
        $reason = 'FORCE';
      } elseif (defined('MM_REPUBLISH_MEETINGS') && MM_REPUBLISH_MEETINGS) {
        // Republish by setting.
        $republish = TRUE;
        $reason = 'MM_REPUBLISH_MEETINGS';
      } elseif (defined('MM_REPUBLISH_SUBVERSION') && MM_REPUBLISH_SUBVERSION) {
        // Republish if meeting_sub_id changed.
        if ($node->field_os2web_meetings_sub_id[LANGUAGE_NONE][0]['value'] < $meeting['meeting_sub_id']) {
          $republish = TRUE;
          $reason = 'MM_REPUBLISH_SUBVERSION';
        }
      } elseif ($meeting['type'] === 'Referat' &&
        ($node->field_os2web_meetings_type[LANGUAGE_NONE][0]['value'] === 'Dagsorden' ||
         $node->field_os2web_meetings_type[LANGUAGE_NONE][0]['value'] === 'Dagsorden_plus')) {
        // Republish if current meeting is of type Referat.
        // This means that the one already exist is a Dagsorden.
        $republish = TRUE;
        $reason = 'DAGSORDEN -> REFERAT';
      } elseif (filemtime($meeting['path']) > $node->changed) {
          $republish = TRUE;
          $reason = 'NEW REFERAT VERSION';
      }

      // Republish.
      if ($republish) {
        watchdog('acadre MM', '[XML_ID: !id] Republishing into !nid. Reason: !reason', array('!id' => $PROCESSING_MEETING_ID, '!nid' => $nid, '!reason' => $reason), WATCHDOG_INFO);
      }
      else {
        watchdog('acadre MM', '[XML_ID: !id] Meeting already imported in !nid. No republish. Skipping.', array('!id' => $PROCESSING_MEETING_ID, '!nid' => $nid), WATCHDOG_NOTICE);
        watchdog('acadre MM', '[XML_ID: !id] Finished meeting import', array('!id' => $PROCESSING_MEETING_ID), WATCHDOG_NOTICE);
        os2web_esdh_provider_index_meeting_update_committee_tid($meeting_id['id'], $meeting['meeting_sub_id'], $node->field_os2web_meetings_committee['und'][0]['tid']);
        continue;
      }
    }
    else {
      // Check if there is an sofd version of this node
      // (acadre and syddjurs systems only).
      if (module_exists('os2dagsorden_esdh_provider')) {
        $committee_term = osdagsorden_esdh_provider_import_or_return_committee($meeting['committee_id'], $meeting['committee']);
        $node = os2dagsorden_esdh_provider_find_sofd_meeting($committee_term, $meeting['meeting_date_start'], $meeting['meeting_date_finish']);
      }
    }

    if (!$node){
      watchdog('acadre MM', '[XML_ID: !id] No node was found, creating a new node', array('!id' => $PROCESSING_MEETING_ID), WATCHDOG_DEBUG);
      $node = new stdClass();
    }
    //$unpublished_status = variable_get('os2dagsorden_meetings_unpublished_status');
    $node->type = "os2web_meetings_meeting";
    $node->language = LANGUAGE_NONE;
    $node->uid = 1;
    //if unpublished
    //if ($unpublished_status == 1)

    node_object_prepare($node);
    if (strlen($meeting['title']) >= 255) {
      $node->title = mb_substr($meeting['title'], 0, 250) . '...';
    }
    else {
      $node->title = $meeting['title'];
    }

    /* The original field for title came from $meeting['title'];
     * This is a rewrite of the function to set the path automaticaly and with
     * custom data - such as date.
     * skifter@bellcom.dk - 2013-04-14 / 2013-04-24 */

    // Is the pathauto module loaded.
    // Don't create aliases (vitaliy.sekan@propeople.com.ua).
    if (module_exists('pathauto') && !(defined('MN_DISABLE_PATHAUTO') && MN_DISABLE_PATHAUTO)) {

      // Loading the path auto modules.
      module_load_include('inc', 'pathauto', 'pathauto');

      // Setting the new title with committee name and meeting date substring.
      $my_date = date_create(substr($meeting['meeting_date_start'], 0, 10));
      $format = "d-m-Y";
      $committee_name = is_array($meeting['committee']) ? $meeting['committee']['esdh_name'] : $meeting['committee'];
      $node->title = $committee_name . ' - ' . date_format($my_date, $format);

      $alias = 'dagsorden/' . pathauto_cleanstring($node->title);
      $source = (isset($node->nid)) ? 'node/' . $node->nid : '';
      pathauto_alias_uniquify($alias, $source, $node->language);

      // Adding the alias and setting pathauto to 0 for this content type.
      // Otherwise we get 2 aliases.
      $path_alias = array(
        'alias' => $alias,
        'pid' => NULL,
        'source' => NULL,
        'language' => LANGUAGE_NONE,
        'pathauto' => 0,
      );
      $node->path = $path_alias;
      watchdog('acadre MM', '[XML_ID: !id] Meeting path: !path', array('!id' => $PROCESSING_MEETING_ID, '!path' => $path_alias), WATCHDOG_DEBUG);
    }


    // If field has a format, you need to define it. Here we define a default
    // filtered_html format for a body field.
   // $node->field_os2web_meetings_abbr[LANGUAGE_NONE][0]['format'] = 'filtered_html';
    // The date.
    $node->field_os2web_meetings_date[LANGUAGE_NONE][0]['value'] = $meeting['meeting_date_start'];
    $node->field_os2web_meetings_date[LANGUAGE_NONE][0]['value2'] = $meeting['meeting_date_finish'];
    $node->field_os2web_meetings_date[LANGUAGE_NONE][0]['timezone'] = 'Europe/Berlin';
    $node->field_os2web_meetings_date[LANGUAGE_NONE][0]['date_type'] = 'datetime';
    // Proper id tagging.
    $node->field_os2web_meetings_id[LANGUAGE_NONE][0]['value'] = $meeting['meeting_id'];
    $node->field_os2web_meetings_sub_id[LANGUAGE_NONE][0]['value'] = $meeting['meeting_sub_id'];
    $node->field_os2web_meetings_system_id[LANGUAGE_NONE][0]['value'] = $meeting['system_id'];
    // Type import.
    $node->field_os2web_meetings_type[LANGUAGE_NONE][0]['value'] = $meeting['type'];
    // Adding participants.
    if (isset($meeting['participants'])) {
      $node->field_os2web_meetings_partic[LANGUAGE_NONE][0]['value'] = implode(variable_get('os2dagsorden_participants_delimeter', ', '), $meeting['participants']);
      $node->field_os2web_meetings_partic[LANGUAGE_NONE][0]['format'] = 'filtered_html';
    }
    // Adding cancelled participants.
    if (isset($meeting['participants_cancellation'])) {
      $node->field_os2web_meetings_particcanl[LANGUAGE_NONE][0]['value'] = implode(variable_get('os2dagsorden_participants_delimeter', ', '), $meeting['participants_cancellation']);
      $node->field_os2web_meetings_particcanl[LANGUAGE_NONE][0]['format'] = 'filtered_html';
    }
    // Adding comments.
    if (isset($meeting['description'])) {
      $node->field_os2web_meetings_comments[LANGUAGE_NONE][0]['value'] = $meeting['description'];
    }

    // Make sure the committee term is created and get the term.
    if (!$committee_term) {
      if (module_exists('os2dagsorden_esdh_provider')) {
        $committee_term = osdagsorden_esdh_provider_import_or_return_committee($meeting['committee_id'], $meeting['committee']);
      } else {
        $committee_term = _acadre_esdh_import_term($meeting['committee'], 'os2web_meetings_tax_committee');
      }
    }
    $node->field_os2web_meetings_committee[LANGUAGE_NONE][0]['tid'] = $committee_term->tid;
    os2web_esdh_provider_index_meeting_update_committee_tid($meeting_id['id'], $meeting['meeting_sub_id'], $committee_term->tid);
    watchdog('acadre MM', '[XML_ID: !id] Meetings committee: !term_name (TID: !tid)',
      array('!id' => $PROCESSING_MEETING_ID, '!term_name' => $committee_term->name, '!tid' => $committee_term->tid), WATCHDOG_DEBUG);

    // location term
    if ($meeting['location']) {
      $location_term = _acadre_esdh_import_term($meeting['location'], 'os2web_meetings_tax_location');
      $node->field_os2web_meetings_location[LANGUAGE_NONE][0]['tid'] = $location_term->tid;
      watchdog('acadre MM', '[XML_ID: !id] Meetings location: !term_name (TID: !tid)',
        array('!id' => $PROCESSING_MEETING_ID, '!term_name' => $location_term->name, '!tid' => $location_term->tid), WATCHDOG_DEBUG);
    }

     $node->status=_os2web_esdh_provider_get_meeting_publish_status($committee_term->tid);

    //adding description
    if (!empty($meeting['full_doc'])){
      if (FALSE !== ($file = _os2web_esdh_provider_import_file($meeting['full_doc']))) {
        if (isset($meeting['agenda_access']) && strcmp($meeting['agenda_access'], 'Lukket') == 0){
          $node->field_os2web_meetings_full_doc_c[$node->language][0] = (array) $file;
          watchdog('acadre MM', '[XML_ID: !id] Meetings closed description: !uri ', array('!id' => $PROCESSING_MEETING_ID, '!uri' => $file->uri), WATCHDOG_DEBUG);
        }
        else {
          $node->field_os2web_meetings_full_doc[$node->language][0] = (array) $file;
          watchdog('acadre MM', '[XML_ID: !id] Meetings open description: !uri ', array('!id' => $PROCESSING_MEETING_ID, '!uri' => $file->uri), WATCHDOG_DEBUG);
        }
      }
    }

    //adding full doc with attachments
    if (!empty($meeting['full_doc_with_attachments'])){
      if (FALSE !== ($file = _os2web_esdh_provider_import_file($meeting['full_doc_with_attachments']))) {
        if (isset($meeting['agenda_access']) && strcmp($meeting['agenda_access'], 'Lukket') == 0){
          $node->field_os2web_meetings_att_doc_c[$node->language][0] = (array) $file;
          watchdog('acadre MM', '[XML_ID: !id] Meetings closed full doc with attachments: !uri ', array('!id' => $PROCESSING_MEETING_ID, '!uri' => $file->uri), WATCHDOG_DEBUG);
        } else {
          $node->field_os2web_meetings_att_doc[$node->language][0] = (array) $file;
          watchdog('acadre MM', '[XML_ID: !id] Meetings open full doc with attachments: !uri ', array('!id' => $PROCESSING_MEETING_ID, '!uri' => $file->uri), WATCHDOG_DEBUG);
        }
      }
    }

    $bullet_points = array();
    if ($node->field_os2web_meetings_bullets['und']) {
      $bullet_points = $node->field_os2web_meetings_bullets['und'];
    }
    // Delete all bullet points before importing.
    if (property_exists($node, 'field_os2web_meetings_bullets') && is_array($node->field_os2web_meetings_bullets)) {
      $bullets = $node->field_os2web_meetings_bullets['und'];
      if (is_array($bullets)) {
        $nids_to_delete = array();
        foreach ($bullets as $bullet_nid) {
          $nids_to_delete[$bullet_nid['target_id']] = $bullet_nid['target_id'];
        }
      }
    }

    // Import items.
    if (is_array($meeting['items'])) {
      $item_nids = _os2web_esdh_provider_import_items($meeting['items'], $bullet_points);
      watchdog('acadre MM', '[XML_ID: !id] Imported bullet points !list ',
        array('!id' => $PROCESSING_MEETING_ID, '!list' => print_r($item_nids, TRUE)), WATCHDOG_DEBUG);

      if (module_exists('os2dagsorden_esdh_provider')) {
        if (is_array($nids_to_delete) && is_array($item_nids)) {
          // Deleting only those, that were not added again.
          $nids_to_delete = array_diff($nids_to_delete, $item_nids);
        }
      }

      if (!empty($nids_to_delete)) {
        watchdog('acadre MM', '[XML_ID: !id] Deleting those bullet points: !list ', array('!id' => $PROCESSING_MEETING_ID, '!list' => print_r($nids_to_delete, TRUE)), WATCHDOG_DEBUG);
        node_delete_multiple($nids_to_delete);
      }
      foreach ($item_nids as $nid) {
        // Adding only unique nodes.
        if (module_exists('os2dagsorden_esdh_provider')) {
          // Adding only unique nodes.
          if (!os2dagsorden_access_helper_check_bullet_point_is_part_of_meeting($node->nid, $nid)) {
            $node->field_os2web_meetings_bullets[LANGUAGE_NONE][]['target_id'] = $nid;
          }
        }
        else {
          $node->field_os2web_meetings_bullets[LANGUAGE_NONE][]['target_id'] = $nid;
        }
      }
    }

    // Save the meeting node.
    $node = node_submit($node);

    $node->created = $meeting['creation_date'];
    node_save($node);
    $nid = $node->nid;
    if ($node->status == 0){//if unpublished
        global $base_url;
        //variable_get('os2dagsorden_meeting_unpublished_state_emails', '');
        $committee_id = $node->field_os2web_meetings_committee['und'][0]['tid'];
        $status = $node->field_os2web_meetings_type['und'][0]['value'];
        $target_email = _os2web_esdh_provider_meeting_unpublished_state_emails($committee_id, $status);
        if (!empty($target_email)) {
          $cName = taxonomy_term_load($committee_id)->name;
          $mName = check_plain($node->title);
          $mDate =  format_date(strtotime($node->field_os2web_meetings_date['und'][0]['value']), 'short');
          $published_item = (strcasecmp($status, 'Dagsorden') == 0) ? 'en dagsorden' : 'et referat';
          $meeting_url = $base_url . '/meeting/' . $node->nid;
          $mLink = '<a href="' . $meeting_url . '">' . $meeting_url . '</a>';

          $subject_template = variable_get('os2dagsorden_meeting_unpublished_state_subject');
          $body_template = variable_get('os2dagsorden_meeting_unpublished_state_body');

          //composing search/replace
          $search = array('!committe', '!meeting_name', '!meeting_date', '!meeting_type', '!meeting_url', PHP_EOL);
          $replace = array($cName, $mName, $mDate, $published_item, $mLink, '<br/>');

          //making replacements
          $subject = str_replace($search, $replace, $subject_template);
          $subject = ucfirst($subject);
          $body = str_replace($search, $replace, $body_template);
          $body = ucfirst($body);

          $from = variable_get('system_mail');
          $params = array(
            'subject' => $subject,
            'body' => $body,
          );
          drupal_mail('os2web_esdh_provider', 'meeting_import_', $target_email, language_default(), $params, $from);
        }
    }
    watchdog('acadre MM', '[XML_ID: !id] Agenda %aid is imported into node %nid .', array(
      '!id' => $meeting_id['id'],
      '%aid' => $meeting['meeting_sub_id'],
      '%nid' => $node->nid), WATCHDOG_NOTICE);
    $nids[] = $node->nid;
    watchdog('acadre MM', '[XML_ID: !id] Finished meeting import', array('!id' => $PROCESSING_MEETING_ID), WATCHDOG_NOTICE);

    os2web_esdh_provider_index_meeting_update_nid($meeting_id['id'], $meeting['meeting_sub_id'], $nid);
    os2web_esdh_provider_index_meeting_update_status($meeting_id['id'], $meeting['meeting_sub_id'], IMPORT_STATUS_IMPORTED);
  }
  if ($republish){
  _os2web_esdh_provider_send_statusmail(t('!id successfully imported into node !nid.', array('!id' => $meeting_id['id'], '!nid' => $node->nid)));

  variable_set('os2web_esdh_provider_last_import', time());
  lock_release(__FUNCTION__ . $meeting_id['id']);
  return $nids;
}
else
  lock_release(__FUNCTION__ . $meeting_id['id']);
      return;
}

/**
 * Imports item metadata into nodes.
 * @access protected
 *
 * @param array $items
 *   List of items to import.
 *
 * @return array
 *   List of imported node ids
 */
function _os2web_esdh_provider_import_items($items, $existing_bullets = NULL) {
  global $PROCESSING_MEETING_ID, $PROCESSING_MEETING_NID, $PROCESSING_BP, $PROCESSING_MEETING_ACCESS;
  $nids = array();
  foreach ($items as $item) {
    $PROCESSING_BP = $item['sysid'];
    $node = NULL;
    watchdog('acadre MM', '[XML_ID: !id] [BP: !sysid] Initialized BP import: !title',
      array('!id' => $PROCESSING_MEETING_ID, '!title' => $item['title'], '!sysid' => $PROCESSING_BP), WATCHDOG_NOTICE);

    if (module_exists('os2dagsorden_esdh_provider')) {
      if (!empty($existing_bullets)) {
        $node = os2dagsorden_esdh_provider_find_corresponding_bullet($item['title'], $item['sysid'], $existing_bullets);
        if ($node) {
          watchdog('acadre MM', '[XML_ID: !id] [BP: !sysid] Found existing BP node nid: !nid',
            array('!id' => $PROCESSING_MEETING_ID, '!sysid' => $PROCESSING_BP, '!nid' => $node->nid), WATCHDOG_INFO);
        }
      }

      //try find bullet from the tillægsagenda
      if (!$node && $PROCESSING_MEETING_NID && TRUE) {
        $node = os2dagsorden_esdh_provider_find_and_reassign_additional_agenda_bullet($PROCESSING_BP, $PROCESSING_MEETING_NID);
        if ($node) {
          $node->title = mb_substr($item['title'], 0, 200);
        }
      }
    }

    if (!$node) {
      watchdog('acadre MM', '[XML_ID: !id] [BP: !sysid] Creating new BP node',
        array('!id' => $PROCESSING_MEETING_ID, '!sysid' => $PROCESSING_BP), WATCHDOG_DEBUG);
      $node = new stdClass();
      $node->type = "os2web_meetings_bullet";
      $node->language = LANGUAGE_NONE;
      $node->uid = 1;
      node_object_prepare($node);
      $node->field_os2web_meetings_bul_case[LANGUAGE_NONE][0]['value'] = $item['case_nr'];
      $node->field_os2web_meetings_bul_caseid[LANGUAGE_NONE][0]['value'] = $item['case_id'];
      $node->field_os2web_bullet_point_id[$node->language][0]['value'] = $item['sysid'];
    }
    $node->title = mb_substr($item['title'], 0, 200);

    if (module_exists('os2dagsorden_esdh_provider')) {
      $node = os2dagsorden_esdh_provider_bullet_add_number($node, $item['id']);
    }

    if (isset($item['comname'])) {
      $node->field_os2web_meetings_bul_com_n[$node->language][0]['value'] = $item['comname'];
    }

    if (isset($item['movie_id']) && is_numeric($item["chapter"])) {
      $node->field_os2web_meetings_qbrickref[LANGUAGE_NONE][0]['id'] = $item['movie_id'];
      $node->field_os2web_meetings_qbrickref[LANGUAGE_NONE][0]['seek'] = $item["chapter"];
    }

    watchdog('acadre MM', '[XML_ID: !id] [BP: !sysid] BP access: !access',
      array('!id' => $PROCESSING_MEETING_ID, '!sysid' => $PROCESSING_BP, '!access' => $item['access']), WATCHDOG_DEBUG);

    if ($item['access'] === 'Lukket' || $item['access'] === 'Person') {
      if ($item['access'] === 'Lukket')
        $node->field_os2web_meetings_bul_closed[LANGUAGE_NONE][0]['value'] = 1;
      if ($item['access'] === 'Person')
        $node->field_os2web_meetings_bul_pers[LANGUAGE_NONE][0]['value'] = 1;

      //allowing overriding of the content only if the agenda == lukket
      if (module_exists('os2dagsorden_esdh_provider') && $PROCESSING_MEETING_ACCESS == 'Lukket') {
        $node = _os2web_esdh_import_handle_bullets($node, $item);
      } else {
        watchdog('acadre MM', '[XML_ID: !id] [BP: !sysid] BP content will not be imported/overwritten, because BP access:
        !access and meeting access: !meeting_access', array('!id' => $PROCESSING_MEETING_ID, '!sysid' => $PROCESSING_BP,
          '!access' => $item['access'], '!meeting_access' => $PROCESSING_MEETING_ACCESS), WATCHDOG_INFO);
      }
    }
    else {
      $node->field_os2web_meetings_bul_closed[LANGUAGE_NONE][0]['value'] = 0;
      $node->field_os2web_meetings_bul_pers[LANGUAGE_NONE][0]['value'] = 0;
      $node = _os2web_esdh_import_handle_bullets($node, $item);
    }
    node_submit($node);
    node_save($node);
    $nids[] = $node->nid;

    watchdog('acadre MM', '[XML_ID: !id] [BP: !sysid] Finished BP import, nid: !nid',
      array('!id' => $PROCESSING_MEETING_ID, '!sysid' => $PROCESSING_BP,  '!nid' => $node->nid), WATCHDOG_NOTICE);
  }
  return $nids;
}

/**
 * Imports bullet metadata into nodes.
 * @access protected
 *
 * @param array $bullets
 *   List of bullets
 *
 * @return array
 *   List of imported node ids
 */
function _os2web_esdh_provider_import_bullets($bullets, $existing_attachments = NULL) {
  global $PROCESSING_MEETING_ID, $PROCESSING_BP;

  // Since we need to run this often,
  // we reset the execution timer to avoid timeouts.
  set_time_limit(180);
  $nids = array();

  foreach ($bullets as $idx => $bullet) {
    watchdog('acadre MM', '[XML_ID: !id] [BP: !sysid] [BPA: !bpa] Initialized BPA import: !title',
      array('!id' => $PROCESSING_MEETING_ID, '!sysid' => $PROCESSING_BP, '!bpa' => $bullet['sysid'], '!title' => $bullet['title']), WATCHDOG_INFO);
    $node = NULL;
    $bullet['body']=os2web_esdh_provider_filter_html_tags($bullet['body']);
    if (module_exists('os2dagsorden_esdh_provider')) {
      if (!empty($existing_attachments)) {
        $node = os2dagsorden_esdh_provider_find_corresponding_attachment($bullet, $existing_attachments);
        if ($node) {
          watchdog('acadre MM', '[XML_ID: !id] [BP: !sysid] [BPA: !bpa] Found existing BPA node: !nid',
            array('!id' => $PROCESSING_MEETING_ID, '!sysid' => $PROCESSING_BP, '!bpa' => $bullet['sysid'], '!nid' => $node->nid), WATCHDOG_INFO);
        }
      }
    }

    if (!$node) {
      watchdog('acadre MM', '[XML_ID: !id] [BP: !sysid] [BPA: !bpa] Creating new BPA node',
        array('!id' => $PROCESSING_MEETING_ID, '!sysid' => $PROCESSING_BP, '!bpa' => $bullet['sysid']), WATCHDOG_DEBUG);
      $node = new stdClass();
      $node->type = "os2web_meetings_bullet_attach";
      $node->language = LANGUAGE_NONE;
      $node->uid = 1;
      $node->title = mb_substr($bullet['title'], 0, 200);
      // Set some default values.
      node_object_prepare($node);
      // Let's add body field.
      $node->field_os2web_meetings_bpa_id[$node->language][0]['value'] = $bullet['sysid'];
      $node->field_os2web_meetings_bpa_body[$node->language][0]['value'] = $bullet['body'];
      // If field has a format, you need to define it.
      // Here we define a default filtered_html format for a body field.
      $node->field_os2web_meetings_bpa_body[$node->language][0]['format'] = _os2web_esdh_provider_bpa_body_format();

      if (isset($bullet['images'])) {
        foreach ($bullet['images'] as $image) {
          $node->field_os2web_meetings_bpa_body[$node->language][0]['value'] .= '<div><img src="' . file_create_url($image['path']) . '" style="width:90%;" /></div>';
        }
      }

    }
    $node = node_submit($node);
    node_save($node);
    $nids[$idx] = $node->nid;
    watchdog('acadre MM', '[XML_ID: !id] [BP: !sysid] [BPA: !bpa] Finished BPA import, nid: !nid',
      array('!id' => $PROCESSING_MEETING_ID, '!sysid' => $PROCESSING_BP, '!bpa' => $bullet['sysid'], '!nid' => $node->nid), WATCHDOG_INFO);
  }
  return $nids;
}

/**
 * Imports a file metadata into a managed drupal file.
 * @access protected
 *
 * @param array $file_meta
 *   File metadata
 *
 * @return object
 *   Drupal standard file object
 */
function _os2web_esdh_provider_import_file($file_meta) {
  global $PROCESSING_MEETING_ID, $PROCESSING_BP;

  // Since we need to run this often,
  // we reset the execution timer to avoid timeouts.
  set_time_limit(300);
  $uri_in = $file_meta['uri'];

  $pinfo = pathinfo($uri_in);
  if ($file_meta['title'] !== '') {
    $fname = $file_meta['title'];
  }
  else {
    $fname = $pinfo['filename'];
  }

  $uri_out = $pinfo['dirname'] . '/' . _os2web_esdh_provider_sanetize_filename($fname . '.' . strtolower($pinfo['extension']));
  if (_os2web_esdh_provider_similar_file_exists(drupal_realpath($uri_out))) {
    $file_counter = 0;
    do {
      $uri_out = $pinfo['dirname'] . '/' . _os2web_esdh_provider_sanetize_filename(mb_substr($fname, 0, 145) . '_' . $file_counter++ . '.' . strtolower($pinfo['extension']));
      watchdog('acadre MM', '[XML_ID: !id] [BP: !sysid] Checking !file_counter and !uri_out:',
        array('!id' => $PROCESSING_MEETING_ID, '!sysid' => $PROCESSING_BP, '!file_counter' => $file_counter, '!uri_out' => $uri_out), WATCHDOG_DEBUG);
    } while (_os2web_esdh_provider_similar_file_exists(drupal_realpath($uri_out)));
  }

  $new_pinfo = pathinfo($uri_out);
  $uri_pdf = $pinfo['dirname'] . '/' . $new_pinfo['filename'] . '.pdf';


  err_debug('Start import file ' . $uri_out . ' ');
watchdog('acadre MM', '[XML_ID: !id] [BP: !sysid] Started importing file !uri and !title into !uri_out',
      array('!id' => $PROCESSING_MEETING_ID, '!sysid' => $PROCESSING_BP, '!uri' => $file_meta['uri'], '!title' => $fname, '!uri_out' => $uri_out), WATCHDOG_DEBUG);

  $uri = FALSE;
  if ($uri_tmp = _os2web_esdh_provider_similar_file_exists(drupal_realpath($uri_pdf))) {
    // We have an already converted pdf file.
    $uri = $uri_pdf;
    $convert = FALSE;
  }
  elseif ($uri_tmp = _os2web_esdh_provider_similar_file_exists(drupal_realpath($uri_out))) {
    // File already copied.
    $convert = TRUE;
    $uri = $uri_out;
  }
  else {
    // Completely unprocessed file.
    $uri_old = $uri_in;
    $uri_in = _os2web_esdh_provider_similar_file_exists(drupal_realpath($uri_in));
    if (strlen($uri_out) > 255) {
      $pi = pathinfo($uri_out);
      if (isset($pi['extension'])) {
        $uri_out = $pi['dirname'] . '/' .  substr($pi['filename'], 0, strlen($pi['filename']) - (strlen($uri_out) - 255)) . '.' . $pi['extension'];
      }
      else {
        $uri_out = $pi['dirname'] . '/' .  substr($pi['filename'], 0, strlen($pi['filename']) - (strlen($uri_out) - 255));
      }
    }
    if ($uri_in === FALSE || FALSE === file_unmanaged_copy($uri_in, $uri_out, FILE_EXISTS_REPLACE)) {
      // Bummed out on copy.
      watchdog('acadre MM', 'File copy failed for %infile -> %outfile. Check folder permissions.', array(
        '%infile' => $uri_old, '%outfile' => $uri_out), WATCHDOG_WARNING);
      return FALSE;
    }
    else {
      $convert = TRUE;
      $uri = $uri_out;
    }
  }

  if (FALSE === $uri || empty($uri)) {
    watchdog('acadre MM', 'Processing of %infile failed. If exists, check permissions.', array(
      '%infile', $uri_in), WATCHDOG_WARNING);
    return FALSE;
  }

  if (!(defined('MM_USE_ALTERNATIVE_FILE_URI_SCHEME') && MM_USE_ALTERNATIVE_FILE_URI_SCHEME) && file_uri_scheme($uri) != 'public' && file_uri_scheme($uri) != 'private') {
    watchdog('acadre MM', 'Invalid scheme for uri %uri, Possibly absolut path ? ' . $uri, array(
      '%uri', $uri), WATCHDOG_ERROR);
    error_log("Var: \$uri = " . print_r($uri, 1));
    error_log("Var: \$uri_in = " . print_r($uri_in, 1));
    error_log("Var: \$uri_out = " . print_r($uri_out, 1));
    error_log("Var: \$uri_pdf = " . print_r($uri_pdf, 1));
  }

  // Is an absolute path.
  if (variable_get('os2web_edoc_esdh_mm_is_abs', FALSE) && module_exists('os2web_edoc_esdh')) {
    $doc_root = realpath($_SERVER['DOCUMENT_ROOT']) . '/';
    $uri = 'public://' . str_replace(variable_get(OS2WEB_EDOC_ESDH_MM_ABS_PATH_SUBS), '', $uri);
  }
  $fid = db_select('file_managed', 'fm')
          ->fields('fm', array('fid'))
          ->condition('uri', $uri)
          ->execute()->fetchField();

  $file = new stdClass();
  if ($fid) {
    $file->fid = $fid;
  }
  $file->uri = $uri;
  $file->display = 1;
  $file->field_titel[LANGUAGE_NONE][]['value'] = mb_substr($file_meta['title'], 0, 254);
  $file->filename = drupal_basename($file->uri);
  $file->filemime = file_get_mimetype($file->uri);
  $file->uid = 1;
  $file->status = FILE_STATUS_PERMANENT;
  $file = file_save($file);

  if (module_exists('os2web_pdf_conversion_manager')) {
    _os2web_pdf_conversion_manager_copy_file_to_convertion_dir($file->fid);
  }

  // Schedule for PDF conversion
  // $convert = FALSE; // DEBUG.
  if ($convert && module_exists('os2web_adlib_api')) {
    drupal_load('module', 'os2web_adlib_api');
    os2web_adlib_api_convert_to_pdf($file->fid);
    watchdog('os2web_adlib_api', 'File %filename (fid: %fid) queued for PDF conversion.', array(
      '%filename' => $file->filename, '%fid' => $file->fid), WATCHDOG_INFO);
  }

  err_debug('File imported.');
  err_debug('End Import of file');
  return $file;
}

/**
 * This function is a handler for item bullets. Groups all items and deletes the items which are to be replaced.
 *
 * @param mixed $node item node
 * @param array $item array containing information about bullets and enclosures
 *
 * @return object $node item node with filled information about bullet/enclosures
 */
function _os2web_esdh_import_handle_bullets($node, $item) {
  global $PROCESSING_MEETING_ID, $PROCESSING_BP, $PROCESSING_MEETING_ACCESS;
  // Gather the bullets for the item.
  if (isset($item['bullets']) && is_array($item['bullets'])) {
    $bullet_attachmets = array();
    if ($node->field_os2web_meetings_attach['und']) {
      $bullet_attachmets = $node->field_os2web_meetings_attach['und'];
    }
    $bullet_nids = _os2web_esdh_provider_import_bullets($item['bullets'], $bullet_attachmets);
    watchdog('acadre MM', '[XML_ID: !id] [BP: !sysid] Imported attachments !list',
      array('!id' => $PROCESSING_MEETING_ID, '!sysid' => $PROCESSING_BP, '!list' => print_r($bullet_nids, TRUE)), WATCHDOG_DEBUG);

    if (module_exists('os2dagsorden_esdh_provider')) {
      // Delete all attachments before importing.
      if (isset($node->field_os2web_meetings_attach['und'])) {
        $attachments_to_delete = array();
        foreach ($node->field_os2web_meetings_attach['und'] as $attachment_nid) {
          $attachments_to_delete[$attachment_nid['target_id']] = $attachment_nid['target_id'];
        }

        if (is_array($attachments_to_delete) && is_array($bullet_nids)) {
          // Deleting only those, that were nor added again.
          $attachments_to_delete = array_diff($attachments_to_delete, $bullet_nids);
        }

        if (!empty($attachments_to_delete)) {
          watchdog('acadre MM', '[XML_ID: !id] [BP: !sysid] Imported attachment to be deleted !list',
            array('!id' => $PROCESSING_MEETING_ID, '!sysid' => $PROCESSING_BP, '!list' => print_r($attachments_to_delete, TRUE)), WATCHDOG_DEBUG);

          //if any of the attachment had attached notes, we try to save the notes
          os2dagsorden_esdh_provider_reassign_notes($attachments_to_delete, $bullet_nids);

          node_delete_multiple($attachments_to_delete);
          unset($node->field_os2web_meetings_attach['und']);
        }
      }
    }
    foreach ($bullet_nids as $nid) {
      $node->field_os2web_meetings_attach[LANGUAGE_NONE][]['target_id'] = $nid;
    }
  }
  else {
    $node->field_os2web_meetings_attach[LANGUAGE_NONE] = array();
  }
  // Gather enclosures.
  foreach ($item['enclosures'] as $enclosure) {
    if ($enclosure['access'] || module_exists('os2dagsorden_esdh_provider')) {
      if ($file = _os2web_esdh_provider_import_file($enclosure)) {
        watchdog('acadre MM', '[XML_ID: !id] [BP: !sysid] Imported file !file',
          array('!id' => $PROCESSING_MEETING_ID, '!sysid' => $PROCESSING_BP, '!file' => $file->uri), WATCHDOG_DEBUG);
        //$node->field_os2web_meetings_enclosures[LANGUAGE_NONE][] = (array) $file;
        if (module_exists('os2dagsorden_esdh_provider')) {
          $node->field_os2web_meetings_attach[LANGUAGE_NONE][]['target_id'] = os2dagsorden_esdh_provider_process_enclosure($enclosure, $file);
        }
      }
      else {
        watchdog('acadre MM', '[XML_ID: !id] [BP: !sysid] There was an error importing file !uri ',
          array('!id' => $PROCESSING_MEETING_ID, '!sysid' => $PROCESSING_BP, '!uri' => $enclosure['uri']), WATCHDOG_ERROR);
      }
    }
  }

  return $node;
}

/**
 * Imports a termname into a vacabulary. Does dupe check.
 *
 * @param mixed $term_name
 *   Term name, or array containing term name and ESDH ID for
 *   the term.
 *
 * @param string $vocab
 *   Vocabulary machine name
 *
 * @return object
 *   Drupal standard Term object
 */
function _acadre_esdh_import_term($term_name, $vocab) {
  // Some MM plugins provide both term name and the ESDH ID for the
  // term. The latter makes it possible to handle multiple terms with
  // same name and automatically updating of term names based on data
  // from the ESDH system.
  if (is_array($term_name)) {
    $term_esdh_id = $term_name['esdh_id'];
    $term_esdh_id_field = $term_name['esdh_id_field'];
    $term_name = $term_name['esdh_name'];
  }


  err_debug('Start import term');

  $vid = db_select('taxonomy_vocabulary', 'tv')
    ->fields('tv', array('vid'))
    ->condition('machine_name', $vocab)
    ->execute()
    ->fetchField();

  $term = new stdClass();
  $term->vid = $vid;
  $term->name = $term_name;

  // Searching for an existing term based on the provided ESDH ID.
  if (!empty($term_esdh_id_field) && !empty($term_esdh_id) && $term_esdh_id > 0) {
    $term->{$term_esdh_id_field}['und'][0]['value'] = $term_esdh_id;

    $query = new EntityFieldQuery();
    $result = $query->entityCondition('entity_type', 'taxonomy_term')
      ->propertyCondition('vid', $vid)
      ->fieldCondition($term_esdh_id_field, 'value', $term_esdh_id, '=')
      ->execute();
    if (isset($result['taxonomy_term'])) {
      $tid = array_shift($result['taxonomy_term']);
    }
  }
  // If no ESDH ID is provided are we falling back and selecting on the
  // term name.
  else {
    $tid = db_select('taxonomy_term_data', 'td')
      ->fields('td', array('tid'))
      ->condition('name', $term->name)
      ->condition('vid', $term->vid)
      ->execute()->fetchObject();
  }

  if (isset($tid->tid) && $tid->tid > 0) {
    $term->tid = (int) $tid->tid;
  }

  taxonomy_term_save($term);

  return $term;
}

/**
 * Page callback. Displays a technical overview of an imported meeting.
 */
function _os2web_esdh_provider_node_tab_page($nid, $op = FALSE) {
  $html = "";
  $node = node_load($nid);
  $meeting_id = $node->field_os2web_meetings_id[LANGUAGE_NONE][0]['value'];
  $system_id = $node->field_os2web_meetings_system_id[LANGUAGE_NONE][0]['value'];
  $filename = 'Unknown';
  $files = file_scan_directory(variable_get('os2web_meetings_path', ACADRE_MM_IMPORT_DIR), '/\.xml$/i', array('recurse' => FALSE));
  foreach ($files as $file) {
    $xml = simplexml_load_file(drupal_realpath($file->uri));
    if (is_object($xml)) {
      $xml_mid = (string) array_shift($xml->xpath("//table[@name='meeting']/fields/field/@sysid"));
      if ($meeting_id == $xml_mid) {
        $filename = $file->filename;
        $agenda = $xml->xpath("//table[@name='producedAgenda']/fields/field[@sysid='$system_id']/../field");
        if (!empty($agenda)) {
          break;
        }
      }
    }
  }

  if ($op) {
    switch ($op) {
      case 'reimport':
        break;

      default:
        drupal_set_message($op . ' not yet implemented.', 'error');
        break;
    }
    drupal_goto('node/' . $nid . '/control');
  }

  $html .= "<h1>" . $node->title . "</h1>";

  $head = array('Node id', 'Meeting id', 'System id', 'Filename');
  $rows[] = array(
    $node->nid,
    $meeting_id,
    $system_id,
    $filename,
  );
  $html .= theme('table', array('header' => $head, 'rows' => $rows));
  $head = array('Attribute', 'Value');
  $rows = array();
  foreach ($agenda as $attr) {
    foreach ($attr->attributes() as $key => $val) {
      $rows[] = array($key, $val);
    }
  }
  $html .= theme('table', array('header' => $head, 'rows' => $rows));
  return $html;
}

/**
 * Sanetizes filename, removing illegal characters.
 *
 * @param string $filename
 *   Filename
 *
 * @return string
 *   Sanetized filename with same extension.
 */
function _os2web_esdh_provider_sanetize_filename($filename) {
  if (module_exists('transliteration')) {
    $filename = transliteration_clean_filename($filename);
  }
  else {
    // Replace whitespace.
    // $filename = str_replace(' ', '_', $filename);
    // Remove remaining unsafe characters.
    // $filename = preg_replace('![^0-9A-Za-z_.- ]!', '', $filename);
    $filename = preg_replace('![/"]!', '-', $filename);
    // Remove multiple consecutive non-alphabetical characters.
    $filename = preg_replace('/(_)_+|(\.)\.+|(-)-+/', '\\1\\2\\3', $filename);
    // Force lowercase to prevent issues on case-insensitive file systems.
    // $filename = strtolower($filename);
  }
  $pi = pathinfo($filename);
  if (isset($pi['extension'])) {
    return mb_substr(trim($pi['filename']), 0, 160) . '.' . $pi['extension'];
  }
  else {
    return mb_substr(trim($pi['filename']), 0, 160);
  }
}

/**
 * Case insensitive fileexists(). Code from comments on php.net.
 *
 * @param string $filename
 *   Filename
 *
 * @return mixed
 *   False if file not found, case corrected filename if found.
 */
function _os2web_esdh_provider_similar_file_exists($filename) {
  if (file_exists($filename)) {
    return $filename;
  }

  $dir = dirname($filename);
  $files = glob($dir . '/*');
  $lcase_filename = strtolower($filename);
  foreach ($files as $file) {
    if (strtolower($file) == $lcase_filename) {
      return $file;
    }
  }
  return FALSE;
}

/**
 * Page callback for the import service call.
 */
function _os2web_esdh_provider_import($id = FALSE) {
  if (!os2web_esdh_provider_has_api('mm')) {
    drupal_json_output(array('status' => 'error', 'message' => 'Not available.'));
  }
  $meetings = os2web_esdh_provider_invoke('mm', 'get_import_list');
  $meeting_id = FALSE;
  foreach ($meetings as $meeting) {
    if ($meeting['id'] == $id) {
      $meeting_id = $meeting;
      break;
    }
  }
  if ($meeting_id === FALSE) {
    _os2web_esdh_provider_import_output();
  }
  else {
    $nids = _os2web_esdh_provider_import_meeting($meeting_id, TRUE);
    if (os2web_esdh_provider_supports('mm', 'post_import_process')) {
      os2web_esdh_provider_invoke('mm', 'post_import_process');
    }
    if (count($nids) > 0) {
      _os2web_esdh_provider_import_output($id, $nids);
    }
    else {
      _os2web_esdh_provider_import_output($id);
    }
  }
}

/**
 * Helper function to dump output from REST importer.
 */
function _os2web_esdh_provider_import_output($id, $nids) {
  if (isset($id)) {
    $msg = 'Meeting not found.';
  }
  if (isset($nids) && empty($nids)) {
    $msg = 'Meeting ' . $id . ' imported, but no nodes created.';
  }
  else {
    $urls = array();
    foreach ($nids as $nid) {
      $urls[] = url('node/' . $nid, array('absolute' => TRUE));
    }
    $msg = 'Meeting ' . $id . ' imported to nodes: ' . implode(',', $urls);
  }
  drupal_add_http_header('Content-Type', 'application/json');
  echo $msg;
}

/**
 * Sends a mail to the importer's email.
 *
 * It only sends an email if the email is entered,
 * and it is not cron which which is calling it.
 *
 * @param string $message
 *   The message to send.
 *
 * @param bool $is_error
 *   Wheter the message is an error
 *
 * @return bool
 *   True on success
 */
function _os2web_esdh_provider_send_statusmail($message, $is_error = FALSE) {
  // Only send if an email is stored.
  if (!strpos(request_uri(), "cron") && $mail_to = variable_get('os2web_esdh_provider_debug_email')) {

    // Set up the mail body.
    $mail_body = t('MM Import') . "\n";
    if ($is_error) {
      $mail_body .= t('Status') . ": " . t('Error') . "\n";
    }
    else {
      $mail_body .= t('Status') . ": " . t('Success') . "\n";
    }
    $mail_body .= t('Time spend') . ": " . number_format(timer_read('mm_import') / 1000, 2) . "sec.\n";
    $mail_body .= t('Messages') . ":\n\n !message\n";

    $from = variable_get('site_mail', '');
    $my_module = 'os2web_esdh_provider';
    $my_mail_token = 'mm_import_status';
    $message = array(
      'id' => $my_module . '_' . $my_mail_token,
      'to' => $mail_to,
      'subject' => t('MM Import status'),
      'body' => format_string($mail_body, array('!message' => check_plain($message))),
      'headers' => array(
        'From' => $from,
        'Sender' => $from,
        'Return-Path' => $from,
      ),
    );
    // Send mail.
    $mail_system = drupal_mail_system($my_module, $my_mail_token);
    return $mail_system->mail($message);

  }
}

/**
 * Checks if a custom text format is defined for the BPA body field.
 *
 * I fall backs to filtered html.
 *
 * @return string
 *   Text format machine name.
 */
function _os2web_esdh_provider_bpa_body_format() {
  static $cache;
  if (empty($cache)) {
    if (defined('MM_BPA_BODY_FORMAT') && filter_format_exists(MM_BPA_BODY_FORMAT)) {
      $cache = MM_BPA_BODY_FORMAT;
    }
    else {
      $cache = 'filtered_html';
    }
  }
  return $cache;
}

/**
 * Clears the cache for all views (if the os2dagsorden_clear_cache_active is TRUE).
 */
function os2web_esdh_provider_clear_cache($success, $results, $operations) {
  if ($success) {
    // Clear views cache, if the Clear cache is active in
    // os2dagsorden setting form.
    if (variable_get('os2dagsorden_clear_cache_active')) {
      // Clear the views cache.
      cache_clear_all('*', 'cache_views', TRUE);
      watchdog('os2web_esdh_provider', 'Cleared views cache after meeting import process.');
      variable_set('os2web_adlib_last_convert', time());
    }
    $message = ' Import processed.';
    drupal_set_message($message);
  }
  else {
    // An error occurred.
    // $operations contains the operations that remained unprocessed.
    $error_operation = reset($operations);
    $message = t('An error occurred while processing %error_operation with arguments: @arguments',
      array(
        '%error_operation' => $error_operation[0],
        '@arguments' => print_r($error_operation[1], TRUE),
      )
    );
    drupal_set_message($message, 'error');
  }
  drupal_goto('admin/config/os2web/esdh_provider');
}

/*
 * Removed inline styles from html tags
 */
function os2web_esdh_provider_filter_html_tags($data) {
  $tags = explode(',', variable_get('os2dagsorden_filtered_tags', ''));
  foreach ($tags as $tag) {
    preg_match_all('#<' . $tag . '(.*?)>(.*?)</' . $tag . '>#is', $data, $matches);
    foreach ($matches[0] as $match) {
      $filtred_data = preg_replace('#style="(.*?)"#is', "", $match);
      $data = str_replace($match, $filtred_data, $data);
    }
  }
  //remove all a tags with attribute Name="Acadre..
  while (preg_match('/(<a name=Acadre(.*?)>((.*?\\s*?))+<\\/a>\\s*)+/', $data, $aTags) > 0) {
    $str = _os2web_esdh_provider_strip_tags($aTags[0], 'a');
    $data = str_replace($aTags[0], $str, $data);
  }

  $stripped_tags = explode(',', variable_get('os2dagsorden_stripped_tags', ''));
  $data = _os2web_esdh_provider_strip_tags($data, $stripped_tags);

  //remove all img tags that link missing files
  $data = _os2web_esdh_provider_remove_img_tags($data);
  //replace all <p></p> and <p>&nbsp;</p> tags with <br />
  $data = preg_replace('#(<p>((<span>)*?)(|&nbsp;)((<\/span>)*?)<\/p>\s*)+#i', '<br />', $data);
  //replace multiple &nbsp; tags with...
  $data = preg_replace('/(\x{00A0}|&nbsp;){2,}/u', variable_get('os2dagsorden_tab_tag', '&nbsp;'), $data);
   return $data;
}

/**
 * Removes the src attribute from img tags.
 *
 * @param $data
 * @return mixed
 */
function _os2web_esdh_provider_remove_img_tags($data){
  preg_match_all('/<img[^>]+>/i',$data, $imgTags);
  for ($i = 0; $i < count($imgTags[0]); $i++) {
    // get the source string
     preg_match('/src="([^"]+)/i',$imgTags[0][$i], $imgage);
  
     $file_headers = @get_headers(array_pop($imgage));

     if($file_headers=== FALSE or $file_headers[0] == 'HTTP/1.0 404 Not Found')       {
         $data = str_replace($imgTags[0][$i], "",  $data);
     }
   }

  return $data;
}

/**
 * Strips the tags from text.
 *
 * @param $str
 * @param $tags
 * @param bool $stripContent, if true the content will be also stripped.
 * @return mixed
 */
function _os2web_esdh_provider_strip_tags($str, $tags, $stripContent = false) {
  $content = '';
  if (!is_array($tags)) {
    $tags = (strpos($str, '>') !== false ? explode('>', str_replace('<', '', $tags)) : array($tags));
    if (end($tags) == '')
      array_pop($tags);
  }
  foreach ($tags as $tag) {
    if (empty($tag)) continue;
    if ($stripContent) {      
      $content = '(.+</' . $tag . '[^>]*>|)';
    }
    $str = preg_replace('#</?' . $tag . '[^>]*>' . $content . '#is', '', $str);
  }
  return $str;
}

/**
 * Return meeting import status by committee
 *
 * @param $tid
 * @return int
 */
function _os2web_esdh_provider_get_meeting_publish_status($tid) {
  $term = taxonomy_term_load($tid);
  if (isset($term->field_os2web_meetings_com_unpub['und'][0]['value']) && $term->field_os2web_meetings_com_unpub['und'][0]['value'] == 1)
    return 0;
  else
    return 1;
}

/**
 * Returns the list of email of the users that are set committee admins.
 *
 * @param $tid
 * @param $meeting_type
 * @return string
 */
function _os2web_esdh_provider_meeting_unpublished_state_emails($tid, $meeting_type) {
  $emails = array();
  $term = taxonomy_term_load($tid);
  if (strcasecmp($meeting_type, 'Dagsorden') == 0)
    $committee_admin =  $term->field_os2web_meetings_com_dag_ad;
  else
    $committee_admin =  $term->field_os2web_meetings_com_ref_ad;
  if (isset($committee_admin['und'])) {
    foreach($committee_admin['und'] as $key => $uid){
      $user = user_load($uid['uid']);
      $emails[] = $user->mail;
    }
  }
  return implode(', ', $emails);
}
