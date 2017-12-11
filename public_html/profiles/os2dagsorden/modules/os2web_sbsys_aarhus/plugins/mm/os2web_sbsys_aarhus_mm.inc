<?php

/**
 * @file
 * This file describes the MM plugin as implemented by SBsys.
 */

/**
 * Plugin definition with callbacks.
 */
$plugin = array(
  'description' => t('SBsys Aarhus MM Backend'),
  'version' => 1,
  'test' => 'os2web_sbsys_aarhus_mm_test',
  'get_import_list' => 'os2web_sbsys_aarhus_mm_get_import_list',
  'import_meeting' => 'os2web_sbsys_aarhus_mm_import_meeting',
  'post_import_process' => '_os2web_sbsys_aarhus_mm_order_addenums',
);

/**
 * For plugin testing purposes.
 */
function os2web_sbsys_aarhus_mm_test($stuff) {
  return 'Test successful. Recieved: ' . $stuff;
}

/**
 * Returns a list of meeting_ids for import. In our case a list of uri's of xml files.
 *
 * @return array
 *   List of URIs
 */
function os2web_sbsys_aarhus_mm_get_import_list() {

  /*
   * For the SBsys service, we need to import meetings from xml files.
   * We will enumerate the list with the publication-id
   * as parsed from the dir name of the manifest.
   */
  $uris = array();
  foreach (file_scan_directory(variable_get('os2web_sbsys_aarhus_mm_path', MM_IMPORT_DIR), '/\.xml$/i', array('recurse' => TRUE)) as $xml_file) {
    $pub_id = (int) str_replace('Publication', '', $xml_file->name);
    $uris[] = array('id' => $pub_id, 'uri' => $xml_file->uri);
  }
  return $uris;
}

/**
 * Strip illegal characters from the XML.
 * Ex &#xC = ASCII new line feed.
 *
 * @param $string
 *   string to sanitise
 *
 *   $return array
 *   The string sanitised
 */
function utf8_for_xml($string) {
  // Using regex.
  if (variable_get('os2web_sbsys_aarhus_banned_activate_regex', FALSE)) {
    $replace_me = variable_get('os2web_sbsys_aarhus_banned_special_regex', '');
    $str_new = preg_replace($replace_me, "", $string);
    // Using CSV list.
  }
  else {
    $replace_me = variable_get('os2web_sbsys_aarhus_banned_special_char', '');
    $str_new = str_replace(explode(',', $replace_me), "", $string);
  }

  return $str_new;
}

/**
 * Imports a meeting, and return the import as a structured array.
 *
 * @param object $meeting
 *   Meeting XML object.
 *
 * @return array
 *   List of meeting_structures to save
 */
