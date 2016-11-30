<?php
/**
 * @file
 * Code for the OS2Web Meeting Views - Kommende moder i mine udvalg
 */
 
/////////////////////////////////////////header START /////////////////////////////////////////
function os2dagsorden_meeting_views_coming_meetings_help_text(){
print '<div class="help-button" id="os2dagsorden_meeting_views_coming_meetings_help" aria-label="' . variable_get('os2dagsorden_upcoming_meetings_help_text', 'Her vises de kommende 5 møder i "Mine udvalg".
  Det vil sige udvalg som man enten er medlem af eller følger. Udvalgene kan ses i boksene 
  "Medlem af" og "Jeg følger" i højremenuen. Der er ikke en dagsorden tilgængelig før 
  status er angivet til Dagsorden eller Dagsorden+.') . '"></div>';
}
/////////////////////////////////////////header END /////////////////////////////////////////

/////////////////////////////////////////PAGE start /////////////////////////////////////////
function os2dagsorden_meeting_views_coming_meetings_fields_meeting_has_sp($meeting_id){
  if (variable_get('os2dagsorden_meetings_views_last_8_show_meeting_title', TRUE)) {
    os2dagsorden_meeting_views_common_meeting_has_sp_else_empty($meeting_id);
  }
}

function os2dagsorden_meeting_views_coming_meetings_fields_meeting_has_notes($meeting_id){
  if (variable_get('os2dagsorden_meetings_views_last_8_show_meeting_title', TRUE)) {
    os2dagsorden_meeting_views_common_meeting_has_notes_else_empty($meeting_id);
  }
}

function os2dagsorden_meeting_views_coming_meetings_fields_meeting_is_closed($meeting_id){
  if (variable_get('os2dagsorden_meetings_views_last_8_show_meeting_is_closed', FALSE))
    os2dagsorden_meeting_views_common_meeting_is_closed_else_empty($meeting_id);
}

function os2dagsorden_meeting_views_coming_meetings_fields_meeting_title($data){
  if (variable_get('os2dagsorden_meetings_views_last_8_show_meeting_title', TRUE)) {
    os2dagsorden_meeting_views_common_meeting_title_listed($data);
  }
}

function os2dagsorden_meeting_views_coming_meetings_fields_meeting_location($meeting_id){
   if (variable_get('os2dagsorden_meetings_views_last_8_show_meeting_location', true)) {
      os2dagsorden_meeting_views_common_meeting_location($meeting_id);
   }
}
/////////////////////////////////////////PAGE END /////////////////////////////////////////

/////////////////////////////////////////FILTER START /////////////////////////////////////////
function os2dagsorden_meeting_views_coming_meetings_filter_in_my_list($tid){
  return os2dagsorden_meeting_views_common_filter_in_my_list($tid);
}
/////////////////////////////////////////FILTER END /////////////////////////////////////////