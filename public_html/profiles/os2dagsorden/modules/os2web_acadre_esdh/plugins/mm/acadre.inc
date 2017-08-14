<?php

/**
 * @file
 * This file describes the MM plugin as implemented by Acadre
 */

// Set this to the publication-id ie. 1577 for file XML_1577.
define('ACADRE_MM_PUB_FOCUS', FALSE);
// Misc. magic numbers.
define('ACADRE_MM_ACCESS_OPEN', 1);
define('ACADRE_MM_ACCESS_LUKKET', 2);
define('ACADRE_MM_ACCESS_PERSON', 3);
define('MM_REPUBLISH_SUBVERSION', TRUE);

/**
 * Plugin definition with callbacks
 */
$plugin = array(
  'description' => t('Acadre ESDH MM Backend'),
  'version' => 1,
  'test' => 'os2web_acadre_esdh_mm_test',
  'get_import_list' => 'os2web_acadre_esdh_mm_get_import_list',
  'import_meeting' => 'os2web_acadre_esdh_mm_import_meeting',
  'post_import_process' => '_os2web_acadre_esdh_mm_order_addendums',
);

/**
 * For plugin testing purposes.
 */
function os2web_acadre_esdh_mm_test($stuff) {
  return 'Test successful. Recieved: ' . $stuff;
}

/**
 * Returns a list of meeting_ids for import.
 *
 * In our case a list of uri's of xml files.
 *
 * @return array
 *   List of URIs
 */
