<?php
/**
 * @file
 * Code for the OS2Web Meeting Views - Seneste 8 moder view.
 */

/////////////////////////////////////////header START /////////////////////////////////////////
function os2dagsorden_meeting_views_last_8_meetings_help_text(){
  print '<div class="help-button" title="Her vises de seneste 8 møder i alle mødefora. 
  Der er ikke et referat tilgængeligt før status er angivet til Referat eller Referat+."></div>';
}
/////////////////////////////////////////header END /////////////////////////////////////////

/////////////////////////////////////////BLOCK ALL MEETING START/////////////////////////////////////////
function os2dagsorden_meeting_views_last_8_meetings_block_all_meetings_access(){
  if (!os2dagsorden_access_helper_get_user()){
    return FALSE;
  }

  if (variable_get('os2dagsorden_latest_meetings_view_mode', 'all') == 'all')
    return TRUE;
  else {//check if 'Mine' display returns no results - if that is the case, return 'All' display anyways
    $view = views_get_view_result(seneste_8_m_der_i_de_st_ende_politiske_udvalg_, 'block_1');
    $result = count($view);
    if (!$result) {
      return TRUE;
    }
  }
  return FALSE;
}
/////////////////////////////////////////BLOCK ALL MEETING  END/////////////////////////////////////////

/////////////////////////////////////////BLOCK MY MEETINGS START/////////////////////////////////////////
function os2dagsorden_meeting_views_last_8_meetings_block_my_meetings_access(){
  if (!os2dagsorden_access_helper_get_user()){
    return FALSE;
  }

  if (variable_get('os2dagsorden_latest_meetings_view_mode', 'all') == 'mine')
    return TRUE;
  else
    return FALSE;
}

function os2dagsorden_meeting_views_last_8_meetings_block_my_meetings_filter($meeting_id){
  //get meeting committee tid
  $meeting = node_load($meeting_id);
  $meeting_committee_tid = $meeting->field_committee['und'][0]['tid'];

  //get full user
  $full_user = os2dagsorden_access_helper_get_user();

  //check if user meeting committee in 'member of'
  if (isset($full_user->field_user_committee['und'])){
    foreach($full_user->field_user_committee['und'] as $com){
      if ($meeting_committee_tid == $com['tid']){
	return FALSE;
      }
    }
  }
  //check if user meeting committee in 'follows'
  if (isset($full_user->field_follows_committee['und'])){
    foreach($full_user->field_follows_committee['und'] as $com){
      if ($meeting_committee_tid == $com['tid']){
	return FALSE;
      }
    }
  }
  //check if user meeting committee in 'follows plus'
  if (isset($full_user->field_follows_committee_plus['und'])){
    foreach($full_user->field_follows_committee_plus['und'] as $com){
      if ($meeting_committee_tid == $com['tid']){
	return FALSE;
      }
    }
  }

  //none of the above, filter entry out
  return TRUE;
}
/////////////////////////////////////////BLOCK MY MEETINGS END/////////////////////////////////////////

/////////////////////////////////////////PAGE START/////////////////////////////////////////
function os2dagsorden_meeting_views_last_8_meetings_fields_meeting_has_sp($meeting_id){
  os2dagsorden_meeting_views_common_meeting_has_sp_else_empty($meeting_id);
}

function os2dagsorden_meeting_views_last_8_meetings_fields_meeting_has_notes($meeting_id){
  os2dagsorden_meeting_views_common_meeting_has_notes_else_empty($meeting_id);
}

function os2dagsorden_meeting_views_last_8_meetings_fields_meeting_title($data){
 os2dagsorden_meeting_views_common_meeting_title_listed($data);
}
/////////////////////////////////////////PAGE END /////////////////////////////////////////
