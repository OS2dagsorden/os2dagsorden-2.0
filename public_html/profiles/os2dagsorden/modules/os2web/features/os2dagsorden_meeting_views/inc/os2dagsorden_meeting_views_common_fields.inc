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

function os2dagsorden_meeting_views_common_meeting_title_listed($data){
  $title = '';
  if (isset($data->_field_data['nid']['entity']->field_title_short['und']))
    $title = $data->_field_data['nid']['entity']->field_title_short['und'][0]['value'];
  else 
    $title = $data->_field_data['nid']['entity']->title;

  //logic for touch devices
  if (os2dagsorden_access_helper_is_touch()){
    if (mb_strlen($title) > 30)
      echo mb_substr($title, 0, 27) . '...';
    else
      echo $title;
  } else {//desktop device
    if (mb_strlen($title) > 42)
      echo mb_substr($title, 0, 39) . '...';
    else
      echo $title;
  }
}
function os2dagsorden_meeting_views_common_meeting_title_short_listed($data){
   $title = '';
  if (isset($data->_field_data['nid']['entity']->field_title_short['und']))
     $title = $data->_field_data['nid']['entity']->field_title_short['und'][0]['value'];
   else 
     $title = $data->_field_data['nid']['entity']->title;
 
   //logic for touch devices
   if (os2dagsorden_access_helper_is_touch()){
     if (mb_strlen($title) > 11)
      echo mb_substr($title, 0, 8) . '...';
     else
       echo $title;
   } else {//desktop device
     if (mb_strlen($title) > 24)
      echo mb_substr($title, 0, 21) . '...';
     else
       echo $title;
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
  if(os2dagsorden_access_helper_bullet_point_has_speaker_paper($bp_id))
    print '<div class="indicator-has-speaker-paper"></div>';
}
/////////////////////////////////////////bullet point END/////////////////////////////////////////
