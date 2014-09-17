<?php

/**
 * @file
 * This file implements the importing functions of the MM functionality and
 * depends on a plugin to do the actual filereads
 */

/**
 * Get human size.
 *
 * @param double $size
 *   The size to convert
 *
 * @return string
 *   The formated size.
 */
function hr_size($size) {
  $unit = array('b', 'kb', 'mb', 'gb', 'tb', 'pb');
  return @round($size / pow(1024, ($i = floor(log($size, 1024)))), 2) . ' ' . $unit[$i];
}

/**
 * Error debug function.
 *
 * @param string $msg
 *   The message
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
  err_debug('Init.');

  $meetings = os2web_esdh_provider_invoke('mm', 'import_meeting', $meeting_id);
  err_debug('Done generate meetings array from XML ' . $meeting_id['id']);

  $nids = array();
  $nid = NULL;

  // Do an initially check on if there are any approved meetings.
  if (count($meetings) === 0) {
    watchdog('acadre MM', 'There was no meetings to import. See if all manifests are OK? ', WATCHDOG_WARNING);
    _os2web_esdh_provider_send_statusmail(t('There was no meetings to import for meeting !id. See if all manifests are OK?', array('!id' => $meeting_id['id'])), TRUE);
    lock_release(__FUNCTION__ . $meeting_id['id']);
    return;
  }

  // Run through all meetings. Remove all unpublished.
  // Retrieve nid of already existing node.
  $number_of_meetings = count($meetings);
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
      }
    }

    if ($meetings[$i]['publish'] === FALSE) {
      unset($meetings[$i]);
    }
  }

  // If any already exist and no one is left to be published,
  // the existing should be unpublished.
  if ($nid && count($meetings) === 0) {
    // Meeting needs to be unpublished.
    err_debug('Unpublish nid: ' . $nid);
    node_delete($nid);
    watchdog('acadre MM', 'Unpublished %nid .', array('%nid' => $nid), WATCHDOG_INFO);
    lock_release(__FUNCTION__ . $meeting_id['id']);
    return;
  }

  // Ideally $meetings will only have one entry.
  // But can have more if manifest is wrong.
  foreach ($meetings as $meeting) {
    err_debug('Start import meeting ' . $meeting['system_id']);
    err_debug('Importing meeting with ' . count($meeting['items']) . ' bullet points.');

    // Meeting already exist.
    // Either republish, delete or skip.
    if ($nid) {

      if ($force) {
        err_debug('Republish nid: ' . $nid);

        $node = node_load($nid);
        watchdog('acadre MM', 'Using %nid for import.', array('%nid' => $nid), WATCHDOG_DEBUG);
      }
      // Republish if current meeting is of type Referat.
      // This means that the one already exist is a Dagsorden.
      elseif ($meeting['type'] === 'Referat') {
        $node = node_load($nid);
        if ($node->field_os2web_meetings_type[LANGUAGE_NONE][0]['value'] !== 'Dagsorden') {
          err_debug('Skipping nid: ' . $nid);
          watchdog('acadre MM', 'Meeting already imported in %nid. Skipṕing.', array('%nid' => $nid), WATCHDOG_DEBUG);
          lock_release(__FUNCTION__ . $meeting_id['id']);
          return;
        }
        err_debug('Republish nid: ' . $nid);
        watchdog('acadre MM', 'Using %nid for import. Type mismatch.', array('%nid' => $nid), WATCHDOG_DEBUG);
      }
      else {
        // Meeting already exists. Skip it.
        err_debug('Skipping nid: ' . $nid);
        watchdog('acadre MM', 'Meeting already imported in %nid. Skipṕing.', array('%nid' => $nid), WATCHDOG_DEBUG);
        lock_release(__FUNCTION__ . $meeting_id['id']);
        return;
      }
    }
    else {
      //check if there is an sofd version of this node (acadre and syddjurs systems only)
      if (module_exists('os2dagsorden_esdh_provider')){
        $committee_term = _acadre_esdh_import_term($meeting['committee'], 'os2web_meetings_tax_committee');
        $node = os2dagsorden_esdh_provider_find_sofd_meeting($committee_term, $meeting['meeting_date_start'], $meeting['meeting_date_finish']);
      } else {
        // We create a new node object.
        $node = new stdClass();
      }
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
    $node->title = $meeting['title'];

    /* The original field for title came from $meeting['title'];
     * This is a rewrite of the function to set the path automaticaly and with
     * custom data - sutch as date.
     * skifter@bellcom.dk - 2013-04-14 / 2013-04-24 */

    // Is the pathauto module loaded.
    if (module_exists('pathauto')) {

      // Loading the path auto modules.
      module_load_include('inc', 'pathauto', 'pathauto');

      // Setting the new title with committee name and meeting date substring.
      $my_date = date_create(substr($meeting['meeting_date_start'], 0, 10));
      $format = "d-m-Y";
      $node->title = $meeting['committee'] . ' - ' . date_format($my_date, $format);

      $alias = 'dagsorden/' . pathauto_cleanstring($node->title);
      $source = (isset($node->nid)) ? 'node/' . $node->nid : '';
      pathauto_alias_uniquify($alias, $source, $node->language);

      // Adding the alias and setting pathauto to 0 for this content type.
      // otherwise we get 2 aliases.
      $path_alias = array(
        'alias' => $alias,
        'pid' => NULL,
        'source' => NULL,
        'language' => LANGUAGE_NONE,
        'pathauto' => 0,
      );
      $node->path = $path_alias;
    }

    $node->field_os2web_meetings_abbr[LANGUAGE_NONE][0]['value'] = substr($meeting['description'], 0, 49);
    // If field has a format, you need to define it. Here we define a default
    // filtered_html format for a body field.
    $node->field_os2web_meetings_abbr[LANGUAGE_NONE][0]['format'] = 'filtered_html';
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
    //Adding default meeting category
    $node->field_os2web_meetings_category[LANGUAGE_NONE][0]['value']=variable_get('os2dagsorden_default_meeting_cateroty','pol');
    //Adding participants
    if (isset($meeting['participants'])){
      $node->field_os2web_meetings_partic[LANGUAGE_NONE][0]['value'] = implode(variable_get('os2dagsorden_participants_delimeter', ', '), $meeting['participants']);
      $node->field_os2web_meetings_partic[LANGUAGE_NONE][0]['format'] ='filtered_html';
    }
 
    //Adding cancelled participants
    if (isset($meeting['participants_cancellation'])){
      $node->field_os2web_meetings_particcanl[LANGUAGE_NONE][0]['value'] = implode(variable_get('os2dagsorden_participants_delimeter', ', '), $meeting['participants_cancellation']);
      $node->field_os2web_meetings_particcanl[LANGUAGE_NONE][0]['format'] ='filtered_html';
    }
    
     //Adding comments
   if (isset($meeting['description'])){
      $node->field_os2web_meetings_comments[LANGUAGE_NONE][0]['value'] = $meeting['comments'];
    }

    // Make sure the committee term is created and get the term.
    if (!$committee_term)
      $committee_term = _acadre_esdh_import_term($meeting['committee'], 'os2web_meetings_tax_committee');
    $node->field_os2web_meetings_committee[LANGUAGE_NONE][0]['tid'] = $committee_term->tid;
    if (module_exists('os2dagsorden_esdh_provider')){
      os2dagsorden_esdh_provider_committee_add_subid($committee_term, $meeting['committee_id']);
    }

    $node->field_os2web_meetings_location[LANGUAGE_NONE][0]['tid'] = _acadre_esdh_import_term($meeting['location'], 'os2web_meetings_tax_location')->tid;
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
    // Add full document.
    if (!empty($meeting['full_doc'])) {
      if (FALSE !== ($file = _os2web_esdh_provider_import_file($meeting['full_doc']))) {
        $node->field_os2web_meetings_full_doc[LANGUAGE_NONE][0] = (array) $file;
      }
    }

    // Delete all bullet points before importing.
    $bullets = array_shift($node->field_os2web_meetings_bullets);
    if (is_array($bullets)) {
      $nids_to_delete = array();
      foreach ($bullets as $nids) {
        $nids_to_delete[$nids['target_id']] = $nids['target_id'];
      }
    }

    // Import items.
    if (is_array($meeting['items'])) {
      $item_nids = _os2web_esdh_provider_import_items($meeting['items']);
      if (!empty($nids_to_delete)) {
        node_delete_multiple($nids_to_delete);
      }
      foreach ($item_nids as $nid) {
        $node->field_os2web_meetings_bullets[LANGUAGE_NONE][]['target_id'] = $nid;
      }
    }

    // Save the meeting node.
    $node = node_submit($node);
    $node->created = $meeting['creation_date'];
    node_save($node);
    watchdog('acadre MM', 'Imported agenda id: %aid (Meeting: %mid) into node %nid .', array(
      '%aid' => $meeting['system_id'],
      '%mid' => $meeting['meeting_id'],
      '%nid' => $node->nid), WATCHDOG_DEBUG);
    $nids[] = $node->nid;
    err_debug('Meeting saved. $node->nid = ' . print_r($node->nid, 1));
  }

  _os2web_esdh_provider_send_statusmail(t('!id successfully imported into node !nid.', array('!id' => $meeting_id['id'], '!nid' => $node->nid)));

  variable_set('os2web_esdh_provider_last_import', time());
  err_debug('END import meeting ' . $meeting['system_id'] . '');
  lock_release(__FUNCTION__ . $meeting_id['id']);
  return $nids;
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
function _os2web_esdh_provider_import_items($items) {

  $nids = array();
  foreach ($items as $item) {

    err_debug('Start import bullet point ');
    $node = new stdClass();
    $node->type = "os2web_meetings_bullet";
    $node->language = LANGUAGE_NONE;
    $node->uid = 1;
    $node->title = $item['title'];
    // Set some default values.
    node_object_prepare($node);
    
    if (module_exists('os2dagsorden_esdh_provider')){
      $node = os2dagsorden_esdh_provider_bullet_add_number($node, $item['id']);
    }

    if ($item['access'] === 'Lukket') {
      $node->field_os2web_meetings_bul_closed[LANGUAGE_NONE][]['value'] = 1;
      if (module_exists('os2dagsorden_esdh_provider')){
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
        $bullet_nids = _os2web_esdh_provider_import_bullets($item['bullets']);
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
            if (module_exists('os2dagsorden_esdh_provider'))
              $node->field_os2web_meetings_attach[LANGUAGE_NONE][]['target_id'] = os2dagsorden_esdh_provider_process_enclosure($enclosure, $file);
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
function _os2web_esdh_provider_import_bullets($bullets) {

  // Since we need to run this often,
  // we reset the execution timer to avoid timeouts.
  set_time_limit(180);
  $nids = array();

  foreach ($bullets as $idx => $bullet) {
    err_debug('Start import bullet ' . $idx . ' ');
    $node = new stdClass();
    $node->type = "os2web_meetings_bullet_attach";
    $node->language = LANGUAGE_NONE;
    $node->uid = 1;
    $node->title = $bullet['title'];
    // Set some default values.
    node_object_prepare($node);
    // Let's add body field.
    $node->field_os2web_meetings_bpa_body[$node->language][0]['value'] = $bullet['body'];
    // If field has a format, you need to define it.
    // Here we define a default filtered_html format for a body field.
    $node->field_os2web_meetings_bpa_body[$node->language][0]['format'] = _os2web_esdh_provider_bpa_body_format();
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
  $uri_pdf = $pinfo['dirname'] . '/' . _os2web_esdh_provider_sanetize_filename($fname . '.pdf');

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

  if (file_uri_scheme($uri) != 'public') {
    watchdog('acadre MM', 'Invalid scheme for uri %uri, Possibly absolut path ? ' . $uri, array(
      '%uri', $uri), WATCHDOG_ERROR);
    error_log("Var: \$uri = " . print_r($uri, 1));
    error_log("Var: \$uri_in = " . print_r($uri_in, 1));
    error_log("Var: \$uri_out = " . print_r($uri_out, 1));
    error_log("Var: \$uri_pdf = " . print_r($uri_pdf, 1));
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
  $file->field_titel[LANGUAGE_NONE][]['value'] = $file_meta['title'];
  $file->filename = drupal_basename($file->uri);
  $file->filemime = file_get_mimetype($file->uri);
  $file->uid = 1;
  $file->status = FILE_STATUS_PERMANENT;
  $file = file_save($file);
  
  if (module_exists('os2web_pdf_conversion_manager'))
    _os2web_pdf_conversion_manager_copy_file_to_convertion_dir($file->fid);

  // Schedule for PDF conversion
  // $convert = FALSE; // DEBUG.
  if ($convert) {
    drupal_load('module', 'os2web_adlib_api');
    os2web_adlib_api_convert_to_pdf($file->fid, $file->filename);
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
 * @param string $term_name
 *   Term machine name
 * @param string $vocab
 *   Vocabulary machine name
 *
 * @return object
 *   Drupal standard Term object
 */
function _acadre_esdh_import_term($term_name, $vocab) {

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

  $tid = db_select('taxonomy_term_data', 'td')
          ->fields('td', array('tid'))
          ->condition('name', $term->name)
          ->condition('vid', $term->vid)
          ->execute()->fetchObject();

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
  // Replace whitespace.
  // $filename = str_replace(' ', '_', $filename);
  // Remove remaining unsafe characters.
  // $filename = preg_replace('![^0-9A-Za-z_.- ]!', '', $filename);
  $filename = preg_replace('![/"]!', '-', $filename);
  // Remove multiple consecutive non-alphabetical characters.
  $filename = preg_replace('/(_)_+|(\.)\.+|(-)-+/', '\\1\\2\\3', $filename);
  // Force lowercase to prevent issues on case-insensitive file systems.
  // $filename = strtolower($filename);
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
