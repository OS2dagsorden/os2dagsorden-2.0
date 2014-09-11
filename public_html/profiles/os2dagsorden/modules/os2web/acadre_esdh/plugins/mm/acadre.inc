<?php

/**
 * @file
 * This file describes the MM plugin as implemented by Acadre
 */

// Set this to the publication-id ie. 1577 for file XML_1577.
define('ACADRE_MM_PUB_FOCUS', FALSE);

/**
 * Plugin definition with callbacks
 */
$plugin = array(
  'description' => t('Acadre ESDH MM Backend'),
  'version' => 1,
  'test' => 'acadre_esdh_mm_test',
  'get_import_list' => 'acadre_esdh_mm_get_import_list',
  'import_meeting' => 'acadre_esdh_mm_import_meeting',
  'post_import_process' => '_acadre_esdh_mm_order_addenums',
);

/**
 * For plugin testing purposes.
 */
function acadre_esdh_mm_test($stuff) {
  return 'Test successful. Recieved: ' . $stuff;
}

/**
 * Returns a list of meeting_ids for import. In our case a list of uri's of xml files.
 *
 * @return array
 *   List of URIs
 */
function acadre_esdh_mm_get_import_list() {
  /*
   * For the acadre service, we need to import meetings from xml files.
   * We will enumerate the list with the publication-id as parsed from the filename.
   */
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
function acadre_esdh_mm_import_meeting($meeting) {
  $file = $meeting['uri'];
  if ($file === FALSE) {
    os2web_meetings_order_addenums();
  }
	$meetings = array();
	  if (is_file(drupal_realpath($file))) {
    $manifest = simplexml_load_file(drupal_realpath($file));
	  if (is_object($manifest)) {
      $items_xml = $manifest->xpath("//table[@name='producedAgenda']/fields");
	   if (empty($items_xml)) {
        watchdog('acadre MM', 'Empty list of import items in %file.', array('%file' => $file), WATCHDOG_WARNING);
      }
			
      foreach ($items_xml as $xml_item) {
        $agendainfo = array(
          'sysid' => (int) array_shift($xml_item->xpath('field/@sysid')),
          'publish' => (int) array_shift($xml_item->xpath('field/@publish')),
          'access' => (string) array_shift($xml_item->xpath('field/@access')),
          'filesfolder' => (string) array_shift($xml_item->xpath('field/@filesfolder')),
          'xmlfilename' => (string) array_shift($xml_item->xpath('field/@xmlfilename')),
          'docfilename' => (string) array_shift($xml_item->xpath('field/@docfilename')),
          'docID' => (int) array_shift($xml_item->xpath('field/@docID')),
          'type' => (int) array_shift($xml_item->xpath('field/@type')),
        );
		   if (empty($agendainfo['filesfolder'])){
	  $agendainfo['filesfolder'] = 'Files_' . $meeting['id'] . '_' . $agendainfo['docID'];
	}
		
        if ($agendainfo['publish'] === 1 && $agendainfo['filesfolder'] != '') {
          $agenda_uri = implode('/', array(variable_get('os2web_meetings_path', ACADRE_MM_IMPORT_DIR),$agendainfo['filesfolder'],$agendainfo['xmlfilename']));
          $agendainfo['agenda_uri'] = $agenda_uri;
				
          $imported = _acadre_esdh_import_meeting($agendainfo);
					
			
			     if (is_array($imported)) {
            $imported['publish'] = TRUE;
            $meetings[] = $imported;
          }
        }
        else {
          // Publication not published or public.
//           $meetings[] = array(
//            'system_id' => $agendainfo['sysid'],
//            'publish' => FALSE,
//           ) + os2web_esdh_provider_default_meeting();
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
function _acadre_esdh_import_meeting($info) {
	if (($real_path = _acadre_esdh_similar_file_exists(drupal_realpath($info['agenda_uri']))) !== FALSE) {
    $xml = simplexml_load_file($real_path);
		$meeting = array(
      'title' =>(string) array_shift($xml->xpath("//table[@name='committee']/fields/field[@name='name']"))." ".(string) array_shift($xml->xpath("//table[@name='meeting']/fields/field[@name='name']")),
      'meeting_id' => (string) array_shift($xml->xpath("//table[@name='meeting']/fields/field[@name='sysid']")),
      'system_id' => $info['sysid'],
      'acadre_version' => $info['docID'],
      'publication_id' => (string) array_shift($xml->xpath("//table[@name='agenda']/fields/field[@name='sysid']")),
      'creation_date' => strtotime((string) array_shift($xml->xpath("//table[@name='agenda']/fields/field[@name='producedate']"))),
      'description' => (string) array_shift($xml->xpath("//table[@name='agenda']/fields/field[@name='description']")),
      'meeting_date_start' => (string) array_shift($xml->xpath("//table[@name='meeting']/fields/field[@name='date']")),
      'meeting_date_finish' => (string) array_shift($xml->xpath("//table[@name='meeting']/fields/field[@name='finish']")),
      'committee' => (string) array_shift($xml->xpath("//table[@name='committee']/fields/field[@name='name']")),
      'committee_name' => (string) array_shift($xml->xpath("//table[@name='committee']/fields/field[@name='name']")),
      'committee_id' => (string) array_shift($xml->xpath("//table[@name='committee']/fields/field[@name='sysid']")),
      'location' => (string) array_shift($xml->xpath("//table[@name='meeting']/fields/field[@name='location']")),
      'agenda_access' => $info['access'],
      'agenda_type' => (string) array_shift($xml->xpath("//fields/field[@name='name']")),
      'items' => array(),
    );

   if (variable_get('os2web_acadre_add_committe_to_title', FALSE))
      $meeting['title']=$meeting['committee_name']." ".$meeting['title'];
    	
    $publish_committee = array_map('trim', explode(',', variable_get('os2web_meetings_approved_committee', ACADRE_MM_DEFAULT_APPROVED)));
    if ($meeting['committee'] == '' || !in_array($meeting['committee_id'], $publish_committee)) {
      watchdog('acadre MM', 'Ignored agenda from %committee .', array('%committee' => $meeting['committee']));
    return FALSE;
    }
		
	
    // Fix dates:
    $date_obj = date_create($meeting['meeting_date_start']);
    //date_timezone_set($date_obj, timezone_open('UTC'));
    $meeting['meeting_date_start'] = date_format($date_obj, 'Y-m-d H:i');
    $date_obj = date_create($meeting['meeting_date_finish']);
    //date_timezone_set($date_obj, timezone_open('UTC'));
    $meeting['meeting_date_finish'] = date_format($date_obj, 'Y-m-d H:i');

    // Full Doc:
    $uri= _acadre_esdh_pdf_file_path(implode('/', array( variable_get('os2web_meetings_path', ACADRE_MM_IMPORT_DIR), $info['filesfolder'])),strtoupper($info['docfilename']));
    $meeting['full_doc'] = array(
      'uri' => $uri/*implode('/', array(
        variable_get('os2web_meetings_path', ACADRE_MM_IMPORT_DIR),
        $info['filesfolder'],
        strtoupper($info['docfilename'])))*/,//avoiding the problem with extensions
      'title' => $meeting['title'],
    );
	
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
    
    //Participants
    $participants = $xml->xpath(variable_get('os2web_meetings_participants_import_path', "//table[@name='committee']/table[@name='commember']/table[@name='member']"));
    foreach ($participants as $participant) {
	$meeting['participants'][] = (string) array_shift($participant->xpath("fields/field[@name='name']"));
    }
	
       foreach ($xml->xpath("//table[@name='agendaitemparents']") as $item_xml) {
      $item_content_xml = array_shift($item_xml->xpath("table[@name='agendaitem']"));

			if (($item = _acadre_esdh_import_item($info, $item_content_xml)) !== FALSE) {

				$item['agenda_type'] = $meeting['agenda_type'];
				if (count($item['enclosures']) > 0) {
					if ((bool) variable_get('os2web_bilag_import', false)) {
						isset($enclosures) ? $enclosures = array_merge($enclosures, $item["enclosures"]) : $enclosures = $item["enclosures"];
						unset($item["enclosures"]);
					}
				}
				if (count($item['cases']) > 0) {
					if ((bool) variable_get('os2web_case_import', false)) {
						isset($cases) ? $cases = array_merge($cases, $item["cases"]) : $cases = $item["cases"];
						unset($item["cases"]);
					} else {				
						isset($item["enclosures"]) ? $item["enclosures"] = array_merge($item["enclosures"], $item["cases"]) : $item["enclosures"] = $item["cases"];
						;
					}
				}
				$meeting['items'][] = $item;
			}
		}

		if (isset($enclosures) && !empty($enclosures)) {
			$item = array(
					'id' => count($meeting['items']) + 1,
					'agenda_type' => $meeting['agenda_type'],
					'sysid' => $meeting['meeting_id'] . count($meeting['items']),
					'caseno' => "",
					'title' => 'Bilag',
					'access' => '',
					'bullets' => array(),
					'enclosures' => $enclosures,
			);
			$meeting['items'][] = $item;
		}
		if (isset($cases) && !empty($cases)) {
			$item = array(
					'id' => count($meeting['items']) + 1,
					'agenda_type' => $meeting['agenda_type'],
					'sysid' => $meeting['meeting_id'] . count($meeting['items']),
					'caseno' => "",
					'title' => 'Sager',
					'access' => '',
					'bullets' => array(),
					'enclosures' => $cases,
			);
			$meeting['items'][] = $item;
		}
		
		
	/** Representing bilag / sage in additional bullet point	
		foreach ($xml->xpath("//table[@name='agendaitemparents']") as $item_xml) {
      $item_content_xml = array_shift($item_xml->xpath("table[@name='agendaitem']"));
	
	  if (($item = _acadre_esdh_import_item($info, $item_content_xml)) !== FALSE) {
	    $item['agenda_type'] = $meeting['agenda_type'];
	    $meeting['items'][] = $item;
	  }
    }
 
	    $item['agenda_type'] = $meeting['agenda_type'];
				if (count($item['enclosures'])>0) {
					isset($enclosures)?$enclosures=array_merge($enclosures, $item["enclosures"]):$enclosures=$item["enclosures"];
					  unset ($item["enclosures"]);
					}
					if (count($item['cases'])>0) {
					isset($cases)?$cases=array_merge($cases, $item["cases"]):$cases=$item["cases"];
					 unset ($item["cases"]);
					}
						$meeting['items'][] = $item;
						}
					}
					
					if (isset($enclosures)&&!empty($enclosures)){
						 $item = array(
					'id' =>count($meeting['items'])+1,
					'agenda_type'=>$meeting['agenda_type'],		 
					'sysid' => $meeting['meeting_id'].count($meeting['items']),
					'caseno'=> "",
					'title' => 'Bilag',
					'access' => '',
					'bullets' => array(),
					'enclosures' => $enclosures,
					
				);
					$meeting['items'][]=$item;}
					if (isset($cases)&&!empty($cases)){
						 $item = array(
					'id' =>count($meeting['items'])+1,
					'agenda_type'=>$meeting['agenda_type'],		 
					'sysid' => $meeting['meeting_id'].count($meeting['items']),
					'caseno'=> "",
					'title' => 'Sager',
					'access' => '',
					'bullets' => array(),
					'enclosures' => $cases,

				); 
					$meeting['items'][]=$item;
						 }
*/		
					
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
function _acadre_esdh_import_item($info, $xml) {

  $id = (int) array_shift($xml->xpath("../fields/field[@name='sort']"));
  $name = (string) array_shift($xml->xpath("fields/field[@name='name']"));
  $item = array(
    'id' => $id,
    'sysid' => (int) array_shift($xml->xpath("fields/field[@name='sysid']")),
    'caseno'=> (string) array_shift($xml->xpath("fields/field[@name='caseno']")),
    'title' => 'Punkt ' . $id . ' ' . $name,
    'access' => (string) array_shift($xml->xpath("fields/field[@name='accessname']")),
    'bullets' => array(),
    'enclosures' => array(),
  );

  // Process attachments.
  foreach ($xml->xpath("table[@name='bullet']") as $bullet_xml) {
    if (($bullet = _acadre_esdh_import_bullet($info, $bullet_xml)) !== FALSE) {
      $item['bullets'][] = $bullet;
    }
  }

  foreach ($xml->xpath("table[@name='Case']") as $case_xml) {
    //if (($bullet = _acadre_esdh_import_case($info, $case_xml)) !== FALSE) {
    //	$item['bullets'][] = $bullet;
      foreach ($case_xml->xpath("table[@name='Files']/table[@name='File']")as $case_file) {
	$filename_in = (string) array_shift($case_file->xpath("fields/field[@name='FileName']"));
	if (strlen($filename_in) > 0) {
	  $filetype = (string) array_shift($case_file->xpath("fields/field[@name='DocumentExtension']"));
	  $folder_path = implode('/', array(variable_get('os2web_meetings_path', ACADRE_MM_IMPORT_DIR), $info['filesfolder']));
	  if (strcasecmp($filetype, 'MSG') == 0) {
	    $folder_path .= '/' . $filename_in . '_attachments'; // e.g. [...]/1709477.MSG_attachments
	    $files = glob(drupal_realpath($folder_path) . '/*.pdf');
	    foreach ($files as $file) {
	      if (strpos(basename($file), 'eml.part1') === false) {//avoiding part1 file import - don't need it
		$item['cases'][] = array(
		  'sysid' => (int) array_shift($case_file->xpath("fields/field[@name='ID']")) . '_' . basename($file),
		  'uri' => $folder_path . '/' . basename($file),
		  'title' => 'Email_' . basename($file),
		  'filetype' => '.PDF',
		  'type' => 'Sag',
		);
	      }
	    }
	  } else {
	    $uri = _acadre_esdh_pdf_file_path($folder_path, $filename_in);
	    $item['cases'][] = array(
	      'sysid' => (int) array_shift($case_file->xpath("fields/field[@name='ID']")). '_' . basename(trim((string) array_shift($case_file->xpath("fields/field[@name='FileNr']")))),
	      'uri' => $uri,
	      'title' => trim((string) array_shift($case_file->xpath("fields/field[@name='Title']"))),
	      'filetype' => "." . (string) array_shift($case_file->xpath("fields/field[@name='DocumentExtension']")),
	      'type' => 'Sag',
	    );
	  }
	}
      }
    //}
  }
		
  // Process enclosures.
  foreach ($xml->xpath("table[@name='enclosure']") as $enclosure) {
    $filename_in = (string) array_shift($enclosure->xpath("fields/field[@name='filename']"));
    
    if (strlen($filename_in) > 0) {
      $filetype = (string) array_shift($enclosure->xpath("fields/field[@name='EnclosureFileType']"));
      $folder_path = implode('/', array(variable_get('os2web_meetings_path', ACADRE_MM_IMPORT_DIR),$info['filesfolder']));
      
      if (strcasecmp($filetype,'.msg') == 0){
      	$folder_path .= '/' . $filename_in . '_attachments';// e.g. [...]/1709477.MSG_attachments
	$files = glob(drupal_realpath($folder_path) . '/*.pdf');
	foreach($files as $file) {
	  if (strpos(basename($file),'eml.part1') === false){//avoiding part1 file import - don't need it
	    $item['enclosures'][] = array(
	      'sysid' => (int) array_shift($enclosure->xpath("fields/field[@name='sysid']")) . '_' . basename($file),
	      'uri' => $folder_path . '/' . basename($file),
	      'title' => 'Email_' . basename($file),
	      'filetype' => '.PDF',
				'type'=>'Bilag',	
	    );
	  }
	}
      } else {
	$uri = _acadre_esdh_pdf_file_path($folder_path, $filename_in);
	
	$item['enclosures'][] = array(
	  'sysid' => (int) array_shift($enclosure->xpath("fields/field[@name='sysid']")),
	  'uri' => $uri,
	  'title' => trim((string) array_shift($enclosure->xpath("fields/field[@name='name']"))),
	  'filetype' => (string) array_shift($enclosure->xpath("fields/field[@name='EnclosureFileType']")),
		'type'=>'Bilag'	,
	 );
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
function _acadre_esdh_import_bullet($info, $bullet_xml) {
  $bullet = array(
    'title' => (string) array_shift($bullet_xml->xpath("fields/field[@name='bulletname']")),
    'body' => (string) array_shift($bullet_xml->xpath("fields/field[@name='bulletcontent']")),
    'sysid' => (int) array_shift($bullet_xml->xpath("fields/field[@name='sysid']")),
  );
  if ($bullet['body'] === '') {
    return FALSE;
  }
  $bullet['body']=  _acadre_esdh_mm_improve_body_html($bullet['body']);

  $bullet += os2web_esdh_provider_default_bullet();
  return $bullet;
}

function _acadre_esdh_import_case($info, $bullet_xml) {

  $bullet = array(
    'title' => (string) array_shift($bullet_xml->xpath("fields/field[@name='Title']")),
		'body'=>((string) array_shift($bullet_xml->xpath("fields/field[@name='ClassificationPrimaryText']")))?(string) array_shift($bullet_xml->xpath("fields/field[@name='ClassificationPrimaryText']")):(string) array_shift($bullet_xml->xpath("fields/field[@name='ClassificationSecondaryText']")),	
    'sysid' => (int) array_shift($bullet_xml->xpath("fields/field[@name='ID']")),
  );
	
  if ($bullet['body'] === '') {
    return FALSE;
  }
	$bullet['body']=  _acadre_esdh_mm_improve_body_html($bullet['body']);
  $bullet += os2web_esdh_provider_default_bullet();
  return $bullet;
}

/**
 * Checks if a there is a PDF version of a file with a given path.
 *
 * @param string $path the path of the original file
 * @param string $name the name of the original file
 *
 * @return string $new_filepath the path of the PDF version of the file (if exists), else old filepath
 *
 */
function _acadre_esdh_pdf_file_path($path, $name){
  $name_arr = explode('.', $name);
  
  $pdf_path = $path . '/' . $name_arr[0] . '.PDF';
  if ($pdf_file_path=_acadre_esdh_similar_file_exists(drupal_realpath($pdf_path))){
 $pdf_file_path_parts=  pathinfo($pdf_file_path);  
      return $path . '/' . $pdf_file_path_parts['basename'] ;
  }
    
  else
    return $path . '/' . $name;
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
function _acadre_esdh_similar_file_exists($filename) {
  if (file_exists($filename)) {
    return $filename;
  }
  $lcase_filename = strtolower($filename);
  if (!empty($lcase_filename)){
    foreach (glob(dirname($filename) . '/*') as $file) {
      if (strtolower($file) == $lcase_filename) {
	return $file;
      }
    }
  }
  return FALSE;
}

/**
 * This function will set up the addenum connections for meetings.
 * @TODO: Rid this of drupal specific code.
 */
function _acadre_esdh_mm_order_addenums($drush = FALSE) {
  $rev_meetings = array(1458);
  // Find all meetings and gather meeting and agenda_ids.
  $nodes = entity_load('node', FALSE, array('type' => 'meeting'));
  $meetings = array();
  // Meetings as: $meetings[<meeting_id>][<system_id>][<node_id>] .
  $nids = array();
  foreach ($nodes as $node) {
    $addenum_to = field_get_items('node', $node, 'field_addenum_to');
    if (isset($addenum_to[0]['nid']) && is_numeric($addenum_to[0]['nid'])) {
      $nids[$node->nid] = $node->nid;
    }
    $meeting_id = array_shift(field_get_items('node', $node, 'field_meeting_id'));
    $system_id = array_shift(field_get_items('node', $node, 'field_system_id'));
    if (isset($meetings[$meeting_id['value']][$system_id['value']])) {
      // Duplicate meeting detected.
      watchdog('os2web_meetings', 'Duplicate import found for meeting %mid. Deleting.', array('%mid' => $meeting_id['value']), WATCHDOG_ERROR);
      node_delete($node->nid);
    }
    else {
      $meetings[$meeting_id['value']][$system_id['value']] = $node->nid;
    }
  }
  foreach ($meetings as $m_id => $meeting) {
    // Lowest system id first.
    ksort($meeting);
    if (in_array($m_id, $rev_meetings)) {
      $meeting = array_reverse($meeting);
    }
    // Lowest system id is primary.
    $primary = array_shift($meeting);
    while ($next = array_shift($meeting)) {
      // Set up references for addenum agendas.
      $node = $nodes[$next];
      $node->field_addenum_to[$node->language][0]['nid'] = $primary;
      node_save($node);
      unset($nids[$node->nid]);
      if ($drush === TRUE) {
        drush_log("Updated meeting $m_id..", 'ok');
      }
    }
  }
  foreach ($nids as $nid) {
    $node = node_load($nid);
    $node->field_addenum_to = array();
    node_save($node);
    if ($drush === TRUE) {
      drush_log("Resetting $nid..", 'ok');
    }
  }
}
function _acadre_esdh_mm_improve_body_html($data) {

	if (preg_match_all('#file:///[^"].*?"#', $data, $uri)){			
	foreach ($uri[0] as $file) {
		$file=str_replace('"','', $file);
		$uri_parts = explode('\\', $file);
		$filename = trim(array_pop($uri_parts));
		//echo $filename;
		$folder_name = array_pop($uri_parts);
	//copy file to public dir.
 		$file_realpath=drupal_realpath(implode('/', array(variable_get('os2web_meetings_path',ACADRE_MM_IMPORT_DIR),'images',$folder_name,$filename)));
		$dest_dir_realpath=drupal_realpath('public://').'/acadre_images/'.$folder_name;
		if (!is_file($dest_dir_realpath))
			exec('mkdir -p '.$dest_dir_realpath);
		exec ('cp '.$file_realpath.' '.$dest_dir_realpath.'/'.$filename);
			$new_uri=file_create_url(implode('/', array('public://','acadre_images',$folder_name,$filename)));
	 //modify uri
		$data = str_replace($file, $new_uri, $data);
		 
	}
	}	
	
return $data;
}
