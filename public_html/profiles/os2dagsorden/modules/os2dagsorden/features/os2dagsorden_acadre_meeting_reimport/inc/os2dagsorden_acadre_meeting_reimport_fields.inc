<?php
/**
 * @file
 * Code for the OS2Dagsorden Acadre meeting reimport field
 */

/////////////////////////////////////////PAGE START /////////////////////////////////////////
function os2dagsorden_acadre_meeting_reimport_fields_filter_criteria($meeting_id){
  $import_dir = drupal_realpath(variable_get('os2web_meetings_path', ACADRE_MM_IMPORT_DIR));
  $skip_meeting = TRUE;
  
  $node = node_load($meeting_id);
  if (isset($node->field_meeting_acadre_version['und'])){
	  foreach($node->field_meeting_acadre_version['und'] as $acadre_version){
	  	$has_files = glob($import_dir . "/*" . $acadre_version['value']);
	    if (is_array($has_files) && array_pop(glob($import_dir . "/*" . $acadre_version['value']))){
	      $skip_meeting = FALSE;
	      break;
	    }
	  }
  }

  return $skip_meeting;
}

function os2dagsorden_acadre_meeting_reimport_fields_esdh_provider($meeting_id){
  print 'Acadre';
}

function os2dagsorden_acadre_meeting_reimport_fields_run_reimport($meeting_id){
  print 'Run reimport';
}
/////////////////////////////////////////PAGE END /////////////////////////////////////////