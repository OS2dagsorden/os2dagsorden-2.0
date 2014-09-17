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
  $form['os2dagsorden_meeting_view_settings'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
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
    '#title' => 'List of committees which agenda is completely hidden to those without the rights',
    '#maxlength' => 200,
    '#description' => 'Comma-separated list of committees ID which agenda and the summary (samlet dokument) is hidden to those without the rights',
    '#default_value' => variable_get('os2dagsorden_hidden_agenda_committee', OS2DAGSORDEN_HIDDEN_AGENGA_COMMITTEE),
  );
  $form['os2dagsorden_meeting_view_settings']['os2dagsorden_meeting_description_download_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Meeting description download button'),
    '#maxlength' => 200,
    '#description' => t('Title of the meeting description download button'),
    '#default_value' => variable_get('os2dagsorden_meeting_description_download_title', 'Hent samlet dokument i PDF'),
  );
  $form['os2dagsorden_meeting_view_settings']['os2dagsorden_meeting_description_download_title_additional'] = array(
    '#type' => 'textfield',
    '#title' => t('Meeting additional description download button'),
    '#maxlength' => 200,
    '#description' => t('Title of the meeting additional description download button'),
    '#default_value' => variable_get('os2dagsorden_meeting_description_download_title_additional', 'Hent tillægsdokument i PDF'),
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
  $form['os2dagsorden_frontpage_layout']['os2dagsorden_show_search_block_title'] = array(
    '#type' => 'radios',
    '#title' => t('Show/Hide search block title'),
    '#default_value' => variable_get('os2dagsorden_show_search_block_title', 'true'),
    '#options' => array('true' => t('Show'), 'false' => t('Hide')),
    '#description' => t('This decides whether a search block title show/hide.'),
  );
  $form['os2dagsorden_frontpage_layout']['os2dagsorden_my_committees_block_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title of my committees block'),
    '#default_value' => variable_get('os2dagsorden_my_committees_block_title', 'Medlem af'),
    '#description' => t('This set a title of a block listing all committees user is a member of.'),
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
    '#title' => t('Show meeting committee on meeting serach view'),
    '#description' => t('This decides whether a meeting committee is visible on meeting search view.'),
    '#default_value' => variable_get('os2dagsorden_meetings_search_show_meeting_committee', TRUE),
  );
  $form['os2dagsorden_meeting_search_view_settings']['os2dagsorden_meetings_search_show_meeting_status'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show meeting status on meeting serach view'),
    '#description' => t('This decides whether a meeting status is visible on meeting search view.'),
    '#default_value' => variable_get('os2dagsorden_meetings_search_show_meeting_status', FALSE),
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
      '#href' => 'admin/structure/context/list/os2dagsorden_sidepane/edit',
      '#title' => t('Change order of sidepane blocks'),
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
    '#title' => 'Send notification of committees',
    '#maxlength' => 250,
    '#default_value' => variable_get('os2dagsorden_send_notification_committee', FALSE),
    '#description' => t('Comma-separated list of committees changing status of which should send an email notification.'),
    '#autocomplete_path' => 'get_committee/autocomplete',
  );
  $form['os2dagsorden_meeting_import']['os2dagsorden_send_email_subject'] = array(
    '#type' => 'textfield',
    '#title' => 'Meeting notification email text',
    '#description' => 'The email subject, which would be send to users interested in meeting publishing - Member / Follow+ / Follow (optional)',
    '#default_value' => variable_get('os2dagsorden_send_email_subject', '!meeting_type til !committee er publiceret'),
  );
  $form['os2dagsorden_meeting_import']['os2dagsorden_send_email_body'] = array(
    '#type' => 'textarea',
    '#title' => 'Meeting notification email text',
    '#description' => 'The email body, which would be send to users interested in meeting publishing - Member / Follow+ / Follow (optional)',
    '#default_value' => variable_get('os2dagsorden_send_email_body', 'Til !user' . PHP_EOL . PHP_EOL .
      'Du abonnerer på !committee.' . PHP_EOL . 'Der er publiceret !meeting_type til !meeting_name !meeting_date.'),
  );
  $form['os2dagsorden_meeting_import']['os2dagsorden_send_email_text_available_variables'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#value' => 'Can be used both in subject and body:<br/>
    <b>!committe</b> - name of the committee<br/>
    <b>!meeting_name</b> - title of the meeting<br/>
    <b>!meeting_date</b> - date of the meeting<br/>
    <b>!meeting_type</b> - type of the meeting with acticle: <i>et referat</i> or <i>en dagsorden</i><br/>
    <b>!user</b> - name of the user that message is sent to<br/>',
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
    '#title' => 'Meeting should be not older than:',
    '#maxlength' => 200,
    '#field_suffix' => 'Days',
    '#size' => 10,
    '#description' => 'If meeting is not older than the set amount of day, notification is sent. <br/>Otherwise notification process is skipped',
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
         '#title' => 'Path to pdf2htmlEX',
         '#description' => 'Path to pdf2htmlEX',
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
    '#default_value'=>variable_get('os2dagsorden_user_default_meeting_category', array())
  );  
   $form['os2dagsorden_political_organizational_settings']['os2dagsorden_default_meeting_cateroty'] = array(
    '#type' => 'radios',
    '#title' => t('Default meeting category'),
    '#default_value' => variable_get('os2dagsorden_default_meeting_cateroty','pol'),
    '#options' =>  array('pol' => t('Political'), 'org' => t('Organisation')),
    '#description' => t('This decides whether a default meeting category'),
  );

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
    '#element_validate' => array('_os2dagsorden_url_responce_validate'),
  );
  $form['os2dagsorden_pws_sofd_group']['os2dagsorden_pws_v_meetinggroups_url'] = array(
    '#type' => 'textfield',
    '#default_value' => variable_get('os2dagsorden_pws_v_meetinggroups_url'),
    '#title' => t('Meeting groups (is member of/follows/follows+) view url:'),
    '#maxlength' => 256,
    '#disabled' => variable_get('os2dagsorden_pws_use_local_copy'),
    '#element_validate' => array('_os2dagsorden_url_responce_validate'),
  );
  $form['os2dagsorden_pws_sofd_group']['os2dagsorden_pws_v_acadregroups_url'] = array(
    '#type' => 'textfield',
    '#default_value' => variable_get('os2dagsorden_pws_v_acadregroups_url'),
    '#title' => t('Acadre groups (committees) url:'),
    '#maxlength' => 256,
    '#disabled' => variable_get('os2dagsorden_pws_use_local_copy'),
    '#element_validate' => array('_os2dagsorden_url_responce_validate'),
  );
  } 
  
   return system_settings_form($form);
}

