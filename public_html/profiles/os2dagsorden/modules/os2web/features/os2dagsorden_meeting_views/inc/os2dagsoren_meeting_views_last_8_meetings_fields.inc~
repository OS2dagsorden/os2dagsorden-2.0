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
