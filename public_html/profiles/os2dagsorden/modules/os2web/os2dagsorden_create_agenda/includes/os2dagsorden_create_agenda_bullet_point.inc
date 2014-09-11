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
 * Generates the form for bullet point creating/modifying
 *
 * @param $form       the form to be created
 * @param $form_state the current state of the form
 *
 * @return $form the created form
*/
function os2dagsorden_create_agenda_bullet_point($form, $form_state, $bullet_point_id) {  
  $form[] = array(
    '#markup' => '<h1 class="title">' . t('Bullet point') . '</h1>',
  );
  
  $form[] = array(
    '#markup' => '<div class="node">',
  );
  
  $form['bp_title'] = array(
    '#type' => 'textfield', 
    '#title' => t('Title:'), 
    '#size' => 60, 
    '#maxlength' => 128, 
    '#required' => TRUE,
    '#description' => t('Full title of the bullet point'),
  );
  
  $form['closed'] = array(
    '#type' => 'checkbox',
    '#title' => t('Closed'),
        '#field_suffix' => '<div class="indicator-form-unlocked"></div>',
  );
  
  $form['personal'] = array(
    '#type' => 'checkbox',
    '#title' => t('Personal'),
    '#field_suffix' => '<div class="indicator-form-personal"></div>',
  );
  
  $form['bpas'] = array(
    '#type' => 'fieldset', 
    '#title' => t('Bullet point attachments'), 
    '#collapsible' => TRUE, 
    '#collapsed' => FALSE,
  );
  
  //filling the fields if meeting_id is not empty
  if ($form_state['bullet_point_id']){
    $node = node_load($form_state['bullet_point_id']);
    $form['bp_title']['#default_value'] = $node->title;
    
    $closed_field = array_pop(field_get_items('node', $node, 'field_bul_point_closed'));
    $form['closed']['#default_value'] = $closed_field['value'];
    
    $personal_field = array_pop(field_get_items('node', $node, 'field_bul_point_personal'));
    $form['personal']['#default_value'] = $personal_field['value'];
    
    if (field_get_items('node', $node, 'field_ref_attachment')){
      $bpas = field_get_items('node', $node, 'field_ref_attachment');
      foreach($bpas as $bpa){
	$bpa = node_load($bpa['target_id']);
	$form['bpas'][] = array(
	  '#markup' => '<div class="create-agenda-list-item">',
	);
	$form['bpas'][] = array(
	  '#markup' => '<span class="create-agenda-edit-delete-container">',
	);
	
	$form['bpas'][] = array(
	  '#type' => 'image_button',
	  '#button_type' => 'submit-edit',
	  '#src' => drupal_get_path('theme', 'os2dagsorden_theme') . '/img/icon_edit.png',
	  '#name' => 'edit_' . $bpa->nid,
	  '#submit' => array('os2dagsorden_create_agenda_bullet_point_submit_add_edit_bpa'),
	  '#bpa_nid' => $bpa->nid,
	);
	$form['bpas'][] = array(
	  '#type' => 'image_button',
	  '#button_type' => 'submit-delete',
	  '#src' => drupal_get_path('theme', 'os2dagsorden_theme') . '/img/icon_delete.png',
	  '#name' => 'delete_' . $bpa->nid,
	  '#submit' => array('os2dagsorden_create_agenda_bullet_point_submit_delete_bpa'),
	  '#bpa_nid' => $bpa->nid,
	  '#ajax' => array(
	    'callback' => 'os2dagsorden_create_agenda_bpa_delete_ajax',
	    'wrapper' => 'edit-bpas',
	    'method' => 'replace',
	    'effect' => 'fade',
	  ),
	);
	$form['bpas'][] = array(
	  '#markup' => '</span>',//'<span class="create-agenda-edit-delete-container">',
	);
	
	$form['bpas'][] = array(
	  '#markup' => $bpa->title,
	);
	$form['bpas'][] = array(
	  '#markup' => '</div>',//'<div class="create-agenda-list-item">',
	);
      }
    }
  }
  
  //finishing form
  $form[] = array(
    '#type'=>'submit',
    '#value' => t('Return to meeting'),
    '#attributes' => array(
      'class' => array('form-back'),
    ),
    '#submit' => array('os2dagsorden_create_agenda_bullet_point_back'),
    '#limit_validation_errors' => array(),
  );
  $form[] = array(
    '#markup' => '&nbsp;',
  );
  $form['save_bullet_point'] = array(
    '#type'=>'submit',
    '#value' => t('Save & return to meeting'),
    '#attributes' => array(
      'class' => array('form-save-submit'),
    ),
    '#submit' => array('os2dagsorden_create_agenda_bullet_point_submit'),
  );
  $form[] = array(
    '#markup' => '&nbsp;',
  );
  $form['save_bullet_point_and_add_bpa'] = array(
    '#type'=>'submit',
    '#value' => t('Save & Add bullet point attachment'),
    '#attributes' => array(
      'class' => array('form-add-submit'),
    ),
    '#submit' => array('os2dagsorden_create_agenda_bullet_point_submit_add_edit_bpa'),
  );
  $form['#attached']['js'] = array(
    drupal_get_path('module', 'os2dagsorden_create_agenda') . '/js/form_js.js',
  );
  
  $form[] = array(
    '#markup' => '</div>',
  );
  
  return $form;
}

