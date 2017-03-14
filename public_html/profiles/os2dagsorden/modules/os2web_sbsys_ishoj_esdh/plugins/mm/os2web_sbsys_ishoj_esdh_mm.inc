<?php

/**
 * @file
 * This file describes the MM plugin as implemented by SBsys
 */

/**
 * Plugin definition with callbacks
 */
$plugin = array(
  'description' => t('SBsys ESDH MM Backend'),
  'version' => 1,
  'test' => 'os2web_sbsys_ishoj_esdh_mm_test',
  'get_import_list' => 'os2web_sbsys_ishoj_esdh_mm_get_import_list',
  'import_meeting' => 'os2web_sbsys_ishoj_esdh_mm_import_meeting',
  'post_import_process' => '_os2web_sbsys_ishoj_esdh_mm_order_addenums',
);

/**
 * For plugin testing purposes.
 */
function os2web_sbsys_ishoj_esdh_mm_test($stuff) {
  return 'Test successful. Recieved: ' . $stuff;
}

/**
 * Returns a list of meeting_ids for import. In our case a list of uri's of xml files.
 *
 * @return array
 *   List of URIs
 */
function os2web_sbsys_ishoj_esdh_mm_get_import_list() {
  /*
   * For the SBsys service, we need to import meetings from xml files.
   * We will enumerate the list with the publication-id
   * as parsed from the dir name of the manifest.
   */
  $uris = array();

  $dir = variable_get('os2web_sbsys_ishoj_esdh_mm_path', MM_IMPORT_DIR);

  foreach (file_scan_directory($dir, '/\.xml$/i', array('recurse' => TRUE)) as $xml_file) {
    // Skip preview.xml files
    if($xml_file->name !== 'preview'){
      $pathinfo = pathinfo($xml_file->uri);
      $pub_id = (int) str_replace($dir . '/Publication', '', $pathinfo['dirname']);
      $uris[] = array('id' => $pub_id, 'uri' => $xml_file->uri);
    }
  }
  return $uris;
}


/**
 * Strip illegal characters from the XML. 
 * Ex &#xC = ASCII new line feed
 * 
 * @param object $string
 *   string to sanitise
 * 
 * $return array
 *   The string sanitised 
 */
