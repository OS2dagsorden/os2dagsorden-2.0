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
    $vid = db_select('taxonomy_vocabulary', 'tv')
            ->fields('tv', array('vid'))
            ->condition('machine_name', 'os2web_meetings_tax_committee')
            ->execute()
            ->fetchField();

    //marking all committees as disabled, they will be enabled by the loop below
    $terms = taxonomy_get_tree($vid);
    foreach ($terms as $term) {
        $term->field_os2web_meetings_com_active['und'][0]['value'] = 0;
        taxonomy_term_save($term);
    }

    foreach ($xml_file as $row) {
        $xml_data = array(
	        'sub_id' => (string) $row->Id,
            'committee_name' => (string) $row->Name,
            'state' => (string) $row->State,
            'active' => (string) $row->Active
        );

        //create/update committee if missing
	    os2dagsorden_acadre_service_importer_create_committee($xml_data, $vid);
    }
}

/**
 * Helper function. Creates/updates the committee
 *
 * @param mixed $xml_data xml
 *
 * @return the id of created/updated entry.
 */
function os2dagsorden_acadre_service_importer_create_committee($xml_data, $vid){
    //getting committee by sub ID
    $term = _os2dagsorden_access_helper_get_committee_by_subid_and_name($xml_data['sub_id'], $xml_data['committee_name']);

    //no success, creating new committee and setting sub id
    if (!$term){
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

    //see if we need to enable term or its parent
    if ($xml_data['state'] == 'Aktivt' && $xml_data['active'] == 'true') {
        $parents = taxonomy_get_parents($term->tid);
        if (empty($parents)) {
            $term->field_os2web_meetings_com_active['und'][0]['value'] = 1;
        } else {
            foreach($parents as $parent) {
                $parent->field_os2web_meetings_com_active['und'][0]['value'] = 1;
                taxonomy_term_save($parent);
            }
        }
    }

    taxonomy_term_save($term);
    return $term->tid;
}
