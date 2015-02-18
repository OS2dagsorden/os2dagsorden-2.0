<?php

/**
 * @file
 * This file implements the importing functions 
 * of the MM functionality and depends on a
 * plugin to do the actual filereads
 */

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
  watchdog('acadre MM', '[XML_ID: !id] Initialized meeting import', array('!id' => $meeting_id['id']), WATCHDOG_NOTICE);

  $meetings = os2web_esdh_provider_invoke('mm', 'import_meeting', $meeting_id);

  $nids = array();
  $nid = NULL;

  // Do an initially check on if there are any approved meetings.
  if (count($meetings) === 0) {
    watchdog('acadre MM', '[XML_ID: !id]  There was no meetings to import. See if all manifests are OK? ', array('!id' => $meeting_id['id']), WATCHDOG_WARNING);
    _os2web_esdh_provider_send_statusmail(t('There was no meetings to import for meeting !id. See if all manifests are OK?', array('!id' => $meeting_id['id'])), TRUE);
    lock_release(__FUNCTION__ . $meeting_id['id']);
    return;
  }

  // Run through all meetings. Remove all unpublished.
  // Retrieve nid of already existing node.
  $number_of_meetings = count($meetings);
  watchdog('acadre MM', '[XML_ID: !id] Number of agendas: !number', array('!id' => $meeting_id['id'], '!number' => $number_of_meetings), WATCHDOG_DEBUG);
  for ($i = 0; $i < $number_of_meetings; $i++) {
    if (!$nid) {
      // Run check to see if meeting is already imported.
      // System ID is the same on all meetings.
      $query = new EntityFieldQuery();
      $result = $query->entityCondition('entity_type', 'node')
        ->propertyCondition('type', 'os2web_meetings_meeting')
        ->fieldCondition('field_os2web_meetings_system_id', 'value', $meetings[$i]['system_id'], '=')
        ->execute();
      if (isset($result['node'])) {
        $nid = array_shift($result['node'])->nid;
        watchdog('acadre MM', '[XML_ID: !id ] Found existing meeting node nid: !nid', array('!id' => $meeting_id['id'], '!nid' => $nid), WATCHDOG_DEBUG);
      }
    }

    if ($meetings[$i]['publish'] === FALSE) {
      watchdog('acadre MM', '[XML_ID: !id] Agenda !meeting_sub_id will NOT be published. [publish]=!publish, [access]=!access',
        array('!id' => $meeting_id['id'],
              '!meeting_sub_id' => $meetings[$i]['meeting_sub_id'],
              '!publish' => intval($meetings[$i]['publish']),
              '!access' => $meetings[$i]['agenda_access'],
        ),
        WATCHDOG_INFO);
      unset($meetings[$i]);
    } else {
      watchdog('acadre MM', '[XML_ID: !id] Agenda !meeting_sub_id is allowed be published. [publish]=!publish, [access]=!access',
        array('!id' => $meeting_id['id'],
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
    watchdog('acadre MM', '[XML_ID: !id] Starting unpublishing of nid: !nid', array('!id' => $meeting_id['id'], '!nid' => $nid), WATCHDOG_DEBUG);
    node_delete($nid);
    watchdog('acadre MM', '[XML_ID: !id] Unpublished !nid .', array('!id' => $meeting_id['id'], '!nid' => $nid), WATCHDOG_NOTICE);
    lock_release(__FUNCTION__ . $meeting_id['id']);
    watchdog('acadre MM', '[XML_ID: !id] Finished meeting import', array('!id' => $meeting_id['id']), WATCHDOG_NOTICE);
    return;
  }
   // Ideally $meetings will only have one entry.
  // But can have more if manifest is wrong.
  foreach ($meetings as $meeting) {
    watchdog('acadre MM', '[XML_ID: !id] Start import agenda !meeting_sub_id with !number bullets, force: !force',
        array('!id' => $meeting_id['id'], '!meeting_sub_id' => $meeting['meeting_sub_id'], '!number' => count($meeting['items']), '!force' => intval($force)), WATCHDOG_DEBUG);

    // Meeting already exist.
    // Either update, republish, delete or skip.
    if ($nid) {
      $node = node_load($nid);
      $republish = FALSE;

      // Republish by Force.
      if ($force) {
        $republish = TRUE;
        $reason = 'FORCE';
      }

      // Republish by setting.
      if (defined('MM_REPUBLISH_MEETINGS') && MM_REPUBLISH_MEETINGS) {
        $republish = TRUE;
        $reason = 'MM_REPUBLISH_MEETINGS';
      }

      // Republish if meeting_sub_id changed.
      if (defined('MM_REPUBLISH_SUBVERSION') && MM_REPUBLISH_SUBVERSION) {
        if ($node->field_os2web_meetings_sub_id[LANGUAGE_NONE][0]['value'] < $meeting['meeting_sub_id']) {
          $republish = TRUE;
          $reason = 'MM_REPUBLISH_SUBVERSION';
        }
      }
      
      // Republish if current meeting is of type Referat.
      // This means that the one already exist is a Dagsorden.
      if ($meeting['type'] === 'Referat' && $node->field_os2web_meetings_type[LANGUAGE_NONE][0]['value'] === 'Dagsorden') {
        $republish = TRUE;
        $reason = 'DAGSORDEN -> REFERAT';
      }
          
      if (filemtime($meeting['path']) > $node->changed){
           $republish = TRUE;
          $reason = 'NEW REFERAT VERSION';
      }
     
      // Republish.
      if ($republish) {
        watchdog('acadre MM', '[XML_ID: !id] Republishing into !nid. Reason: !reason', array('!id' => $meeting_id['id'], '!nid' => $nid, '!reason' => $reason), WATCHDOG_INFO);
      }
      else {
        err_debug('Skipping nid: ' . $nid);
        watchdog('acadre MM', '[XML_ID: !id] Meeting already imported in !nid. No republish. Skipping.', array('!id' => $meeting_id['id'], '!nid' => $nid), WATCHDOG_NOTICE);
        watchdog('acadre MM', '[XML_ID: !id] Finished meeting import', array('!id' => $meeting_id['id']), WATCHDOG_NOTICE);
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
      watchdog('acadre MM', '[XML_ID: !id] No node was found, creating a new node', array('!id' => $meeting_id['id']), WATCHDOG_DEBUG);
      $node = new stdClass();
    }

    // Or any other content type you want.
    $node->type = "os2web_meetings_meeting";
    // Or any language code if Locale module is enabled. More on this below.
    $node->language = LANGUAGE_NONE;
    // Or any id you wish.
    $node->uid = 1;
    // Set some default values.
    node_object_prepare($node);
    // Set field values:
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
      watchdog('acadre MM', '[XML_ID: !id] Meeting path: !path', array('!id' => $meeting_id['id'], '!path' => $path_alias), WATCHDOG_DEBUG);
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
    watchdog('acadre MM', '[XML_ID: !id] Meetings committee: !term_name (TID: !tid)',
      array('!id' => $meeting_id['id'], '!term_name' => $committee_term->name, '!tid' => $committee_term->tid), WATCHDOG_DEBUG);

    $location_term = _acadre_esdh_import_term($meeting['location'], 'os2web_meetings_tax_location');
    $node->field_os2web_meetings_location[LANGUAGE_NONE][0]['tid'] = $location_term->tid;
    watchdog('acadre MM', '[XML_ID: !id] Meetings location: !term_name (TID: !tid)',
      array('!id' => $meeting_id['id'], '!term_name' => $location_term->name, '!tid' => $location_term->tid), WATCHDOG_DEBUG);

    // Add QBrick info @FIXME This should be in a node_save hook in qbrick
    // module.
    if (function_exists('_os2web_qbrick_get_movie_id')) {
      $movie_id = _os2web_qbrick_get_movie_id($node);
      if ($movie_id != FALSE) {
        $meeting['movie_id'] = $movie_id;
        $chapters = _os2web_qbrick_get_chapters($movie_id);
        $node->field_os2web_meetings_qbrickref[LANGUAGE_NONE][0]['id'] = $movie_id;
        $node->field_os2web_meetings_qbrickref[LANGUAGE_NONE][0]['seek'] = 0;
        foreach ($meeting['items'] as &$item) {
          $item['chapter'] = isset($chapters[$item['id']]) ? $chapters[$item['id']] : 0;
          $item['movie_id'] = $movie_id;
        }
      }
      else {
        $node->field_os2web_meetings_qbrickref = array();
      }
    }
    //adding description
    if (!empty($meeting['full_doc'])){
	  if (FALSE !== ($file = _os2web_esdh_provider_import_file($meeting['full_doc']))) {
        if (isset($meeting['agenda_access']) && strcmp($meeting['agenda_access'], 'Lukket') == 0){
             $node->field_os2web_meetings_full_doc_c[LANGUAGE_NONE][0] = (array) $file;
             watchdog('acadre MM', '[XML_ID: !id] Meetings closed description: !uri ', array('!id' => $meeting_id['id'], '!uri' => $file->uri), WATCHDOG_DEBUG);
        }
        else {
             $node->field_os2web_meetings_full_doc[LANGUAGE_NONE][0] = (array) $file;
             watchdog('acadre MM', '[XML_ID: !id] Meetings open description: !uri ', array('!id' => $meeting_id['id'], '!uri' => $file->uri), WATCHDOG_DEBUG);
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
      err_debug("Imported items: " . print_r($item_nids, TRUE));
      if (module_exists('os2dagsorden_esdh_provider')) {
        if (is_array($nids_to_delete) && is_array($item_nids)) {
          // Deleting only those, that were nor added again.
          $nids_to_delete = array_diff($nids_to_delete, $item_nids);
        }
      }
    
      err_debug("Items to delete: " . print_r($nids_to_delete, TRUE));  
      if (!empty($nids_to_delete)) {       
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
    watchdog('acadre MM', '[XML_ID: !id] Agenda %aid is imported into node %nid .', array(
      '!id' => $meeting_id['id'],
      '%aid' => $meeting['meeting_sub_id'],
      '%nid' => $node->nid), WATCHDOG_INFO);
    $nids[] = $node->nid;
    watchdog('acadre MM', '[XML_ID: !id] Finished meeting import', array('!id' => $meeting_id['id']), WATCHDOG_NOTICE);
  }
  if ($republish){
  _os2web_esdh_provider_send_statusmail(t('!id successfully imported into node !nid.', array('!id' => $meeting_id['id'], '!nid' => $node->nid)));

  variable_set('os2web_esdh_provider_last_import', time());
  err_debug('END import meeting ' . $meeting['system_id'] . '');
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

  $nids = array();
  foreach ($items as $item) {
    $node = NULL;
    err_debug('Start import bullet point: ' . print_r($item['title'], TRUE));
    if (module_exists('os2dagsorden_esdh_provider')) {
      if (!empty($existing_bullets)) {
        $node = os2dagsorden_esdh_provider_find_corresponding_bullet($item['title'], $existing_bullets);
      }
    }

    err_debug('Start import bullet point ');
    if (!$node) {
      $node = new stdClass();
      $node->type = "os2web_meetings_bullet";
      $node->language = LANGUAGE_NONE;
      $node->uid = 1;
      $node->title = mb_substr($item['title'], 0, 255);
      node_object_prepare($node);
      $node->field_os2web_meetings_bul_case[LANGUAGE_NONE][0]['value'] = $item['case_nr'];
      $node->field_os2web_bullet_point_id[$node->language][0]['value'] = $item['sysid'];
    }

    if (module_exists('os2dagsorden_esdh_provider')) {
      $node = os2dagsorden_esdh_provider_bullet_add_number($node, $item['id']);
    }
  
    
    if ($item['access'] === 'Lukket' || $item['access'] === 'Person') {
     if ($item['access'] === 'Lukket')
      $node->field_os2web_meetings_bul_closed[LANGUAGE_NONE][0]['value'] = 1;
     if ($item['access'] === 'Person')
      $node->field_os2web_meetings_bul_pers[LANGUAGE_NONE][0]['value'] = 1;
      if (module_exists('os2dagsorden_esdh_provider')) {
        $node = os2dagsorden_esdh_provider_process_closed_bullet($node, $item);
      }
      
      node_submit($node);
      node_save($node);
      $nids[] = $node->nid;
    }
    else {
      $node->field_os2web_meetings_bul_closed[LANGUAGE_NONE][]['value'] = 0;
      if (isset($item['movie_id']) && is_numeric($item["chapter"])) {
        $node->field_os2web_meetings_qbrickref[LANGUAGE_NONE][0]['id'] = $item['movie_id'];
        $node->field_os2web_meetings_qbrickref[LANGUAGE_NONE][0]['seek'] = $item["chapter"];
      }
      // Gather the bullets for the item.
      if (isset($item['bullets']) && is_array($item['bullets'])) {
        $bullet_attachmets = array();
        if ($node->field_os2web_meetings_attach['und']) {
          $bullet_attachmets = $node->field_os2web_meetings_attach['und'];
        }
        $bullet_nids = _os2web_esdh_provider_import_bullets($item['bullets'], $bullet_attachmets);

        if (module_exists('os2dagsorden_esdh_provider')) {
          // Delete all attachments before importing.
          if (isset($node->field_os2web_meetings_attach['und'])) {
            $attachments_to_delete = array();
            foreach ($node->field_os2web_meetings_attach['und'] as $attachment_nid) {
              $attachments_to_delete[$attachment_nid['target_id']] = $attachment_nid['target_id'];
            }

            err_debug("TO DELETE: " . print_r($attachments_to_delete, TRUE));
            err_debug("TO KEEP: " . print_r($bullet_nids, TRUE));
            if (is_array($attachments_to_delete) && is_array($bullet_nids)) {
              // Deleting only those, that were nor added again.
              $attachments_to_delete = array_diff($attachments_to_delete, $bullet_nids);
            }

            err_debug("DELETING: " . print_r($attachments_to_delete, TRUE));
            if (!empty($attachments_to_delete)) {
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
        if ($enclosure['access']) {
          if ($file = _os2web_esdh_provider_import_file($enclosure)) {
            $node->field_os2web_meetings_enclosures[LANGUAGE_NONE][] = (array) $file;
            if (module_exists('os2dagsorden_esdh_provider')) {
              $node->field_os2web_meetings_attach[LANGUAGE_NONE][]['target_id'] = os2dagsorden_esdh_provider_process_enclosure($enclosure, $file);
            }
          }
          else {
            watchdog('acadre MM', 'There was an error importing file %uri ', array('%uri' => $enclosure['uri']), WATCHDOG_ERROR);
          }
        }
      }
      $node = node_submit($node);
      node_save($node);
      $nids[] = $node->nid;
      err_debug('Item saved');
    }
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

  // Since we need to run this often,
  // we reset the execution timer to avoid timeouts.
  set_time_limit(180);
  $nids = array();

  foreach ($bullets as $idx => $bullet) {
    err_debug('Start import bullet ' . $idx . ' ');
    $node = NULL;
    if (module_exists('os2dagsorden_esdh_provider')) {
      if (!empty($existing_attachments)) {
        $node = os2dagsorden_esdh_provider_find_corresponding_attachment($bullet, $existing_attachments);
      }
    }

    if (!$node) {
      $node = new stdClass();
      $node->type = "os2web_meetings_bullet_attach";
      $node->language = LANGUAGE_NONE;
      $node->uid = 1;
      $node->title = mb_substr($bullet['title'], 0, 254);
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
          $node->field_os2web_meetings_bpa_body[$node->language][0]['value'] .= '<div><img src="' . file_create_url($image['path']) . '" /></div>';
        }
      }

    }
    $node = node_submit($node);
    node_save($node);
    $nids[$idx] = $node->nid;
    err_debug('Bullet saved.');
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
      $uri_out = $pinfo['dirname'] . '/' . _os2web_esdh_provider_sanetize_filename($fname . '_' . $file_counter++ . '.' . strtolower($pinfo['extension']));
    } while (_os2web_esdh_provider_similar_file_exists(drupal_realpath($uri_out)));
  }

  $new_pinfo = pathinfo($uri_out);
  $uri_pdf = $pinfo['dirname'] . '/' . $new_pinfo['filename'] . '.pdf';


  err_debug('Start import file ' . $uri_out . ' ');

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
        $uri_out = $pi['dirname'] . '/' .  substr($pi['filename'], 0, len($pi['filename']) - (len($uri_out) - 255)) . '.' . $pi['extension'];
      }
      else {
        $uri_out = $pi['dirname'] . '/' .  substr($pi['filename'], 0, len($pi['filename']) - (len($uri_out) - 255));
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

  // TODO: Process members of the committee.
  // FIXME: MAke vocab name configurable.
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
    return substr(trim($pi['filename']), 0, 160) . '.' . $pi['extension'];
  }
  else {
    return substr(trim($pi['filename']), 0, 160);
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
 * Todo, add docblock.
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