function utf8_for_xml($string)
{
    #$replace_me = "&#xC;";
    $replace_me =  variable_get('os2web_sbsys_ishoj_esdh_banned_special_char');
    $str_new = str_replace($replace_me, "", $string);
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
function os2web_sbsys_ishoj_esdh_mm_import_meeting($meeting) {
  $file = $meeting['uri'];
  if ($file === FALSE) {
    os2web_meetings_order_addenums();
  }
  $meetings = array();
  if (is_file(drupal_realpath($file))) {
    libxml_use_internal_errors(true);
    $manifest = simplexml_load_string(utf8_for_xml(file_get_contents(drupal_realpath($file))), 'SimpleXMLElement', LIBXML_NOCDATA);
    //print_r($manifest);
    libxml_clear_errors();
    libxml_use_internal_errors(false);

    if ($manifest === false) {
       error_log("Failed loading XML");
       foreach(libxml_get_errors() as $error) {
          error_log ($error->message);
       }
    }
    if (is_object($manifest)) {
      $committee = $manifest->xpath("Møde/@UdvalgID");
      //$committee_group_id = $manifest->xpath("Agendas/Agenda/Committee/CommitteeGroup/@ID");
      $committee_name = $manifest->xpath("Møde/@Udvalg");
      //$meeting_uri = $manifest->xpath("/Publication/OutputFileName");
      //$meeting_data = $manifest->xpath("/Publication/Agendas/Agenda/Meeting");
      $meeting_public = $manifest->xpath("@Åben");
      $meeting_id = $manifest->xpath("Møde/@MødeID");
      $sys_id = $manifest->xpath("@DagsordenID");
      //$meeting_name = $manifest->xpath("/Publication/Agendas/Agenda/Name");
      //$acadre_version = $manifest->xpath("/Publication/GeneratorSettings/@ID");
      //$members = $manifest->xpath("Agendas/Agenda/Meeting/Members/MeetingMember");
      $meeting_type = $manifest->xpath('@Dagsordentype');
      $meeting_date_when_date = $manifest->xpath("Møde/@Mødedato");
      $meeting_date_when_time = $manifest->xpath("Møde/@Mødetid");
      $meeting_where = $manifest->xpath("Møde/@Mødested");
      $additional_agenda = $manifest->xpath("@Tillægsdagsorden");

      $committee = (string) $committee[0]['UdvalgID'];
      //$committee_group_id = (string) $committee_group_id[0][ID];
      $committee_name = (string) $committee_name[0];
      $sys_id = (string) $sys_id[0];
      $meeting_id = (string) $meeting_id[0]['MødeID'];
      $meeting_public = (string) $meeting_public[0];
      $meeting_type = (string) $meeting_type[0];
      $additional_agenda = (string) $additional_agenda[0];

      $meeting_date_when = $meeting_date_when_date[0]['Mødedato'] . ' ' . $meeting_date_when_time[0]['Mødetid'];
      //$meeting_date_until = $meeting_data[0]->Until;
      $meeting_where = (string) $meeting_where[0]['Mødested'][0];
      $meeting_name = $committee_name;
      //$meeting_uri = (string) $meeting_uri[0];
      //$acadre_version = (string) $acadre_version[0][ID];
      $directory_name = dirname(drupal_realpath($file));

      $folder_uri = str_replace(basename($file), '', $file);

      $full_doc = array(
        'uri' => $folder_uri . '/Dagsorden.html',
        'title' => 'Samlet dokument',
      );

      // Check if the committee is allowed to publish.
      $publish_committee = array_map('trim', explode(',', variable_get('os2web_sbsys_ishoj_esdh_approved_committees', MM_DEFAULT_APPROVED)));
      if ($committee == '' || !in_array($committee, $publish_committee)) {
        watchdog('SBsys MM', 'Ignored agenda from "%committee" .', array('%committee' => $committee));
        return FALSE;
      }

      // Fix dates.
      $meeting_date_when = str_ireplace(array(". januar ", ". februar ", ". marts ", ". april ", ". maj ", ". juni ", ". juli ", ". august ",". september ", ". oktober ", ". november ", ". december "),
                                        array("-1-", "-2-", "-3-", "-4-", "-5-", "-6-", "-7-", "-8-", "-9-", "-10-", "-11-", "-12-"), $meeting_date_when);
      $date_obj = date_create($meeting_date_when);
      //date_timezone_set($date_obj, timezone_open('UTC'));
      $meeting_date_when = date_format($date_obj, 'Y-m-d H:i');

      ////Members
      //foreach ($members as $member){
      //  // Changed by skifter@bellcom.dk 01.08.2013 - to handle "no show" members and messages for "no shoW"
      //  if (!empty($member->ParticipationNote)) {
      //    $member->ParticipationNote = ", " . $member->ParticipationNote;
      //  }
      //
      //  if ($member->ParticipationStatusAsValue == '1' || $member->ParticipationStatusAsValue == '4') {
      //    $participants[] = (string) $member->Name . " - " . $member->ParticipationStatusAsText . $member->ParticipationNote;
      //  }
      //  // Changed by stan@bellcom.dk 19.09.2013 - to consider participants with "Ikke bestemt" status as actual participants
      //  else if($member->ParticipationStatusAsText == 'NotDecided' || $member->ParticipationStatusAsValue == '0'){
      //    $participants[] = (string) $member->Name . $member->ParticipationNote;
      //  }
      //  else {
      //    $participants_cancellation[] = (string) $member->Name . " - " . $member->ParticipationStatusAsText . $member->ParticipationNote;
      //  }
      //}

      $meeting = array(
        'system_id' => $sys_id,
        'meeting_id' => $meeting_id,
        'meeting_sub_id' => $sys_id,
        'committee' => $meeting_name,
        'committee_name' => $committee_name,
        'committee_id' => $committee,
        'committee_group_id' => $committee,
        'title' => $meeting_name,
        'uri' => $file,
        'folder' => $folder_uri,
        'type' => $meeting_type,
        'meeting_date_start' => $meeting_date_when,
        'full_doc' => $full_doc,
        'location' => $meeting_where,
        'additional_agenda' => $additional_agenda,
      );

      /*stan@bellcom.dk 06.10 - importing multiple agendas*/
      $meeting_agendas = array();
      foreach($manifest->xpath("/Dagsorden/Dagsordenpunkter") as $agenda_instance){
        if (!$meeting_agendas){
          if (sizeof($agenda_instance->xpath("Dagsordenpunkt")))
            $meeting_agendas = $agenda_instance->xpath("Dagsordenpunkt");
          else {
            //importing open agenda
            $meeting_agendas = $agenda_instance->xpath("Gruppe[@navn='Åbne dagsordenspunkter']/Dagsordenpunkt");
            //importing closed agenda
            if (variable_get('os2web_meetings_import_closed_agenda', false))
              $meeting_agendas = array_merge($meeting_agendas, $agenda_instance->xpath("Gruppe[@navn='Lukkede dagsordenspunkter']/Dagsordenpunkt"));
          }
        }
        else {
          foreach($agenda_instance->xpath("Dagsordenpunkt") as $items_child){
            $meeting_agendas[] = $items_child;
            //$toDom = dom_import_simplexml($meeting_agendas[0]);
            //$fromDom = dom_import_simplexml($items_child);
            //$toDom->appendChild($toDom->ownerDocument->importNode($meeting_agendas, true));
          }
        }
      }

      //$meeting_pdf = $manifest->xpath('/Meeting/MeetingAgendaTypes/MeetingAgendaType/PDFDocument');
      //$meeting['pdf'] = (string) $meeting_pdf[0];
      //$meeting['state'] = (string) $meeting_state[0];
      if (empty($meeting_agendas)) {
        watchdog('SBsys MM', 'Empty list of import items in %file.', array('%file' => $file), WATCHDOG_WARNING);
      }
      //foreach ($meeting_agendas as $meeting_agenda) {
        $imported = _os2web_sbsys_ishoj_esdh_mm_import_meeting_agenda($meeting, $meeting_agendas);
        if (is_array($imported)) {
          $imported['publish'] = TRUE;
          $meetings[] = $imported;
        }
      //}
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
function _os2web_sbsys_ishoj_esdh_mm_import_meeting_agenda(&$meeting, $agenda_xml) {
  $meeting['items'] = array();
  $agenda = $meeting;

  // Import all agenda items.
  $agenda_bullet = $agenda_xml;
  $meeting['current_item_nr'] = 1;
  foreach ($agenda_bullet as $agenda_item) {
    if (($item = _os2web_sbsys_ishoj_esdh_mm_import_meeting_agenda_item($meeting, $agenda_item)) !== FALSE) {
      $meeting['current_item_nr']++;
      $agenda['items'][] = $item;
    }
  }

  // Apply defaults, just in case we missed something.
  $agenda += os2web_esdh_provider_default_meeting();
  return $agenda;
}

/**
 * Imports a single item for an agenda.
 *
 * @param array $meeting
 *   Meeting array.
 *
 * @param SimpleXMLElement $xml
 *   Xml segment containing the item
 *
 * @return array
 *   The imported item.
 */
function _os2web_sbsys_ishoj_esdh_mm_import_meeting_agenda_item($meeting, $xml) {
  $xml_item['id'] = (string)$xml->attributes()->DagsordenpunktID;
  $xml_item['number'] = (string)$xml->attributes()->Nummer;
  //$xml_item['pdf'] = (string) $xml->PDFDocument;
  $xml_item_document = $xml->Bilagsliste;
  $xml_item_bullet = $xml->Indhold;
  $xml_item['name'] = (string) $xml->attributes()->Nummer . '. ' . $xml->Overskrift;
  $xml_item['document_type'] = (string) $xml->attributes()->Åbent;

  $item = array(
    'id' => $xml_item['number'],
    'number' => $xml_item['number'],
    'sysid' => (int) $xml_item['id'],
    'access' => $xml_item['document_type'],
    'bullets' => array(),
    'enclosures' => array(),
    'title' => $xml_item['name'],
  );

  if (strcasecmp($item['access'], 'true') != 0) {
    //rewriting the access field to match esdh provider module
    $item['access'] = 'Lukket';
  }
  //importing open bullets only, or open and closed if it is permitted
  if ($item['access'] !== 'Lukket' || variable_get('os2web_meetings_import_closed_agenda', false)){
    //// Process attachments.
    $xml_item_bullet = (array) $xml_item_bullet;
    foreach ($xml_item_bullet as $title => $body) {
      $item['bullets'][] = array(
        'title' => (string) $title,
        'body' => (string) $body,
        //'sysid' => (string) $bullet_xml['ID'],
      );
    }

    //// Process enclosures.
    foreach ($xml_item_document->Bilag as $enclosure) {
      $item['enclosures'][] = array(
        'uri' => $meeting['folder'] . (string) $enclosure->attributes()->BilagUrl,
        'title' => (string) $enclosure->attributes()->Navn,
        'access' => strcmp((string)$enclosure->attributes()->MaaPubliceres,'true') ? TRUE : FALSE,
        'sysid' => (string) $enclosure->attributes()->BilagID,
        'type' => 'Bilag',
      );
    }
  }

  $item += os2web_esdh_provider_default_item();
  return $item;
}

/**
 * This function will set up the addenum connections for meetings.
 */
function _os2web_sbsys_ishoj_esdh_mm_order_addenums($drush = FALSE) {
  if (!lock_acquire(__FUNCTION__)) {
    return;
  }

  // Debug bit set in os2web_esdh_provider settings.
  $debug = variable_get('os2web_esdh_provider_debug_info');
  $debug && timer_start('_os2web_sbsys_ishoj_esdh_mm_order_addenums') && error_log('MM Import - Start of addendums - ' . timer_read('_os2web_sbsys_ishoj_esdh_mm_order_addenums') . 'ms - ' . memory_get_usage());

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

  $debug && error_log('MM Import - Retrieve nodes with addendums from ' . count($nodes) . ' nodes - ' . timer_read('_os2web_sbsys_ishoj_esdh_mm_order_addenums') . 'ms - ' . memory_get_usage());
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
      watchdog('SBsys MM', 'Duplicate import found for meeting %mid. Deleting nid=%nid.', array('%mid' => $meeting_id['value'], '%nid' => $node->nid), WATCHDOG_WARNING);
      node_delete($node->nid);
    }
    else {
      $meetings[$meeting_id[0]['value']][$meeting_sub_id[0]['value']] = $node->nid;
    }
  }

  $debug && error_log('MM Import - Update addendums on ' . count($meetings) . ' nodes - ' . timer_read('_os2web_sbsys_ishoj_esdh_mm_order_addenums') . 'ms - ' . memory_get_usage());
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
        $addenum_to = is_array($addenum_to) ? array_shift(array_shift($addenum_to)) : FALSE;
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
        // node_delete($node->nid);
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

  $debug && error_log('MM Import - Start reset addendums on ' . count($nids_with_addendums) . ' nodes - ' . timer_read('_os2web_sbsys_ishoj_esdh_mm_order_addenums') . 'ms - ' . memory_get_usage());
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
  $debug && error_log('MM Import - End of addendums - ' . timer_read('_os2web_sbsys_ishoj_esdh_mm_order_addenums') . 'ms - ' . memory_get_usage());
  lock_release(__FUNCTION__);
}
