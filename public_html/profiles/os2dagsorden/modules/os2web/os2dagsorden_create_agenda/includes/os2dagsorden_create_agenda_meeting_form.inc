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
 * Add to the form the field both used for simple and full agenda meeting creation.
 *
 * @param $form the form which should be modified
 *
 * @return $form the form with new field
*/
function os2dagsorden_create_agenda_meeting_form_add_general_fields($form){  
  $form[] = array(
    '#markup' => '<div class="node">',
  );

  $form['title'] = array(
    '#type' => 'textfield', 
    '#title' => t('Title:'), 
    '#size' => 60, 
    '#maxlength' => 128, 
    '#required' => TRUE,
    '#description' => 'Full title of the meeting',
  );
  
  $form['short_title'] = array(
    '#type' => 'textfield', 
    '#title' => t('Short title:'), 
    '#size' => 40, 
    '#maxlength' => 35, 
    '#required' => TRUE,
    '#description' => 'Maximum 35 characters. <br/>Short title will be used in places with limited contatiner width, e.g, front page views',
  );
  $form['status'] = array(
    '#type' => 'select',
    '#title' => t('Status:'), 
    '#required' => TRUE,
    '#options' => array(
	'Planlagt' => t('Planlagt'),
	'Ændret' => t('Ændret'),
	'Aflyst' => t('Aflyst'),
	'Referat' => t('Referat'),
	'Dagsorden' => t('Dagsorden'),
    ),
    '#multiple' => FALSE,
    '#default_value' => 'Planlagt',
  );
  $form['meeting_category'] = array(
    '#type' => 'select', 
    '#title' => t('Meeting category:'), 
    '#required' => TRUE,
    '#options' => array(
	'pol' => t('Political'),
	'org' => t('Organizational'),
    ),
    '#multiple' => FALSE,
    '#default_value' => 'pol',
  );
  $form['hex_color'] = array(
    '#type' => 'jquery_colorpicker',
    '#title' => t('Meeting color:'),
    '#default_value' => '757575',
    '#description' => 'Choose a color for meeting, will be used to for marking the meeting in the calendar',
  );
  $form[] = array(
    '#markup' => '<div class="clearfix">',
  );
  $form['start_date'] = array(
    '#type' => 'date_popup',
    '#title' => t('Start Date:'), 
    '#size' => 10, 
    '#required' => TRUE,
    '#date_format' => 'd/m/Y H:i',
  );
  $form['end_date'] = array(
    '#type' => 'date_popup',
    '#title' => t('End Date:'), 
    '#size' => 10, 
    '#required' => FALSE,
    '#date_format' => 'd/m/Y H:i',
  );
  $form[] = array(
    '#markup' => '</div>',
  );
  
  $loc_voc = taxonomy_vocabulary_machine_name_load('lokation');
  $loc_terms = taxonomy_get_tree($loc_voc->vid);
  $loc_select = array();
  foreach ($loc_terms as $loc_term) {
    $loc_select[$loc_term->tid] = $loc_term->name;
  }
  $form['location'] = array(
    '#type' => 'select',
    '#title' => t('Location:'), 
    '#required' => FALSE,
    '#options' => $loc_select,
    '#multiple' => FALSE,
    '#empty_value' => 0,
  );
  
  $com_voc = taxonomy_vocabulary_machine_name_load('committee');
  $com_terms = taxonomy_get_tree($com_voc->vid);
  $com_select = array();
  foreach ($com_terms as $com_term) {
    $com_select[$com_term->tid] = $com_term->name;
  }
  $form['committee'] = array(
    '#type' => 'select',
    '#title' => t('Committee:'), 
    '#required' => TRUE,
    '#options' => $com_select,
    '#multiple' => FALSE,
  );
  
  $user_select = array();
  $users = entity_load('user');
  foreach($users as $user) {
    $user_select[$user->uid] = $user->field_user_full_name['und'][0]['value'] . " ($user->name)";
  }
  $form['participants'] = array(
    '#type' => 'select',
    '#title' => t('Participants:'), 
    '#required' => FALSE,
    '#options' => $user_select,
    '#multiple' => TRUE,
    '#attributes' => array('class' => array('improved-multi-select')),
  );
  
  //finishing form
  $form['#attached']['css'] = array(
    drupal_get_path('module', 'os2dagsorden_create_agenda') . '/css/form_theme.css',
  );
  
  return $form;
}

