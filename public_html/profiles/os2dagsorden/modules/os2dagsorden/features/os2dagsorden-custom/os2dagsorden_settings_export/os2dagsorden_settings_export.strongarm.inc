<?php
/**
 * @file
 * os2dagsorden_settings_export.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function os2dagsorden_settings_export_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'clean_url';
  $strongarm->value = '1';
  $export['clean_url'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'file_default_scheme';
  $strongarm->value = 'private';
  $export['file_default_scheme'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'file_private_path';
  $strongarm->value = 'sites/default/files/acadre';
  $export['file_private_path'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'jquery_update_compression_type';
  $strongarm->value = 'min';
  $export['jquery_update_compression_type'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'jquery_update_jquery_cdn';
  $strongarm->value = 'google';
  $export['jquery_update_jquery_cdn'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'jquery_update_jquery_version';
  $strongarm->value = '1.5';
  $export['jquery_update_jquery_version'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2dagsorden_adlib_api_cron';
  $strongarm->value = '0 */3 * * *';
  $export['os2dagsorden_adlib_api_cron'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2dagsorden_collapse_menu';
  $strongarm->value = 'true';
  $export['os2dagsorden_collapse_menu'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2dagsorden_expand_all_bullets';
  $strongarm->value = 0;
  $export['os2dagsorden_expand_all_bullets'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2dagsorden_expand_attachment';
  $strongarm->value = 'false';
  $export['os2dagsorden_expand_attachment'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2dagsorden_group_closed_bullet_points';
  $strongarm->value = 'true';
  $export['os2dagsorden_group_closed_bullet_points'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2dagsorden_hidden_agenda_committee';
  $strongarm->value = '28';
  $export['os2dagsorden_hidden_agenda_committee'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2dagsorden_importer_cron';
  $strongarm->value = '0 */3 * * *';
  $export['os2dagsorden_importer_cron'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2dagsorden_latest_meetings_view_mode';
  $strongarm->value = 'all';
  $export['os2dagsorden_latest_meetings_view_mode'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2dagsorden_meetings_search_show_meeting_committee';
  $strongarm->value = 1;
  $export['os2dagsorden_meetings_search_show_meeting_committee'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2dagsorden_meetings_search_show_meeting_status';
  $strongarm->value = 0;
  $export['os2dagsorden_meetings_search_show_meeting_status'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2dagsorden_meetings_views_last_8_show_meeting_committee';
  $strongarm->value = 0;
  $export['os2dagsorden_meetings_views_last_8_show_meeting_committee'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2dagsorden_meetings_views_last_8_show_meeting_location';
  $strongarm->value = 0;
  $export['os2dagsorden_meetings_views_last_8_show_meeting_location'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2dagsorden_participants_delimeter';
  $strongarm->value = '<br/>';
  $export['os2dagsorden_participants_delimeter'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2dagsorden_pdf2htmlex_cron';
  $strongarm->value = '0 */3 * * *';
  $export['os2dagsorden_pdf2htmlex_cron'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2dagsorden_pws_use_local_copy';
  $strongarm->value = 0;
  $export['os2dagsorden_pws_use_local_copy'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2dagsorden_pws_v_acadregroups_url';
  $strongarm->value = '706dwweb01.intern.syddjurs.dk/OS2DagsordenDataService/OS2DagsordenDataService.asmx/GetXMLView?viewName=V_web_AcadreGroups';
  $export['os2dagsorden_pws_v_acadregroups_url'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2dagsorden_pws_v_meetinggroups_url';
  $strongarm->value = '706dwweb01.intern.syddjurs.dk/OS2DagsordenDataService/OS2DagsordenDataService.asmx/GetXMLView?viewName=V_web_MeetingGroups';
  $export['os2dagsorden_pws_v_meetinggroups_url'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2dagsorden_pws_v_meetings_url';
  $strongarm->value = '706dwweb01.intern.syddjurs.dk/OS2DagsordenDataService/OS2DagsordenDataService.asmx/GetXMLView?viewName=V_web_Meetings';
  $export['os2dagsorden_pws_v_meetings_url'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2dagsorden_send_notification_committee';
  $strongarm->value = '138,28,136,59,62,59,64,53,54,56,57,63,58,51,55,61,68,69,42,28,71,36,44,53,67,72,66,34';
  $export['os2dagsorden_send_notification_committee'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2dagsorden_send_timespan_of_notification';
  $strongarm->value = '10';
  $export['os2dagsorden_send_timespan_of_notification'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2dagsorden_show_bilag';
  $strongarm->value = 1;
  $export['os2dagsorden_show_bilag'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2dagsorden_show_meeting_category';
  $strongarm->value = '';
  $export['os2dagsorden_show_meeting_category'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2dagsorden_show_meeting_committee';
  $strongarm->value = 0;
  $export['os2dagsorden_show_meeting_committee'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2dagsorden_show_meeting_enddate';
  $strongarm->value = 0;
  $export['os2dagsorden_show_meeting_enddate'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2dagsorden_show_meeting_type';
  $strongarm->value = 1;
  $export['os2dagsorden_show_meeting_type'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2dagsorden_show_participants_afbud';
  $strongarm->value = 1;
  $export['os2dagsorden_show_participants_afbud'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2dagsorden_show_print_icon';
  $strongarm->value = 1;
  $export['os2dagsorden_show_print_icon'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2dagsorden_show_samlet dokument link';
  $strongarm->value = 0;
  $export['os2dagsorden_show_samlet dokument link'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2dagsorden_show_samlet_dokument_link';
  $strongarm->value = 1;
  $export['os2dagsorden_show_samlet_dokument_link'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2web_adlib_url';
  $strongarm->value = 'http://706CAR01/ExponentWSA/ExponentWSA.asmx?wsdl';
  $export['os2web_adlib_url'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2web_meetings_approved_committee';
  $strongarm->value = '138,28,136,59,62,59,64,53,54,56,57,63,58,51,55,61,68,69,42,28,71,36,44,53,67,72,66,34';
  $export['os2web_meetings_approved_committee'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2web_meetings_import_closed_agenda';
  $strongarm->value = 1;
  $export['os2web_meetings_import_closed_agenda'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2web_meetings_path';
  $strongarm->value = 'private://';
  $export['os2web_meetings_path'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'site_name';
  $strongarm->value = 'OS2Dagsorden';
  $export['site_name'] = $strongarm;

  return $export;
}