function os2web_acadre_esdh_mm_get_import_list() {
  /*
   * For the acadre service, we need to miport meetings from xml files.
   * We will enumerate the list with the publication-id
   * as parsed from the filename.
   */

  // Debug bit set in os2web_esdh_provider settings.
  $debug = variable_get('os2web_esdh_provider_debug_info');

  $uris = array();
  foreach (file_scan_directory(variable_get('os2web_meetings_path', ACADRE_MM_IMPORT_DIR), '/\.xml$/i', array('recurse' => FALSE)) as $xml_file) {
    $pub_id = (int) str_replace('XML_', '', $xml_file->name);
    if (is_numeric($pub_id)) {
      $uris[] = array('id' => $pub_id, 'uri' => $xml_file->uri);
    }
    else {
      $uris[] = array('id' => $xml_file->name, 'uri' => $xml_file->uri);
    }
  }
  if (ACADRE_MM_PUB_FOCUS !== FALSE) {
    // We wish to only handle a single publication, så we return only that.
    if (isset($uris[ACADRE_MM_PUB_FOCUS])) {
      $uris = array(
        ACADRE_MM_PUB_FOCUS => $uris[ACADRE_MM_PUB_FOCUS],
      );
    }
  }

  $debug && error_log('MM Import - ' . count($uris) . ' uris found.');
  return $uris;
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
function os2web_acadre_esdh_mm_import_meeting($meeting) {
  // Debug bit set in os2web_esdh_provider settings.
  $debug = variable_get('os2web_esdh_provider_debug_info');
    
  $file = $meeting['uri'];
  if ($file === FALSE) {
    os2web_meetings_order_addendums();
  }
  $meetings = array();
  if (is_file(drupal_realpath($file))) {
    $manifest = simplexml_load_file(drupal_realpath($file));
    if (is_object($manifest)) {
      $agenda_id = _get_value_from_xml($manifest->xpath("/root/table[@name='agenda']/fields/field/@sysid"), 'int');
      $items_xml = $manifest->xpath("//table[@name='producedAgenda']/fields");
      if (empty($items_xml)) {
        watchdog('acadre MM', 'Empty list of import items in %file.', array('%file' => $file), WATCHDOG_WARNING);
      }
      foreach ($items_xml as $xml_item) {
        $debug && error_log('MM Import - Found meeting ' . $meeting['uri'] . ' - ' . timer_read('mm_import') . 'ms');

        $agendainfo = array(
          'sysid' => $agenda_id,
          'publish' => _get_value_from_xml($xml_item->xpath('field/@publish') ,'int'),
          'access' => _get_value_from_xml($xml_item->xpath('field/@access')),
          'filesfolder' => _get_value_from_xml($xml_item->xpath('field/@filesfolder')),
          'xmlfilename' => _get_value_from_xml($xml_item->xpath('field/@xmlfilename')),
          'docfilename' => _get_value_from_xml($xml_item->xpath('field/@docfilename')),
          'type' => _get_value_from_xml($xml_item->xpath('field/@type'),'int'),
          'docID' => _get_value_from_xml($xml_item->xpath('field/@docID'), 'int'),
          'pdffilename' => _get_value_from_xml($xml_item->xpath('field/@pdffilename')),
        );

        if ($agendainfo['publish'] === 1 &&
            ($agendainfo['access'] !== 'Lukket' || ($agendainfo['access'] === 'Lukket' && variable_get('os2web_meetings_import_closed_agenda', FALSE))) &&
            $agendainfo['filesfolder'] != '') {
          $agenda_uri =  variable_get('os2web_meetings_path', ACADRE_MM_IMPORT_DIR) .
            implode('/', array(
            $agendainfo['filesfolder'],
            $agendainfo['xmlfilename'])
          );
          $agendainfo['agenda_uri'] = $agenda_uri;
          $imported = _os2web_acadre_esdh_import_meeting($agendainfo);
          if (is_array($imported)) {
            $imported['publish'] = TRUE;
            $imported['agenda_xmlid'] = _get_value_from_xml($xml_item->xpath('field/@xmlFusionID'), 'int');
            $imported['meeting_sub_id'] = _get_value_from_xml($xml_item->xpath('field/@sysid'), 'int');
            $meetings[] = $imported;
          }
        }
        else {
          $message = '[XML_ID: !id] Agenda !sub_id, was not allowed to be published from xml !file. [publish]=!publish, [access]=!access, [filesfolder]=!filesfolder';
          
          $entries = array(
            '!id' => $agenda_id,
            '!sub_id' => _get_value_from_xml($xml_item->xpath('field/@sysid'), 'int'),
            '!publish' => $agendainfo['publish'],
            '!access' => $agendainfo['access'],
            '!filesfolder' => $agendainfo['filesfolder'],
            '!file' => $file,
          );
          watchdog('acadre MM', $message, $entries, WATCHDOG_INFO);
          if (function_exists('_os2web_esdh_provider_send_statusmail')) {
            _os2web_esdh_provider_send_statusmail(format_string($message, $entries), TRUE);
          }

          // Publication not published or public.
          $meetings[] = array(
            'meeting_id' => _get_value_from_xml($manifest->xpath("/root/table[@name='meeting']/fields/field/@sysid"), 'int'),
            'meeting_sub_id' => _get_value_from_xml($xml_item->xpath('field/@sysid'), 'int'),
            'agenda_access' => $agendainfo['access'],
            'publish' => FALSE,
          ) + os2web_esdh_provider_default_meeting();
        }
      }
    }
    else {
      watchdog('acadre MM', 'Failed to parse XML in %file during import.', array('%file' => $file), WATCHDOG_WARNING);
    }
  }
  return $meetings;
}

/**
 * Imports a meeting from filesystem.
 *
 * @param array $info
 *   Meeting info block derived from XML.
 *
 * @return mixed
 *   Meeting_struct array for an accepted import, else FALSE
 */
function _os2web_acadre_esdh_import_meeting($info) {

  // Debug bit set in os2web_esdh_provider settings.
  $debug = variable_get('os2web_esdh_provider_debug_info');
  $debug && error_log('MM Import - import meeting from XML - sysid=' . $info['sysid'] . ' - ' . timer_read('mm_import') . 'ms');
  if (($real_path = _os2web_acadre_esdh_similar_file_exists(drupal_realpath($info['agenda_uri']))) !== FALSE) {
    $xml = simplexml_load_file($real_path);
    $committee = _get_value_from_xml($xml->xpath("//table[@name='committee']/fields/field[@name='name']"));
    $committee_id = _get_value_from_xml($xml->xpath("//table[@name='committee']/fields/field[@name='sysid']"));
    if (variable_get('os2web_acadre_location_field', 'true') === 'true')
      $location = _get_value_from_xml($xml->xpath("//table[@name='meeting']/fields/field[@name='location']"));
    else
      $location = _get_value_from_xml($xml->xpath("//table[@name='location']/fields/field[@name='name']"));

    //Checking if meeting is in approved committees list
    $is_meeting_approved = TRUE;
    if (variable_get('os2dagsorden_committees_positive_list_as_import_list', FALSE) && module_exists('os2dagsorden_settings')){
      if ($committee == '' || !in_array($committee_id, os2dagsorden_settings_get_import_committees_sub_id()))
        $is_meeting_approved = FALSE;
    } else {
      $publish_committee = array_map('trim', explode(',', variable_get('os2web_meetings_approved_committee', ACADRE_MM_DEFAULT_APPROVED)));
      if ($committee == '' || !in_array($committee_id, $publish_committee))
        $is_meeting_approved = FALSE;
    }

    if (!$is_meeting_approved){
      watchdog('acadre MM', 'Ignored agenda from %committee (%committee_id).', array('%committee' => $committee, '%committee_id' =>$committee_id));
      return FALSE;
    }
    
    if (variable_get('os2web_acadre_description_field', 'true') === 'true')
      $description = _get_value_from_xml($xml->xpath("//table[@name='agenda']/fields/field[@name='name']"));
    else
      $description = _get_value_from_xml($xml->xpath("//table[@name='agenda']/fields/field[@name='description']"));

    

    $meeting = array(
      'title' => _get_value_from_xml($xml->xpath("//table[@name='meeting']/fields/field[@name='name']")),
      'meeting_id' => _get_value_from_xml($xml->xpath("//table[@name='meeting']/fields/field[@name='sysid']")),
      'system_id' => $info['sysid'],
      'path' => $real_path,
      'agenda_access' => $info['access'],
      'publication_id' => _get_value_from_xml($xml->xpath("//table[@name='agenda']/fields/field[@name='sysid']")),
      'creation_date' => strtotime(_get_value_from_xml($xml->xpath("//table[@name='agenda']/fields/field[@name='producedate']"))),
      'description' =>  $description,//_get_value_from_xml($xml->xpath("//table[@name='agenda']/fields/field[@name='name']")),
      'meeting_date_start' => _get_value_from_xml($xml->xpath("//table[@name='meeting']/fields/field[@name='date']")),
      'meeting_date_finish' => _get_value_from_xml($xml->xpath("//table[@name='meeting']/fields/field[@name='finish']")),
      'committee' => $committee,
      'committee_id' => $committee_id,
      'location'  => $location,
      'agenda_name' => _get_value_from_xml($xml->xpath("//table[@name='agenda']/fields/field[@name='name']")),
      'special_conditions' => _get_value_from_xml($xml->xpath("//table[@name='meeting']/fields/field[@name='description']")),
      'items' => array(),
    );
    if (variable_get('os2web_acadre_add_committee_to_title', FALSE)) {
      $meeting['title'] = $meeting['committee'] . " " . $meeting['title'];
    }

    // Fix dates:
    $date_obj = date_create($meeting['meeting_date_start']);
    date_timezone_set($date_obj, timezone_open('UTC'));
    $meeting['meeting_date_start'] = date_format($date_obj, 'Y-m-d H:i');
    $date_obj = date_create($meeting['meeting_date_finish']);
    date_timezone_set($date_obj, timezone_open('UTC'));
    $meeting['meeting_date_finish'] = date_format($date_obj, 'Y-m-d H:i');

    // Fix location.
    if (empty($meeting['location'])) {
      $meeting['location'] = _get_value_from_xml($xml->xpath("//table[@name='meeting']/fields/field[@name='address']"));
    }
    if (empty($meeting['location'])) {
      $meeting['location'] = _get_value_from_xml($xml->xpath("//table[@name='meeting']/fields/field[@name='location']"));
    }

    // Full Doc:
    $doc_uri = variable_get('os2web_meetings_path', ACADRE_MM_IMPORT_DIR).
        implode('/', array(       
        $info['filesfolder'],
        $info['docfilename']));
    $pdf_uri = variable_get('os2web_meetings_path', ACADRE_MM_IMPORT_DIR).
        implode('/', array(
        $info['filesfolder'],
        pathinfo($info['docfilename'], PATHINFO_FILENAME).'.pdf'));
    
    if (file_exists(drupal_realpath($pdf_uri))) 
        $uri =  $pdf_uri;
    else
        $uri = $doc_uri;

    $meeting['full_doc'] = array(
      'uri' => $uri,  
      'title' => $meeting['title'],
    );

    //Full Doc with content:
    $full_doc_with_attachements_uri = variable_get('os2web_meetings_path', ACADRE_MM_IMPORT_DIR).
      implode('/', array(
        $info['filesfolder'],
        $info['pdffilename']));

    if (file_exists(drupal_realpath($full_doc_with_attachements_uri))) {
      $meeting['full_doc_with_attachments'] = array(
        'uri' => $full_doc_with_attachements_uri,
        'title' => $meeting['title'],
      );
    }

    // Type:
    switch ($info['type']) {
      case 1:
        $meeting['type'] = 'Dagsorden';
        break;

      case 2:
        $meeting['type'] = 'Referat';
        break;

      default:
        $meeting['type'] = 'Anden';
        watchdog('acadre MM', 'Unknown meeting type value: %type', array('%type' => $meeting['type']), WATCHDOG_WARNING);
    }

    // Participants.
    $participants = $xml->xpath("//table[@name='committee']/table[@name='commember']/table[@name='member']");
    foreach ($participants as $participant) {
      $meeting['participants'][] = _get_value_from_xml($participant->xpath("fields/field[@name='name']"));
    }

    // Participant cancelled.
    $participants_cancelled = $xml->xpath("//table[@name='meeting']/table[@name='meetmember']/table[@name='member']");
    foreach ($participants_cancelled as $participant_cancelled) {
      // Check if the absent is true, then add participants
      // to participants_cancelled list.
      $absent = _get_value_from_xml($participant_cancelled->xpath("fields/field[@name='absent']"));
      if ($absent == "1") {
        $meeting['participants_cancellation'][] = _get_value_from_xml($participant_cancelled->xpath("fields/field[@name='name']"));
      }
    }

    foreach ($xml->xpath("//table[@name='agendaitemparents']") as $item_xml) {
      $item_content_xml = $item_xml->xpath("table[@name='agendaitem']");
      $item_content_xml = array_shift($item_content_xml);
      if (($item = _os2web_acadre_esdh_import_item($info, $item_content_xml)) !== FALSE) {
        $item['additional'] = (stripos($meeting['agenda_name'], 'tillæg') !== FALSE) ? TRUE : FALSE;
        $meeting['items'][] = $item;
      }
    }
    // Apply defaults, just in case we missed something.
    $meeting += os2web_esdh_provider_default_meeting();
    return $meeting;
  }
  else {
    // Requested file not found.
    watchdog('acadre MM', 'Failed to read agenda manifest file %uri', array('%uri' => $info['agenda_uri']), WATCHDOG_WARNING);
  }
  return FALSE;
}

/**
 * Imports a single item for an agenda.
 *
 * @param array $info
 *   Import info array
 * @param SimpleXMLElement $xml
 *   Xml segment containing the item
 *
 * @return array
 *   The imported item.
 */
function _os2web_acadre_esdh_import_item($info, $xml) {
  // Debug bit set in os2web_esdh_provider settings.
  $debug = variable_get('os2web_esdh_provider_debug_info');

  $id = _get_value_from_xml($xml->xpath("../fields/field[@name='sort']"), 'int');
  $name = _get_value_from_xml($xml->xpath("fields/field[@name='name']"));
  $access = _get_value_from_xml($xml->xpath("fields/field[@name='accessname']"));
  $case = _get_value_from_xml($xml->xpath("fields/field[@name='caseno']"));
  $case_id = _get_value_from_xml($xml->xpath("table/table/fields/field[@name='sysid']"));
  $sysid = _get_value_from_xml($xml->xpath("fields/field[@name='sysid']"), 'int');
  $comname = _get_value_from_xml($xml->xpath("fields/field[@name='comname']"));

  $item = array(
    'id' => $id,
    'sysid' => $sysid,
    'title' => 'Punkt ' . $id . ' ' . $name,
    'case_nr' => $case,
    'access' => $access,
    'comname' => $comname,
    'bullets' => array(),
    'enclosures' => array(),
  );

  $debug && error_log('MM Import - Import item from XML - id=' . $id . ' - ' . timer_read('mm_import') . 'ms');

  // Process attachments.
  if ($item['access'] !== 'Lukket' ||
    variable_get('os2web_meetings_import_closed_agenda', FALSE)) {
    foreach ($xml->xpath("table[@name='bullet']") as $bullet_xml) {
      if (($bullet = _os2web_acadre_esdh_import_bullet($info, $bullet_xml)) !== FALSE) {
        if (is_int($bullet['sort']) && $bullet['sort'] > 0) {
          $item['bullets'][$bullet['sort'] - 1] = $bullet;
        }
        else {
          $item['bullets'][] = $bullet;
        }
      }
    }
    foreach ($xml->xpath("table[@name='Case']") as $case_xml) {
      foreach ($case_xml->xpath("table[@name='Files']/table[@name='File']") as $case_file) {
        $filename_in = _get_value_from_xml($case_file->xpath("fields/field[@name='FileName']"));
        if (strlen($filename_in) > 0) {
          $filetype = _get_value_from_xml($case_file->xpath("fields/field[@name='DocumentExtension']"));
          $folder_path =  variable_get('os2web_meetings_path', ACADRE_MM_IMPORT_DIR) . $info['filesfolder'];
          if (strcasecmp($filetype, 'MSG') == 0) {
            // E.g. [...]/1709477.MSG_attachments.
            $attachments_folder_path = $folder_path . '/' . $filename_in . '_attachments';
            $files = glob(drupal_realpath($attachments_folder_path) . '/*.pdf');
            if (file_exists($attachments_folder_path)) {
              foreach ($files as $file) {
                // Avoiding part1 file import - don't need it.
                if (strpos(basename($file), 'eml.part1') === FALSE) {
                  $item['enclosures'][] = array(
                    'uri' => $folder_path . '/' . basename($file),
                    'title' => 'Email:' . _get_value_from_xml($case_file->xpath("fields/field[@name='Title']")),
                    'filetype' => '.PDF',
                    'type' => 'Sager',
                    'access' => (_get_value_from_xml($case_file->xpath("fields/field[@name='PublicAccessLevelName']")) == 'Åben'),
                  );
                }
              }
            }
            else {
              if (_os2web_acadre_esdh_similar_file_exists(drupal_realpath($folder_path . '/' . $filename_in))) {
                $uri = _os2web_acadre_esdh_pdf_file_path($folder_path, $filename_in);
                $item['enclosures'][] = array(
                  'uri' => $uri,
                  'title' => 'Email:' . _get_value_from_xml($case_file->xpath("fields/field[@name='Title']")),
                  'filetype' => "." . _get_value_from_xml($case_file->xpath("fields/field[@name='DocumentExtension']")),
                  'type' => 'Sager',
                  'access' => (_get_value_from_xml($case_file->xpath("fields/field[@name='PublicAccessLevelName']")) == 'Åben'),
                );
              }
            }
          }
          else {
            $uri = _os2web_acadre_esdh_pdf_file_path($folder_path, $filename_in);
            $item['enclosures'][] = array(
              'uri' => $uri,
              'title' => _get_value_from_xml($case_file->xpath("fields/field[@name='Title']")),
              'filetype' => "." . _get_value_from_xml($case_file->xpath("fields/field[@name='DocumentExtension']")),
              'type' => 'Sager',
              'access' => (_get_value_from_xml($case_file->xpath("fields/field[@name='PublicAccessLevelName']")) == 'Åben'),
            );
          }
        }
      }
    }
    // Process enclosures.
    foreach ($xml->xpath("table[@name='enclosure']") as $enclosure) {
      $filename_in = _get_value_from_xml($enclosure->xpath("fields/field[@name='filename']"));
      if (strlen($filename_in) > 0) {
        $filetype = _get_value_from_xml($enclosure->xpath("fields/field[@name='EnclosureFileType']"));
        $folder_path = variable_get('os2web_meetings_path', ACADRE_MM_IMPORT_DIR) . $info['filesfolder'];

        if (strcasecmp($filetype, '.msg') == 0) {
          // E.g. [...]/1709477.MSG_attachments.
          $attachments_folder_path = $folder_path . '/' . $filename_in . '_attachments';
          $files = glob(drupal_realpath($attachments_folder_path) . '/*.pdf');
          if (file_exists($attachments_folder_path)) {
            foreach ($files as $file) {
              // Avoiding part1 file import - don't need it.
              if (strpos(basename($file), 'eml.part1') === FALSE) {
                $item['enclosures'][] = array(
                  'uri' => $folder_path . '/' . basename($file),
                  'title' => 'Email:' . _get_value_from_xml($enclosure->xpath("fields/field[@name='name']")),
                  'filetype' => '.PDF',
                  'type' => 'Bilag',
                  'access' => ACADRE_MM_ACCESS_OPEN == _get_value_from_xml($enclosure->xpath("fields/field[@name='access']"), 'int'),
                );
              }
            }
          }
          else {
            if (_os2web_acadre_esdh_similar_file_exists(drupal_realpath($folder_path . '/' . $filename_in))) {
              $uri = _os2web_acadre_esdh_pdf_file_path($folder_path, $filename_in);
              $item['enclosures'][] = array(
                'sysid'  => _get_value_from_xml($enclosure->xpath("fields/field[@name='sysid']"), 'int'),
                'uri' => $uri,
                'title' => 'Email:' . _get_value_from_xml($enclosure->xpath("fields/field[@name='name']")),
                'filetype' => _get_value_from_xml($enclosure->xpath("fields/field[@name='EnclosureFileType']")),
                'type' => 'Bilag',
                'access' => ACADRE_MM_ACCESS_OPEN == _get_value_from_xml($enclosure->xpath("fields/field[@name='access']"), 'int'),
              );
            }
          }

        }
        else {
          $uri = _os2web_acadre_esdh_pdf_file_path($folder_path, $filename_in);
          $item['enclosures'][] = array(
            'sysid'  => _get_value_from_xml($enclosure->xpath("fields/field[@name='sysid']"), 'int'),
            'uri' => $uri,
            'title' => _get_value_from_xml($enclosure->xpath("fields/field[@name='name']")),
            'filetype' => _get_value_from_xml($enclosure->xpath("fields/field[@name='EnclosureFileType']")),
            'type' => 'Bilag',
            'access' => ACADRE_MM_ACCESS_OPEN == _get_value_from_xml($enclosure->xpath("fields/field[@name='access']"), 'int'),
          );
        }
      }
    }
  }
  $item += os2web_esdh_provider_default_item();
  return $item;
}

/**
 * Imports a single bullet for an agenda item.
 *
 * @param array $info
 *   Import info array
 * @param SimpleXMLElement $bullet_xml
 *   Xml segment containing the bullet
 *
 * @return array
 *   The imported bullet.
 */
function _os2web_acadre_esdh_import_bullet($info, $bullet_xml) {
  // Debug bit set in os2web_esdh_provider settings.
  $debug = variable_get('os2web_esdh_provider_debug_info');
  $debug && error_log('MM Import - import bullet - ' . timer_read('mm_import') . 'ms');

  $bullet = array(
    'title' => _get_value_from_xml($bullet_xml->xpath("fields/field[@name='bulletname']")),
    'body' => _get_value_from_xml($bullet_xml->xpath("fields/field[@name='bulletcontent']")),
    'sort' => _get_value_from_xml($bullet_xml->xpath("fields/field[@name='bulletsortorder']"), 'int'),
    'sysid' => _get_value_from_xml($bullet_xml->xpath("fields/field[@name='sysid']"), 'int'),
  );
  if ($bullet['body'] === '') {
    return FALSE;
  }
  $bullet['body'] = _acadre_esdh_mm_improve_body_html($bullet['body']);
  $bullet += os2web_esdh_provider_default_bullet();
  return $bullet;
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
function _os2web_acadre_esdh_similar_file_exists($filename) {
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
 * This function will set up the addendum connections for meetings.
 *
 * @param bool $drush
 */
function _os2web_acadre_esdh_mm_order_addendums($drush = FALSE) {
  if (!lock_acquire(__FUNCTION__)) {
    return;
  }

  // Debug bit set in os2web_esdh_provider settings.
  $debug = variable_get('os2web_esdh_provider_debug_info');
  $debug && timer_start('_os2web_acadre_esdh_mm_order_addendums') && error_log('MM Import - Start of addendums - ' . timer_read('_os2web_acadre_esdh_mm_order_addendums') . 'ms - ' . memory_get_usage());

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
  $fields = field_info_instances('node', 'os2web_meetings_meeting');
  field_attach_load('node', $nodes, FIELD_LOAD_CURRENT, array('field_id' => $fields['field_os2web_meetings_addendum']['field_id']));
  field_attach_load('node', $nodes, FIELD_LOAD_CURRENT, array('field_id' => $fields['field_os2web_meetings_id']['field_id']));
  field_attach_load('node', $nodes, FIELD_LOAD_CURRENT, array('field_id' => $fields['field_os2web_meetings_sub_id']['field_id']));
  field_attach_load('node', $nodes, FIELD_LOAD_CURRENT, array('field_id' => $fields['field_os2web_meetings_system_id']['field_id']));
  field_attach_load('node', $nodes, FIELD_LOAD_CURRENT, array('field_id' => $fields['field_os2web_meetings_full_doc']['field_id']));
  field_attach_load('node', $nodes, FIELD_LOAD_CURRENT, array('field_id' => $fields['field_os2web_meetings_full_doc_c']['field_id']));

  // Should the sub_id or system_id be used in SORT
  // to determine dagsorden/tillæg

  // Meetings as: $meetings[<meeting_id>][<system_id>][<node_id>] .
  $meetings = array();

  $nids_with_addendums = array();

  $debug && error_log('MM Import - Retrieve nodes with addendums from ' . count($nodes) . ' nodes - ' . timer_read('_os2web_acadre_esdh_mm_order_addendums') . 'ms - ' . memory_get_usage());
  // Loop through all meeting nodes, and generate an array with meeting grouped.
  foreach ($nodes as $node) {
    $addendum_to = field_get_items('node', $node, 'field_os2web_meetings_addendum');
    if (isset($addendum_to[0]['nid']) && is_numeric($addendum_to[0]['nid'])) {
      $nids_with_addendums[$node->nid] = $node->nid;
    }
    $meeting_id = field_get_items('node', $node, 'field_os2web_meetings_id');
    $meeting_system_id = field_get_items('node', $node, 'field_os2web_meetings_system_id');
    if (!isset($meeting_id[0]['value']) || !isset($meeting_system_id[0]['value'])) {
      $debug && error_log('MM Import - Missing meeting_id or meeting_system_id for nid=' . $node->nid);
      continue;
    }
    if (isset($meetings[$meeting_id[0]['value']][$meeting_system_id[0]['value']])) {
      // Duplicate meeting detected.
      watchdog('acadre MM', 'Duplicate import found for meeting %mid. Deleting nid=%nid.', array('%mid' => $meeting_id['value'], '%nid' => $node->nid), WATCHDOG_WARNING);
      node_delete($node->nid);
    }
    else {
      $meetings[$meeting_id[0]['value']][$meeting_system_id[0]['value']] = $node->nid;
    }
  }

  $debug && error_log('MM Import - Update addendums on ' . count($meetings) . ' nodes - ' . timer_read('_os2web_acadre_esdh_mm_order_addendums') . 'ms - ' . memory_get_usage());
  // Run through the meeting array, to determine the addendums.
  foreach ($meetings as $m_id => $meeting) {
    // Lowest system id first.
    ksort($meeting);
    if (in_array($m_id, $rev_meetings)) {
      $meeting = array_reverse($meeting);
    }
    // Lowest system id is primary.
    $primary = $nodes[array_shift($meeting)];
    $addendum_to = field_get_items('node', $primary, 'field_os2web_meetings_addendum');
    if (!empty($addendum_to[0]['nid'])) {
      $primary->field_os2web_meetings_addendum[LANGUAGE_NONE] = array();
      node_save($primary);
    }
    while ($next = array_shift($meeting)) {
      // Set up references for addendum agendas.
      $node = $nodes[$next];
      if ($primary) {
        $addendum_to = field_get_items('node', $node, 'field_os2web_meetings_addendum');
        $addendum_to = is_array($addendum_to) ? array_shift(array_shift($addendum_to)) : FALSE;
        // Save time by only updating what is needed.
        if ($addendum_to != $primary->nid) {
          $node->field_os2web_meetings_addendum[LANGUAGE_NONE][0]['nid'] = $primary->nid;
          node_save($node);
          // $node_to_access = node_load($node->nid);
          // node_access_acquire_grants($node_to_access);
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
          drush_log("Removed stale addendum $m_id..", 'ok');
        }
      }
    }
  }

  $debug && error_log('MM Import - Start reset addendums on ' . count($nids_with_addendums) . ' nodes - ' . timer_read('_os2web_acadre_esdh_mm_order_addendums') . 'ms - ' . memory_get_usage());
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
  $debug && error_log('MM Import - End of addendums - ' . timer_read('_os2web_acadre_esdh_mm_order_addendums') . 'ms - ' . memory_get_usage());
  lock_release(__FUNCTION__);
}

/**
 * Checks if a there is a PDF version of a file with a given path.
 *
 * @param string $path
 *   The path of the original file
 * @param string $name
 *   The name of the original file
 *
 * @return string
 *   The path of the PDF version of the file (if exists), else old filepath
 */
function _os2web_acadre_esdh_pdf_file_path($path, $name) {
  $name_arr = explode('.', $name);

  $pdf_path = $path . '/' . $name_arr[0] . '.PDF';
  if (_os2web_acadre_esdh_similar_file_exists(drupal_realpath($pdf_path))) {
    return $pdf_path;
  }
  else {
    return $path . '/' . $name;
  }
}

/**
 * Improve the body HTML by stripping long URLs and substituting img references,
 *
 * @param $data
 * @return mixed
 */
function _acadre_esdh_mm_improve_body_html($data) {
  $data = _acadre_esdh_mm_remove_empty_tags($data);
  $url_strip_count = variable_get('os2dagsorden_url_strip_count','100');
  $data = preg_replace('/(<a.+?>)(.{0,'.$url_strip_count.'}).*?(<\/a>)/is', '$1$2...$3', $data);
  $doc = new DOMDocument();
  $doc->loadHTML( $data);
  $elements = $doc->getElementsByTagName('img');
  if($elements->length > 0){
      foreach($elements as $element)  {
	 $file = $element->getAttribute('src');
            if (strpos($file, 'http://') === FALSE) {
               $file = str_replace('"', '', $file);
               $uri_parts = explode('\\', $file);
               $filename = trim(array_pop($uri_parts));
               $folder_name = array_pop($uri_parts);
               $file_realpath = drupal_realpath(variable_get('os2web_meetings_acadre_images') .
                  implode('/', array(
                  $folder_name,
                  $filename,
                )));
                $dest_dir_realpath = drupal_realpath(variable_get('os2web_meetings_acadre_images_destination_folder') . $folder_name);
                if (!file_exists($dest_dir_realpath)) {
                  if (!mkdir($dest_dir_realpath)) {
                     watchdog('acadre MM', 'Could not create subdirectory %dir. Check the permissions', array('%dir' => $dest_dir_realpath), WATCHDOG_ERROR);
                    return $data;
                   }
                }
                copy($file_realpath, $dest_dir_realpath . '/' . $filename);
                watchdog('acadre MM', 'Copying %from to %to', array('%from' => $file_realpath, '%to' => $dest_dir_realpath . '/' . $filename), WATCHDOG_DEBUG);
               
                $new_uri = file_create_url(variable_get('os2web_meetings_acadre_images_destination_folder') . 
                  implode('/', array(
                  $folder_name,
                  $filename,
                )));
                // Modify uri.
                $data = str_replace($file, $new_uri, $data);
         }
      }
   }
   return $data;
}

/**
 * Removed the empty tags (tags having no content, or nbsp) from the provided text.
 *
 * @param $data
 * @return mixed
 */
function _acadre_esdh_mm_remove_empty_tags($data) {
do
{
   $len1 = mb_strlen($data);
   $data = preg_replace( '/(<(a|span)[^>]*>[\s|&nbsp;?]*<(\/a|\/span)>)/', '' ,$data);
   $len2 = mb_strlen($data);

} while ($len1 > 0 && $len2 > 0 && $len1 != $len2);

return $data;

}

/**
 * Gets the string value from the raw XML.
 *
 * @param $xml_raw
 * @param string $convert_to
 * @return int|string
 */
function _get_value_from_xml($xml_raw, $convert_to = 'string'){
  if ($convert_to == 'string')
    return trim((string) array_shift($xml_raw));
  elseif ($convert_to = 'int')
    return (int) array_shift($xml_raw);
}
