<?php

/**
 * Helper function. Processes the meetings xml.
 * Delegates to create meeings, unpublish meetings, create committee function based on controllers.
 *
 * @param mixed $xml_file xml file
 *
 * @return none
 */
function _os2dagsorden_acadre_service_importer_process_meetings($xml_file){
    foreach ($xml_file as $row) {
        $xml_data = array(
            'meeting_id' => $row->Id,
            'title' => $row->Name,
            'committee_id' => $row->CommitteeId,
            'meeting_start_date' => $row->Start,
            'meeting_end_date' => $row->Finish,
	    'location' => $row->Location,
            'active' => $row->Active,
        );

        if ($xml_data['active'] == 'true') {
	    $term = _os2dagsorden_access_helper_get_committee_by_subid_and_name($xml_data['committee_id']);
            if (isset($term))
	      _os2dagsorden_acadre_service_importer_create_meeting($xml_data, $term->tid);
        }
        else {
            _os2dagsorden_acadre_service_importer_unpublish_meeting($xml_data);
        }
    }
}

/**
 * Helper function. Creates/updates the meeting
 *
 * @param array $xml_data entry parameters
 * @param int   $tid      committee id.
 *
 * @return none
 */
function _os2dagsorden_acadre_service_importer_create_meeting($xml_data, $tid) {
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
            ->fieldCondition('field_os2web_meetings_id', 'value', intval($xml_data['meeting_id']), '=');

    $result = $query->execute();
    if (!isset($result['node'])) {//no meetings found, create a new one
        $node = new stdClass();
	$node->type = "os2web_meetings_meeting";
	$node->language = LANGUAGE_NONE;
	node_object_prepare($node);
	$node->field_os2web_meetings_type[$node->language][0]['value'] = 'Planlagt';
    } else {//meeting found, loading existing one
	$nids = array_keys($result['node']);
        $node = reset(entity_load('node', $nids));
    }

    //changing params only if status is Planlagt, which is either a freshly created meeting or the one importerted before - we don't care.
    //It's safe to update those values
    if ($node->field_os2web_meetings_type[$node->language][0]['value'] == 'Planlagt'){
	$node->title = $xml_data['title'];
	$node->field_os2web_meetings_id[$node->language][0]['value'] = $xml_data['meeting_id'];
	$node->field_os2web_meetings_abbr[$node->language][0]['value'] = $xml_data['title'];
	$node->field_os2web_meetings_system_id[$node->language][0]['value'] = '0';
	$node->field_os2web_meetings_committee[$node->language][0]['tid'] = $tid;
	$node->field_os2web_meetings_location[$node->language][0]['tid'] = _os2dagsorden_acadre_service_importer_get_location($xml_data['location']);
    
	if (!empty($xml_data['meeting_start_date'])) {
	    $node->field_os2web_meetings_date[$node->language][0]['value'] = $xml_data['meeting_start_date'];
	}
	
	if (!empty($xml_data['meeting_end_date'])) {
	    $node->field_os2web_meetings_date[$node->language][0]['value2'] = $xml_data['meeting_end_date'];
	} else {//to represent that there is no end date
	    $node->field_os2web_meetings_date[$node->language][0]['value2'] = $xml_data['meeting_start_date'];
	}

	node_submit($node);
	node_save($node);
    }
}

/**
 * Helper function. Marks the meeting as unpublished.
 *
 * @param array $xml_data entry params
 *
 * @return none
 */
function _os2dagsorden_acadre_service_importer_unpublish_meeting($xml_data) {
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
            ->fieldCondition('field_os2web_meetings_id', 'value', intval($xml_data['meeting_id']), '=');

    $result = $query->execute();
    if (isset($result['node'])) {
        $nids = array_keys($result['node']);
        $node = reset(entity_load('node', $nids));

        if ($node->status == NODE_PUBLISHED) {
            node_unpublish_action($node);
            node_save($node);
	}
    }
}

/**
 * Helper function. Finds the location term based on the name, if none found new term is created.
 *
 * @param string $location name of the location.
 *
 * @return term tid
 */
function _os2dagsorden_acadre_service_importer_get_location($location){
    $location_term = array_pop(taxonomy_get_term_by_name($location, 'os2web_meetings_tax_location'));
    if (!isset($location_term)){
	$vid = db_select('taxonomy_vocabulary', 'tv')
	    ->fields('tv', array('vid'))
	    ->condition('machine_name', 'os2web_meetings_tax_location')
	    ->execute()
	    ->fetchField();

	$location_term = new stdClass();
	$location_term->vid = $vid;
	$location_term->name = $location;
	taxonomy_term_save($location_term);
    }

    return $location_term->tid;
}