function os2web_sbsys_aarhus_mm_import_meeting($meeting) {

  $file = $meeting['uri'];

  if ($file === FALSE) {
    _os2web_sbsys_aarhus_mm_order_addenums();
  }
  $meetings = array();
  $real_path = drupal_realpath($file);

  if ($real_path !== FALSE && is_file($real_path)) {

    libxml_use_internal_errors(TRUE);
    $manifest = simplexml_load_string(utf8_for_xml(file_get_contents($real_path)), 'SimpleXMLElement', LIBXML_NOCDATA);
    libxml_clear_errors();
    libxml_use_internal_errors(FALSE);

    if ($manifest === FALSE) {
      error_log("Failed loading XML");
      foreach (libxml_get_errors() as $error) {
        error_log($error->message);
      }
    }
    if (is_object($manifest)) {

      $committee = $manifest->xpath("Agendas/Agenda/Committee/@ID");

      // Id is not numeric - need to convert.
      $id = (string) $committee[0]['ID'];
      $id = _os2web_sbsys_aarhus_generate_crc_id($id);

      $committee_name = $manifest->xpath("Agendas/Agenda/Name");
      $committee = $id;
      $committee_group_id = $id;
      $meeting_uri = pathinfo($file)['dirname'] . '/';
      $meeting_data = $manifest->xpath("/Publication/Agendas/Agenda/Meeting");
      $sys_id = $id;
      $xml_id = $id;
      $acadre_version = $id;
      $members = $manifest->xpath("Agendas/Agenda/Meeting/Members/MeetingMember");

      // Type is not set in XML - always use Dagsorden.
      $meeting_type = 'Dagsorden';

      $committee_name = (string) $committee_name[0];
      $meeting_date_when = $meeting_data[0]->When;
      $meeting_date_until = $meeting_data[0]->Until;
      $meeting_where = (string) $meeting_data[0]->Where;
      $meeting_name = $committee_name;

      $directory_name = dirname($real_path);
      $dir_parts = explode('/', $directory_name);
      $pdf = array_pop($dir_parts) . ".pdf";

      // Fix dates.
      $date_obj = date_create($meeting_date_when);
      date_timezone_set($date_obj, timezone_open('UTC'));
      $meeting_date_when = date_format($date_obj, 'Y-m-d H:i');

      $date_obj1 = date_create($meeting_date_until);
      date_timezone_set($date_obj1, timezone_open('UTC'));
      $meeting_date_until = date_format($date_obj1, 'Y-m-d H:i');

      // Members.
      $participants = array();
      $participants_cancellation = array();
      foreach ($members as $member) {

        // Now use 'True' value as cancellation.
        if ($member->Participate == 0) {
          $participants[] = (string) $member->Name;
        }
        else {
          $participants_cancellation[] = (string) $member->Name;
        }
      }
      $meeting = array(
        'system_id' => $xml_id,
        'meeting_id' => $xml_id,
        'committee' => $meeting_name,
        'committee_name' => $committee_name,
        'committee_id' => $xml_id,
        'committee_group_id' => $committee_group_id,
        'title' => $meeting_name,
        'uri' => $meeting_uri,
        'path' => drupal_realpath($file),
        'pdf' => $pdf,
        'type' => $meeting_type,
        'meeting_date_start' => $meeting_date_when,
        'meeting_date_finish' => $meeting_date_until,
        'location' => $meeting_where,
        'acadre_version' => $acadre_version,
        'participants' => $participants,
        'participants_cancellation' => $participants_cancellation,
      );

      // var_dump($meeting);
      /* stan@bellcom.dk 06.10 - importing multiple agendas */
      $meeting_agendas = array();
      foreach ($manifest->xpath("/Publication/Agendas/Agenda") as $agenda_instance) {
        if (!$meeting_agendas) {
          $meeting_agendas = $agenda_instance->xpath("Items");
        }
        else {
          foreach ($agenda_instance->xpath("Items/Item") as $items_child) {
            $toDom = dom_import_simplexml($meeting_agendas[0]);
            $fromDom = dom_import_simplexml($items_child);
            $toDom->appendChild($toDom->ownerDocument->importNode($fromDom, TRUE));
          }
        }
      }

      $meeting_pdf = $manifest->xpath('/Meeting/MeetingAgendaTypes/MeetingAgendaType/PDFDocument');
      if (!empty($meeting_pdf)) {
        $meeting['pdf'] = (string) $meeting_pdf[0];
      }

      if (empty($meeting_agendas)) {
        watchdog('SBsys MM', 'Empty list of import items in %file.', array('%file' => $file), WATCHDOG_WARNING);
      }

      foreach ($meeting_agendas as $meeting_agenda) {

        $imported = _os2web_sbsys_aarhus_mm_import_meeting_agenda($meeting, $meeting_agenda);
        if (is_array($imported)) {
          $imported['publish'] = TRUE;
          $imported['meeting_sub_id'] = $sys_id;
          // stan@bellcom.dk - 17.03.2016
          // forcing the agenda to be considered as closed, otherwise the closed BP will not be imported.
          $imported['agenda_access'] = 'Lukket';
          $meetings[] = $imported;
        }
      }
    }
    else {
      watchdog('SBsys MM', 'Failed to parse XML in %file during import.', array('%file' => $file), WATCHDOG_WARNING);
    }
  }
  return $meetings;
}

/**
 * Imports a meeting from filesystem.
 *
 * @param array $meeting
 *   Meeting array.
 *
 * @param SimpleXMLElement $agenda_xml
 *   Meeting agenda XML object.
 *
 * @return mixed
 *   Meeting_struct array for an accepted import, else FALSE
 */
