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
    $term = _os2dagsorden_access_helper_get_committee_by_subid_and_name($xml_data['sub_id'], $xml_data['committee_name']);

    //no success, creating new committee and setting sub id
    if (!$term){
	$vid = db_select('taxonomy_vocabulary', 'tv')
            ->fields('tv', array('vid'))
            ->condition('machine_name', 'os2web_meetings_tax_committee') 
            ->execute()
            ->fetchField();
        $term = new stdClass();
        $term->vid = $vid;
	$term->field_os2web_meetings_com_subid['und'][]['value'] = $xml_data['sub_id'];
	$term->name = $xml_data['committee_name'];
    }

    if (!isset($term->field_os2web_meetings_com_shname['und']) || empty( $term->field_os2web_meetings_com_shname['und'][0]['value']))
        $term->field_os2web_meetings_com_shname['und'][0]['value'] = $xml_data['committee_name'];
    if (!isset($term->field_os2web_meetings_com_abbr['und']) || empty($term->field_os2web_meetings_com_abbr['und'][0]['value']))
       $term->field_os2web_meetings_com_abbr['und'][0]['value'] =  $xml_data['committee_name'];
    if (!isset($term->field_os2web_meetings_com_cat['und']) || empty($term->field_os2web_meetings_com_cat['und'][0]['value']))
       $term->field_os2web_meetings_com_cat['und'][0]['value'] =  'pol';
    taxonomy_term_save($term);
    return $term->tid;
}