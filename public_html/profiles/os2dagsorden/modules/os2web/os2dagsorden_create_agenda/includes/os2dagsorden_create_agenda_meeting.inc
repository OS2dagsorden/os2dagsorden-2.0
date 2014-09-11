<?php

/**
 * os2dagsorden_create_agenda
 *
 * PHP version 5
 *
 * @category OS2Dagsorden
 * @package  Os2dagsorden_Create_Agenda
 * @author   Stanislav Kutasevits <stan@bellcom.dk>
 * @license  http://www.gnu.org/licenses/gpl-2.0.html GNU General Public License, version 2
 * @link     http://bellcom.dk
 */

 /**
 * Generates the form for meeting creating/modifying
 *
 * @param $form       the form to be created
 * @param $form_state the current state of the form
 *
 * @return $form the created form
*/
function os2dagsorden_create_agenda_meeting($form, $form_state, $meeting_id) {
  if (!empty($form_state['page_num']) && $form_state['page_num'] == 2) {
    return os2dagsorden_create_agenda_bullet_point($form, $form_state, $bullet_point_id);
  } else if (!empty($form_state['page_num']) && $form_state['page_num'] == 3) {
    return os2dagsorden_create_agenda_bpa($form, $form_state);
  } 
  $form_state['page_num'] = 1;
  
  $form[] = array(
    '#markup' => '<h1 class="title">' . t('Meeting') . '</h1>',
  );
  
  //adding general fields
  $form = os2dagsorden_create_agenda_meeting_form_add_general_fields($form);
  
  //adding other fields
  $form['description_opened'] = array(
    '#title' => t('Description opened:'),
    '#type' => 'managed_file',
    '#description' => 'Files must be less than <b>2 MB</b>.<br/>Allowed file types: <b>doc docx pdf</b>.',
    '#upload_validators' => array(
      'file_validate_extensions' => array('doc docx pdf'),
      // Pass the maximum file size in bytes
      'file_validate_size' => array(2*1024*1024*1024),//2 MB
    ),
  );
  $form['description_closed'] = array(
    '#title' => t('Description closed:'),
    '#type' => 'managed_file',
    '#description' => 'Files must be less than <b>2 MB</b>.<br/>Allowed file types: <b>doc docx pdf</b>.',
    '#upload_validators' => array(
      'file_validate_extensions' => array('doc docx pdf'),
      // Pass the maximum file size in bytes
      'file_validate_size' => array(2*1024*1024*1024),//2 MB
    ),
  );
  
  $form['agenda'] = array(
    '#type' => 'fieldset', 
    '#title' => t('Agenda'), 
    '#collapsible' => TRUE, 
    '#collapsed' => FALSE,
  );
  
  //filling the fields if meeting_id is not empty
  if (!$meeting_id)
    $meeting_id = $form_state['meeting_id'];//if meeting id is empty, try to fill it with form_state meeting_id value
    
  if ($meeting_id) {
    $form_state['meeting_id'] = $meeting_id;//saving for usage in the submit function
    
    $node = node_load($meeting_id);
    
    //filling general fields
    $form = os2dagsorden_create_agenda_meeting_form_fill_general_fields($form, $node);
    
    //filling other fields
    if (field_get_items('node', $node, 'field_meeting_description')){
      $description_opened_field = array_pop(field_get_items('node', $node, 'field_meeting_description'));
      $form['description_opened']['#default_value'] = $description_opened_field['fid'];
    }
    
    if (field_get_items('node', $node, 'field_meeting_description_closed')){
      $description_closed_field = array_pop(field_get_items('node', $node, 'field_meeting_description_closed'));
      $form['description_closed']['#default_value'] = $description_closed_field['fid'];
    }
    
    if (field_get_items('node', $node, 'field_ref_bullet_points')){
      $bullet_points = field_get_items('node', $node, 'field_ref_bullet_points');
      foreach($bullet_points as $bp){
	$bp = node_load($bp['target_id']);
	$form['agenda'][] = array(
	  '#markup' => '<div id="fsdfsdfdsfdsfsdfds" class="create-agenda-list-item">',
	);	
	$form['agenda'][] = array(
	  '#markup' => '<span class="create-agenda-edit-delete-container">',
	);
	$form['agenda'][] = array(
	  '#type' => 'image_button',
	  '#button_type' => 'submit-edit',
	  '#src' => drupal_get_path('theme', 'os2dagsorden_theme') . '/img/icon_edit.png',
	  '#name' => 'edit_' . $bp->nid,
	  '#submit' => array('os2dagsorden_create_agenda_meeting_submit_add_edit_bullet_point'),
	  '#bp_nid' => $bp->nid,
	);
	$form['agenda'][] = array(
	  '#type' => 'image_button',
	  '#button_type' => 'submit-delete',
	  '#src' => drupal_get_path('theme', 'os2dagsorden_theme') . '/img/icon_delete.png',
	  '#name' => 'delete_' . $bp->nid,
	  '#submit' => array('os2dagsorden_create_agenda_meeting_submit_delete_bullet_point'),
	  '#bp_nid' => $bp->nid,
	  '#ajax' => array(
	    'callback' => 'os2dagsorden_create_agenda_bullet_point_delete_ajax',
	    'wrapper' => 'edit-agenda',
	    'method' => 'replace',
	    'effect' => 'fade',
	  ),
	);
	
	$form['agenda'][] = array(
	  '#markup' => '</span>',//'<span class="create-agenda-edit-delete-container">',
	);
	
	$form['agenda'][] = array(
	  '#markup' => '<span class="create-agenda-privacy-container">',
	);
	$closed_field = array_pop(field_get_items('node', $bp, 'field_bul_point_closed'));
	if ($closed_field['value'])
	  $form['agenda'][] = array(
	    '#markup' => '<span class="indicator-form-unlocked"></span>',
	  );
	else
	  $form['agenda'][] = array(
	    '#markup' => '<span class="indicator-form-empty"></span>',
	  );
	
	$personal_field = array_pop(field_get_items('node', $bp, 'field_bul_point_personal'));
	if ($personal_field['value'])
	  $form['agenda'][] = array(
	    '#markup' => '<span class="indicator-form-personal"></span>',
	  );
	else
	  $form['agenda'][] = array(
	    '#markup' => '<span class="indicator-form-empty"></span>',
	  );
	  
	$form['agenda'][] = array(
	  '#markup' => '</span>',//'<span class="create-agenda-privacy-container">',
	);
	
	$form['agenda'][] = array(
	  '#markup' => $bp->title,
	);
	$form['agenda'][] = array(
	  '#markup' => '</div>',//'<div class="create-agenda-list-item">',
	);
      }
    }
  }
  
  //finishing form
  $form['#attached']['css'] = array(
    drupal_get_path('module', 'os2dagsorden_create_agenda') . '/css/form_theme.css',
  );
  $form['#attached']['js'] = array(
    drupal_get_path('module', 'os2dagsorden_create_agenda') . '/js/form_js.js',
  );
  
  $form['save_meeting'] = array(
    '#type' => 'submit',
    '#attributes' => array(
      'class' => array('form-save-submit'),
    ),
    '#value' => t('Save meeting'),
    '#submit' => array('os2dagsorden_create_agenda_meeting_submit'),
  );
  $form[] = array(
    '#markup' => '&nbsp;',
  );
  $form['save_meeting_and_add_bullet_point'] = array(
    '#type' => 'submit', 
    '#attributes' => array(
      'class' => array('form-add-submit'),
    ),
    '#value' => t('Save & Add bullet point'),
    '#submit' => array('os2dagsorden_create_agenda_meeting_submit_add_edit_bullet_point'),
  );
  $form[] = array(
    '#markup' => '</div>',
  );
  
  return $form;
}