function _os2web_sbsys_aarhus_mm_import_meeting_agenda(&$meeting, $agenda_xml) {

  // Check if the committee is allowed to publish.
  $publish_committee = array_map('trim', explode(',', variable_get('os2web_sbsys_aarhus_approved_committees', MM_DEFAULT_APPROVED)));
  $publish_committee = array_map('_os2web_sbsys_aarhus_generate_crc_id', $publish_committee);

  if ($meeting['committee_id'] == '' || !in_array($meeting['committee_id'], $publish_committee)) {
    watchdog('SBsys MM', 'Ignored agenda from "%committee" .', array('%committee' => $meeting['committee_id']));
    return FALSE;
  }

  // Check meeting status.
  if ($meeting['type'] == 'Klade') {
    watchdog('SBsys MM', 'Ignored DRAFT: Meeting %id is of type %type.', array(
      '%id' => $meeting['system_id'],
      '%type' => $meeting['type'],
    ), WATCHDOG_WARNING);
    return FALSE;
  }

  $meeting['items'] = array();
  $agenda = $meeting;

  $real_path = drupal_realpath($meeting['uri']);
  if ($real_path !== FALSE && file_exists($real_path)) {
    // There were no SBSYS meeting with meeting description, therefore disabled.
    $fulldoc_real_path = drupal_realpath($meeting['uri'] . $meeting['pdf']);
    if ($fulldoc_real_path !== FALSE && file_exists($fulldoc_real_path)) {
      $agenda['full_doc'] = array(
        'uri' => $meeting['uri'] . $meeting['pdf'],
        'title' => $meeting['committee'],
      );
    }

    // Import all agenda items.
    $agenda_bullet = $agenda_xml;
    $meeting['current_item_nr'] = 1;
    foreach ($agenda_bullet as $agenda_item) {
      if (($item = _os2web_sbsys_aarhus_mm_import_meeting_agenda_item($meeting, $agenda_item)) !== FALSE) {
        $meeting['current_item_nr']++;
        $agenda['items'][] = $item;
      }
    }
    // Apply defaults, just in case we missed something.
    $agenda += os2web_esdh_provider_default_meeting();

    return $agenda;
  }

  watchdog('SBsys MM', 'File do not exist in folder. %file', array('%file' => drupal_realpath($meeting['uri'])), WATCHDOG_WARNING);
  return FALSE;
}

/**
 * Imports a single item for an agenda.
 *
 * @param array $meeting
 *   Meeting array.
 *
 * @param SimpleXMLElement $xml
 *   Xml segment containing the item.
 *
 * @return array
 *   The imported item.
 */