function _os2dagsorden_pdf2htmlEX_validate($element, &$form_state){
    $value = $element['#value'];
    $exec = shell_exec("which " . $value);
    if(empty($exec)){
            form_error($element, "Incorrect pdf2htmlEX path");
            watchdog("os2dagsorden", t('Incorrect pdf2htmlEX path'));
        }
}

function _os2dagsorden_url_responce_validate($element, &$form_state){
  $value = $element['#value'];

  if ($value != "") {
    $url = (strpos($value, "http://") !== 0) ? 'http://' . $value : $value;

    $ch = curl_init($url);
    curl_setopt($ch, CURLOPT_NOBODY, true);
    curl_exec($ch);
    $retcode = curl_getinfo($ch, CURLINFO_HTTP_CODE);

    if ($retcode != 200) {
      form_error($element, "Specified url does not respond.");
    }
    curl_close($ch);
  }
}

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
          form_error($element, "File " . $file . " does not exist.");
        }
      }

    }
    else{
      form_error($element, "directory public://acadre_views does not exist.");
    }

  }
}

function _os2dagsorden_pdf2html_rendering_path_validate($element, &$form_state){
  $value = $element['#value'];
  if ($value != "") {
    if (is_dir($value)) {
      if (!is_writable($value)) {
        form_error($element, "Could not writte to directory. Please check permissions");
      }
    }
    else {
      form_error($element, "Directory does not exist");
    }
  }
}

function _os2dagsorden_os2web_convertion_dir_validate($element, &$form_state){
  $value = $element['#value'];
  if(file_exists($value)){
    if(!is_writable($value)){
      form_error($element, "Could not writte to directory. Please check permissions");
    }
  }else{
    form_error($element, "Directory " . $value . " does nor exist");
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