/**
 * Callback for deleting bullet point
 *
 * @param $form       the form
 * @param $form_state the current state of the form
 *
 * @return none
*/
function os2dagsorden_create_agenda_bullet_point_delete_ajax($form, $form_state) {
  return $form['agenda'];
}

/**
 * Saves the meeting - either by creating new or modifying the existing
 *
 * @param $form       the form
 * @param $form_state the current state of the form
 *
 * @return $node meeting
*/
function os2dagsorden_create_agenda_save_meeting($form, $form_state){
  $node = os2dagsorden_create_agenda_populate_meeting_general($form, $form_state);
  
  $input = $form_state['input'];
  //file extraction
  $description_opened = $form_state['values']['description_opened'];
  $description_closed = $form_state['values']['description_closed'];
  
  if($description_opened != 0){
    //resaving file permanently
    $description_opened = file_load($description_opened);
    $description_opened->status = FILE_STATUS_PERMANENT;
    $description_opened->display = 1;
    file_save($description_opened);

    $node->field_meeting_description['und'][0] = (array) $description_opened;
  } else {
    if (field_get_items('node', $node, 'field_meeting_description')){
      $description_opened_field = array_pop(field_get_items('node', $node, 'field_meeting_description'));
      $to_del_file = file_load($description_opened_field['fid']); 
      unset($node->field_meeting_description['und']);
      file_delete($to_del_file);
    }
  }
  
  if($description_closed != 0){
    //resaving file permanently
    $description_closed = file_load($description_closed);
    $description_closed->status = FILE_STATUS_PERMANENT;
    $description_closed->display = 1;
    file_save($description_closed);
    
    $node->field_meeting_description_closed['und'][0] = (array) $description_closed;
  } else {
    if (field_get_items('node', $node, 'field_meeting_description_closed')){
      $description_closed_field = array_pop(field_get_items('node', $node, 'field_meeting_description_closed'));
      $to_del_file = file_load($description_closed_field['fid']); 
      unset($node->field_meeting_description_closed['und']);
      file_delete($to_del_file);
    }
  }
  
  $node = os2dagsorden_access_helper_set_meeting_status_and_save($node, $input['status']);
  
  return $node;
}