function _os2web_sbsys_aarhus_mm_import_meeting_agenda_item($meeting, $xml) {
  $xml_item = array();

  // Number is not numeric - need to convert.
  $xml_item['number'] = $xml->xpath("@ID");
  $xml_item['number'] = (string) $xml_item['number'][0]['ID'];
  $xml_item['number'] = _os2web_sbsys_aarhus_generate_item_number($xml_item['number']);

  $xml_item['pdf'] = (string) $xml->PDFDocument;
  $xml_item_document = $xml->Enclosures;
  $xml_item_bullet = $xml->Fields;
  $xml_item_history = $xml->ItemHistory;
  $xml_item['name'] = (string) $xml->Caption;
  $xml_item['document_type'] = (string) $xml->IsPublic;
  $xml_item_participants = $xml->Members;
  $xml_case_id = (string) $xml->ItemCaseNumber;

  $item = array(
    'id' => $xml_item['number'],
    'sysid' => (string) _os2web_sbsys_aarhus_generate_crc_id($xml['ID']),
      // 'title' => 'Punkt ' . $xml_item['number'] . ' ' . $xml_item['name'],06.10 stan@bellcom.dk commented to support multiple agendas.
    'title' => 'Punkt ' . $xml_item['number'] . ' ' . $xml_item['name'],
    'case_nr' => $xml_case_id,
    'access' => $xml_item['document_type'],
    'bullets' => array(),
    'enclosures' => array(),
    'doc' => array(
      'uri' => implode('/', array(
        trim($meeting['uri'], "/"),
        $xml_item['pdf'],
      )),
      'title' => $xml_item['name'],
    ),
  );

  /* stan@bellcom.dk - 08.10 - closed item now has only non participants bullet */

  if (0 <> strcasecmp($item['access'], 'true')) {
    // Rewriting the access field to match esdh provider module.
    $item['access'] = 'Lukket';
  }

  // Process attachments.
  foreach ($xml_item_bullet->ItemField as $bullet_xml) {

    if (((string) $bullet_xml->HasContent) === 'True') {
      $images = array();
      foreach ($bullet_xml->Images->Image as $image) {
        $images[] = array(
          'name' => (string) $image->InstantiationFileName,
          'path' => $meeting['uri'] . 'Images/' . ((string) $image->InstantiationFileName),
        );
      }
      $body = _os2web_sbsys_aarhus_mm_improve_html((string) $bullet_xml->Content, $meeting['uri'] . 'Images/');
      $item['bullets'][] = array(
        'title' => !empty($bullet_xml->Caption) ? (string) $bullet_xml->Caption : 'Indhold',
      // (string) $bullet_xml->Content,.
        'body' => $body,
        'sysid' => (string) $bullet_xml['ID'],
        'images' => $images,
      );
    }
  }

  // Process item history.
  if (!empty($xml_item_history)) {
    $history = array(
      'title' => t('Beslutningshistorik'),
      'body' => '',
    );
    foreach ($xml_item_history->ItemField as $item_history) {

      if (((string) $item_history->HasContent) === 'True') {
        $history['body'] .= t('@decision truffet af @comittee d. @date', array(
          '@decision' => (string) $item_history->Caption,
          '@comittee' => (string) $item_history->MeetingDetails->CommitteeName,
          '@date' => date('d-m-Y', strtotime((string) $item_history->MeetingDetails->MeetingDueDate)),
        ));
        $history['body'] .= '<br>' . strip_tags((string) $item_history->Content) . '<br>';
      }
    }
    if ($history['body'] !== '') {
      // If this is a Referat, put the history in before the beslutning element.
      // Else just put in the buttom of the list.
      if ($meeting['type'] === 'Referat') {
        foreach ($item['bullets'] as $key => $bullet) {
          if ($bullet['title'] === 'Beslutning') {
            array_splice($item['bullets'], $key, 0, array($history));
            break;
          }
        }
      }
      else {
        $item['bullets'][] = $history;
      }
    }
  }

  // Process enclsures.
  foreach ($xml_item_document as $enclosures) {
    foreach ($enclosures->Enclosure as $enclosure) {
      $enclosure_item['filename_in'] = (string) $enclosure->FileName;
      $enclosure_item['access'] = (string) $enclosure->PublishingType;
      // If (strlen($enclosure_item['filename_in']) > 0 && $enclosure_item['access'] === 'SKAL PUBLICERES') {.
      if (strlen($enclosure_item['filename_in']) > 0) {
        $item['enclosures'][] = array(
          'uri' => implode('/', array(
            trim($meeting['uri'], "/"),
            $enclosure_item['filename_in'],
          )),
          'title' => trim((string) $enclosure->Name),
          'access' => 0 <> strcasecmp((string) $enclosure->IsPublic, 'true') ? FALSE : TRUE,
          'sysid' => _os2web_sbsys_aarhus_generate_crc_id($enclosure_item['filename_in']),
          'type' => 'Bilag',
        );
      }
    }
  }

  // Process members that did not participate in the bullet discussion.
  $non_participants = '';
  foreach ($xml_item_participants->ItemMember as $participant) {
    if (((string) $participant->ParticipationStatusAsValue) === '4') {
      $non_participants .= (string) $participant->Name . "<br/>";
    }
  }

  if (!empty($non_participants)) {
    // Add members that did not participate in the bullet discussion as a last bullet point.
    $item['bullets'][] = array(
      'title' => 'Afbud / Fraværende',
      'body' => $non_participants,
    );
  }

  $item += os2web_esdh_provider_default_item();
  return $item;
}

/**
 * Case insensitive fileexists(). Code from comments on php.net.
 *
 * @param string $filename
 *   File name to check.
 *
 * @return mixed
 *   False if file not found, case corrected filename if found.
 */
function _os2web_sbsys_aarhus_similar_file_exists($filename) {

  if (file_exists($filename)) {
    return $filename;
  }
  $lcase_filename = strtolower($filename);
  foreach (glob(dirname($filename) . '/*') as $file) {
    if (strtolower($file) == $lcase_filename) {
      return $file;
    }
  }
  return FALSE;
}

