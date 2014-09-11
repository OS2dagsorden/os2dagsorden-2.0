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
 
function os2dagsorden_create_agenda_meeting_simple($form, $form_state, $meeting_id) {  
  $form[] = array(
    '#markup' => '<h1 class="title">' . t('Meeting') . '</h1>',
  );
  
  //adding general fields
  $form = os2dagsorden_create_agenda_meeting_form_add_general_fields($form);
  
  //filling the fields if meeting_id is not empty
  if (!$meeting_id)
    $meeting_id = $form_state['meeting_id'];//if meeting id is empty, try to fill it with form_state meeting_id value
    
  if ($meeting_id) {
    $form_state['meeting_id'] = $meeting_id;//saving for usage in the submit function
    
    $node = node_load($meeting_id);
    
    //filling general fields
    $form = os2dagsorden_create_agenda_meeting_form_fill_general_fields($form, $node);
  }
  
  //finishing form
  $form['#attached']['css'] = array(
    drupal_get_path('module', 'os2dagsorden_create_agenda') . '/css/form_theme.css',
  );
  
  $form['save_meeting'] = array(
    '#type' => 'submit',
    '#attributes' => array(
      'class' => array('form-save-submit'),
    ),
    '#value' => t('Save meeting'),
    '#submit' => array('os2dagsorden_create_agenda_meeting_simple_submit'),
  );
  $form[] = array(
    '#markup' => '</div>',
  );
  
  return $form;
}

function os2dagsorden_create_agenda_save_meeting_simple($form, $form_state){
  $node = os2dagsorden_create_agenda_populate_meeting_general($form, $form_state);
  
  $input = $form_state['input'];
  $node = os2dagsorden_access_helper_set_meeting_status_and_save($node, $input['status']);
  
  return $node;
}

function os2dagsorden_create_agenda_meeting_simple_submit($form, &$form_state){
  $node = os2dagsorden_create_agenda_save_meeting_simple($form, $form_state);
  $start_date = $form_state['input']['start_date']['date'];
  $start_date = date_create_from_format("d/m/Y", $start_date);
  
  $form_state['redirect'] = 'calendar-field-date/month/' . $start_date->format('Y') . '-' . $start_date->format('m');
}