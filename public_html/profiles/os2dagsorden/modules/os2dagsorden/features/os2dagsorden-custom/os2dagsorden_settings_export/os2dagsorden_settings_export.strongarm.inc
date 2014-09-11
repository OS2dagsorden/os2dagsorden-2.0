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
  $strongarm->name = 'os2dagsorden_default_meeting_cateroty';
  $strongarm->value = 'pol';
  $export['os2dagsorden_default_meeting_cateroty'] = $strongarm;

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
  $strongarm->name = 'os2dagsorden_expand_attachment_onload';
  $strongarm->value = 1;
  $export['os2dagsorden_expand_attachment_onload'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2dagsorden_expand_bilags';
  $strongarm->value = 'true';
  $export['os2dagsorden_expand_bilags'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2dagsorden_expand_cases';
  $strongarm->value = 'false';
  $export['os2dagsorden_expand_cases'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2dagsorden_follows_committee_send_notification';
  $strongarm->value = 0;
  $export['os2dagsorden_follows_committee_send_notification'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2dagsorden_group_closed_bullet_points';
  $strongarm->value = 'false';
  $export['os2dagsorden_group_closed_bullet_points'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2dagsorden_hidden_agenda_committee';
  $strongarm->value = '';
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
  $strongarm->value = 0;
  $export['os2dagsorden_meetings_search_show_meeting_committee'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2dagsorden_meetings_search_show_meeting_status';
  $strongarm->value = 1;
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
  $strongarm->name = 'os2dagsorden_my_committees_block_title';
  $strongarm->value = 'Adgang lukket dagsorden';
  $export['os2dagsorden_my_committees_block_title'] = $strongarm;

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
  $strongarm->value = '*/15 * * * *';
  $export['os2dagsorden_pdf2htmlex_cron'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2dagsorden_pdf2htmlex_path';
  $strongarm->value = '/usr/bin/pdf2htmlEX';
  $export['os2dagsorden_pdf2htmlex_path'] = $strongarm;

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
  $strongarm->name = 'os2dagsorden_referat_send_timespan_of_notification';
  $strongarm->value = '70';
  $export['os2dagsorden_referat_send_timespan_of_notification'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2dagsorden_sager_group_title';
  $strongarm->value = 'Sagsdokumenter';
  $export['os2dagsorden_sager_group_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2dagsorden_send_email_body';
  $strongarm->value = 'Til !user

Du abonnerer på !committee.
Der er publiceret !meeting_type til !meeting_name !meeting_date.';
  $export['os2dagsorden_send_email_body'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2dagsorden_send_email_subject';
  $strongarm->value = '!meeting_type til !committee er publiceret';
  $export['os2dagsorden_send_email_subject'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2dagsorden_send_notification_committee';
  $strongarm->value = '';
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
  $strongarm->name = 'os2dagsorden_show_attachments_mode';
  $strongarm->value = 'true';
  $export['os2dagsorden_show_attachments_mode'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2dagsorden_show_bilag';
  $strongarm->value = 1;
  $export['os2dagsorden_show_bilag'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2dagsorden_show_bilag_bullet_point';
  $strongarm->value = 1;
  $export['os2dagsorden_show_bilag_bullet_point'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2dagsorden_show_calender';
  $strongarm->value = 1;
  $export['os2dagsorden_show_calender'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2dagsorden_show_case_bullet_point';
  $strongarm->value = 1;
  $export['os2dagsorden_show_case_bullet_point'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2dagsorden_show_closed_bullet_point_content';
  $strongarm->value = 1;
  $export['os2dagsorden_show_closed_bullet_point_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2dagsorden_show_comments';
  $strongarm->value = 1;
  $export['os2dagsorden_show_comments'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2dagsorden_show_massive_expand_collapse_button';
  $strongarm->value = 'true';
  $export['os2dagsorden_show_massive_expand_collapse_button'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2dagsorden_show_meeting_category';
  $strongarm->value = 'false';
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
  $strongarm->value = 0;
  $export['os2dagsorden_show_samlet_dokument_link'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2dagsorden_show_search_block_title';
  $strongarm->value = 'false';
  $export['os2dagsorden_show_search_block_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2dagsorden_user_default_meeting_category';
  $strongarm->value = array(
    'pol' => 'pol',
    'org' => 0,
  );
  $export['os2dagsorden_user_default_meeting_category'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2web_acadre_add_committee_to_title';
  $strongarm->value = 1;
  $export['os2web_acadre_add_committee_to_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2web_acadre_esdh_enabled_plugins';
  $strongarm->value = array(
    'mm' => 'mm',
    'cm' => 0,
    'cp' => 0,
  );
  $export['os2web_acadre_esdh_enabled_plugins'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2web_adlib_url';
  $strongarm->value = '';
  $export['os2web_adlib_url'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2web_convertion_dir';
  $strongarm->value = 'private://os2convert';
  $export['os2web_convertion_dir'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'os2web_meetings_approved_committee';
  $strongarm->value = '94,95,103,104,114,125,130,131,134,135,136,137,138,139,140,151,153,154,155,157,158,159,163,164,165,166,167,168,169,170';
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
  $strongarm->name = 'pdf2html_rendering_path';
  $strongarm->value = '';
  $export['pdf2html_rendering_path'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'site_name';
  $strongarm->value = 'OS2Dagsorden';
  $export['site_name'] = $strongarm;

  return $export;
}