/**
 * Callback for deleting bullet point attachments
 *
 * @param $form       the form
 * @param $form_state the current state of the form
 *
 * @return none
*/
function os2dagsorden_create_agenda_bpa_delete_ajax($form, $form_state) {
  return $form['bpas'];
}

/**
 * Saves the bullet point - either by creating new or modifying the existing
 * calls os2dagsorden_create_agenda_add_bullet_point_to_meeting
 *
 * @param $form       the form
 * @param $form_state the current state of the form
 *
 * @return $node bullet point
*/
function os2dagsorden_create_agenda_save_bullet_point($form, &$form_state){
  $input = $form_state['input'];
  
  $title = $input['bp_title'];
  $closed = $form_state['values']['closed'];
  $personal = $form_state['values']['personal'];

    
  if (!$form_state['bullet_point_id']){
    //node creating
    $node = new stdClass();
    $node->type = "bullet_point";
    $node->language = LANGUAGE_NONE;
    node_object_prepare($node);
  } else {
    $node = node_load($form_state['bullet_point_id']);
  }  
  
  $node->title = $title;
  $node->field_bul_point_closed['und'][0]['value'] = $closed;
  $node->field_bul_point_personal['und'][0]['value'] = $personal;
  
  node_save($node);
  
  os2dagsorden_create_agenda_add_bullet_point_to_meeting($form_state['meeting_id'], $node->nid);
  
  return $node;
}

/**
 * Adds the bullet point to the meeting, if it has not been added before.
 *
 * @param $meeting_id      id of the meeting
 * @param $bullet_point_id id of the bullet point
 *
 * @return none
*/
function os2dagsorden_create_agenda_add_bullet_point_to_meeting($meeting_id, $bullet_point_id){
  $meeting = node_load($meeting_id);
  if (field_get_items('node', $meeting, 'field_ref_bullet_points')){
    $bullet_points = field_get_items('node', $meeting, 'field_ref_bullet_points');
    foreach($bullet_points as $bp){
      if ($bp['target_id'] == $bullet_point_id)
	return;//no need to readd
    }
  }
  
  $meeting->field_ref_bullet_points['und'][]['target_id'] = $bullet_point_id;
  node_save($meeting);
}

/**
 * Removes the bullet point attachment from the bullet point
 *
 * @param $bullet_point_id id of the bullet point
 * @param $bpa_id          id of the bullet point attachment
 *
 * @return none
*/
function os2dagsorden_create_agenda_remove_bpa_from_bullet_point($bullet_point_id, $bpa_id){
  $bullet_point = node_load($bullet_point_id);
  if (field_get_items('node', $bullet_point, 'field_ref_attachment')){
    $bpas = field_get_items('node', $bullet_point, 'field_ref_attachment');
    foreach($bpas as $key => $bpa){
      if ($bpa['target_id'] == $bpa_id){
	unset($bullet_point->field_ref_attachment['und'][$key]);
      }
    }
  }
  
  $bullet_point->field_ref_attachment['und'] = array_values($bullet_point->field_ref_attachment['und']);
  node_save($bullet_point);
}

/**
 * Helper functions, bullet point form submit. Calls saving and controls the form rebuild (page switching) - returning back to meeting view.
 *
 * @param $form       the form
 * @param $form_state the current state of the form
 *
 * @return none
*/
function os2dagsorden_create_agenda_bullet_point_submit($form, &$form_state) {
  $node = os2dagsorden_create_agenda_save_bullet_point($form, $form_state);
  
  $form_state['page_num'] = 1;
  $form_state['rebuild'] = TRUE;
}

/**
 * Helper functions, bullet point attachment form submit. Calls saving and controls the form rebuild (page switching) - 
 * redirecting to bullet point attachment creation/editing page
 *
 * @param $form       the form
 * @param $form_state the current state of the form
 *
 * @return none
*/
function os2dagsorden_create_agenda_bullet_point_submit_add_edit_bpa($form, &$form_state) {
  $node = os2dagsorden_create_agenda_save_bullet_point($form, $form_state);
  
  $form_state['bullet_point_id'] = $node->nid;
  //if empty - will be treated as new node creation
  $form_state['bpa_id'] = $form_state['triggering_element']['#bpa_nid'];

  $form_state['page_num'] = 3;
  $form_state['rebuild'] = TRUE;
}

/**
 * Helper functions to delete bullet point attachment.
 *
 * @param $form       the form
 * @param $form_state the current state of the form
 *
 * @return none
*/
function os2dagsorden_create_agenda_bullet_point_submit_delete_bpa($form, &$form_state) {
  $node = os2dagsorden_create_agenda_save_bullet_point($form, $form_state);
  
  $bpa_id = $form_state['triggering_element']['#bpa_nid'];
  os2dagsorden_create_agenda_remove_bpa_from_bullet_point($node->nid, $bpa_id);
  
  node_delete($bpa_id);
  
  $form_state['page_num'] = 2;
  $form_state['rebuild'] = TRUE;
}

/**
 * Helper functions redirects back to meeting view.
 *
 * @param $form       the form
 * @param $form_state the current state of the form
 *
 * @return none
*/
function os2dagsorden_create_agenda_bullet_point_back($form, &$form_state) {
  $form_state['page_num'] = 1;
  $form_state['rebuild'] = TRUE;
}