/**
 * This function will set up the addenum connections for meetings.
 */
function _os2web_sbsys_aarhus_mm_order_addenums($drush = FALSE) {
  if (!lock_acquire(__FUNCTION__)) {
    return;
  }

  // Debug bit set in os2web_esdh_provider settings.
  $debug = variable_get('os2web_esdh_provider_debug_info');
  $debug && timer_start('_os2web_sbsys_aarhus_mm_order_addenums') && error_log('MM Import - Start of addendums - ' . timer_read('_os2web_sbsys_aarhus_mm_order_addenums') . 'ms - ' . memory_get_usage());
  $rev_meetings = array();

  // Find all meetings and gather meeting and agenda_ids.
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node', '=')
    ->propertyCondition('type', 'os2web_meetings_meeting', '=');
  $nodes_result = $query->execute();

  if (!isset($nodes_result['node'])) {
    return;
  }
  $nodes = $nodes_result['node'];
  // Load necessary fields into the node object.
  $fields = field_info_instances('node', 'meeting');
  field_attach_load('node', $nodes, FIELD_LOAD_CURRENT, array('field_id' => $fields['field_os2web_meetings_addendum']['field_id']));
  field_attach_load('node', $nodes, FIELD_LOAD_CURRENT, array('field_id' => $fields['field_os2web_meetings_id']['field_id']));
  field_attach_load('node', $nodes, FIELD_LOAD_CURRENT, array('field_id' => $fields['field_os2web_meetings_sub_id']['field_id']));

  // Meetings as: $meetings[<meeting_id>][<system_id>][<node_id>] .
  $meetings = array();

  $nids_with_addendums = array();

  $debug && error_log('MM Import - Retrieve nodes with addendums from ' . count($nodes) . ' nodes - ' . timer_read('_os2web_sbsys_aarhus_mm_order_addenums') . 'ms - ' . memory_get_usage());
  // Loop through all meeting nodes, and generate an array with meeting grouped.
  foreach ($nodes as $node) {
    $addenum_to = field_get_items('node', $node, 'field_os2web_meetings_addendum');
    if (isset($addenum_to[0]['nid']) && is_numeric($addenum_to[0]['nid'])) {
      $nids_with_addendums[$node->nid] = $node->nid;
    }
    $meeting_id = field_get_items('node', $node, 'field_os2web_meetings_id');
    $meeting_sub_id = field_get_items('node', $node, 'field_os2web_meetings_sub_id');
    if (!isset($meeting_id[0]['value']) || !isset($meeting_sub_id[0]['value'])) {
      $debug && error_log('MM Import - Missing meeting_id or meeting_sub_id for nid=' . $node->nid);
      continue;
    }
    if (isset($meetings[$meeting_id[0]['value']][$meeting_sub_id[0]['value']])) {
      // Duplicate meeting detected.
      watchdog('SBsys MM', 'Duplicate import found for meeting %mid. Deleting nid=%nid.', array(
        '%mid' => $meeting_id['value'],
        '%nid' => $node->nid,
      ), WATCHDOG_WARNING);
      node_delete($node->nid);
    }
    else {
      $meetings[$meeting_id[0]['value']][$meeting_sub_id[0]['value']] = $node->nid;
    }
  }

  $debug && error_log('MM Import - Update addendums on ' . count($meetings) . ' nodes - ' . timer_read('_os2web_sbsys_aarhus_mm_order_addenums') . 'ms - ' . memory_get_usage());
  // Run through the meeting array, to determine the addendums.
  foreach ($meetings as $m_id => $meeting) {
    // Lowest system id first.
    ksort($meeting);
    if (in_array($m_id, $rev_meetings)) {
      $meeting = array_reverse($meeting);
    }
    // Lowest system id is primary.
    $primary = $nodes[array_shift($meeting)];
    $addenum_to = field_get_items('node', $primary, 'field_os2web_meetings_addendum');
    if (!empty($addenum_to[0]['nid'])) {
      $primary->field_os2web_meetings_addendum[LANGUAGE_NONE] = array();
      node_save($primary);
    }
    while ($next = array_shift($meeting)) {
      // Set up references for addenum agendas.
      $node = $nodes[$next];
      if ($primary) {
        $addenum_to = field_get_items('node', $node, 'field_os2web_meetings_addendum');
        if (is_array($addenum_to)) {
          $addenum_to = array_shift($addenum_to);
          $addenum_to = array_shift($addenum_to);
        }
        else {
          $addenum_to = FALSE;
        }

        // Save time by only updating what is needed.
        if ($addenum_to != $primary->nid) {
          error_log(basename(__FILE__) . ':' . __LINE__ . ' Var: $primary = ' . print_r($primary->nid, 1));
          error_log(basename(__FILE__) . ':' . __LINE__ . ' Var: $addenum_to = ' . print_r($addenum_to, 1));
          $node->field_os2web_meetings_addendum[LANGUAGE_NONE][0]['nid'] = $primary->nid;
          node_save($node);
        }
      }
      else {
        error_log('MARK - ' . basename(__FILE__) . ':' . __LINE__ . ' in ' . __FUNCTION__ . '()');
        error_log(basename(__FILE__) . ':' . __LINE__ . " jm@bellcom.dk: wanted to delete $node->nid");
        // node_delete($node->nid);.
      }
      // Remove node from final nids_with_addendums.
      unset($nids_with_addendums[$node->nid]);
      if ($drush === TRUE) {
        if ($primary) {
          drush_log("Updated meeting $m_id..", 'ok');
        }
        else {
          drush_log("Removed stale addenum $m_id..", 'ok');
        }
      }
    }
  }

  $debug && error_log('MM Import - Start reset addendums on ' . count($nids_with_addendums) . ' nodes - ' . timer_read('_os2web_sbsys_aarhus_mm_order_addenums') . 'ms - ' . memory_get_usage());
  // Remove any addendums from nodes which hasnt been proccessed.
  foreach ($nids_with_addendums as $nid) {
    // Load the node from the local variable.
    $node = $nodes[$nid];
    $node->field_os2web_meetings_addendum = array();
    node_save($node);
    if ($drush === TRUE) {
      drush_log("Resetting $nid..", 'ok');
    }
  }
  $debug && error_log('MM Import - End of addendums - ' . timer_read('_os2web_sbsys_aarhus_mm_order_addenums') . 'ms - ' . memory_get_usage());
  lock_release(__FUNCTION__);
}

