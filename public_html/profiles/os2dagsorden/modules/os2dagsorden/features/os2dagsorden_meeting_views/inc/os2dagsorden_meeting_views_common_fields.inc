 <?php
/**
 * @file
 * Code for the OS2Web Meeting Views - common/shared field
 */

/////////////////////////////////////////meeting START /////////////////////////////////////////
function os2dagsorden_meeting_views_common_meeting_has_sp_else_empty($meeting_id){
  if (os2dagsorden_access_helper_meeting_has_speaker_paper($meeting_id))
    print '<div class="indicator-has-speaker-paper"></div>';
  else
    print '<div class="indicator-empty"></div>';
}

function os2dagsorden_meeting_views_common_meeting_has_sp($meeting_id){
  if (os2dagsorden_access_helper_meeting_has_speaker_paper($meeting_id))
    print '<div class="indicator-has-speaker-paper"></div>';
}

function os2dagsorden_meeting_views_common_meeting_has_notes_else_empty($meeting_id){
  $annotations = os2dagsorden_annotator_get_notes_by_meeting_id($meeting_id);
  if (!empty($annotations))
    print '<div class="indicator-has-notes"></div>';
  else
    print '<div class="indicator-empty"></div>';
}

function os2dagsorden_meeting_views_common_meeting_has_notes($meeting_id){
  $annotations = os2dagsorden_annotator_get_notes_by_meeting_id($meeting_id);
  if (!empty($annotations))
    print '<div class="indicator-has-notes"></div>';
}

function os2dagsorden_meeting_views_common_meeting_is_closed_else_empty($meeting_id){
  if (os2dagsorden_access_helper_meeting_has_closed_bullet_point($meeting_id))
    print '<div class="indicator-unlocked"></div>';
  else
    print '<div class="indicator-empty"></div>';
}

function os2dagsorden_meeting_views_common_meeting_is_closed($meeting_id){
  if (os2dagsorden_access_helper_meeting_has_closed_bullet_point($meeting_id))
    print '<div class="indicator-unlocked"></div>';
}

function os2dagsorden_meeting_views_common_meeting_title_listed($data){
  $title = '';
  $committee= taxonomy_term_load($data->_field_data['nid']['entity']->field_os2web_meetings_committee['und'][0]['tid']);
  //if (variable_get('os2dagsorden_use_abbr', TRUE) && isset($data->_field_data['nid']['entity']->field_os2web_meetings_abbr['und']) && !empty($data->_field_data['nid']['entity']->field_os2web_meetings_abbr['und'][0]['value']))
  if (variable_get('os2dagsorden_use_abbr', TRUE) && isset($committee->field_os2web_meetings_com_shname['und']) && !empty($committee->field_os2web_meetings_com_shname['und'][0]['value']))
   $title = $committee->field_os2web_meetings_com_shname['und'][0]['value'] ;//$data->_field_data['nid']['entity']->field_os2web_meetings_abbr['und'][0]['value'];
  else
    $title = $data->_field_data['nid']['entity']->title;

  os2dagsorden_meeting_views_common_meeting_has_sp($data->_field_data['nid']['entity']->nid);
  os2dagsorden_meeting_views_common_meeting_has_notes($data->_field_data['nid']['entity']->nid);

  echo $title;
}

function  os2dagsorden_meeting_views_common_meeting_committee($meeting_id){
    $meeting = node_load($meeting_id);
    $meeting_committee=field_get_items('node', $meeting, 'field_os2web_meetings_committee');
    $short_name=taxonomy_term_load($meeting_committee[0]["tid"])->field_os2web_meetings_com_shname['und'][0]['value'];
    if (!empty($short_name))
       print taxonomy_term_load($meeting_committee[0]["tid"])->field_os2web_meetings_com_shname['und'][0]['value'];
    else
        print taxonomy_term_load($meeting_committee[0]["tid"])->name;
}
function  os2dagsorden_meeting_views_common_meeting_location($meeting_id){
    $meeting = node_load($meeting_id);
    $meeting_committee=field_get_items('node', $meeting, 'field_os2web_meetings_location');
    if ($meeting_committee) {

      $location = taxonomy_term_load($meeting_committee[0]["tid"])->name;
      print $location;
    }
    else {
      print '';
    }

}
/////////////////////////////////////////meeting END/////////////////////////////////////////

/////////////////////////////////////////bullet point START/////////////////////////////////////////
function os2dagsorden_meeting_views_common_bullet_point_has_notes($bp_id){
  $annotations = os2dagsorden_annotator_get_notes_by_bullet_point_id($bp_id);
  if (!empty($annotations))
    print '<div class="indicator-has-notes"></div>';
}

function os2dagsorden_meeting_views_common_bullet_point_has_sp($bp_id){
  if(os2dagsorden_access_helper_bullet_point_has_speaker_paper($bp_id, variable_get('os2dagsorden_shared_speaker_paper', TRUE)))
    print '<div class="indicator-has-speaker-paper"></div>';
}
/////////////////////////////////////////bullet point END/////////////////////////////////////////


/////////////////////////////////////////FILTER START /////////////////////////////////////////

/**
 * Checks if the current committee is in the user's list
 * Returns INVERTED VALUE
 */
function os2dagsorden_meeting_views_common_filter_in_my_list($tid){
  $user = os2dagsorden_access_helper_get_user();
  //checking user rights
  if (!os2dagsorden_access_helper_check_user_can_see_meeting('', $tid)) {
		return TRUE;
  }
  if (!empty($user->field_user_committee)) { //is part of the committee
    foreach ($user->field_user_committee['und'] as $user_committee_id) {
      if ($tid == $user_committee_id['tid']) {
	return FALSE;
      }
    }
  }

  if (!empty($user->field_follows_committee)) { //follows committee
    foreach ($user->field_follows_committee['und'] as $user_committee_id) {
      if ($tid == $user_committee_id['tid']) {
	return FALSE;
      }
    }
  }

  if (!empty($user->field_follows_committee_plus)) { //follows committee PLUS
    foreach ($user->field_follows_committee_plus['und'] as $user_committee_id) {
      if ($tid == $user_committee_id['tid']) {
	return FALSE;
      }
    }
  }

  if (!empty($user->field_follows_committee_pp)) { //follow committee PLUS PLUS
    foreach ($user->field_follows_committee_pp['und'] as $user_committee_id) {
      if ($tid == $user_committee_id['tid']) {
	return FALSE;
      }
    }
  }

  return TRUE;
}
/////////////////////////////////////////FILTER END /////////////////////////////////////////