/**
 * Helper functions, meeting form submit. Calls meeting save and redirects to the calendar view.
 *
 * @param $form       the form
 * @param $form_state the current state of the form
 *
 * @return none
*/
function os2dagsorden_create_agenda_meeting_submit($form, &$form_state) {  
  $node = os2dagsorden_create_agenda_save_meeting($form, $form_state);
  $start_date = $form_state['input']['start_date']['date'];
  $start_date = date_create_from_format("d/m/Y", $start_date);
  
  $form_state['redirect'] = 'calendar-field-date/month/' . $start_date->format('Y') . '-' . $start_date->format('m');
}

/**
 * Calls os2dagsorden_create_agenda_save_meeting and redirects to bullet point creation/modification page.
 *
 * @param $bullet_point_id id of the bullet point
 * @param $bpa_id          id of the bullet point attachment
 *
 * @return none
*/
function os2dagsorden_create_agenda_meeting_submit_add_edit_bullet_point($form, &$form_state) {
  $node = os2dagsorden_create_agenda_save_meeting($form, $form_state);
  
  $form_state['meeting_id'] = $node->nid;
  //if empty - will be treated as new node creation
  $form_state['bullet_point_id'] = $form_state['triggering_element']['#bp_nid'];
  
  $form_state['page_num'] = 2;
  $form_state['rebuild'] = TRUE;
}

/**
 * Helper functions to delete bullet point.
 *
 * @param $form       the form
 * @param $form_state the current state of the form
 *
 * @return none
*/
function os2dagsorden_create_agenda_meeting_submit_delete_bullet_point($form, &$form_state) {
  $node = os2dagsorden_create_agenda_save_meeting($form, $form_state);
  
  $bp_id = $form_state['triggering_element']['#bp_nid'];
  os2dagsorden_create_agenda_remove_bullet_point_from_meeting($node->nid, $bp_id);
  
  node_delete($bp_id);
  
  $form_state['page_num'] = 1;
  $form_state['rebuild'] = TRUE;
}

/**
 * Removes the bullet point from the meeting
 *
 * @param $bullet_point_id id of the bullet point
 * @param $bpa_id          id of the bullet point attachment
 *
 * @return $meeting meeting
*/
function os2dagsorden_create_agenda_remove_bullet_point_from_meeting($meeting_id, $bullet_point_id){
  $meeting = node_load($meeting_id);
  if (field_get_items('node', $meeting, 'field_ref_bullet_points')){
    $bullet_points = field_get_items('node', $meeting, 'field_ref_bullet_points');
    foreach($bullet_points as $key => $bp){
      if ($bp['target_id'] == $bullet_point_id){
	unset($meeting->field_ref_bullet_points['und'][$key]);
      }
    }
  }
  
  $meeting->field_ref_bullet_points['und'] = array_values($meeting->field_ref_bullet_points['und']);
  node_save($meeting);
}