/**
 * Fill the general fields of the form with the values from meeting. Both used for simple and full agenda meeting creation.
 *
 * @param $form the form which should be filled
 * @param $node the meeting node, where the information should be taken from
 *
 * @return $form the form with filled fields
*/
function os2dagsorden_create_agenda_meeting_form_fill_general_fields($form, $node){
    $form['title']['#default_value'] = $node->title;
    
    if (field_get_items('node', $node, 'field_title_short')){
      $short_title_field = array_pop(field_get_items('node', $node, 'field_title_short'));
      $form['short_title']['#default_value'] = $short_title_field['safe_value'];
    }
    
    $status_field = array_pop(field_get_items('node', $node, 'field_meeting_status'));
    $form['status']['#default_value'] = $status_field['safe_value'];
    
    if (field_get_items('node', $node, 'field_hex')){
      $hex_field = array_pop(field_get_items('node', $node, 'field_hex'));
      $form['hex_color']['#default_value'] = $hex_field['safe_value'];
    }
    
    if (field_get_items('node', $node, 'field_meeting_category')){
      $category_field = array_pop(field_get_items('node', $node, 'field_meeting_category'));
      $form['meeting_category']['#default_value'] = $category_field['value'];
    }
    
    $date_field = array_pop(field_get_items('node', $node, 'field_date'));
    $form['start_date']['#default_value'] = $date_field['value'];
    if ($date_field['value2'] != $date_field['value'])
      $form['end_date']['#default_value'] = $date_field['value2'];
    
    $committee_field = array_pop(field_get_items('node', $node, 'field_committee'));
    $form['committee']['#default_value'] = $committee_field['tid'];
    
    if (field_get_items('node', $node, 'field_location')){
      $location_field = array_pop(field_get_items('node', $node, 'field_location'));
      $form['location']['#default_value'] = $location_field['tid'];
    }
    
    if (field_get_items('node', $node, 'field_meeting_participants')){
      $participants_field = array_pop(field_get_items('node', $node, 'field_meeting_participants'));
      $participants = explode(',',$participants_field['safe_value']);
      foreach ($participants as $el => $value){
	$value = explode(' ', $value); //array
	$value = end($value);//(name)
	$username = substr($value, 1, strlen($value)-2);//name
	$account = user_load_by_name($username);
	$selection[] = $account->uid;
      }
      $form['participants']['#default_value'] = $selection;
    }
    
    return $form;
}

/**
 * Populates the meeting node (either new or existing depending on the content) with the information taken from the form.
 *
 * @param $form       the form where information is taken from
 * @param $form_state the current state of the form
 *
 * @return populated but unsaved(!) node
*/
function os2dagsorden_create_agenda_populate_meeting_general($form, $form_state){
  $input = $form_state['input'];
  
  //input extraction
  $title = $input['title'];
  $short_title = $input['short_title'];
  $status = $input['status'];
  $meeting_category = $input['meeting_category'];
  $hex_color = $input['hex_color'];
  $start_date = $input['start_date']['date'];
  $start_time = $input['start_date']['time'];
  $end_date = $input['end_date']['date'];
  $end_time = $input['end_date']['time'];
  $loc_tid = $input['location'];
  $com_tid = $input['committee'];
  $participants = $input['participants'];

  if (!$form_state['meeting_id']){
    //node creating
    $node = new stdClass();
    $node->type = "meeting";
    $node->language = LANGUAGE_NONE;
    node_object_prepare($node);    
  } else {
    $node = node_load($form_state['meeting_id']);
  }
  
  //node population
  $node->title = $title;
  $node->field_title_short['und'][0]['value'] = $short_title;
  $node->field_meeting_status['und'][0]['value'] = $status;
  $start_datetime = date_create_from_format("d/m/Y H:i", $start_date . ' ' . $start_time);
  $node->field_date['und'][0]['value'] = $start_datetime->format('Y-m-d H:i:s');
  $node->field_committee['und'][0]['tid'] = $com_tid;
  
  $node->field_meeting_category['und'][0]['value'] = $meeting_category;
  $node->field_hex['und'][0]['value'] = $hex_color;

  if (!empty($end_date)){
    $end_datetime = date_create_from_format("d/m/Y H:i", $end_date . ' ' . $end_time);
    $node->field_date['und'][0]['value2'] = $end_datetime->format('Y-m-d H:i:s');
  } else {//same as start date - default
    $node->field_date['und'][0]['value2'] = $start_datetime->format('Y-m-d H:i:s');
  }
  
  $node->field_location['und'][0]['tid'] = $loc_tid;
  
  if ($participants){
    $participant_str = '';
    foreach ($participants as $participant => $value){
      $user = user_load($value);
      $participant_str .= $user->field_user_full_name['und'][0]['value'] . " ($user->name), ";
    }
    //removing last coma
    $node->field_meeting_participants['und'][0]['value'] = substr($participant_str, 0, strlen($participant_str)-2);
  } else 
    $node->field_meeting_participants['und'][0]['value'] = '';
  
  return $node;
}