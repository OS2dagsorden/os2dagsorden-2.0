<?php
/**
 * os2dagsorden_settings
 *
 * PHP version 5
 *
 * @category OS2dagsorden
 * @package  OS2dagsorden_Settings
 * @file     Admin page file
 * @author   Stanislav Kutasevits <stan@bellcom.dk>
 * @license  http://www.gnu.org/licenses/gpl-2.0.html GNU General Public License, version 2
 * @link     http://bellcom.dk
 */

define('ACADRE_MM_IMPORT_DIR', 'private://');
define('OS2DAGSORDEN_HIDDEN_AGENGA_COMMITTEE', '28');

/**
 * Implementation of settings form specifically for OS2dagsorden system.
 *
 * @param $form       the settings form
 * @param $form_state the state of the form
 *
 * @return settings form.
 */
function os2dagsorden_settings_settings_form($form, $form_state) {
  $output = os2dagsorden_blocks_positioning_show_git_version();

  $info_path = drupal_get_path('profile','os2dagsorden'). '/os2dagsorden.info';
  $info = drupal_parse_info_file($info_path);
  $version = (isset($info["version"])) ? $info["version"]: 'no version' ;

  $form['os2dagsorden_version_text'] = array(
    '#type' => 'item',
    '#weight' => -10,
    '#title' => t('OS2dagsorden - versionsnummer'),
    '#markup' => '<div class= "text">' .  $output . '</div>',
  );
  variable_set('os2dagsorden_version_no', variable_get('os2dagsorden_version_no', 1.0));
  $link = '';
  if ($version > variable_get('os2dagsorden_version_no')) {
    $link = '<td> <a href="/admin/updatedb">' . t('Gå her til at opdatere DB') . '</a></td>';
  }
  $form['os2dagsorden_version_no'] = array(
    '#type' => 'item',
    '#weight' => -9,
    '#title' => t('OS2dagsorden - opdatering version'),
    '#markup' => '<div class="text"><table><tr><td style = "width:17%">' . t('DB opdatering version') . ':' .' </td><td> <b>  ' . variable_get('os2dagsorden_version_no') . '</b></td>' . $link . '</tr></table></div>',
  );
  $form['os2dagsorden_settings_file_fieldset'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Settings file'),
  );

  $form['os2dagsorden_settings_file_fieldset'][] = array(
      '#type' => 'link',
      '#preffix' => '<p>',
      '#href' => 'os2dagsorden/export_settings',
      '#title' => t('Download current settings as a file'),
      '#suffix' => '</p>',
  );

  $settings_file = null;
  if (variable_get('os2dagsorden_settings_file', FALSE))
    $settings_file = file_load(variable_get('os2dagsorden_settings_file'));

  if ($settings_file){
    $form['os2dagsorden_settings_file_fieldset'][] = array(
      '#markup' => '<p>' . t('File in use: ') . (($settings_file)? $settings_file->filename : 'none') . '</p>',
    );
  }

  $form['os2dagsorden_settings_file_fieldset']['os2dagsorden_settings_file'] = array(
    '#title' => t('New settings file'),
    '#type' => 'managed_file',
    '#description' => t('Extract the settings from the file'),
    '#upload_location' => 'public://os2dagsorden_settings',
    '#upload_validators' => array(
      'file_validate_extensions' => array('settings'),
    ),
  );

  $form['os2dagsorden_settings_file_fieldset']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Import settings from file'),
    '#submit' => array('os2dagsorden_settings_import_from_file'),
  );

  $form['os2dagsorden_meeting_view_settings'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Meeting view settings'),
  );
  $form['os2dagsorden_meeting_view_settings']['os2dagsorden_show_meeting_committee'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show meeting committee on meeting view'),
    '#description' => t('This decides whether a meeting committee is visible on meeting view.'),
    '#default_value' => variable_get('os2dagsorden_show_meeting_committee', TRUE),
  );
  $form['os2dagsorden_meeting_view_settings']['os2dagsorden_show_meeting_enddate'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show meeting end date on meeting view'),
    '#description' => t('This decides whether a meeting end date is visible on meeting view.'),
    '#default_value' => variable_get('os2dagsorden_show_meeting_enddate', TRUE),
  );
  $form['os2dagsorden_meeting_view_settings']['os2dagsorden_show_meeting_type'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show meeting type on meeting view'),
    '#description' => t('This decides whether a meeting type field is visible on meeting view.'),
    '#default_value' => variable_get('os2dagsorden_show_meeting_type', TRUE),
  );
  $form['os2dagsorden_meeting_view_settings']['os2dagsorden_show_samlet_dokument_link'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show samlet dokument link on meeting view'),
    '#description' => t('This decides whether a samlet dokument link is visible on meeting view.'),
    '#default_value' => variable_get('os2dagsorden_show_samlet_dokument_link', TRUE),
  );
  $form['os2dagsorden_meeting_view_settings']['os2dagsorden_show_participants_afbud'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show cancelled participants'),
    '#description' => t('This decides whether a list of cancelled participants  is visible on meeting view'),
    '#default_value' => variable_get('os2dagsorden_show_participants_afbud', FALSE),
  );
  $form['os2dagsorden_meeting_view_settings']['os2dagsorden_show_print_icon'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show print icon on bullets in agenda'),
    '#description' => t('This decides whether a print button is visible on each bullet point on meeting view.'),
    '#default_value' => variable_get('os2dagsorden_show_print_icon', FALSE),
  );
  $form['os2dagsorden_meeting_view_settings']['os2dagsorden_show_send_to_friend_icon'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show send to friend icon on bullets in agenda'),
    '#description' => t('This decides whether a send to friend button is visible on each bullet point on meeting view.'),
    '#default_value' => variable_get('os2dagsorden_show_send_to_friend_icon', FALSE),
  );
  $form['os2dagsorden_meeting_view_settings']['os2dagsorden_show_bullet_case_id_link'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show case id link'),
    '#description' => t('This decides whether case id is visible on each bullet point on the meeting view (assuming bullet point has case id provided)'),
    '#default_value' => variable_get('os2dagsorden_show_bullet_case_id_link', FALSE),
  );
  $form['os2dagsorden_meeting_view_settings']['os2dagsorden_bullet_case_id_link_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Case nr link'),
    '#description' => t('That is the case cr link prefix that is linking to external case presentation system. Case identifier will added to the end of the provided link'),
    '#default_value' => variable_get('os2dagsorden_bullet_case_id_link_url', ""),
    '#states' => array(
      'visible' => array(
        ':input[name="os2dagsorden_show_bullet_case_id_link"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['os2dagsorden_meeting_view_settings']['os2dagsorden_show_comments'] = array(
   '#type' => 'checkbox',
   '#title' => t('Show comments on meeting view'),
   '#description'=>t('This decides whether a comments field is visible on meeting view.'),
   '#default_value' => variable_get('os2dagsorden_show_comments', false),
  );
  $form['os2dagsorden_meeting_view_settings']['os2dagsorden_show_closed_bullet_point_content'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show closed bullet point content on directly on meeting view'),
    '#description' => t('This decides whether a closed bullet point content will shown the same way as open bullet point - directly on the meeting view.'),
    '#default_value' => variable_get('os2dagsorden_show_closed_bullet_point_content', FALSE),
  );
  $form['os2dagsorden_meeting_view_settings']['os2dagsorden_show_bilag'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show bullet point attachment (bilag) on meeting view and bullet point attachment views'),
    '#description' => t('This decides whether a bullet point attachment converted from PDF to HTML is going to be shown in the application.<br/>Can be useful to disable display if users are known to used old browser versions (>IE8).'),
    '#default_value' => variable_get('os2dagsorden_show_bilag', TRUE),
  );
  $form['os2dagsorden_meeting_view_settings']['os2dagsorden_use_abbr'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use abbreviation of the meeting in the meeting views'),
    '#description' => t('This decides whether in some places a short version (abbreviation) of the meeting will be used instead of the full title'),
    '#default_value' => variable_get('os2dagsorden_use_abbr', TRUE),
  );
  $form['os2dagsorden_meeting_view_settings']['os2dagsorden_show_bp_comname'] = array(
    '#type' => 'checkbox',
    '#title' => t('Bullet point <i>"Afgøres i"</i> field'),
    '#description'=>t('This decides whether bullet point <i>"Afgøres i"</i> will be shown'),
    '#default_value' => variable_get('os2dagsorden_show_bp_comname', FALSE),
  );
  $form['os2dagsorden_meeting_view_settings']['os2dagsorden_allow_pdf_download'] = array(
    '#type' => 'checkbox',
    '#title' => t('Allow download meeting document and attachment as PDF'),
    '#description'=>t('This decides whether meeting and attachments are available for download as PDF'),
    '#default_value' => variable_get('os2dagsorden_allow_pdf_download', TRUE),
  );
  $form['os2dagsorden_meeting_view_settings']['os2dagsorden_sager_group_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Sager group title'),
    '#description'=>t('This decides how a group of Cases/Sager will be titled'),
    '#default_value' => variable_get('os2dagsorden_sager_group_title', 'Sager'),
  );
  $form['os2dagsorden_meeting_view_settings']['os2dagsorden_group_closed_bullet_points'] = array(
    '#type' => 'radios',
    '#title' => t('Group closed closed bullet points as a separate block'),
    '#default_value' => variable_get('os2dagsorden_group_closed_bullet_points', 'false'),
    '#options' => array('true' => t('Group separately'), 'false' => t('Put inline')),
    '#description' => t('This decides whether closed bullet points will be grouped separately as a additional block called "Lukket dagsorden", or put inline together the rest of the bullet points.'),
  );
  //hidden agenda
  $form['os2dagsorden_meeting_view_settings']['os2dagsorden_hidden_agenda_committee'] = array(
    '#type' => 'textfield',
    '#title' => t('List of committees which agenda is completely hidden to those without the rights'),
    '#maxlength' => 200,
    '#description' => t('Comma-separated list of committees ID which agenda and the summary (samlet dokument) is hidden to those without the rights'),
    '#default_value' => variable_get('os2dagsorden_hidden_agenda_committee', OS2DAGSORDEN_HIDDEN_AGENGA_COMMITTEE),
  );
  $form['os2dagsorden_meeting_view_settings']['os2dagsorden_meeting_description_download_dropdown'] = array(
    '#type' => 'textfield',
    '#title' => t('Meeting description download dropdown button'),
    '#maxlength' => 200,
    '#description' => t('Title of the meeting description download dropdown button'),
    '#default_value' => variable_get('os2dagsorden_meeting_description_download_dropdown', 'Hent dokumenter'),
  );
  $form['os2dagsorden_meeting_view_settings']['os2dagsorden_meeting_description_download_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Meeting description download button'),
    '#maxlength' => 200,
    '#description' => t('Title of the meeting description download button'),
    '#default_value' => variable_get('os2dagsorden_meeting_description_download_title', 'Hent samlet dokument i PDF'),
  );
  $form['os2dagsorden_meeting_view_settings']['os2dagsorden_meeting_description_with_att_download_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Meeting description with attachments download button'),
    '#maxlength' => 200,
    '#description' => t('Title of the meeting description with attachments download button'),
    '#default_value' => variable_get('os2dagsorden_meeting_description_with_att_download_title', 'Samlet dokument med bilag'),
  );
  $form['os2dagsorden_meeting_view_settings']['os2dagsorden_meeting_description_download_title_additional'] = array(
    '#type' => 'textfield',
    '#title' => t('Meeting additional description download button'),
    '#maxlength' => 200,
    '#description' => t('Title of the meeting additional description download button'),
    '#default_value' => variable_get('os2dagsorden_meeting_description_download_title_additional', 'Hent tillægsdokument i PDF'),
  );
  $form['os2dagsorden_meeting_view_settings']['os2dagsorden_meeting_description_with_att_download_title_additional'] = array(
    '#type' => 'textfield',
    '#title' => t('Meeting additional description with attachments download button'),
    '#maxlength' => 200,
    '#description' => t('Title of the meeting additional description with attachments download button'),
    '#default_value' => variable_get('os2dagsorden_meeting_description_with_att_download_title_additional', 'Tillægsdokument med bilag'),
  );
  $form['os2dagsorden_meeting_view_settings']['print_pdf_page_orientation'] = array(
      '#type' => 'select',
      '#title' => t('Page orientation in PDF file'),
      '#options' => array('portrait' => t('Portrait'), 'landscape' => t('Landscape')),
      '#default_value' => variable_get('print_pdf_page_orientation', PRINT_PDF_PAGE_ORIENTATION_DEFAULT),
      '#description' => t('Choose the page orientation of the generated PDF.'),
    );
  $form['os2dagsorden_meeting_view_settings']['os2dagsorden_print_pdf_show_commitee'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show committee and meeting date in bullet point title'),
      '#default_value' => variable_get('os2dagsorden_print_pdf_show_commitee', FALSE),
      '#description' => t('This decides whether meetimg committee and date will be shown in bullet point title in PDF'),
  );

  //expand or not expand bilag on bullet point expand
  //Meetig view settings
  $form['os2dagsorden_meeting_view_layout'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed'=>TRUE,
    '#title' => t('Meeting view layout'),
  );

  //meeting view settings
  $form['os2dagsorden_meeting_view_layout']['os2dagsorden_expand_all_bullets'] = array(
    '#type' => 'checkbox',
    '#title' => t('Expand all bullets on agenda page load'),
    '#description' => t('This decides whether all bullet points will be expanded on page load'),
    '#default_value' => variable_get('os2dagsorden_expand_all_bullets',FALSE),
  );
  $form['os2dagsorden_meeting_view_layout']['os2dagsorden_expand_attachment_onload'] = array(
    '#type' => 'checkbox',
    '#title' => t('Expand all attachments on bullet point open'),
    '#description' => t('This decides whether all attachments will be expanded on bullet point open'),
    '#default_value' => variable_get('os2dagsorden_expand_attachment_onload', FALSE),
  );
  $options = array(
    'true' => t('Expand'),
    'false' => t('Not expand (but keep it that way if the bilag has been expanded before)')
  );
  $form['os2dagsorden_meeting_view_layout']['os2dagsorden_expand_bilags'] = array(
    '#type' => 'radios',
    '#title' => t('Expand Bilag'),
    '#default_value' => variable_get('os2dagsorden_expand_bilags', 'true'),
    '#options' => $options,
    '#description' => t('This decides whether a certain type of bullet point attachment - bilag will be expanded (activated) when functionality "Expand whole bullet point" is executed.'),
  );
  $form['os2dagsorden_meeting_view_layout']['os2dagsorden_expand_cases'] = array(
    '#type' => 'radios',
    '#title' => t('Expand Sag'),
    '#default_value' => variable_get('os2dagsorden_expand_cases', 'false'),
    '#options' => $options,
    '#description' => t('This decides whether a certain type of bullet point attachment -case will be expanded (activated) when functionality "Expand whole bullet point" is executed.'),
  );
  $form['os2dagsorden_meeting_view_layout']['os2dagsorden_show_massive_expand_collapse_button'] = array(
    '#type' => 'radios',
    '#title' => t('Massive expand/collapse button'),
    '#default_value' => variable_get('os2dagsorden_show_massive_expand_collapse_button', 'true'),
    '#options' => array('true' => t('Show'), 'false' => t('Hide')),
    '#description' => t('This decides whether massive expand/collapse button will be shown on meeting views.'),
  );
  $form['os2dagsorden_meeting_view_layout']['os2dagsorden_show_bilag_bullet_point'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show bilags under Bilag bullet point'),
    '#description' => t('This decides whether all bilags grouped under Bilag bullet point'),
    '#default_value' => variable_get('os2dagsorden_show_bilag_bullet_point', FALSE),
  );
  $form['os2dagsorden_meeting_view_layout']['os2dagsorden_show_case_bullet_point'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show cases under Case bullet point'),
    '#description' => t('This decides whether all Cases/Sager grouped under Cases bullet point '),
    '#default_value' => variable_get('os2dagsorden_show_case_bullet_point', FALSE),
  );
  $form['os2dagsorden_meeting_view_layout']['os2dagsorden_show_bullet_case_nr'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show case nr next to bullet title'),
    '#description' => t('This decides case nr will be shown next to the bullet title'),
    '#default_value' => variable_get('os2dagsorden_show_bullet_case_nr', FALSE),
  );

   //show latest meetings in my committee or all committees
  $form['os2dagsorden_latest_meetings_view_settings'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Latest 8 meetings/upcoming meetings'),
  );
  $form['os2dagsorden_latest_meetings_view_settings']['os2dagsorden_latest_meetings_view_mode'] = array(
    '#type' => 'radios',
    '#title' => t('Switch beetween all/my committees meetings'),
    '#options' => array(
      'all' => t('Show meetings from all committees'),
      'mine' => t('Show meetings from my committees only')
    ),
    '#default_value' => variable_get('os2dagsorden_latest_meetings_view_mode', 'all'),
    '#description' => t('This decides whether the front page view will show 8 latest meeting from all committees or only from user committees (member of, follows, follows+)'),
  );
  $form['os2dagsorden_latest_meetings_view_settings']['os2dagsorden_meetings_views_last_8_show_meeting_title'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show meeting title on latest 8 meetings/upcoming meetings view'),
    '#description' => t('This decides whether a meeting title is visible on latest 8 meetings/upcoming meetings view.'),
    '#default_value' => variable_get('os2dagsorden_meetings_views_last_8_show_meeting_title', TRUE),
  );
  $form['os2dagsorden_latest_meetings_view_settings']['os2dagsorden_meetings_views_last_8_show_meeting_committee'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show meeting committee on latest 8 meetings/upcoming meetings view'),
    '#description' => t('This decides whether a meeting committee is visible on latest 8 meetings/upcoming meetings view.'),
    '#default_value' => variable_get('os2dagsorden_meetings_views_last_8_show_meeting_committee', TRUE),
  );
  $form['os2dagsorden_latest_meetings_view_settings']['os2dagsorden_meetings_views_last_8_show_meeting_location'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show meeting location on latest 8 meetings/upcoming meetings view'),
    '#description' => t('This decides whether a meeting location is visible on latest 8 meetings/upcoming meetings view.'),
    '#default_value' => variable_get('os2dagsorden_meetings_views_last_8_show_meeting_location', TRUE),
  );
  $form['os2dagsorden_latest_meetings_view_settings']['os2dagsorden_meetings_views_last_8_show_meeting_is_closed'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show closed indicator on latest 8 meetings/upcoming meetings view'),
    '#description' => t('This decides whether a closed indicator will be shown next to meeting if meeting has at least one bullet that is closed'),
    '#default_value' => variable_get('os2dagsorden_meetings_views_last_8_show_meeting_is_closed', FALSE),
  );
  $form['os2dagsorden_latest_meetings_view_settings']['os2dagsorden_meetings_views_last_8_meeting_title_len'] = array(
    '#type' => 'textfield',
    '#title' => t('Meeting title lenght'),
    '#description' => t('This specify how many characters the "møde column" should crop the text at. If this is set to 0 then we show the full title.'),
    '#default_value' => variable_get('os2dagsorden_meetings_views_last_8_meeting_title_len', 25),
  );
  $form['os2dagsorden_latest_meetings_view_settings']['os2dagsorden_meetings_views_last_8_meeting_location_len'] = array(
    '#type' => 'textfield',
    '#title' => t('Meeting location lenght'),
    '#description' => t('This specify how many characters the location column should crop the text at. If this is set to 0 then we show the full title.'),
    '#default_value' => variable_get('os2dagsorden_meetings_views_last_8_meeting_location_len', 25),
  );
  
  // frontpage layout settings
  $form['os2dagsorden_frontpage_layout'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Frontpage layout'),
  );
  $options3 = array('false' => t('Expand'), 'true' => t('Collapse'));
  $form['os2dagsorden_frontpage_layout']['os2dagsorden_collapse_menu'] = array(
    '#type' => 'radios',
    '#title' => t('Collapse/expand menu'),
    '#default_value' => variable_get('os2dagsorden_collapse_menu', TRUE),
    '#options' => $options3,
    '#description' => t('This decides whether a side menu expanded/collapsed.'),
  );
  $form['os2dagsorden_frontpage_layout']['os2dagsorden_collapse_menu_touch'] = array(
    '#type' => 'radios',
    '#title' => t('Collapse/expand menu touch devices'),
    '#default_value' => variable_get('os2dagsorden_collapse_menu_touch', TRUE),
    '#options' => $options3,
    '#description' => t('This decides whether a side menu expanded/collapsed for touch devices (tabels, phone etc).'),
  );
  $form['os2dagsorden_frontpage_layout']['os2dagsorden_collapse_menu_touch_pages'] = array(
    '#type' => 'textarea',
    '#title' => t('Hide side menu on those pages (touch)'),
    '#default_value' => variable_get('os2dagsorden_collapse_menu_touch_pages', 'meetings/print'),
    '#description' => t('List the pages where the side menu will be hidden by default (overruling the settings).<br/>Each page on new line'),
  );

  $form['os2dagsorden_frontpage_layout']['os2dagsorden_show_search_block_title'] = array(
    '#type' => 'radios',
    '#title' => t('Show/Hide search block title'),
    '#default_value' => variable_get('os2dagsorden_show_search_block_title', 'true'),
    '#options' => array('true' => t('Show'), 'false' => t('Hide')),
    '#description' => t('This decides whether a search block title show/hide.'),
  );

  // Body text size
  $form['os2dagsorden_body_text_layout'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Body text size'),
  );
  $form['os2dagsorden_body_text_layout']['os2dagsorden_body_text_size'] = array(
    '#type' => 'textfield',
    '#title' => t('Body text size'),
    '#maxlength' => 10,
    '#size' => 10,
    '#field_suffix' => ' px',
    '#default_value' => variable_get('os2dagsorden_body_text_size', '13'),
    '#description' => t('Default body text font size is 13 px. When you change the body text size, then please clear the cache to apply change'),
  );

  // Title text size
  $form['os2dagsorden_title_text_layout'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Title text size'),
  );
  $form['os2dagsorden_title_text_layout']['os2dagsorden_title_text_size'] = array(
    '#type' => 'textfield',
    '#title' => t('Title text size'),
    '#maxlength' => 10,
    '#size' => 10,
    '#field_suffix' => ' px',
    '#default_value' => variable_get('os2dagsorden_title_text_size', '13'),
    '#description' => t('Default title text font size is 13 px. When you change the title text size, then please clear the cache to apply change'),
  );

  //Import meeting in unpublished state
  $form['os2dagsorden_meeting_unpublished_state'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Meeting in unpublished state notification'),
  );
  /*$form['os2dagsorden_meeting_unpublished_state']['os2dagsorden_meetings_unpublished_status'] = array(
    '#type' => 'checkbox',
    '#title' => t('Meeting in unpublished status'),
    '#description' => t('Meetings are to be imported in an unpublished status.'),
    '#default_value' => variable_get('os2dagsorden_meetings_unpublished_status', ''),
  );
  $form['os2dagsorden_meeting_unpublished_state']['os2dagsorden_meeting_unpublished_state_emails'] = array(
    '#type' => 'textfield',
    '#title' => t('To'),
    '#description' => ('Add emails'),
    '#default_value' => variable_get('os2dagsorden_meeting_unpublished_state_emails', ''),
  );*/
  $form['os2dagsorden_meeting_unpublished_state']['os2dagsorden_meeting_unpublished_state_subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Subject'),
    '#description' => t('Add subject'),
    '#default_value' => variable_get('os2dagsorden_meeting_unpublished_state_subject', ''),
  );
  $form['os2dagsorden_meeting_unpublished_state']['os2dagsorden_meeting_unpublished_state_body'] = array(
    '#type' => 'textarea',
    '#title' => t('Message'),
    '#description' => t('Add text'),
    '#default_value' => variable_get('os2dagsorden_meeting_unpublished_state_body', ''),
  );
  $form['os2dagsorden_meeting_unpublished_state']['os2dagsorden_meeting_unpublished_state_email_text_available_variables'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#value' => t('Can be used both in subject and body:') . '<br/>
    <b>!committe</b> - ' . t('name of the committee') . '<br/>
    <b>!meeting_name</b> - ' . t('title of the meeting') . '<br/>
    <b>!meeting_date</b> - ' . t('date of the meeting') . '<br/>
    <b>!meeting_type</b> - ' . t('type of the meeting with acticle: <i>et referat</i> or <i>en dagsorden</i>') . '<br/>
    <b>!meeting_url</b> - ' . t('link to the meeting'),
    '#title' => t('Available variables'),
  );

  //meeting search view settings
  $form['os2dagsorden_meeting_search_view_settings'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Meeting search view settings'),
  );
  $form['os2dagsorden_meeting_search_view_settings']['os2dagsorden_meetings_search_show_meeting_committee'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show meeting committee on meeting search view'),
    '#description' => t('This decides whether a meeting committee is visible on meeting search view.'),
    '#default_value' => variable_get('os2dagsorden_meetings_search_show_meeting_committee', TRUE),
  );
  $form['os2dagsorden_meeting_search_view_settings']['os2dagsorden_meetings_search_show_meeting_location'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show meeting location on meeting search view'),
    '#description' => t('This decides whether a meeting location is visible on meeting search view.'),
    '#default_value' => variable_get('os2dagsorden_meetings_search_show_meeting_location', FALSE),
  );
  $form['os2dagsorden_meeting_search_view_settings']['os2dagsorden_meetings_search_show_meeting_status'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show meeting status on meeting search view'),
    '#description' => t('This decides whether a meeting status is visible on meeting search view.'),
    '#default_value' => variable_get('os2dagsorden_meetings_search_show_meeting_status', FALSE),
  );
  $form['os2dagsorden_meeting_search_view_settings']['os2dagsorden_meetings_search_include_add_agenda'] = array(
    '#type' => 'checkbox',
    '#title' => t('Include additional agendas into search by committee (empty keyword)'),
    '#description' => t('This decides whether the additional agenda meeting (tillaæegsdagsorden) will be included into the search results, when keyword is empty.<br/>
      If keyword is not empty additional agenda meeting will be included disregarding of this setting.'),
    '#default_value' => variable_get('os2dagsorden_meetings_search_include_add_agenda', TRUE),
  );

  $month_choise = array();
  foreach (range(0, 12) as $number) {
    $month_choise[$number] = $number;
  }

  $form['os2dagsorden_meeting_search_view_settings']['os2dagsorden_search_startdate'] = array(
    '#type' => 'select',
    '#title' => t('Search start date'),
    '#field_suffix' => t('months before today'),
    '#description' => t('This sets the default search start date for meeting search'),
    '#options' => $month_choise,
    '#default_value' => variable_get('os2dagsorden_search_startdate', 1),
  );

  $form['os2dagsorden_meeting_search_view_settings']['os2dagsorden_search_enddate'] = array(
    '#type' => 'select',
    '#title' => t('Search end date'),
    '#field_suffix' => t('months after today'),
    '#description' => t('This sets the default search end date for meeting search'),
    '#options' => $month_choise,
    '#default_value' => variable_get('os2dagsorden_search_enddate', 1),
  );
  $form['os2dagsorden_meeting_search_view_settings']['os2dagsorden_search_meeting_is_closed'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show closed indicator on meetings search view'),
    '#description' => t('This decides whether a closed indicator will be shown next to meeting if meeting has at least one bullet that is closed'),
    '#default_value' => variable_get('os2dagsorden_search_meeting_is_closed', FALSE),
  );

  // sidemenu layout settings
  $form['os2dagsorden_sidepane_menu_layout'] = array(
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#title' => t('Sidepane menu layout'),
  );

  $form['os2dagsorden_sidepane_menu_layout']['main_menu_links'] = array(
      '#type' => 'link',
      '#prefix' => '<p>',
      '#href' => 'admin/structure/menu/manage/menu-sidepane-menu',
      '#title' => t('Change order of the main menu links'),
      '#sufix' => '</p>',
  );
  $form['os2dagsorden_sidepane_menu_layout']['sipepane_blocks_order'] = array(
    '#type' => 'link',
    '#prefix' => '<p>',
    '#href' => 'admin/structure/block',
    '#title' => t('Change order of sidepane blocks (Sidebar Second)'),
    '#sufix' => '</p>',
  );
  $vid = db_select('taxonomy_vocabulary', 'tv')
            ->fields('tv', array('vid'))
            ->condition('machine_name', 'os2web_meetings_tax_committee')
            ->execute()
            ->fetchField();

  $committees = taxonomy_get_tree($vid);
  $options_committee = array();
  foreach ($committees as $committee){
    $options_committee[$committee->tid] = $committee->name;
  }

  $form['os2dagsorden_sidepane_menu_layout']['os2dagsorden_budget_committee'] = array(
    '#type' => 'select',
    '#title' => t('Select a committee which meeting will be available in <b>Budget</b> menu link'),
    '#description' => t('This decides committee will update the meeting link in Budget menu link in the side panel'),
    '#options' => $options_committee,
    '#empty_option' => t('- None - '),
    '#default_value' => variable_get('os2dagsorden_budget_committee', FALSE),
  );

  //Meeting import settings
  $form['os2dagsorden_meeting_import'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('General meeting import settings'),
  );
  $form['os2dagsorden_meeting_import']['os2dagsorden_participants_delimeter'] = array(
    '#type' => 'textfield',
    '#title' => t('Participants delimeter sign'),
    '#default_value' => variable_get('os2dagsorden_participants_delimeter', ', '),
    '#description' => t('Sign with which the participants of the meeting will be separated. Is used in the meeting view.<br/> E.g. if delimeter is <b>coma (,)</b> the list would look like:<br/>
    Jørgen Andersen, Nich Bendtsen, Poul Møller, ...<br/><br/>HTML tags (such as &lt;br/&gt;) can be used.'),
  );
  $form['os2dagsorden_meeting_import']['os2dagsorden_send_notification_committee'] = array(
    '#type' => 'textfield',
    '#title' => t('Send notification of committees'),
    '#maxlength' => 250,
    '#default_value' => variable_get('os2dagsorden_send_notification_committee', FALSE),
    '#description' => t('Comma-separated list of committees changing status of which should send an email notification.'),
    '#autocomplete_path' => 'get_committee/autocomplete',
  );
  $form['os2dagsorden_meeting_import']['os2dagsorden_send_email_subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Meeting notification email text'),
    '#description' => t('The email subject, which would be send to users interested in meeting publishing - Member / Follow+ / Follow (optional)'),
    '#default_value' => variable_get('os2dagsorden_send_email_subject', '!meeting_type til !committee er publiceret'),
  );
  $form['os2dagsorden_meeting_import']['os2dagsorden_send_email_body'] = array(
    '#type' => 'textarea',
    '#title' => t('Meeting notification email text'),
    '#description' => t('The email body, which would be send to users interested in meeting publishing - Member / Follow+ / Follow (optional)'),
    '#default_value' => variable_get('os2dagsorden_send_email_body', 'Til !user' . PHP_EOL . PHP_EOL .
      'Du abonnerer på !committee.' . PHP_EOL . 'Der er publiceret !meeting_type til !meeting_name !meeting_date.'),
  );
  $form['os2dagsorden_meeting_import']['os2dagsorden_send_email_text_available_variables'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#value' => t('Can be used both in subject and body:') . '<br/>
    <b>!committee</b> - ' . t('name of the committee') . '<br/>
    <b>!meeting_name</b> - ' . t('title of the meeting') . '<br/>
    <b>!meeting_date</b> - ' . t('date of the meeting') . '<br/>
    <b>!meeting_type</b> - ' . t('type of the meeting with acticle: <i>et referat</i> or <i>en dagsorden</i>') . '<br/>
    <b>!meeting_link</b> - ' . t('link to the meeting') . '<br/>
    <b>!user</b> - ' . t('name of the user that message is sent to') . '<br/>',
    '#title' => t('Available variables'),
  );
  $form['os2dagsorden_meeting_import']['os2dagsorden_follows_committee_send_notification'] = array(
    '#type' => 'checkbox',
    '#title' => t('User that are just Follow the committee are getting notifications '),
    '#description' => t('Decide whether user that are just Follow the committee are getting notifications about new messages appeared on that committee.'),
    '#default_value' => variable_get('os2dagsorden_follows_committee_send_notification', FALSE),
  );
  $form['os2dagsorden_meeting_import']['os2dagsorden_send_timespan_of_notification'] = array(
    '#type' => 'textfield',
    '#title' => t('Meeting should be not older than:'),
    '#maxlength' => 200,
    '#field_suffix' => t('Days'),
    '#size' => 10,
    '#description' => t('If meeting is not older than the set amount of day, notification is sent. <br/>Otherwise notification process is skipped'),
    '#default_value' => variable_get('os2dagsorden_send_timespan_of_notification', 10),
  );

  $form['os2dagsorden_meeting_import']['os2dagsorden_add_type_prefix'] = array(
    '#type' => 'radios',
    '#title' => t('Add prefix to Bilag/Sag bullet point attachments'),
    '#options' => array('true' => t('Add <i>Bilag/Sag</i> prefix'), 'false' => t('Add no prefix')),
    '#description' => t('This decides whether the will be added a prefix to Bilag or Case bullet point attachment on import.<br/>e.g. <b>Bilag:</b> Indsigelser of Bemaerkninger.'),
    '#default_value' => variable_get('os2dagsorden_add_type_prefix', 'true'),
  );
  $form['os2dagsorden_meeting_import']['os2dagsorden_committee_category_pol'] = array(
    '#type' => 'textfield',
    '#title' => t('Political committees'),
    '#maxlength' => 250,
    '#default_value' => variable_get('os2dagsorden_committee_category_pol', FALSE),
    '#description' => t('Comma-separated list of committees meetings of which should be tagged as POLITICAL during the import.'),
  );
  $form['os2dagsorden_meeting_import']['os2dagsorden_committee_category_org'] = array(
    '#type' => 'textfield',
    '#title' => t('Organisational committees'),
    '#maxlength' => 250,
    '#default_value' => variable_get('os2dagsorden_committee_category_org', FALSE),
    '#description' => t('Comma-separated list of committees meetings of which should be tagged as ORGANISATIONAL during the import.'),
  );
  $form['os2dagsorden_meeting_import']['os2dagsorden_filtered_tags'] = array(
    '#type' => 'textfield',
    '#title' => t('Filtered HTML tags lists'),
    '#maxlength' => 250,
    '#default_value' => variable_get('os2dagsorden_filtered_tags', ''),
    '#description' => t('Comma-separated list of html tags that want to filter out (fe. p,h1,h2).'),
  );
  $form['os2dagsorden_meeting_import']['os2dagsorden_stripped_tags'] = array(
    '#type' => 'textfield',
    '#title' => t('Striped HTML tags lists'),
    '#maxlength' => 250,
    '#default_value' => variable_get('os2dagsorden_stripped_tags', ''),
    '#description' => t('Comma-separated list of html tags that want to strip (fe. font, span).'),
  );
   $form['os2dagsorden_meeting_import']['os2dagsorden_tab_tag'] = array(
    '#type' => 'textfield',
    '#title' => t('Replace  multiple &amp;nbsp; tags with: '),
    '#maxlength' => 250,
    '#default_value' => variable_get('os2dagsorden_tab_tag', '&nbsp;'),
    '#description' => t('Tag what should be put into the document instead of multiple &amp;nbsp; tags'),
  );
   $form['os2dagsorden_meeting_import']['os2dagsorden_url_strip_count'] = array(
     '#type' => 'textfield',
     '#title' => t('Link (a href) limit: '),
     '#maxlength' => 250,
     '#default_value' => variable_get('os2dagsorden_url_strip_count', '20'),
     '#description' => t('Specify a max limit in chars, which a link can have. If the link has more than specified, then link text is trimmed and ... is added.'),
   );

  //PDF conversion settings
  if (module_exists('os2web_pdf_conversion_manager')) {
    $form['os2dagsorden_file_import'] = array(
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#title' => t('* > PDF converting configuration'),
    );
    $form['os2dagsorden_file_import']['os2web_copied_filetype'] = array(
      '#type' => 'textfield',
      '#title' => t('Type of files to be converted when importing:'),
      '#maxlength' => 200,
      '#description' => t('Comma-separated list of file types. Example: xls,doc,docx,xlsx'),
      '#default_value' => variable_get('os2web_copied_filetype', OS2WEB_COPIED_FILETYPE),
    );
    $form['os2dagsorden_file_import']['os2web_convertion_dir'] = array(
      '#type' => 'textfield',
      '#title' => t('Directory to send the files for converting:'),
      '#maxlength' => 200,
      '#description' => t('This is the path where files copy for converting'),
      '#default_value' => variable_get('os2web_convertion_dir', OS2WEB_CONVERTION_DIR),
      '#element_validate' => array('_os2dagsorden_os2web_convertion_dir_validate'),
    );
  }
  if (module_exists('os2dagsorden_pdf2htmlex')) {
    $form['os2dagsorden_pdf2htmlex_settings'] = array(
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#title' => t('PDF > HTML Converter settings'),
    );
    $form['os2dagsorden_pdf2htmlex_settings']['os2dagsorden_pdf2htmlex_path'] = array(
      '#type' => 'textfield',
      '#title' => t('Path to pdf2htmlEX'),
      '#description' => t('Path to pdf2htmlEX'),
      '#default_value' => variable_get('os2dagsorden_pdf2htmlex_path', ""),
      '#element_validate' => array('_os2dagsorden_pdf2htmlEX_validate'),
    );
    $form['os2dagsorden_pdf2htmlex_settings']['pdf2html_rendering_path'] = array(
      '#type' => 'textfield',
      '#title' => t('Path for HTML files to be rendered'),
      '#default_value' => variable_get('pdf2html_rendering_path', ''),
      '#description' => t('Relative path for HTML files to be rendered by os2dagsorden_pdf2htmlEX module. If empty, the path with the original PDF files will be used.<br/><b>Important!</b> You will need to create the path yourself.'),
      '#element_validate' => array('_os2dagsorden_pdf2html_rendering_path_validate'),
    );
  }

  // Clear cache settings
  $form['os2dagsorden_clear_cache_after_import'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Clear cache after import settings'),
  );
  $form['os2dagsorden_clear_cache_after_import']['os2dagsorden_clear_cache_active'] = array(
    '#type' => 'checkbox',
    '#title' => t('Active clear cahce after importing meetings'),
    '#default_value' => variable_get('os2dagsorden_clear_cache_active', 0),
  );

  $form['os2dagsorden_clear_cache_after_import']['os2dagsorden_clear_cache_frequency'] = array(
    '#type' => 'select',
    '#title' => t('Clear cache frequency after pdf convert'),
    '#options' => array(
      '0' => t('Never'),
      '10' => t('Every 10 mins'),
      '30' => t('Every 30 mins'),
      '60' => t('Every hour'),
    ),
    '#default_value' => variable_get('os2dagsorden_clear_cache_frequency', 0),
  );

  $form['os2dagsorden_political_organizational_settings'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Political/organizational category settings'),
  );
  $options2 = array('true' => t('Show'), 'false' => t('Do not show'));
  $form['os2dagsorden_political_organizational_settings']['os2dagsorden_show_meeting_category'] = array(
    '#type' => 'radios',
    '#title' => t('Show meeting categories'),
    '#default_value' => variable_get('os2dagsorden_show_meeting_category'),
    '#options' => $options2,
    '#description' => t('This decides whether a meeting title in the calendar view will be prefixed with the meeting category (<b>[P]</b>olitical/<b>[O]</b>rganization)'),
  );
   $form['os2dagsorden_political_organizational_settings']['os2dagsorden_user_default_meeting_category']=array(
    '#title' => t('Default value for user meeting category'),
    '#type' => 'checkboxes',
    '#description' => t('Select default value for user meeting category.'),
    '#options' => array('pol' => t('Political'), 'org' => t('Organisation')),
    '#default_value'=>variable_get('os2dagsorden_user_default_meeting_category', 'pol')
  );
 /*  $form['os2dagsorden_political_organizational_settings']['os2dagsorden_default_meeting_cateroty'] = array(
    '#type' => 'radios',
    '#title' => t('Default meeting category'),
    '#default_value' => variable_get('os2dagsorden_default_meeting_cateroty','pol'),
    '#options' =>  array('pol' => t('Political'), 'org' => t('Organisation')),
    '#description' => t('This decides whether a default meeting category'),
  );*/

  if (module_exists('ultimate_cron')) {
    //cron frequencies
    $form['os2dagsorden_cron_job_freq'] = array(
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#title' => t('Cron job frequencies settings'),
    );

    $options = array(
      '*/5 * * * *' => 'Every 5 min',
      '*/15 * * * *' => 'Every 15 min',
      '*/30 * * * *' => 'Every 30 min',
      '0 */1 * * *' => 'Every 1 hour',
      '0 */2 * * *' => 'Every 2 hours',
      '0 */3 * * *' => 'Every 3 hours',
      '0 */5 * * *' => 'Every 5 hours',
      '0 */10 * * *' => 'Every 10 hours',
    );
    if (module_exists('os2dagsorden_importer')){
      $conf = ultimate_cron_get_settings("os2dagsorden_importer_cron");
      $form['os2dagsorden_cron_job_freq']['os2dagsorden_importer_cron'] = array(
        '#type' => 'select',
        '#options' => $options,
        '#default_value' => isset($conf['rules']) ? implode(';', $conf['rules']) : variable_get('ultimate_cron_rule', ULTIMATE_CRON_RULE),
        '#title' => t('Frequency of SOFD import cron job'),
      );
      $form['os2dagsorden_cron_job_freq']['os2dagsorden_importer_cron_button'] = array(
        '#type' => 'button',
        '#value' => t('Run now'),
        '#attributes' => array('onclick' => 'location.href="/admin/ultimate-cron/service/start/os2dagsorden_importer_cron?destination=/admin/config/os2dagsorden/settings"; return false;'),
      );
    }
    if (module_exists('os2dagsorden_acadre_service_importer')){
      $conf = ultimate_cron_get_settings('os2dagsorden_acadre_service_importer_cron');
      $form['os2dagsorden_cron_job_freq']['os2dagsorden_acadre_service_importer_cron'] = array(
        '#type' => 'select',
        '#options' => $options,
        '#default_value' => isset($conf['rules']) ? implode(';', $conf['rules']) : variable_get('ultimate_cron_rule', ULTIMATE_CRON_RULE),
        '#title' => t('Frequency of Acadre Service import cron job'),
      );
      $form['os2dagsorden_cron_job_freq']['os2dagsorden_acadre_service_importer_cron_button'] = array(
        '#type' => 'button',
        '#value' => t('Run now'),
        '#attributes' => array('onclick' => 'location.href="/admin/ultimate-cron/service/start/os2dagsorden_acadre_service_importer_cron?destination=/admin/config/os2dagsorden/settings"; return false;'),
      );
    }

    $conf = ultimate_cron_get_settings("os2web_esdh_provider_cron");
    $form['os2dagsorden_cron_job_freq']['os2web_esdh_provider_cron'] = array(
      '#type' => 'select',
      '#options' => $options,
      '#default_value' => isset($conf['rules']) ? implode(';', $conf['rules']) : variable_get('ultimate_cron_rule', ULTIMATE_CRON_RULE),
      '#title' => t('Frequency of Acadre import cron job'),
    );
    $form['os2dagsorden_cron_job_freq']['os2web_esdh_provider_cron_button'] = array(
      '#type' => 'button',
      '#value' => t('Run now'),
      '#attributes' => array('onclick' => 'location.href="/admin/ultimate-cron/service/start/os2web_esdh_provider_cron?destination=/admin/config/os2dagsorden/settings"; return false;'),
    );
    $conf = ultimate_cron_get_settings("os2dagsorden_pdf2htmlex_cron");
    $form['os2dagsorden_cron_job_freq']['os2dagsorden_pdf2htmlex_cron'] = array(
      '#type' => 'select',
      '#options' => $options,
      '#default_value' => isset($conf['rules']) ? implode(';', $conf['rules']) : variable_get('ultimate_cron_rule', ULTIMATE_CRON_RULE),
      '#title' => t('Frequency of PDF to HTML conversion cron job'),
    );
    $form['os2dagsorden_cron_job_freq']['os2dagsorden_pdf2htmlex_cron_button'] = array(
      '#type' => 'button',
      '#value' => t('Run now'),
      '#attributes' => array('onclick' => 'location.href="/admin/ultimate-cron/service/start/os2dagsorden_pdf2htmlex_cron?destination=/admin/config/os2dagsorden/settings"; return false;'),
    );
    $conf = ultimate_cron_get_settings("os2dagsorden_adlib_api_cron");
    $form['os2dagsorden_cron_job_freq']['os2dagsorden_adlib_api_cron'] = array(
      '#type' => 'select',
      '#options' => $options,
      '#default_value' => isset($conf['rules']) ? implode(';', $conf['rules']) : variable_get('ultimate_cron_rule', ULTIMATE_CRON_RULE),
      '#title' => t('Frequency of Adlib (* to PDF) conversion cron job'),
    );
     $form['os2dagsorden_cron_job_freq']['os2dagsorden_adlib_api_cron_button'] = array(
      '#type' => 'button',
      '#value' => t('Run now'),
      '#attributes' => array('onclick' => 'location.href="/admin/ultimate-cron/service/start/os2web_adlib_api_cron?destination=/admin/config/os2dagsorden/settings"; return false;'),
    );
    $form['#submit'][] = 'os2dagsorden_settings_cron_job_submit';
  }

   // SOFD Integration settings
  if (module_exists('os2dagsorden_importer')){
    $form['os2dagsorden_pws_sofd_group'] = array(
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#title' => t('SOFD Integration settings'),
    );
    $form['os2dagsorden_pws_sofd_group']['os2dagsorden_pws_use_local_copy'] = array(
      '#type' => 'checkbox',
      '#default_value' => variable_get('os2dagsorden_pws_use_local_copy'),
      '#title' => t('Use local XML files'),
      '#description' => variable_get('os2dagsorden_pws_use_local_copy') ? 'Diselect and click save to enable the fields below' : 'Selecting and clicking save will disable the textfields below',
      '#element_validate' => array('_os2dagsorden_sofd_local_copy_validate'),
    );
    $form['os2dagsorden_pws_sofd_group']['os2dagsorden_pws_v_meetings_url'] = array(
      '#type' => 'textfield',
      '#default_value' => variable_get('os2dagsorden_pws_v_meetings_url'),
      '#title' => t('Meeting (planned meetings) view url:'),
      '#maxlength' => 256,
      '#disabled' => variable_get('os2dagsorden_pws_use_local_copy'),
     // '#element_validate' => array('_os2dagsorden_url_responce_validate'),
    );
    $form['os2dagsorden_pws_sofd_group']['os2dagsorden_pws_v_meetinggroups_url'] = array(
      '#type' => 'textfield',
      '#default_value' => variable_get('os2dagsorden_pws_v_meetinggroups_url'),
      '#title' => t('Meeting groups (is member of/follows/follows+) view url:'),
      '#maxlength' => 256,
      '#disabled' => variable_get('os2dagsorden_pws_use_local_copy'),
    //  '#element_validate' => array('_os2dagsorden_url_responce_validate'),
    );
    $form['os2dagsorden_pws_sofd_group']['os2dagsorden_pws_v_acadregroups_url'] = array(
      '#type' => 'textfield',
      '#default_value' => variable_get('os2dagsorden_pws_v_acadregroups_url'),
      '#title' => t('Acadre groups (committees) url:'),
      '#maxlength' => 256,
      '#disabled' => variable_get('os2dagsorden_pws_use_local_copy'),
      //'#element_validate' => array('_os2dagsorden_url_responce_validate'),
    );
  }

  // Acadre service importer
  if (module_exists('os2dagsorden_acadre_service_importer')){
    $form['os2dagsorden_acadre_service_importer_placeholder'] = array(
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#title' => t('Acadre Service importer Integration settings'),
    );
    $form['os2dagsorden_acadre_service_importer_placeholder']['os2dagsorden_acadre_service_meetings_url'] = array(
      '#type' => 'textfield',
      '#default_value' => variable_get('os2dagsorden_acadre_service_meetings_url'),
      '#title' => t('Meeting (planned meetings) view url:'),
      '#maxlength' => 256,
      //'#element_validate' => array('_os2dagsorden_url_responce_validate'),
    );
    $form['os2dagsorden_acadre_service_importer_placeholder']['os2dagsorden_acadre_service_committees_url'] = array(
      '#type' => 'textfield',
      '#default_value' => variable_get('os2dagsorden_acadre_service_committees_url'),
      '#title' => t('Committees url:'),
      '#maxlength' => 256,
      //'#element_validate' => array('_os2dagsorden_url_responce_validate'),
    );
  }

  //Allowed committees
  /*$form['os2dagsorden_committees_list_placeholder'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Committees positive list'),
  );
  $form['os2dagsorden_committees_list_placeholder']['os2dagsorden_committees_positive_list_as_import_list'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use this list during import'),
    '#default_value' => variable_get('os2dagsorden_committees_positive_list_as_import_list', false),
    '#description' => t('If checkbox is clicked, this is the list that will be used during meetings import'),
  );
  $committees = taxonomy_get_tree($vid);
  $options_committee = array();
  foreach ($committees as $committee){
    $committee_full = taxonomy_term_load($committee->tid);
    $ids = '';
    foreach($committee_full->field_os2web_meetings_com_subid['und'] as $id){
      $ids .= ' ' . $id['value'] . ',';
    }
    if (!empty($ids)) $ids = substr($ids, 0, -1);
    $options_committee[$committee->tid] = $committee->name . ' [ID:' . $ids . ']';
  }
  $form['os2dagsorden_committees_list_placeholder']['os2dagsorden_committees_positive_list'] = array(
    '#type' => 'checkboxes',
    '#options' => $options_committee,
    '#title' => t('Select committees to be in positive list'),
    '#default_value' => variable_get('os2dagsorden_committees_positive_list'), 
  );*/

  $form['os2dagsorden_help_text_placeholder'] = array(
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#title' => t('Help-button texts'),
  );

  $form['os2dagsorden_help_text_placeholder']['os2dagsorden_upcoming_meetings_help_text'] = array(
      '#type' => 'textarea',
      '#rows' => 2,
      '#default_value' => variable_get('os2dagsorden_upcoming_meetings_help_text', 'Her vises de kommende 5 møder i "Mine udvalg". Det vil sige udvalg som man enten er medlem af eller følger. Udvalgene kan ses i boksene "Medlem af" og "Jeg følger" i højremenuen. Der er ikke en dagsorden tilgængelig før status er angivet til Dagsorden eller Dagsorden+.'),
      '#title' => t('Coming meeting help text'),
  );

  $form['os2dagsorden_help_text_placeholder']['os2dagsorden_meetings_search_help_text'] = array(
      '#type' => 'textarea',
      '#rows' => 2,
      '#default_value' => variable_get('os2dagsorden_meetings_search_help_text', 'Her vises de møder der indeholdt møder, punkter eller bilag der matchede dine søgekriterier. Søgeresultatet vises på mødeniveau i listen.'),
      '#title' => t('Meetings search page help text'),
  );

  $form['os2dagsorden_help_text_placeholder']['os2dagsorden_meetings_search_block_help_text'] = array(
      '#type' => 'textarea',
      '#rows' => 2,
      '#default_value' => variable_get('os2dagsorden_meetings_search_block_help_text', 'Her kan der søges i dagsordenspunkters tekst og i bilagenes fritekst, hvis sidstnævnte er konverteret til html. Søgning kan filtreres via dato, udvalg og søgeord.'),
      '#title' => t('Meetings search block help text'),
  );

  $form['os2dagsorden_help_text_placeholder']['os2dagsorden_last_8_meetings_help_text'] = array(
      '#type' => 'textarea',
      '#rows' => 2,
      '#default_value' => variable_get('os2dagsorden_last_8_meetings_help_text', 'Her vises de seneste 8 møder i alle mødefora. Der er ikke et referat tilgængeligt før status er angivet til Referat eller Referat+.'),
      '#title' => t('Last 8 meetings help text'),
  );

  $form['os2dagsorden_help_text_placeholder']['os2dagsorden_annotator_help_text'] = array(
      '#type' => 'textarea',
      '#rows' => 2,
      '#default_value' => variable_get('os2dagsorden_annotator_help_text', 'Hvis du ønsker at lave en kommentar til et ord eller et afsnit, så marker blot dette hvorefter du får mulighed for at indtaste kommentaren.'),
      '#title' => t('Annotator page help text'),
  );

  $form['os2dagsorden_help_text_placeholder']['os2dagsorden_calendar_help_text'] = array(
      '#type' => 'textarea',
      '#rows' => 2,
      '#default_value' => variable_get('os2dagsorden_calendar_help_text', 'Her findes en dags- eller månedskalender med links til dagsordner og referater hvis de er publicerede. Det er muligt at eksportere møderne til en fil, som så kan importeres til egen kalender, eks. i Outlook.'),
      '#title' => t('Calendar block help text'),
  );

  $form['os2dagsorden_help_text_placeholder']['os2dagsorden_user_committees_help_text'] = array(
      '#type' => 'textarea',
      '#rows' => 2,
      '#default_value' => variable_get('os2dagsorden_user_committees_help_text', 'Her kan du se de udvalg du er medlem af. Ret henvendelse til Direktionssekretariatet hvis du mener det skal ændres.'),
      '#title' => t('User committees help text'),
  );

  $form['os2dagsorden_help_text_placeholder']['os2dagsorden_user_follows_help_text'] = array(
      '#type' => 'textarea',
      '#rows' => 2,
      '#default_value' => variable_get('os2dagsorden_user_follows_help_text', 'Her kan du se de udvalg du er sat op til at følge. Følger betyder at du kun kan se åbne punkter og Følger+ betyder at du også kan se lukkede punkter. Ret henvendelse til Direktionssekretariatet hvis du mener det skal ændres.'),
      '#title' => t('User follows help text'),
  );
  $form['os2dagsorden_help_text_placeholder']['os2dagsorden_calendar_replacement_block_text'] = array(
    '#type' => 'textfield',
    '#title' => t('Print meeting calendar block text (asking person to turn his/her device horizontally)'),
    '#default_value' => variable_get('os2dagsorden_calendar_replacement_block_text', 'Vend venligst din iPad horisontalt'),
  );

  $form['os2dagsorden_terminology_placeholder'] = array(
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#title' => t('Terminology settings'),
  );

  $form['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_general_placeholder'] = array(
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#title' => t('General'),
  );
  $form['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_general_placeholder']['os2dagsorden_title_general_mine_indstillinger'] = array(
      '#type' => 'textfield',
      '#default_value' => variable_get('os2dagsorden_title_general_mine_indstillinger', 'Mine indstillinger'),
      '#title' => t('Log af'),
  );
  $form['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_general_placeholder']['os2dagsorden_title_general_log_off'] = array(
      '#type' => 'textfield',
      '#default_value' => variable_get('os2dagsorden_title_general_log_off', 'Log af'),
      '#title' => t('Log af'),
  );
  $form['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_general_placeholder']['os2dagsorden_title_general_search'] = array(
      '#type' => 'textfield',
      '#default_value' => variable_get('os2dagsorden_title_general_search', 'Søg'),
      '#title' => t('Søg'),
  );

  $form['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_frontpage_placeholder'] = array(
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#title' => t('Front page'),
  );
  $form['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_frontpage_placeholder']['os2dagsorden_title_frontpage_coming_meetings'] = array(
      '#type' => 'textfield',
      '#default_value' => variable_get('os2dagsorden_title_frontpage_coming_meetings', 'Kommende møder i mine udvalg'),
      '#title' => t('View: Kommende møder i mine udvalg'),
  );
  $form['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_frontpage_placeholder']['os2dagsorden_title_frontpage_last_8_my_meetings'] = array(
      '#type' => 'textfield',
      '#default_value' => variable_get('os2dagsorden_title_frontpage_last_8_my_meetings', 'Seneste 8 møder i mine udvalg'),
      '#title' => t('View: Seneste 8 møder i mine udvalg'),
  );
  $form['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_frontpage_placeholder']['os2dagsorden_title_frontpage_last_8_all_meetings'] = array(
      '#type' => 'textfield',
      '#default_value' => variable_get('os2dagsorden_title_frontpage_last_8_all_meetings', 'Seneste møder i alle udvalg'),
      '#title' => t('View: Seneste møder i alle udvalg'),
  );
  $form['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_frontpage_placeholder']['os2dagsorden_title_frontpage_calendar'] = array(
      '#type' => 'textfield',
      '#default_value' => variable_get('os2dagsorden_title_frontpage_calendar', 'Kalender'),
      '#title' => t('Block: Kalender'),
  );
  $form['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_frontpage_placeholder']['os2dagsorden_title_frontpage_member_of'] = array(
      '#type' => 'textfield',
      '#default_value' => variable_get('os2dagsorden_title_frontpage_member_of', 'Medlem af'),
      '#title' => t('Block: Medlem af'),
  );
  $form['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_frontpage_placeholder']['os2dagsorden_title_frontpage_following'] = array(
      '#type' => 'textfield',
      '#default_value' => variable_get('os2dagsorden_title_frontpage_following', 'Jeg følger'),
      '#title' => t('Block: Jeg følger'),
  );
  $form['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_frontpage_placeholder']['os2dagsorden_title_frontpage_account_settings'] = array(
      '#type' => 'textfield',
      '#default_value' => variable_get('os2dagsorden_title_frontpage_account_settings', 'Konto indstillinger'),
      '#title' => t('Menu: Konto indstillinger'),
  );
  $form['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_frontpage_placeholder']['os2dagsorden_title_frontpage_home'] = array(
      '#type' => 'textfield',
      '#default_value' => variable_get('os2dagsorden_title_frontpage_home', 'Forsiden'),
      '#title' => t('Menu: Forsiden'),
  );
  $form['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_frontpage_placeholder']['os2dagsorden_title_frontpage_halfyear_calendar'] = array(
      '#type' => 'textfield',
      '#default_value' => variable_get('os2dagsorden_title_frontpage_halfyear_calendar', 'Halvårs-kalender'),
      '#title' => t('Menu: Halvårs Kalender'),
  );

  $form['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_meeting_placeholder'] = array(
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#title' => t('Meeting'),
  );
  $form['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_meeting_placeholder']['os2dagsorden_title_meeting_status'] = array(
      '#type' => 'textfield',
      '#default_value' => variable_get('os2dagsorden_title_meeting_status', 'Status'),
      '#title' => t('Status'),
  );
  $form['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_meeting_placeholder']['os2dagsorden_title_meeting_meeting'] = array(
      '#type' => 'textfield',
      '#default_value' => variable_get('os2dagsorden_title_meeting_meeting', 'Møde'),
      '#title' => t('Møde'),
  );
  $form['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_meeting_placeholder']['os2dagsorden_title_meeting_date'] = array(
      '#type' => 'textfield',
      '#default_value' => variable_get('os2dagsorden_title_meeting_date', 'Dato'),
      '#title' => t('Dato'),
  );
  $form['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_meeting_placeholder']['os2dagsorden_title_meeting_location'] = array(
      '#type' => 'textfield',
      '#default_value' => variable_get('os2dagsorden_title_meeting_location', 'Lokation'),
      '#title' => t('Lokation'),
  );
  $form['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_meeting_placeholder']['os2dagsorden_title_meeting_freetext_placing'] = array(
      '#type' => 'textfield',
      '#default_value' => variable_get('os2dagsorden_title_meeting_freetext_placing', 'Placering'),
      '#title' => t('Placering'),
  );
  $form['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_meeting_placeholder']['os2dagsorden_title_meeting_comments'] = array(
      '#type' => 'textfield',
      '#default_value' => variable_get('os2dagsorden_title_meeting_comments', 'Bemærkninger'),
      '#title' => t('Bemærkninger'),
  );
  $form['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_meeting_placeholder']['os2dagsorden_title_meeting_special_comments'] = array(
      '#type' => 'textfield',
      '#default_value' => variable_get('os2dagsorden_title_meeting_special_comments', 'Særlige forhold'),
      '#title' => t('Særlige forhold'),
  );
  $form['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_meeting_placeholder']['os2dagsorden_title_meeting_participants'] = array(
      '#type' => 'textfield',
      '#default_value' => variable_get('os2dagsorden_title_meeting_participants', 'Deltagere'),
      '#title' => t('Deltagere'),
  );
  $form['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_meeting_placeholder']['os2dagsorden_title_meeting_cancelled_participants'] = array(
      '#type' => 'textfield',
      '#default_value' => variable_get('os2dagsorden_title_meeting_cancelled_participants', 'Afbud / Fraværende'),
      '#title' => t('Afbud / Fraværende'),
  );
  $form['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_meeting_placeholder']['os2dagsorden_title_meeting_agenda'] = array(
      '#type' => 'textfield',
      '#default_value' => variable_get('os2dagsorden_title_meeting_agenda', 'Dagsorden:'),
      '#title' => t('Dagsorden'),
  );
  $form['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_meeting_placeholder']['os2dagsorden_title_meeting_closed_agenda'] = array(
      '#type' => 'textfield',
      '#default_value' => variable_get('os2dagsorden_title_meeting_closed_agenda', 'Lukket Dagsorden:'),
      '#title' => t('Lukket Dagsorden'),
  );
  $form['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_meeting_placeholder']['os2dagsorden_title_meeting_committee'] = array(
      '#type' => 'textfield',
      '#default_value' => variable_get('os2dagsorden_title_meeting_committee', 'Udvalg'),
      '#title' => t('Udvalg'),
  );
  $form['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_meeting_placeholder']['os2dagsorden_title_meeting_new_speaker_paper'] = array(
      '#type' => 'textfield',
      '#default_value' => variable_get('os2dagsorden_title_meeting_new_speaker_paper', 'Nyt talepapir'),
      '#title' => t('Nyt talepapir'),
  );
  /*
  $form['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_meeting_placeholder']['os2dagsorden_title_meeting_make_note'] = array(
      '#type' => 'textfield',
      '#default_value' => variable_get('os2dagsorden_title_meeting_make_note', 'Lav note'),
      '#title' => t('Lav note'),
  );*/
  // Upload quide PDF file.
  $form['upload_guide'] = array(
    '#type' => 'fieldset',
    '#title' => t('Quick quide PDF file'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['upload_guide']['quick_guide_upload_fid'] = array(
    '#title' => t('Choose a file'),
    '#type' => 'managed_file',
    '#default_value' => variable_get('quick_guide_upload_fid', ''),
    '#description' => t('Remember to save this form.'),
    '#upload_location' => 'public://PDF/',
  );
    // Upload quide PDF file.
  $form['os2dagsorden_right_sidebar_arrow_position'] = array(
    '#type' => 'fieldset',
    '#title' => t('Sidepane arrow position'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['os2dagsorden_right_sidebar_arrow_position']['os2dagsorden_right_sidebar_arrow_position_radios'] = array(
    '#title' => t('Sidepane arrow position'),
    '#type' => 'radios',
    '#options' => array('classic' => 'classic', 'equal_height' => 'equal height'),
    '#default_value' => variable_get('os2dagsorden_right_sidebar_arrow_position_radios', 'classic'),
    '#description' => t('Default position or equal height with meeting blocks.'),
  );

  //meeting calendar view settings
  $form['os2dagsorden_meeting_view_calendar_settings'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed'=>TRUE,
    '#title' => t('Meeting view calendar settings'),
  );
  $form['os2dagsorden_meeting_view_calendar_settings']['os2dagsorden_meeting_view_calendar_short_name'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use committee short instead of the meeting name'),
    '#description' => t('This decides whether a committee short name will used instead of meeting name in the calendar view'),
    '#default_value' => variable_get('os2dagsorden_meeting_view_calendar_short_name',FALSE),
  );
  //sort items alphabetically
  ksort($form);
  return system_settings_form($form);
}

/**
 * Validates pdf2htmlEX installation by checking if which commands returns anything.
 *
 * @param $element
 * @param $form_state
 */
function _os2dagsorden_pdf2htmlEX_validate($element, &$form_state){
  $value = $element['#value'];
  if(!empty($value)) {
    $exec = shell_exec("which " . $value);
    if(empty($exec)){
            form_error($element, "Incorrect pdf2htmlEX path");
            watchdog("os2dagsorden", t('Incorrect pdf2htmlEX path'));
    }
  }
}

/**
 * Validates URL responce.
 * if response code not 200, form error is set.
 *
 * @param $element
 * @param $form_state
 */
function _os2dagsorden_url_responce_validate($element, &$form_state){
  $value = $element['#value'];

  if ($value != "") {
    $url = (strpos($value, "http://") !== 0) ? 'http://' . $value : $value;
     
    $ch = curl_init($url);
    curl_setopt($ch, CURLOPT_NOBODY, true);
    curl_exec($ch);
    $retcode = curl_getinfo($ch, CURLINFO_HTTP_CODE);
 
    if ($retcode != 200) {
      form_error(
        $element,
        t("Specified url !url does not respond. Error code: !retcode", array(
          '!url' => $url,
          '!retcode' => $retcode,
        ))
      );
    }
    curl_close($ch);
  }
}

/**
 * Checks that files for SOFD are presen.
 * File paths are: "public://acadre_views/V_web_MeetingGroups.xml",
 * "public://acadre_views/V_web_AcadreGroups.xml",
 * "public://acadre_views/V_web_Meetings.xml",
 *
 * @param $element
 * @param $form_state
 */
function _os2dagsorden_sofd_local_copy_validate($element, &$form_state){
  $value = $element['#value'];
  //if checked
  if($value == 1){
    if(is_dir("public://acadre_views"))
    {
      //check files in directory
      $files = array("public://acadre_views/V_web_MeetingGroups.xml",
        "public://acadre_views/V_web_AcadreGroups.xml",
        "public://acadre_views/V_web_Meetings.xml",
      );

      foreach ($files as $file) {
        if (!file_exists($file)) {
          form_error($element, t("File !file does not exist.", array('!file' => $file)));
        }
      }

    }
    else{
      form_error($element, t("directory public://acadre_views does not exist."));
    }

  }
}

/**
 * Validates that the pdf rendering path is present and writable.
 *
 * @param $element
 * @param $form_state
 */
function _os2dagsorden_pdf2html_rendering_path_validate($element, &$form_state){
  $value = $element['#value'];
  if ($value != "") {
    if (is_dir($value)) {
      if (!is_writable($value)) {
        form_error($element, t("Could not writte to directory. Please check permissions"));
      }
    }
    else {
      form_error($element, t("Directory does not exist"));
    }
  }
}

/**
 * Validates that the os2web conversion path is present and writable.
 *
 * @param $element
 * @param $form_state
 */
function _os2dagsorden_os2web_convertion_dir_validate($element, &$form_state){
  $value = $element['#value'];
  if(file_exists($value)){
    if(!is_writable($value)){
      form_error($element, t("Could not writte to directory. Please check permissions"));
    }
  }else{
    form_error($element, t("Directory !value does nor exist", array('!value' => $value)));
  }
}

/**
 * Hook to system for submit. Stores the frequencies of the cronjob if they are different from the default provided by ultimate cron module
 *
 * @param $form       the settings form
 * @param $form_state the state of the form
 *
 * @return none.
 */
function os2dagsorden_settings_cron_job_submit($form, &$form_state) {
  $input = $form_state['input'];

  //os2dagsorden_importer_cron
  $conf = _ultimate_cron_default_settings();
  if (!empty($input['os2dagsorden_importer_cron']) && $input['os2dagsorden_importer_cron'] !== variable_get('ultimate_cron_rule', ULTIMATE_CRON_RULE)) {
    $conf['rules'][0] = $input['os2dagsorden_importer_cron'];
  }
  else {
    unset($conf['rules']);
  }
  $conf['service_group'] = "";
  ultimate_cron_set_settings('os2dagsorden_importer_cron', $conf);

  //os2dagsorden_acadre_service_importer
  $conf = _ultimate_cron_default_settings();
  if (!empty($input['os2dagsorden_acadre_service_importer_cron']) && $input['os2dagsorden_acadre_service_importer_cron'] !== variable_get('ultimate_cron_rule', ULTIMATE_CRON_RULE)) {
    $conf['rules'][0] = $input['os2dagsorden_acadre_service_importer_cron'];
  }
  else {
    unset($conf['rules']);
  }
  $conf['service_group'] = "";
  ultimate_cron_set_settings('os2dagsorden_acadre_service_importer_cron', $conf);

  //os2web_esdh_provider_cron
  $conf = _ultimate_cron_default_settings();
  if (!empty($input['os2web_esdh_provider_cron']) && $input['os2web_esdh_provider_cron'] !== variable_get('ultimate_cron_rule', ULTIMATE_CRON_RULE)) {
    $conf['rules'][0] = $input['os2web_esdh_provider_cron'];
  }
  else {
    unset($conf['rules']);
  }
  $conf['service_group'] = "";
  ultimate_cron_set_settings('os2web_esdh_provider_cron', $conf);

  //os2dagsorden_pdf2htmlex_cron
  $conf = _ultimate_cron_default_settings();
  if (!empty($input['os2dagsorden_pdf2htmlex_cron']) && $input['os2dagsorden_pdf2htmlex_cron'] !== variable_get('ultimate_cron_rule', ULTIMATE_CRON_RULE)) {
    $conf['rules'][0] = $input['os2dagsorden_pdf2htmlex_cron'];
  }
  else {
    unset($conf['rules']);
  }
  $conf['service_group'] = "";
  ultimate_cron_set_settings('os2dagsorden_pdf2htmlex_cron', $conf);

  //os2dagsorden_adlib_api_cron
  $conf = _ultimate_cron_default_settings();
  if (!empty($input['os2dagsorden_adlib_api_cron']) && $input['os2dagsorden_adlib_api_cron'] !== variable_get('ultimate_cron_rule', ULTIMATE_CRON_RULE)) {
    $conf['rules'][0] = $input['os2dagsorden_adlib_api_cron'];
  }
  else {
    unset($conf['rules']);
  }
  $conf['service_group'] = "";
  ultimate_cron_set_settings('os2dagsorden_adlib_api_cron', $conf);
}

/**
 * Sets the variables to the ones imported from the file.
 *
 * @param $form       the settings form
 * @param $form_state the state of the form
 *
 * @return none.
 */
function os2dagsorden_settings_import_from_file($form, &$form_state){
  if (!$form_state['values']['os2dagsorden_settings_file']){
    drupal_set_message(t('No file has beed added'), 'error');
  } else {
    drupal_set_message(t('Imported settings from file'));

    $file = file_load($form_state['values']['os2dagsorden_settings_file']);
    $file->status = FILE_STATUS_PERMANENT;
    file_save($file);

    variable_set('os2dagsorden_settings_file', $file->fid);
    $content = file_get_contents(drupal_realpath($file->uri));
    file_put_contents(drupal_realpath($file->uri), trim($content));
    $setting_array = parse_ini_file(drupal_realpath($file->uri),true);

    variable_set('os2dagsorden_body_text_size', $setting_array['os2dagsorden_body_text_layout']['os2dagsorden_body_text_size']);
    variable_set('os2dagsorden_title_text_size', $setting_array['os2dagsorden_title_text_layout']['os2dagsorden_title_text_size']);

    variable_set('os2dagsorden_show_meeting_committee', $setting_array['os2dagsorden_meeting_view_settings']['os2dagsorden_show_meeting_committee']);
    variable_set('os2dagsorden_show_meeting_enddate', $setting_array['os2dagsorden_meeting_view_settings']['os2dagsorden_show_meeting_enddate']);
    variable_set('os2dagsorden_show_meeting_type', $setting_array['os2dagsorden_meeting_view_settings']['os2dagsorden_show_meeting_type']);
    variable_set('os2dagsorden_show_samlet_dokument_link', $setting_array['os2dagsorden_meeting_view_settings']['os2dagsorden_show_samlet_dokument_link']);
    variable_set('os2dagsorden_show_participants_afbud', $setting_array['os2dagsorden_meeting_view_settings']['os2dagsorden_show_participants_afbud']);
    variable_set('os2dagsorden_show_print_icon', $setting_array['os2dagsorden_meeting_view_settings']['os2dagsorden_show_print_icon']);
    variable_set('os2dagsorden_show_bullet_case_id_link', $setting_array['os2dagsorden_meeting_view_settings']['os2dagsorden_show_bullet_case_id_link']);
    variable_set('os2dagsorden_bullet_case_id_link_url', $setting_array['os2dagsorden_meeting_view_settings']['os2dagsorden_bullet_case_id_link_url']);
    variable_set('os2dagsorden_show_comments', $setting_array['os2dagsorden_meeting_view_settings']['os2dagsorden_show_comments']);
    variable_set('os2dagsorden_show_closed_bullet_point_content', $setting_array['os2dagsorden_meeting_view_settings']['os2dagsorden_show_closed_bullet_point_content']);
    variable_set('os2dagsorden_show_bilag', $setting_array['os2dagsorden_meeting_view_settings']['os2dagsorden_show_bilag']);
    variable_set('os2dagsorden_use_abbr', $setting_array['os2dagsorden_meeting_view_settings']['os2dagsorden_use_abbr']);
    variable_set('os2dagsorden_show_bp_comname', $setting_array['os2dagsorden_meeting_view_settings']['os2dagsorden_show_bp_comname']);
    variable_set('os2dagsorden_allow_pdf_download', $setting_array['os2dagsorden_meeting_view_settings']['os2dagsorden_allow_pdf_download']);

    variable_set('os2dagsorden_sager_group_title', $setting_array['os2dagsorden_meeting_view_settings']['os2dagsorden_sager_group_title']);
    variable_set('os2dagsorden_group_closed_bullet_points', $setting_array['os2dagsorden_meeting_view_settings']['os2dagsorden_group_closed_bullet_points']);
    variable_set('os2dagsorden_hidden_agenda_committee', $setting_array['os2dagsorden_meeting_view_settings']['os2dagsorden_hidden_agenda_committee']);
    variable_set('os2dagsorden_meeting_description_download_dropdown', $setting_array['os2dagsorden_meeting_view_settings']['os2dagsorden_meeting_description_download_dropdown']);
    variable_set('os2dagsorden_meeting_description_download_title', $setting_array['os2dagsorden_meeting_view_settings']['os2dagsorden_meeting_description_download_title']);
    variable_set('os2dagsorden_meeting_description_download_title_additional', $setting_array['os2dagsorden_meeting_view_settings']['os2dagsorden_meeting_description_download_title_additional']);

    variable_set('os2dagsorden_shared_speaker_paper', $setting_array['os2dagsorden_speaker_paper_settings']['os2dagsorden_shared_speaker_paper']);

    variable_set('os2dagsorden_expand_all_bullets',$setting_array['os2dagsorden_meeting_view_layout']['os2dagsorden_expand_all_bullets']);
    variable_set('os2dagsorden_expand_attachment_onload', $setting_array['os2dagsorden_meeting_view_layout']['os2dagsorden_expand_attachment_onload']);
    variable_set('os2dagsorden_expand_bilags', $setting_array['os2dagsorden_meeting_view_layout']['os2dagsorden_expand_bilags']);
    variable_set('os2dagsorden_expand_cases', $setting_array['os2dagsorden_meeting_view_layout']['os2dagsorden_expand_cases']);
    variable_set('os2dagsorden_show_massive_expand_collapse_button', $setting_array['os2dagsorden_meeting_view_layout']['os2dagsorden_show_massive_expand_collapse_button']);
    variable_set('os2dagsorden_show_bilag_bullet_point', $setting_array['os2dagsorden_meeting_view_layout']['os2dagsorden_show_bilag_bullet_point']);
    variable_set('os2dagsorden_show_case_bullet_point', $setting_array['os2dagsorden_meeting_view_layout']['os2dagsorden_show_case_bullet_point']);
    variable_set('os2dagsorden_show_bullet_case_nr', $setting_array['os2dagsorden_meeting_view_layout']['os2dagsorden_show_bullet_case_nr']);

    variable_set('os2dagsorden_latest_meetings_view_mode', $setting_array['os2dagsorden_latest_meetings_view_settings']['os2dagsorden_latest_meetings_view_mode']);
    variable_set('os2dagsorden_meetings_views_last_8_show_meeting_title', $setting_array['os2dagsorden_latest_meetings_view_settings']['os2dagsorden_meetings_views_last_8_show_meeting_title']);
    variable_set('os2dagsorden_meetings_views_last_8_show_meeting_committee', $setting_array['os2dagsorden_latest_meetings_view_settings']['os2dagsorden_meetings_views_last_8_show_meeting_committee']);
    variable_set('os2dagsorden_meetings_views_last_8_show_meeting_location', $setting_array['os2dagsorden_latest_meetings_view_settings']['os2dagsorden_meetings_views_last_8_show_meeting_location']);
    variable_set('os2dagsorden_meetings_views_last_8_show_meeting_is_closed', $setting_array['os2dagsorden_latest_meetings_view_settings']['os2dagsorden_meetings_views_last_8_show_meeting_is_closed']);

    variable_set('os2dagsorden_collapse_menu', $setting_array['os2dagsorden_frontpage_layout']['os2dagsorden_collapse_menu']);
    variable_set('os2dagsorden_collapse_menu_touch', $setting_array['os2dagsorden_frontpage_layout']['os2dagsorden_collapse_menu_touch']);
    variable_set('os2dagsorden_frontpage_layout', $setting_array['os2dagsorden_frontpage_layout']['os2dagsorden_frontpage_layout']);
    variable_set('os2dagsorden_show_search_block_title', $setting_array['os2dagsorden_frontpage_layout']['os2dagsorden_show_search_block_title']);

    variable_set('os2dagsorden_meetings_search_show_meeting_committee', $setting_array['os2dagsorden_meeting_search_view_settings']['os2dagsorden_meetings_search_show_meeting_committee']);
    variable_set('os2dagsorden_meetings_search_show_meeting_location', $setting_array['os2dagsorden_meeting_search_view_settings']['os2dagsorden_meetings_search_show_meeting_location']);
    variable_set('os2dagsorden_meetings_search_show_meeting_status', $setting_array['os2dagsorden_meeting_search_view_settings']['os2dagsorden_meetings_search_show_meeting_status']);
    variable_set('os2dagsorden_meetings_search_include_add_agenda', $setting_array['os2dagsorden_meeting_search_view_settings']['os2dagsorden_meetings_search_include_add_agenda']);

    variable_set('os2dagsorden_search_startdate', $setting_array['os2dagsorden_meeting_search_view_settings']['os2dagsorden_search_startdate']);
    variable_set('os2dagsorden_search_enddate', $setting_array['os2dagsorden_meeting_search_view_settings']['os2dagsorden_search_enddate']);
    variable_set('os2dagsorden_search_meeting_is_closed', $setting_array['os2dagsorden_meeting_search_view_settings']['os2dagsorden_search_meeting_is_closed']);

    variable_set('os2dagsorden_budget_committee', $setting_array['os2dagsorden_sidepane_menu_layout']['os2dagsorden_budget_committee']);

    variable_set('os2dagsorden_participants_delimeter', $setting_array['os2dagsorden_meeting_import']['os2dagsorden_participants_delimeter']);
    variable_set('os2dagsorden_send_notification_committee', $setting_array['os2dagsorden_meeting_import']['os2dagsorden_send_notification_committee']);
    variable_set('os2dagsorden_send_email_subject', $setting_array['os2dagsorden_meeting_import']['os2dagsorden_send_email_subject']);
    variable_set('os2dagsorden_send_email_body', $setting_array['os2dagsorden_meeting_import']['os2dagsorden_send_email_body']);
    variable_set('os2dagsorden_follows_committee_send_notification', $setting_array['os2dagsorden_meeting_import']['os2dagsorden_follows_committee_send_notification']);
    variable_set('os2dagsorden_send_timespan_of_notification', $setting_array['os2dagsorden_meeting_import']['os2dagsorden_send_timespan_of_notification']);

    variable_set('os2dagsorden_add_type_prefix', $setting_array['os2dagsorden_meeting_import']['os2dagsorden_add_type_prefix']);
    variable_set('os2dagsorden_committee_category_pol', $setting_array['os2dagsorden_meeting_import']['os2dagsorden_committee_category_pol']);
    variable_set('os2dagsorden_committee_category_org', $setting_array['os2dagsorden_meeting_import']['os2dagsorden_committee_category_org']);

    if (module_exists('os2web_pdf_conversion_manager')) {
	variable_set('os2web_copied_filetype', $setting_array['os2dagsorden_file_import']['os2web_copied_filetype']);
	variable_set('os2web_convertion_dir', $setting_array['os2dagsorden_file_import']['os2web_convertion_dir']);
    }

    if (module_exists('os2dagsorden_pdf2htmlex')) {
	variable_set('os2dagsorden_pdf2htmlex_path', $setting_array['os2dagsorden_pdf2htmlex_settings']['os2dagsorden_pdf2htmlex_path']);
	variable_set('pdf2html_rendering_path', $setting_array['os2dagsorden_pdf2htmlex_settings']['pdf2html_rendering_path']);
    }

    variable_set('os2dagsorden_show_meeting_category', $setting_array['os2dagsorden_political_organizational_settings']['os2dagsorden_show_meeting_category']);
    variable_set('os2dagsorden_user_default_meeting_category', $setting_array['os2dagsorden_political_organizational_settings']['os2dagsorden_user_default_meeting_category']);
    variable_set('os2dagsorden_default_meeting_cateroty',$setting_array['os2dagsorden_political_organizational_settings']['os2dagsorden_default_meeting_cateroty']);


    variable_set('ultimate_cron_rule', $setting_array['os2dagsorden_cron_job_freq']['os2dagsorden_importer_cron']);
    variable_set('ultimate_cron_rule', $setting_array['os2dagsorden_cron_job_freq']['os2dagsorden_acadre_service_importer_cron']);
    variable_set('ultimate_cron_rule',  $setting_array['os2dagsorden_cron_job_freq']['os2web_esdh_provider_cron']);
    variable_set('ultimate_cron_rule', $setting_array['os2dagsorden_cron_job_freq']['os2dagsorden_pdf2htmlex_cron']);
    variable_set('ultimate_cron_rule', $setting_array['os2dagsorden_cron_job_freq']['os2dagsorden_adlib_api_cron']);

    if (module_exists('os2dagsorden_importer')){
	variable_set('os2dagsorden_pws_use_local_copy', $setting_array['os2dagsorden_pws_sofd_group']['os2dagsorden_pws_use_local_copy']);
	variable_set('os2dagsorden_pws_v_meetings_url', $setting_array['os2dagsorden_pws_sofd_group']['os2dagsorden_pws_v_meetings_url']);
	variable_set('os2dagsorden_pws_v_meetinggroups_url', $setting_array['os2dagsorden_pws_sofd_group']['os2dagsorden_pws_v_meetinggroups_url']);
	variable_set('os2dagsorden_pws_v_acadregroups_url', $setting_array['os2dagsorden_pws_sofd_group']['os2dagsorden_pws_v_acadregroups_url']);
    }

    if (module_exists('os2dagsorden_acadre_service_importer')){
      variable_set('os2dagsorden_acadre_service_meetings_url', $setting_array['os2dagsorden_acadre_service_importer_placeholder']['os2dagsorden_acadre_service_meetings_url']);
      variable_set('os2dagsorden_acadre_service_committees_url', $setting_array['os2dagsorden_acadre_service_importer_placeholder']['os2dagsorden_acadre_service_committees_url']);
    }

    variable_set('os2dagsorden_upcoming_meetings_help_text', $setting_array['os2dagsorden_help_text_placeholder']['os2dagsorden_upcoming_meetings_help_text']);
    variable_set('os2dagsorden_meetings_search_help_text', $setting_array['os2dagsorden_help_text_placeholder']['os2dagsorden_meetings_search_help_text']);
    variable_set('os2dagsorden_meetings_search_block_help_text', $setting_array['os2dagsorden_help_text_placeholder']['os2dagsorden_meetings_search_block_help_text']);
    variable_set('os2dagsorden_last_8_meetings_help_text', $setting_array['os2dagsorden_help_text_placeholder']['os2dagsorden_last_8_meetings_help_text']);
    variable_set('os2dagsorden_annotator_help_text', $setting_array['os2dagsorden_help_text_placeholder']['os2dagsorden_annotator_help_text']);
    variable_set('os2dagsorden_calendar_help_text', $setting_array['os2dagsorden_help_text_placeholder']['os2dagsorden_calendar_help_text']);
    variable_set('os2dagsorden_user_committees_help_text', $setting_array['os2dagsorden_help_text_placeholder']['os2dagsorden_user_committees_help_text']);
    variable_set('os2dagsorden_user_follows_help_text', $setting_array['os2dagsorden_help_text_placeholder']['os2dagsorden_user_follows_help_text']);
    variable_set('os2dagsorden_calendar_replacement_block_text', $setting_array['os2dagsorden_help_text_placeholder']['os2dagsorden_calendar_replacement_block_text']);

    variable_set('os2dagsorden_title_general_mine_indstillinger', $setting_array['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_general_placeholder']['os2dagsorden_title_general_mine_indstillinger']);
    variable_set('os2dagsorden_title_general_log_off', $setting_array['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_general_placeholder']['os2dagsorden_title_general_log_off']);
    variable_set('os2dagsorden_title_general_search', $setting_array['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_general_placeholder']['os2dagsorden_title_general_search']);

    variable_set('os2dagsorden_title_frontpage_coming_meetings', $setting_array['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_frontpage_placeholder']['os2dagsorden_title_frontpage_coming_meetings'] );
    variable_set('os2dagsorden_title_frontpage_last_8_my_meetings', $setting_array['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_frontpage_placeholder']['os2dagsorden_title_frontpage_last_8_my_meetings']);
    variable_set('os2dagsorden_title_frontpage_last_8_all_meetings', $setting_array['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_frontpage_placeholder']['os2dagsorden_title_frontpage_last_8_all_meetings']);
    variable_set('os2dagsorden_title_frontpage_calendar', $setting_array['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_frontpage_placeholder']['os2dagsorden_title_frontpage_calendar']);
    variable_set('os2dagsorden_title_frontpage_member_of', $setting_array['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_frontpage_placeholder']['os2dagsorden_title_frontpage_member_of']);
    variable_set('os2dagsorden_title_frontpage_following', $setting_array['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_frontpage_placeholder']['os2dagsorden_title_frontpage_following']);
    variable_set('os2dagsorden_title_frontpage_account_settings', $setting_array['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_frontpage_placeholder']['os2dagsorden_title_frontpage_account_settings']);
    variable_set('os2dagsorden_title_frontpage_home', $setting_array['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_frontpage_placeholder']['os2dagsorden_title_frontpage_home']);
    variable_set('os2dagsorden_title_frontpage_halfyear_calendar', $setting_array['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_frontpage_placeholder']['os2dagsorden_title_frontpage_halfyear_calendar']);

    variable_set('os2dagsorden_title_meeting_status', $setting_array['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_meeting_placeholder']['os2dagsorden_title_meeting_status']);
    variable_set('os2dagsorden_title_meeting_meeting', $setting_array['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_meeting_placeholder']['os2dagsorden_title_meeting_meeting']);
    variable_set('os2dagsorden_title_meeting_date', $setting_array['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_meeting_placeholder']['os2dagsorden_title_meeting_date']);
    variable_set('os2dagsorden_title_meeting_location', $setting_array['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_meeting_placeholder']['os2dagsorden_title_meeting_freetext_placing']);
    variable_set('os2dagsorden_title_meeting_freetext_placing', $setting_array['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_meeting_placeholder']['os2dagsorden_title_meeting_location']);
    variable_set('os2dagsorden_title_meeting_comments', $setting_array['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_meeting_placeholder']['os2dagsorden_title_meeting_comments']);
    variable_set('os2dagsorden_title_meeting_special_comments', $setting_array['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_meeting_placeholder']['os2dagsorden_title_meeting_special_comments']);
    variable_set('os2dagsorden_title_meeting_participants', $setting_array['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_meeting_placeholder']['os2dagsorden_title_meeting_participants']);
    variable_set('os2dagsorden_title_meeting_cancelled_participants', $setting_array['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_meeting_placeholder']['os2dagsorden_title_meeting_cancelled_participants']);
    variable_set('os2dagsorden_title_meeting_agenda', $setting_array['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_meeting_placeholder']['os2dagsorden_title_meeting_agenda']);
    variable_set('os2dagsorden_title_meeting_closed_agenda', $setting_array['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_meeting_placeholder']['os2dagsorden_title_meeting_closed_agenda']);
    variable_set('os2dagsorden_title_meeting_committee', $setting_array['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_meeting_placeholder']['os2dagsorden_title_meeting_committee']);
    variable_set('os2dagsorden_title_meeting_new_speaker_paper', $setting_array['os2dagsorden_terminology_placeholder']['os2dagsorden_terminology_meeting_placeholder']['os2dagsorden_title_meeting_new_speaker_paper']);

    variable_set('os2dagsorden_meeting_view_calendar_short_name', $setting_array['os2dagsorden_meeting_view_calendar_settings']['os2dagsorden_meeting_view_calendar_short_name']);
  }
}