/**
 * Replaces the src attribute for img tag by providing the valid path to file.
 *
 * @param $html
 * @param $image_folder_uri
 *
 * @return mixed
 */
function _os2web_sbsys_aarhus_mm_improve_html($html, $image_folder_uri) {

  preg_match_all('/src="([^"]+)"/', $html, $matches);

  foreach ($matches[1] as $path) {
    $real_path = drupal_realpath($image_folder_uri . basename($path) . ".*");
    if ($real_path !== FALSE) {
      $glob_real_path = glob($real_path);
      if ($glob_real_path !== FALSE) {
        $image_path = array_pop($glob_real_path);
        $image_uri = file_create_url($image_folder_uri . basename($image_path));
        if (!empty($image_path)) {
          $new_uri = file_create_url($image_uri);
          if ($new_uri !== FALSE) {
            $html = str_replace($path, $new_uri, $html);
          }
        }
        else {
          $html = str_replace($path, "", $html);
        }
      }
    }
  }
  $html = preg_replace('/<img([^>]+)src=""([^>]*)>/', "", $html);
  return $html;
}

/**
 * This function generates numeric IDs, when it is missing in the XML.
 *
 * @param $string
 *
 * @return int|string
 */
function _os2web_sbsys_aarhus_generate_crc_id($string) {
  $id = abs(crc32($string));
  if ($id > 2147483647) {
    // Mysql int out of range fix.
    $id = substr($id, 0, 9);
  }
  return $id;
}

/**
 * This function generates numeric Number field, from Item ID string by first 2 chars.
 *
 * @param $string
 *
 * @return int|string
 */
function _os2web_sbsys_aarhus_generate_item_number($string) {

  $number = substr($string, 0, 2);
  if ($number[1] == '_') {
    $number = $number[0];
  }
  if ($number == 0) {
    // todo: set as last item.
    $number = 0;
  }
  return $number;
}
