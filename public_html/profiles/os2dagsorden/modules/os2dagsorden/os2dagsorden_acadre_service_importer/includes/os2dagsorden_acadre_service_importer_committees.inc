<?php

/**
 * Helper function. Processes the committees xml.
 * Delegates to create committees.
 *
 * @param mixed $xml_file xml file
 *
 * @return none
 */
function _os2dagsorden_acadre_service_importer_process_committees($xml_file){
    foreach ($xml_file as $row) {
        $xml_data = array(
	    'sub_id' =>$row->Id,
            'committee_name' => $row->Name,
        );
	os2dagsorden_acadre_service_importer_create_committee($xml_data);
    }
}

/**
 * Helper function. Creates/updates the committee
 *
 * @param mixed $xml_data xml
 *
 * @return the id of created/updated entry.
 */
function os2dagsorden_acadre_service_importer_create_committee($xml_data){
    //getting committee by sub ID
    $term = _os2dagsorden_acadre_service_importer_get_committee_by_subid($xml_data['sub_id']);
    
    //no success, getting committee by name and setting sub id
    if (!isset($term)){
	$term = array_pop(taxonomy_get_term_by_name($xml_data['committee_name'], 'os2web_meetings_tax_committee'));
	if (isset($term))
	    $term->field_os2web_meetings_com_subid['und'][]['value'] = $xml_data['sub_id'];	
    }
	
    //no success, creating new committee and setting sub id
    if (!isset($term)){
	$vid = db_select('taxonomy_vocabulary', 'tv')
            ->fields('tv', array('vid'))
            ->condition('machine_name', 'os2web_meetings_tax_committee') 
            ->execute()
            ->fetchField();
        $term = new stdClass();
        $term->vid = $vid;
	$term->field_os2web_meetings_com_subid['und'][]['value'] = $xml_data['sub_id'];	
    }

    $term->name = $xml_data['committee_name'];
    if (!isset($term->field_os2web_meetings_com_shname['und']) || empty($term->field_os2web_meetings_com_shname['und'][0]['value']))
         $term->field_os2web_meetings_com_shname['und'][0]['value'] = $xml_data['committee_name'];
    if (!isset($term->field_os2web_meetings_com_abbr['und']) || empty($term->field_os2web_meetings_com_abbr['und'][0]['value']))      
        $term->field_os2web_meetings_com_abbr['und'][0]['value'] =  $xml_data['committee_name'];
        
    taxonomy_term_save($term);
    return $term->tid;
}

/**
 * Helper function. Returns the committee based on its sub id.
 *
 * @param int $com_subid committee sub id
 *
 * @return the committee term, if found.
 */
function _os2dagsorden_acadre_service_importer_get_committee_by_subid($com_subid){
    $vid = db_select('taxonomy_vocabulary', 'tv')
            ->fields('tv', array('vid'))
            ->condition('machine_name', 'os2web_meetings_tax_committee')
            ->execute()
            ->fetchField();
	    
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'taxonomy_term')
            ->propertyCondition('vid', $vid)
            ->fieldCondition('field_os2web_meetings_com_subid', 'value', intval($com_subid), '=');
	    
    $result = $query->execute();
    if (isset($result['taxonomy_term'])) {   
        $tids = array_keys($result['taxonomy_term']);
        $tid = reset($tids);
        $term = taxonomy_term_load($tid);
        return $term;
    }    
}
