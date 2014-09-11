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
 * Generates the form for bullet point attachment creating/modifying
 *
 * @param $form       the form to be created
 * @param $form_state the current state of the form
 *
 * @return $form the created form
*/
function os2dagsorden_create_agenda_bpa($form, $form_state){  
  $form[] = array(
    '#markup' => '<h1 class="title">' . t('Bullet point attachment') . '</h1>',
  );
  
  $form[] = array(
    '#markup' => '<div class="node">',
  );
  
  $form['bpa_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title:'),
    '#required' => TRUE,
  );
  
  $form['add_attachment'] = array(
    '#type' => 'vertical_tabs',
  );
   
  $form['attachment'] = array(
    '#type' => 'fieldset',
    '#title' => t('Attachment'),
    '#collapsible' => TRUE,
    '#description' => t('Add the text-based bullet point attachment to the bullet point.'),
    '#group' => 'add_attachment'
  );
  
  $form['attachment']['body'] = array(
    '#type'=>'text_format',
    '#title' => t('Body:'),
    '#format' => 'full_html',
    '#group' => 'add_attachment',
  );

  $form['bilag'] = array(
    '#type' => 'fieldset',
    '#title' => t('Bilag'),
    '#collapsible' => TRUE,
    '#description' => t('Enclose a file to the bullet point attachment.'),
    '#group' => 'add_attachment'
  );
  
  $form['bilag']['file'] = array(
    '#type' => 'managed_file',
    '#title' => t('Bilag file:'),
    '#group' => 'add_attachment',
    '#description' => 'Files must be less than <b>20 MB</b>.<br/>Allowed file types: <b>doc docx pdf</b>.',
    '#upload_validators' => array(
      'file_validate_extensions' => array('doc docx pdf'),
      // Pass the maximum file size in bytes
      'file_validate_size' => array(20*1024*1024*1024),//2 MB
    ),
  );
  
  //filling the fields if meeting_id is not empty
  if ($form_state['bpa_id']){
    $node = node_load($form_state['bpa_id']);
    $form['bpa_title']['#default_value'] = $node->title;
    
    if (field_get_items('node', $node, 'field_bpa_body')){
      $body_field = array_pop(field_get_items('node', $node, 'field_bpa_body'));
      $form['attachment']['body']['#default_value'] = $body_field['value'];
      $form['add_attachment']['#default_tab'] = 'edit-attachment';
    }
    
    if (field_get_items('node', $node, 'field_bpa_file')){
      $file_field = array_pop(field_get_items('node', $node, 'field_bpa_file'));
      $form['bilag']['file']['#default_value'] = $file_field['fid'];
      $form['add_attachment']['#default_tab'] = 'edit-bilag';
    }
  }
  
  $form[] = array(
    '#type'=>'submit',
    '#value' => t('Return to bullet point'),
    '#attributes' => array(
      'class' => array('form-back'),
    ),
    '#submit' => array('os2dagsorden_create_agenda_bpa_back'),
    '#limit_validation_errors' => array(),
  );
  $form[] = array(
    '#markup' => '&nbsp;',
  );
  $form['submit'] = array(
    '#type'=>'submit',
    '#value' => t('Save & return to bullet point'),
    '#attributes' => array(
      'class' => array('form-save-submit'),
    ),
    '#validate' => array('os2dagsorden_create_agenda_bpa_validate'),
    '#submit' => array('os2dagsorden_create_agenda_bpa_submit'),
  );
  
  $form[] = array(
    '#markup' => '</div>',
  );
  
  return $form;
}

/**
 * Custom validation of bullet point attachment form. Validates that only one of the option 
 * is chosen  - either file is uploaded or body of the bullet point attachmet is filled.
 *
 * @param $form       the form
 * @param $form_state the current state of the form
 *
 * @return none
*/
function os2dagsorden_create_agenda_bpa_validate($form, &$form_state) {
  $input = $form_state['input'];
  
  $body = $input['body']['value'];
  $bilag = $form_state['values']['file'];
  if (!empty($body) && $bilag != 0) {
    form_set_error('body', t('You cannot provide both file and the body text.<br/>Please choose one of the options.'));
  }
} 

/**
 * Saves the bullet point attachment - either by creating new or modifying the existing.
 * Performs call to os2dagsorden_create_agenda_add_bpa_to_bullet_point
 *
 * @param $form       the form
 * @param $form_state the current state of the form
 *
 * @return $node bullet point attachment
*/
function os2dagsorden_create_agenda_save_bpa($form, &$form_state){
  $input = $form_state['input'];
  
  $title = $input['bpa_title'];
  $body = $input['body']['value'];
  $bilag = $form_state['values']['file'];

  if (!$form_state['bpa_id']){
    //node creating
    $node = new stdClass();
    $node->type = "bullet_point_attachment";
    $node->language = LANGUAGE_NONE;
    node_object_prepare($node);
  } else {
    $node = node_load($form_state['bpa_id']);
  }  
  
  $node->title = $title;
  $node->field_bpa_body['und'][0]['value'] = $body;
  
  if ($bilag != 0){
    //resaving file permanently
    $bilag = file_load($bilag);
    $bilag->status = FILE_STATUS_PERMANENT;
    $bilag->display = 1;
    file_save($bilag);
    
    $node->field_bpa_file['und'][0] = (array) $bilag;
  } else {
    if (field_get_items('node', $node, 'field_bpa_file')){
      $bilag = array_pop(field_get_items('node', $node, 'field_bpa_file'));
      $to_del_file = file_load($bilag['fid']); 
      unset($node->field_bpa_file['und']);
      file_delete($to_del_file);
    }
  }
  
  node_save($node);
  
  os2dagsorden_create_agenda_add_bpa_to_bullet_point($form_state['bullet_point_id'], $node->nid);
  
  return $node;
}

/**
 * Adds the bullet points attachment to the bullet point, if it has not been added before.
 *
 * @param $bullet_point_id id of the bullet point
 * @param $bpa_id          id of the bullet point attachment
 *
 * @return none
*/
function os2dagsorden_create_agenda_add_bpa_to_bullet_point($bullet_point_id, $bpa_id){
  $bullet_point = node_load($bullet_point_id);
  if (field_get_items('node', $bullet_point, 'field_ref_attachment')){
    $bpas = field_get_items('node', $bullet_point, 'field_ref_attachment');
    foreach($bpas as $bpa){
      if ($bpa['target_id'] == $bpa_id)
	return;//no need to readd
    }
  }
  
  $bullet_point->field_ref_attachment['und'][]['target_id'] = $bpa_id;
  node_save($bullet_point);
}

/**
 * Helper functions, bullet point attachment form submit. Calls os2dagsorden_create_agenda_save_bpa
 * returns to the previous page of multiform (bullet point creation/modification).
 *
 * @param $form       the form to be created
 * @param $form_state the current state of the form
 *
 * @return none
*/
function os2dagsorden_create_agenda_bpa_submit($form, &$form_state){
  os2dagsorden_create_agenda_save_bpa($form, $form_state);
  
  $form_state['page_num'] = 2;
  $form_state['rebuild'] = TRUE;
}

/**
 * Helper functions, returns to the previous page of multiform (bullet point creation/modification).
 *
 * @param $form       the form to be created
 * @param $form_state the current state of the form
 *
 * @return none
*/
function os2dagsorden_create_agenda_bpa_back($form, &$form_state){
  $form_state['page_num'] = 2;
  $form_state['rebuild'] = TRUE;
}