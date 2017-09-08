<?php
/**
 * @file
 * os2dagsorden_meeting_views.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function os2dagsorden_meeting_views_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'kommende_m_der_i_mine_udvalg';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Kommende møder i mine udvalg';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Kommende møder i mine udvalg';
  $handler->display->display_options['css_class'] = 'front-page-content-block';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    2 => '2',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['query']['options']['pure_distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Gendan';
  $handler->display->display_options['pager']['type'] = 'mini';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« første';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ forrige';
  $handler->display->display_options['pager']['options']['tags']['next'] = 'næste >';
  $handler->display->display_options['pager']['options']['tags']['last'] = 'sidste »';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'nid' => 'nid',
    'tid' => 'tid',
    'field_os2web_meetings_type' => 'field_os2web_meetings_type',
    'php_1' => 'php_2',
    'php' => 'php_2',
    'php_2' => 'php_2',
    'field_os2web_meetings_date' => 'field_os2web_meetings_date',
    'php_4' => 'php_4',
    'field_os2web_meetings_committee' => 'field_os2web_meetings_committee',
    'field_os2web_meetings_com_shname' => 'field_os2web_meetings_com_shname',
    'php_3' => 'php_3',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'nid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'tid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_os2web_meetings_type' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'php_1' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'php' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'php_2' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'field_os2web_meetings_date' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'php_4' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'field_os2web_meetings_committee' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_os2web_meetings_com_shname' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'php_3' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
  );
  /* Header: help text */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['ui_name'] = 'help text';
  $handler->display->display_options['header']['area']['empty'] = TRUE;
  $handler->display->display_options['header']['area']['content'] = '<?php
os2dagsorden_meeting_views_coming_meetings_help_text();
?>';
  $handler->display->display_options['header']['area']['format'] = 'php_code';
  /* Relationship: Content: Committee (field_os2web_meetings_committee) */
  $handler->display->display_options['relationships']['field_os2web_meetings_committee_tid']['id'] = 'field_os2web_meetings_committee_tid';
  $handler->display->display_options['relationships']['field_os2web_meetings_committee_tid']['table'] = 'field_data_field_os2web_meetings_committee';
  $handler->display->display_options['relationships']['field_os2web_meetings_committee_tid']['field'] = 'field_os2web_meetings_committee_tid';
  /* Field: nid hidden */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['ui_name'] = 'nid hidden';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: committee tid */
  $handler->display->display_options['fields']['tid']['id'] = 'tid';
  $handler->display->display_options['fields']['tid']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['tid']['field'] = 'tid';
  $handler->display->display_options['fields']['tid']['relationship'] = 'field_os2web_meetings_committee_tid';
  $handler->display->display_options['fields']['tid']['ui_name'] = 'committee tid';
  $handler->display->display_options['fields']['tid']['label'] = '';
  $handler->display->display_options['fields']['tid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['tid']['element_label_colon'] = FALSE;
  /* Field: Content: Type */
  $handler->display->display_options['fields']['field_os2web_meetings_type']['id'] = 'field_os2web_meetings_type';
  $handler->display->display_options['fields']['field_os2web_meetings_type']['table'] = 'field_data_field_os2web_meetings_type';
  $handler->display->display_options['fields']['field_os2web_meetings_type']['field'] = 'field_os2web_meetings_type';
  $handler->display->display_options['fields']['field_os2web_meetings_type']['label'] = 'Status';
  $handler->display->display_options['fields']['field_os2web_meetings_type']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_os2web_meetings_type']['alter']['path'] = 'meeting/[nid]';
  /* Field: title - php */
  $handler->display->display_options['fields']['php_2']['id'] = 'php_2';
  $handler->display->display_options['fields']['php_2']['table'] = 'views';
  $handler->display->display_options['fields']['php_2']['field'] = 'php';
  $handler->display->display_options['fields']['php_2']['ui_name'] = 'title - php';
  $handler->display->display_options['fields']['php_2']['label'] = 'Møde';
  $handler->display->display_options['fields']['php_2']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['php_2']['alter']['path'] = 'meeting/[nid]';
  $handler->display->display_options['fields']['php_2']['element_class'] = 'views-field-field-title-short';
  $handler->display->display_options['fields']['php_2']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_2']['php_output'] = '<?php
os2dagsorden_meeting_views_coming_meetings_fields_meeting_title($data);
?>';
  $handler->display->display_options['fields']['php_2']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_2']['php_click_sortable'] = '';
  /* Field: Content: Date */
  $handler->display->display_options['fields']['field_os2web_meetings_date']['id'] = 'field_os2web_meetings_date';
  $handler->display->display_options['fields']['field_os2web_meetings_date']['table'] = 'field_data_field_os2web_meetings_date';
  $handler->display->display_options['fields']['field_os2web_meetings_date']['field'] = 'field_os2web_meetings_date';
  $handler->display->display_options['fields']['field_os2web_meetings_date']['label'] = 'Dato';
  $handler->display->display_options['fields']['field_os2web_meetings_date']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_os2web_meetings_date']['alter']['path'] = 'meeting/[nid]';
  $handler->display->display_options['fields']['field_os2web_meetings_date']['empty'] = '&nbsp;';
  $handler->display->display_options['fields']['field_os2web_meetings_date']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'value',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Location */
  $handler->display->display_options['fields']['php_4']['id'] = 'php_4';
  $handler->display->display_options['fields']['php_4']['table'] = 'views';
  $handler->display->display_options['fields']['php_4']['field'] = 'php';
  $handler->display->display_options['fields']['php_4']['ui_name'] = 'Location';
  $handler->display->display_options['fields']['php_4']['label'] = 'Lokation';
  $handler->display->display_options['fields']['php_4']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['php_4']['alter']['path'] = 'meeting/[nid]';
  $handler->display->display_options['fields']['php_4']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_4']['php_output'] = '<?php
os2dagsorden_meeting_views_coming_meetings_fields_meeting_location($row->nid);
?>';
  $handler->display->display_options['fields']['php_4']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_4']['php_click_sortable'] = '';
  /* Field: Content: Committee */
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['id'] = 'field_os2web_meetings_committee';
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['table'] = 'field_data_field_os2web_meetings_committee';
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['field'] = 'field_os2web_meetings_committee';
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['label'] = '';
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['alter']['path'] = 'meeting/[nid]';
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['type'] = 'taxonomy_term_reference_plain';
  /* Field: Taxonomy term: Name short */
  $handler->display->display_options['fields']['field_os2web_meetings_com_shname']['id'] = 'field_os2web_meetings_com_shname';
  $handler->display->display_options['fields']['field_os2web_meetings_com_shname']['table'] = 'field_data_field_os2web_meetings_com_shname';
  $handler->display->display_options['fields']['field_os2web_meetings_com_shname']['field'] = 'field_os2web_meetings_com_shname';
  $handler->display->display_options['fields']['field_os2web_meetings_com_shname']['relationship'] = 'field_os2web_meetings_committee_tid';
  $handler->display->display_options['fields']['field_os2web_meetings_com_shname']['label'] = 'Udvalg';
  $handler->display->display_options['fields']['field_os2web_meetings_com_shname']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_os2web_meetings_com_shname']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_os2web_meetings_com_shname']['alter']['path'] = 'meeting/[nid]';
  $handler->display->display_options['fields']['field_os2web_meetings_com_shname']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_os2web_meetings_com_shname']['empty'] = '[field_os2web_meetings_committee]';
  $handler->display->display_options['fields']['field_os2web_meetings_com_shname']['type'] = 'text_plain';
  /* Field: Committe */
  $handler->display->display_options['fields']['php_3']['id'] = 'php_3';
  $handler->display->display_options['fields']['php_3']['table'] = 'views';
  $handler->display->display_options['fields']['php_3']['field'] = 'php';
  $handler->display->display_options['fields']['php_3']['ui_name'] = 'Committe';
  $handler->display->display_options['fields']['php_3']['label'] = 'Udvalg';
  $handler->display->display_options['fields']['php_3']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['php_3']['alter']['path'] = 'meeting/[nid]';
  $handler->display->display_options['fields']['php_3']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['php_3']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_3']['php_output'] = '<?php
    os2dagsorden_meeting_views_last_8_meetings_fields_meeting_committee($row->nid);
?>';
  $handler->display->display_options['fields']['php_3']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_3']['php_click_sortable'] = '';
  /* Sort criterion: Content: Date -  start date (field_os2web_meetings_date) */
  $handler->display->display_options['sorts']['field_os2web_meetings_date_value']['id'] = 'field_os2web_meetings_date_value';
  $handler->display->display_options['sorts']['field_os2web_meetings_date_value']['table'] = 'field_data_field_os2web_meetings_date';
  $handler->display->display_options['sorts']['field_os2web_meetings_date_value']['field'] = 'field_os2web_meetings_date_value';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'os2web_meetings_meeting' => 'os2web_meetings_meeting',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Date -  start date (field_os2web_meetings_date) */
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['id'] = 'field_os2web_meetings_date_value';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['table'] = 'field_data_field_os2web_meetings_date';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['field'] = 'field_os2web_meetings_date_value';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['operator'] = '>=';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['group'] = 1;
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['default_date'] = 'today';
  /* Filter criterion: Content: Tillæg til (field_os2web_meetings_addendum) */
  $handler->display->display_options['filters']['field_os2web_meetings_addendum_nid']['id'] = 'field_os2web_meetings_addendum_nid';
  $handler->display->display_options['filters']['field_os2web_meetings_addendum_nid']['table'] = 'field_data_field_os2web_meetings_addendum';
  $handler->display->display_options['filters']['field_os2web_meetings_addendum_nid']['field'] = 'field_os2web_meetings_addendum_nid';
  $handler->display->display_options['filters']['field_os2web_meetings_addendum_nid']['operator'] = 'empty';
  $handler->display->display_options['filters']['field_os2web_meetings_addendum_nid']['group'] = 1;
  /* Filter criterion: filter in users list */
  $handler->display->display_options['filters']['php']['id'] = 'php';
  $handler->display->display_options['filters']['php']['table'] = 'views';
  $handler->display->display_options['filters']['php']['field'] = 'php';
  $handler->display->display_options['filters']['php']['ui_name'] = 'filter in users list';
  $handler->display->display_options['filters']['php']['group'] = 1;
  $handler->display->display_options['filters']['php']['use_php_setup'] = 0;
  $handler->display->display_options['filters']['php']['php_filter'] = 'return os2dagsorden_meeting_views_coming_meetings_filter_in_my_list($row->tid);;';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'mini';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹‹';
  $handler->display->display_options['pager']['options']['tags']['next'] = '››';
  $handler->display->display_options['block_description'] = 'coming_meetings_my_committee';
  $translatables['kommende_m_der_i_mine_udvalg'] = array(
    t('Master'),
    t('Kommende møder i mine udvalg'),
    t('more'),
    t('Apply'),
    t('Gendan'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« første'),
    t('‹ forrige'),
    t('næste >'),
    t('sidste »'),
    t('<?php
os2dagsorden_meeting_views_coming_meetings_help_text();
?>'),
    t('term from field_os2web_meetings_committee'),
    t('.'),
    t(','),
    t('Status'),
    t('Møde'),
    t('Dato'),
    t('&nbsp;'),
    t('Lokation'),
    t('Udvalg'),
    t('[field_os2web_meetings_committee]'),
    t('Block'),
    t('« first'),
    t('‹‹'),
    t('››'),
    t('last »'),
    t('coming_meetings_my_committee'),
  );
  $export['kommende_m_der_i_mine_udvalg'] = $view;

  $view = new view();
  $view->name = 'meeting_details';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Meeting details';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Deltagerne';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'php';
  $handler->display->display_options['access']['php_access'] = 'return os2dagsorden_meeting_views_meeting_details_lukket_dagsorden_access();';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Gendan';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['row_class'] = 'table-plain-text';
  $handler->display->display_options['style_options']['columns'] = array(
    'nid' => 'nid',
    'php' => 'php',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'nid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'php' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
  );
  /* Header: breadcrumb override */
  $handler->display->display_options['header']['php']['id'] = 'php';
  $handler->display->display_options['header']['php']['table'] = 'views';
  $handler->display->display_options['header']['php']['field'] = 'php';
  $handler->display->display_options['header']['php']['ui_name'] = 'breadcrumb override';
  $handler->display->display_options['header']['php']['empty'] = TRUE;
  $handler->display->display_options['header']['php']['php_output'] = '<?php
os2dagsorden_meeting_views_meeting_details_breadcrumb();
?>';
  /* Header: agenda edit button */
  $handler->display->display_options['header']['php_2']['id'] = 'php_2';
  $handler->display->display_options['header']['php_2']['table'] = 'views';
  $handler->display->display_options['header']['php_2']['field'] = 'php';
  $handler->display->display_options['header']['php_2']['ui_name'] = 'agenda edit button';
  $handler->display->display_options['header']['php_2']['php_output'] = '<?php
os2dagsorden_meeting_views_meeting_details_agenda_and_edit_button();
?>';
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Field: Meeting id - hidden */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['relationship'] = 'reverse_field_os2web_meetings_addendum_node';
  $handler->display->display_options['fields']['nid']['ui_name'] = 'Meeting id - hidden';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: print all speaker papers */
  $handler->display->display_options['fields']['php']['id'] = 'php';
  $handler->display->display_options['fields']['php']['table'] = 'views';
  $handler->display->display_options['fields']['php']['field'] = 'php';
  $handler->display->display_options['fields']['php']['ui_name'] = 'print all speaker papers';
  $handler->display->display_options['fields']['php']['label'] = '';
  $handler->display->display_options['fields']['php']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php']['php_output'] = '<?php
    os2dagsorden_meeting_views_meeting_details_fields_print_all_speaker_papers($row->nid);
?>';
  $handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php']['php_click_sortable'] = '';
  /* Sort criterion: Content: Number (field_os2web_meetings_bul_number) */
  $handler->display->display_options['sorts']['field_os2web_meetings_bul_number_value']['id'] = 'field_os2web_meetings_bul_number_value';
  $handler->display->display_options['sorts']['field_os2web_meetings_bul_number_value']['table'] = 'field_data_field_os2web_meetings_bul_number';
  $handler->display->display_options['sorts']['field_os2web_meetings_bul_number_value']['field'] = 'field_os2web_meetings_bul_number_value';
  $handler->display->display_options['sorts']['field_os2web_meetings_bul_number_value']['relationship'] = 'field_os2web_meetings_bullets_target_id';
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $handler->display->display_options['sorts']['title']['relationship'] = 'field_os2web_meetings_bullets_target_id';
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['exception']['title'] = 'Alle';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'raw';
  $handler->display->display_options['arguments']['nid']['default_argument_options']['index'] = '1';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['nid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['nid']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['nid']['validate_options']['types'] = array(
    'os2web_meetings_meeting' => 'os2web_meetings_meeting',
  );
  $handler->display->display_options['arguments']['nid']['validate_options']['access'] = TRUE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'os2web_meetings_meeting' => 'os2web_meetings_meeting',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Mødedetaljer';
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    2 => '2',
  );
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['row_class'] = 'table-plain-text';
  $handler->display->display_options['style_options']['columns'] = array(
    'nid' => 'nid',
    'php_1' => 'title',
    'php' => 'title',
    'title' => 'title',
    'field_os2web_meetings_date' => 'field_os2web_meetings_date',
    'field_os2web_meetings_date_1' => 'field_os2web_meetings_date_1',
    'php_2' => 'php_2',
    'php_3' => 'php_3',
    'php_4' => 'php_4',
    'field_os2web_meetings_committee' => 'field_os2web_meetings_committee',
    'field_name_short' => 'field_name_short',
    'php_5' => 'php_5',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'nid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'php_1' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'php' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_os2web_meetings_date' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_os2web_meetings_date_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'php_2' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'php_3' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'php_4' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'field_os2web_meetings_committee' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_name_short' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'php_5' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: breadcrumb override */
  $handler->display->display_options['header']['php']['id'] = 'php';
  $handler->display->display_options['header']['php']['table'] = 'views';
  $handler->display->display_options['header']['php']['field'] = 'php';
  $handler->display->display_options['header']['php']['ui_name'] = 'breadcrumb override';
  $handler->display->display_options['header']['php']['empty'] = TRUE;
  $handler->display->display_options['header']['php']['php_output'] = '<?php
os2dagsorden_meeting_views_meeting_details_breadcrumb();
?>';
  /* Header: agenda edit button */
  $handler->display->display_options['header']['php_2']['id'] = 'php_2';
  $handler->display->display_options['header']['php_2']['table'] = 'views';
  $handler->display->display_options['header']['php_2']['field'] = 'php';
  $handler->display->display_options['header']['php_2']['ui_name'] = 'agenda edit button';
  $handler->display->display_options['header']['php_2']['php_output'] = '<?php
os2dagsorden_meeting_views_meeting_details_agenda_and_edit_button();
?>';
  /* Header: admin controls */
  $handler->display->display_options['header']['php_3']['id'] = 'php_3';
  $handler->display->display_options['header']['php_3']['table'] = 'views';
  $handler->display->display_options['header']['php_3']['field'] = 'php';
  $handler->display->display_options['header']['php_3']['ui_name'] = 'admin controls';
  $handler->display->display_options['header']['php_3']['php_output'] = '<?php
os2dagsorden_meeting_views_meeting_details_admin_controls();
?>';
  /* Header: description download */
  $handler->display->display_options['header']['php_1']['id'] = 'php_1';
  $handler->display->display_options['header']['php_1']['table'] = 'views';
  $handler->display->display_options['header']['php_1']['field'] = 'php';
  $handler->display->display_options['header']['php_1']['ui_name'] = 'description download';
  $handler->display->display_options['header']['php_1']['php_output'] = '<?php
os2dagsorden_meeting_views_meeting_details_description_download();
?>
';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Content: Committee (field_os2web_meetings_committee) */
  $handler->display->display_options['relationships']['field_os2web_meetings_committee_tid']['id'] = 'field_os2web_meetings_committee_tid';
  $handler->display->display_options['relationships']['field_os2web_meetings_committee_tid']['table'] = 'field_data_field_os2web_meetings_committee';
  $handler->display->display_options['relationships']['field_os2web_meetings_committee_tid']['field'] = 'field_os2web_meetings_committee_tid';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: indicator - has speaker paper */
  $handler->display->display_options['fields']['php_1']['id'] = 'php_1';
  $handler->display->display_options['fields']['php_1']['table'] = 'views';
  $handler->display->display_options['fields']['php_1']['field'] = 'php';
  $handler->display->display_options['fields']['php_1']['ui_name'] = 'indicator - has speaker paper';
  $handler->display->display_options['fields']['php_1']['label'] = '';
  $handler->display->display_options['fields']['php_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php_1']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_1']['php_output'] = '<?php
os2dagsorden_meeting_views_meeting_details_fields_indicator_meeting_has_sp($row->nid);
?>';
  $handler->display->display_options['fields']['php_1']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_1']['php_click_sortable'] = '';
  /* Field: indicator - has notes */
  $handler->display->display_options['fields']['php']['id'] = 'php';
  $handler->display->display_options['fields']['php']['table'] = 'views';
  $handler->display->display_options['fields']['php']['field'] = 'php';
  $handler->display->display_options['fields']['php']['ui_name'] = 'indicator - has notes';
  $handler->display->display_options['fields']['php']['label'] = '';
  $handler->display->display_options['fields']['php']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php']['php_output'] = '<?php
os2dagsorden_meeting_views_meeting_details_fields_indicator_meeting_has_notes($row->nid);
?>';
  $handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php']['php_click_sortable'] = '';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Møde';
  $handler->display->display_options['fields']['title']['alter']['max_length'] = '50';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Date */
  $handler->display->display_options['fields']['field_os2web_meetings_date']['id'] = 'field_os2web_meetings_date';
  $handler->display->display_options['fields']['field_os2web_meetings_date']['table'] = 'field_data_field_os2web_meetings_date';
  $handler->display->display_options['fields']['field_os2web_meetings_date']['field'] = 'field_os2web_meetings_date';
  $handler->display->display_options['fields']['field_os2web_meetings_date']['label'] = 'Startdato';
  $handler->display->display_options['fields']['field_os2web_meetings_date']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'value',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Date */
  $handler->display->display_options['fields']['field_os2web_meetings_date_1']['id'] = 'field_os2web_meetings_date_1';
  $handler->display->display_options['fields']['field_os2web_meetings_date_1']['table'] = 'field_data_field_os2web_meetings_date';
  $handler->display->display_options['fields']['field_os2web_meetings_date_1']['field'] = 'field_os2web_meetings_date';
  $handler->display->display_options['fields']['field_os2web_meetings_date_1']['label'] = 'Slutdato';
  $handler->display->display_options['fields']['field_os2web_meetings_date_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_os2web_meetings_date_1']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'value2',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Date (Slutdato) */
  $handler->display->display_options['fields']['php_2']['id'] = 'php_2';
  $handler->display->display_options['fields']['php_2']['table'] = 'views';
  $handler->display->display_options['fields']['php_2']['field'] = 'php';
  $handler->display->display_options['fields']['php_2']['ui_name'] = 'Date (Slutdato)';
  $handler->display->display_options['fields']['php_2']['label'] = 'Slutdato';
  $handler->display->display_options['fields']['php_2']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php_2']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['php_2']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['php_2']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_2']['php_output'] = '<?php
os2dagsorden_meeting_views_meeting_details_fields_enddate($row->nid);
?>';
  $handler->display->display_options['fields']['php_2']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_2']['php_click_sortable'] = '';
  /* Field: Committee (Udvalg) */
  $handler->display->display_options['fields']['php_3']['id'] = 'php_3';
  $handler->display->display_options['fields']['php_3']['table'] = 'views';
  $handler->display->display_options['fields']['php_3']['field'] = 'php';
  $handler->display->display_options['fields']['php_3']['ui_name'] = 'Committee (Udvalg)';
  $handler->display->display_options['fields']['php_3']['label'] = 'Udvalg';
  $handler->display->display_options['fields']['php_3']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_3']['php_output'] = '<?php
os2dagsorden_meeting_views_meeting_details_fields_committee($row->nid);
?>';
  $handler->display->display_options['fields']['php_3']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_3']['php_click_sortable'] = '';
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['php_4']['id'] = 'php_4';
  $handler->display->display_options['fields']['php_4']['table'] = 'views';
  $handler->display->display_options['fields']['php_4']['field'] = 'php';
  $handler->display->display_options['fields']['php_4']['label'] = 'Type';
  $handler->display->display_options['fields']['php_4']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php_4']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_4']['php_output'] = '<?php
os2dagsorden_meeting_views_meeting_details_fields_type($row->nid);
?>';
  $handler->display->display_options['fields']['php_4']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_4']['php_click_sortable'] = '';
  /* Field: Content: Committee */
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['id'] = 'field_os2web_meetings_committee';
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['table'] = 'field_data_field_os2web_meetings_committee';
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['field'] = 'field_os2web_meetings_committee';
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['label'] = '';
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['alter']['max_length'] = '20';
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'os2web_meetings_meeting' => 'os2web_meetings_meeting',
  );
  $handler->display->display_options['path'] = 'meeting/%';

  /* Display: Lokation */
  $handler = $view->new_display('attachment', 'Lokation', 'attachment_3');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Lokation';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    2 => '2',
  );
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '0';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['row_class'] = 'table-plain-text';
  $handler->display->display_options['style_options']['columns'] = array(
    'nid_1' => 'nid_1',
    'field_os2web_meetings_location' => 'field_os2web_meetings_location',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'nid_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_os2web_meetings_location' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Meeting id - hidden */
  $handler->display->display_options['fields']['nid_1']['id'] = 'nid_1';
  $handler->display->display_options['fields']['nid_1']['table'] = 'node';
  $handler->display->display_options['fields']['nid_1']['field'] = 'nid';
  $handler->display->display_options['fields']['nid_1']['ui_name'] = 'Meeting id - hidden';
  $handler->display->display_options['fields']['nid_1']['label'] = '';
  $handler->display->display_options['fields']['nid_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid_1']['element_label_colon'] = FALSE;
  /* Field: Content: Lokation */
  $handler->display->display_options['fields']['field_os2web_meetings_location']['id'] = 'field_os2web_meetings_location';
  $handler->display->display_options['fields']['field_os2web_meetings_location']['table'] = 'field_data_field_os2web_meetings_location';
  $handler->display->display_options['fields']['field_os2web_meetings_location']['field'] = 'field_os2web_meetings_location';
  $handler->display->display_options['fields']['field_os2web_meetings_location']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_os2web_meetings_location']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'os2web_meetings_meeting' => 'os2web_meetings_meeting',
  );
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );
  $handler->display->display_options['attachment_position'] = 'after';

  /* Display: Comments */
  $handler = $view->new_display('attachment', 'Comments', 'attachment_5');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Kommentarer';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'php';
  $handler->display->display_options['access']['php_access'] = 'return os2dagsorden_meeting_views_meeting_details_comments_access();';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '0';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['row_class'] = 'table-plain-text';
  $handler->display->display_options['style_options']['columns'] = array(
    'nid_1' => 'nid_1',
    'field_os2web_meetings_comments' => 'field_os2web_meetings_comments',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'nid_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_os2web_meetings_comments' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Meeting id - hidden */
  $handler->display->display_options['fields']['nid_1']['id'] = 'nid_1';
  $handler->display->display_options['fields']['nid_1']['table'] = 'node';
  $handler->display->display_options['fields']['nid_1']['field'] = 'nid';
  $handler->display->display_options['fields']['nid_1']['ui_name'] = 'Meeting id - hidden';
  $handler->display->display_options['fields']['nid_1']['label'] = '';
  $handler->display->display_options['fields']['nid_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid_1']['element_label_colon'] = FALSE;
  /* Field: Content: Comments */
  $handler->display->display_options['fields']['field_os2web_meetings_comments']['id'] = 'field_os2web_meetings_comments';
  $handler->display->display_options['fields']['field_os2web_meetings_comments']['table'] = 'field_data_field_os2web_meetings_comments';
  $handler->display->display_options['fields']['field_os2web_meetings_comments']['field'] = 'field_os2web_meetings_comments';
  $handler->display->display_options['fields']['field_os2web_meetings_comments']['label'] = 'Bemærkninger';
  $handler->display->display_options['fields']['field_os2web_meetings_comments']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'os2web_meetings_meeting' => 'os2web_meetings_meeting',
  );
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );
  $handler->display->display_options['attachment_position'] = 'after';

  /* Display: Særlige Forhold */
  $handler = $view->new_display('attachment', 'Særlige Forhold', 'attachment_7');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Særlige Forhold';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'php';
  $handler->display->display_options['access']['php_access'] = 'return os2dagsorden_meeting_views_meeting_details_special_conditions_access();';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '0';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['row_class'] = 'table-plain-text';
  $handler->display->display_options['style_options']['columns'] = array(
    'nid_1' => 'nid_1',
    'field_os2web_meetings_conditions' => 'field_os2web_meetings_conditions',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'nid_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_os2web_meetings_conditions' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Meeting id - hidden */
  $handler->display->display_options['fields']['nid_1']['id'] = 'nid_1';
  $handler->display->display_options['fields']['nid_1']['table'] = 'node';
  $handler->display->display_options['fields']['nid_1']['field'] = 'nid';
  $handler->display->display_options['fields']['nid_1']['ui_name'] = 'Meeting id - hidden';
  $handler->display->display_options['fields']['nid_1']['label'] = '';
  $handler->display->display_options['fields']['nid_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid_1']['element_label_colon'] = FALSE;
  /* Field: Content:  Særlige Forhold */
  $handler->display->display_options['fields']['field_os2web_meetings_conditions']['id'] = 'field_os2web_meetings_conditions';
  $handler->display->display_options['fields']['field_os2web_meetings_conditions']['table'] = 'field_data_field_os2web_meetings_conditions';
  $handler->display->display_options['fields']['field_os2web_meetings_conditions']['field'] = 'field_os2web_meetings_conditions';
  $handler->display->display_options['fields']['field_os2web_meetings_conditions']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'os2web_meetings_meeting' => 'os2web_meetings_meeting',
  );
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );
  $handler->display->display_options['attachment_position'] = 'after';

  /* Display: Deltagerne */
  $handler = $view->new_display('attachment', 'Deltagerne', 'attachment_2');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    2 => '2',
  );
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['row_class'] = 'table-plain-text';
  $handler->display->display_options['style_options']['columns'] = array(
    'nid' => 'nid',
    'php' => 'php',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'nid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'php' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Meeting id - hidden */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['ui_name'] = 'Meeting id - hidden';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Participants */
  $handler->display->display_options['fields']['php']['id'] = 'php';
  $handler->display->display_options['fields']['php']['table'] = 'views';
  $handler->display->display_options['fields']['php']['field'] = 'php';
  $handler->display->display_options['fields']['php']['ui_name'] = 'Participants';
  $handler->display->display_options['fields']['php']['label'] = 'Deltagere';
  $handler->display->display_options['fields']['php']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php']['php_output'] = '<?php
os2dagsorden_meeting_views_meeting_details_fields_participants_deltog($row->nid);
?>';
  $handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php']['php_click_sortable'] = '';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'os2web_meetings_meeting' => 'os2web_meetings_meeting',
  );
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );
  $handler->display->display_options['attachment_position'] = 'after';

  /* Display: Afbud / Fraværende */
  $handler = $view->new_display('attachment', 'Afbud / Fraværende', 'attachment_4');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Afbud / Fraværende';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'php';
  $handler->display->display_options['access']['php_access'] = 'return os2dagsorden_meeting_views_meeting_details_fields_participants_afbud_access();';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['row_class'] = 'table-plain-text';
  $handler->display->display_options['style_options']['columns'] = array(
    'nid' => 'nid',
    'php' => 'php',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'nid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'php' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Meeting id - hidden */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['ui_name'] = 'Meeting id - hidden';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Participants (Cancelled) */
  $handler->display->display_options['fields']['php']['id'] = 'php';
  $handler->display->display_options['fields']['php']['table'] = 'views';
  $handler->display->display_options['fields']['php']['field'] = 'php';
  $handler->display->display_options['fields']['php']['ui_name'] = 'Participants (Cancelled)';
  $handler->display->display_options['fields']['php']['label'] = 'Afbud / Fraværende';
  $handler->display->display_options['fields']['php']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php']['php_output'] = '<?php
os2dagsorden_meeting_views_meeting_details_fields_participants_afbud($row->nid);
?>';
  $handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php']['php_click_sortable'] = '';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );
  $handler->display->display_options['attachment_position'] = 'after';

  /* Display: Print all speaker papers */
  $handler = $view->new_display('attachment', 'Print all speaker papers', 'attachment_print_all_speaker_papers');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Print alle talepapirer';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    2 => '2',
  );
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['row_class'] = 'table-plain-text';
  $handler->display->display_options['style_options']['columns'] = array(
    'nid' => 'nid',
    'php' => 'php',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'nid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'php' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );
  $handler->display->display_options['attachment_position'] = 'after';

  /* Display: Dagsorden */
  $handler = $view->new_display('attachment', 'Dagsorden', 'attachment_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Dagsorden';
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['css_class'] = 'bullet-point-attachments';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'php';
  $handler->display->display_options['access']['php_access'] = 'return os2dagsorden_meeting_views_meeting_details_dagsorden_access();';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '0';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'nid_1' => 'nid_1',
    'nid' => 'nid',
    'nothing' => 'nothing',
    'field_os2web_meetings_bul_closed' => 'php_4',
    'field_os2web_meetings_bul_pers' => 'php_4',
    'php_1' => 'php_4',
    'php' => 'php',
    'title' => 'title',
    'php_4' => 'php_4',
    'php_3' => 'php_4',
    'php_6' => 'php_6',
    'php_5' => 'php_5',
    'php_2' => 'php_2',
    'php_7' => 'php_4',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'nid_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nothing' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_os2web_meetings_bul_closed' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_os2web_meetings_bul_pers' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'php_1' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'php' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'php_4' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'php_3' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'php_6' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'php_5' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'php_2' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'php_7' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Dagsorden header */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['ui_name'] = 'Dagsorden header';
  $handler->display->display_options['header']['area']['content'] = '<?php
os2dagsorden_meeting_views_meeting_details_fields_dagsorden_header();
?>';
  $handler->display->display_options['header']['area']['format'] = 'php_code';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: bullet point */
  $handler->display->display_options['relationships']['field_os2web_meetings_bullets_target_id']['id'] = 'field_os2web_meetings_bullets_target_id';
  $handler->display->display_options['relationships']['field_os2web_meetings_bullets_target_id']['table'] = 'field_data_field_os2web_meetings_bullets';
  $handler->display->display_options['relationships']['field_os2web_meetings_bullets_target_id']['field'] = 'field_os2web_meetings_bullets_target_id';
  $handler->display->display_options['relationships']['field_os2web_meetings_bullets_target_id']['ui_name'] = 'bullet point';
  $handler->display->display_options['relationships']['field_os2web_meetings_bullets_target_id']['required'] = TRUE;
  /* Relationship: bullet point speaking paper */
  $handler->display->display_options['relationships']['reverse_field_os2web_meetings_bullets_node']['id'] = 'reverse_field_os2web_meetings_bullets_node';
  $handler->display->display_options['relationships']['reverse_field_os2web_meetings_bullets_node']['table'] = 'node';
  $handler->display->display_options['relationships']['reverse_field_os2web_meetings_bullets_node']['field'] = 'reverse_field_os2web_meetings_bullets_node';
  $handler->display->display_options['relationships']['reverse_field_os2web_meetings_bullets_node']['relationship'] = 'field_os2web_meetings_bullets_target_id';
  $handler->display->display_options['relationships']['reverse_field_os2web_meetings_bullets_node']['ui_name'] = 'bullet point speaking paper';
  $handler->display->display_options['relationships']['reverse_field_os2web_meetings_bullets_node']['label'] = 'bullet point speaking paper';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_os2web_meetings_attach_target_id']['id'] = 'field_os2web_meetings_attach_target_id';
  $handler->display->display_options['relationships']['field_os2web_meetings_attach_target_id']['table'] = 'field_data_field_os2web_meetings_attach';
  $handler->display->display_options['relationships']['field_os2web_meetings_attach_target_id']['field'] = 'field_os2web_meetings_attach_target_id';
  $handler->display->display_options['relationships']['field_os2web_meetings_attach_target_id']['relationship'] = 'field_os2web_meetings_bullets_target_id';
  $handler->display->display_options['relationships']['field_os2web_meetings_attach_target_id']['label'] = 'bullet point attachment';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Meeting id - hidden */
  $handler->display->display_options['fields']['nid_1']['id'] = 'nid_1';
  $handler->display->display_options['fields']['nid_1']['table'] = 'node';
  $handler->display->display_options['fields']['nid_1']['field'] = 'nid';
  $handler->display->display_options['fields']['nid_1']['ui_name'] = 'Meeting id - hidden';
  $handler->display->display_options['fields']['nid_1']['label'] = '';
  $handler->display->display_options['fields']['nid_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid_1']['element_label_colon'] = FALSE;
  /* Field: Bullet point id - hidden */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['relationship'] = 'field_os2web_meetings_bullets_target_id';
  $handler->display->display_options['fields']['nid']['ui_name'] = 'Bullet point id - hidden';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: hide show container */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'hide show container';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['element_class'] = 'hide_show_button_container';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Field: bullet point title [hidden], for speaker paper link */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'field_os2web_meetings_bullets_target_id';
  $handler->display->display_options['fields']['title']['ui_name'] = 'bullet point title [hidden], for speaker paper link';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Bullet point title - php */
  $handler->display->display_options['fields']['php_4']['id'] = 'php_4';
  $handler->display->display_options['fields']['php_4']['table'] = 'views';
  $handler->display->display_options['fields']['php_4']['field'] = 'php';
  $handler->display->display_options['fields']['php_4']['ui_name'] = 'Bullet point title - php';
  $handler->display->display_options['fields']['php_4']['label'] = '';
  $handler->display->display_options['fields']['php_4']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php_4']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_4']['php_output'] = '<?php
$title = $data->node_field_data_field_os2web_meetings_bullets_title;
$meeting_id = $row->nid_1;
$bp_id = $row->nid;

os2dagsorden_meeting_views_meeting_details_fields_bullet_point_title($title, $meeting_id, $bp_id);
?>';
  $handler->display->display_options['fields']['php_4']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_4']['php_click_sortable'] = '';
  /* Field: bullet point attachments with text */
  $handler->display->display_options['fields']['php_3']['id'] = 'php_3';
  $handler->display->display_options['fields']['php_3']['table'] = 'views';
  $handler->display->display_options['fields']['php_3']['field'] = 'php';
  $handler->display->display_options['fields']['php_3']['ui_name'] = 'bullet point attachments with text';
  $handler->display->display_options['fields']['php_3']['label'] = '';
  $handler->display->display_options['fields']['php_3']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php_3']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_3']['php_output'] = '<?php
$meeting_id = $row->nid_1;
$bp_id = $row->nid;

os2dagsorden_meeting_views_meeting_details_fields_bullet_point_attachments_with_text($meeting_id, $bp_id);
?>';
  $handler->display->display_options['fields']['php_3']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_3']['php_click_sortable'] = '';
  /* Field: CaseIdentifier link */
  $handler->display->display_options['fields']['php']['id'] = 'php';
  $handler->display->display_options['fields']['php']['table'] = 'views';
  $handler->display->display_options['fields']['php']['field'] = 'php';
  $handler->display->display_options['fields']['php']['ui_name'] = 'CaseIdentifier link';
  $handler->display->display_options['fields']['php']['label'] = '';
  $handler->display->display_options['fields']['php']['element_class'] = 'case-id-link-container';
  $handler->display->display_options['fields']['php']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['php']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php']['php_output'] = '<?php os2dagsorden_meeting_views_meeting_details_fields_bullet_point_case_identifier_link($row->nid_1, $row->nid); ?>';
  $handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php']['php_click_sortable'] = '';
  /* Field: send to friend */
  $handler->display->display_options['fields']['php_6']['id'] = 'php_6';
  $handler->display->display_options['fields']['php_6']['table'] = 'views';
  $handler->display->display_options['fields']['php_6']['field'] = 'php';
  $handler->display->display_options['fields']['php_6']['ui_name'] = 'send to friend';
  $handler->display->display_options['fields']['php_6']['label'] = '';
  $handler->display->display_options['fields']['php_6']['element_class'] = 'send-bullet-point-link';
  $handler->display->display_options['fields']['php_6']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php_6']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_6']['php_output'] = '<?php os2dagsorden_meeting_views_meeting_details_fields_bullet_point_send_link($row->nid_1, $row->nid); ?>';
  $handler->display->display_options['fields']['php_6']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_6']['php_click_sortable'] = '';
  /* Field: bullet point print link */
  $handler->display->display_options['fields']['php_5']['id'] = 'php_5';
  $handler->display->display_options['fields']['php_5']['table'] = 'views';
  $handler->display->display_options['fields']['php_5']['field'] = 'php';
  $handler->display->display_options['fields']['php_5']['ui_name'] = 'bullet point print link';
  $handler->display->display_options['fields']['php_5']['label'] = '';
  $handler->display->display_options['fields']['php_5']['alter']['path'] = 'print/meeting/[nid_1]/bullet-point/[nid]/print';
  $handler->display->display_options['fields']['php_5']['element_class'] = 'print-bullet-point-link';
  $handler->display->display_options['fields']['php_5']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php_5']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_5']['php_output'] = '<?php
$meeting_id = $row->nid_1;
$bp_id = $row->nid;
os2dagsorden_meeting_views_meeting_details_fields_bullet_point_print_link($meeting_id, $bp_id);

?>';
  $handler->display->display_options['fields']['php_5']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_5']['php_click_sortable'] = '';
  /* Field: speaker paper link */
  $handler->display->display_options['fields']['php_2']['id'] = 'php_2';
  $handler->display->display_options['fields']['php_2']['table'] = 'views';
  $handler->display->display_options['fields']['php_2']['field'] = 'php';
  $handler->display->display_options['fields']['php_2']['ui_name'] = 'speaker paper link';
  $handler->display->display_options['fields']['php_2']['label'] = '';
  $handler->display->display_options['fields']['php_2']['element_class'] = 'speaker-paper-link-container';
  $handler->display->display_options['fields']['php_2']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php_2']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_2']['php_output'] = '<?php
$meeting_id = $row->nid_1;
$bp_id = $row->nid;
$bp_title = $row->title;

os2dagsorden_meeting_views_meeting_details_fields_speaker_paper_link($meeting_id, $bp_id, $bp_title);
?>';
  $handler->display->display_options['fields']['php_2']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_2']['php_click_sortable'] = '';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'os2web_meetings_meeting' => 'os2web_meetings_meeting',
  );
  /* Filter criterion: Filter on closed/open bullet points, depending on current settings */
  $handler->display->display_options['filters']['php']['id'] = 'php';
  $handler->display->display_options['filters']['php']['table'] = 'views';
  $handler->display->display_options['filters']['php']['field'] = 'php';
  $handler->display->display_options['filters']['php']['ui_name'] = 'Filter on closed/open bullet points, depending on current settings';
  $handler->display->display_options['filters']['php']['use_php_setup'] = 0;
  $handler->display->display_options['filters']['php']['php_filter'] = 'return os2dagsorden_meeting_views_meeting_details_fields_filter_bullet_point($row->nid, true);';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );
  $handler->display->display_options['attachment_position'] = 'after';

  /* Display: Lukket Dagsorden */
  $handler = $view->new_display('attachment', 'Lukket Dagsorden', 'attachment_6');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Lukket Dagsorden';
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['css_class'] = 'bullet-point-attachments lukket-dagsorden';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'php';
  $handler->display->display_options['access']['php_access'] = 'return os2dagsorden_meeting_views_meeting_details_lukket_dagsorden_access();';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '0';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'nid_1' => 'nid_1',
    'nid' => 'nid',
    'nothing' => 'nothing',
    'field_os2web_meetings_bul_closed' => 'php_4',
    'field_os2web_meetings_bul_pers' => 'php_4',
    'php_1' => 'php_4',
    'php' => 'php_4',
    'php_4' => 'php_4',
    'php_3' => 'php_4',
    'php_2' => 'php_2',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'nid_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nothing' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_os2web_meetings_bul_closed' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_os2web_meetings_bul_pers' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'php_1' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'php' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'php_4' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'php_3' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'php_2' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Lukket dagsorden header */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['ui_name'] = 'Lukket dagsorden header';
  $handler->display->display_options['header']['area']['content'] = '<?php
os2dagsorden_meeting_views_meeting_details_fields_lukket_dagsorden_header();
?>';
  $handler->display->display_options['header']['area']['format'] = 'php_code';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: bullet point */
  $handler->display->display_options['relationships']['field_os2web_meetings_bullets_target_id']['id'] = 'field_os2web_meetings_bullets_target_id';
  $handler->display->display_options['relationships']['field_os2web_meetings_bullets_target_id']['table'] = 'field_data_field_os2web_meetings_bullets';
  $handler->display->display_options['relationships']['field_os2web_meetings_bullets_target_id']['field'] = 'field_os2web_meetings_bullets_target_id';
  $handler->display->display_options['relationships']['field_os2web_meetings_bullets_target_id']['ui_name'] = 'bullet point';
  $handler->display->display_options['relationships']['field_os2web_meetings_bullets_target_id']['required'] = TRUE;
  /* Relationship: bullet point speaking paper */
  $handler->display->display_options['relationships']['reverse_field_os2web_meetings_bullets_node']['id'] = 'reverse_field_os2web_meetings_bullets_node';
  $handler->display->display_options['relationships']['reverse_field_os2web_meetings_bullets_node']['table'] = 'node';
  $handler->display->display_options['relationships']['reverse_field_os2web_meetings_bullets_node']['field'] = 'reverse_field_os2web_meetings_bullets_node';
  $handler->display->display_options['relationships']['reverse_field_os2web_meetings_bullets_node']['relationship'] = 'field_os2web_meetings_bullets_target_id';
  $handler->display->display_options['relationships']['reverse_field_os2web_meetings_bullets_node']['ui_name'] = 'bullet point speaking paper';
  $handler->display->display_options['relationships']['reverse_field_os2web_meetings_bullets_node']['label'] = 'bullet point speaking paper';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_os2web_meetings_attach_target_id']['id'] = 'field_os2web_meetings_attach_target_id';
  $handler->display->display_options['relationships']['field_os2web_meetings_attach_target_id']['table'] = 'field_data_field_os2web_meetings_attach';
  $handler->display->display_options['relationships']['field_os2web_meetings_attach_target_id']['field'] = 'field_os2web_meetings_attach_target_id';
  $handler->display->display_options['relationships']['field_os2web_meetings_attach_target_id']['relationship'] = 'field_os2web_meetings_bullets_target_id';
  $handler->display->display_options['relationships']['field_os2web_meetings_attach_target_id']['label'] = 'bullet point attachment';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Meeting id - hidden */
  $handler->display->display_options['fields']['nid_1']['id'] = 'nid_1';
  $handler->display->display_options['fields']['nid_1']['table'] = 'node';
  $handler->display->display_options['fields']['nid_1']['field'] = 'nid';
  $handler->display->display_options['fields']['nid_1']['ui_name'] = 'Meeting id - hidden';
  $handler->display->display_options['fields']['nid_1']['label'] = '';
  $handler->display->display_options['fields']['nid_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid_1']['element_label_colon'] = FALSE;
  /* Field: Bullet point id - hidden */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['relationship'] = 'field_os2web_meetings_bullets_target_id';
  $handler->display->display_options['fields']['nid']['ui_name'] = 'Bullet point id - hidden';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: hide show container */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'hide show container';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['element_class'] = 'hide_show_button_container';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Field: bullet point title [hidden], for speaker paper link */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'field_os2web_meetings_bullets_target_id';
  $handler->display->display_options['fields']['title']['ui_name'] = 'bullet point title [hidden], for speaker paper link';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Bullet point title - php */
  $handler->display->display_options['fields']['php_4']['id'] = 'php_4';
  $handler->display->display_options['fields']['php_4']['table'] = 'views';
  $handler->display->display_options['fields']['php_4']['field'] = 'php';
  $handler->display->display_options['fields']['php_4']['ui_name'] = 'Bullet point title - php';
  $handler->display->display_options['fields']['php_4']['label'] = '';
  $handler->display->display_options['fields']['php_4']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php_4']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_4']['php_output'] = '<?php
$title = $data->node_field_data_field_os2web_meetings_bullets_title;
$meeting_id = $row->nid_1;
$bp_id = $row->nid;

os2dagsorden_meeting_views_meeting_details_fields_bullet_point_title($title, $meeting_id, $bp_id);
?>';
  $handler->display->display_options['fields']['php_4']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_4']['php_click_sortable'] = '';
  /* Field: bullet point attachments with text */
  $handler->display->display_options['fields']['php_3']['id'] = 'php_3';
  $handler->display->display_options['fields']['php_3']['table'] = 'views';
  $handler->display->display_options['fields']['php_3']['field'] = 'php';
  $handler->display->display_options['fields']['php_3']['ui_name'] = 'bullet point attachments with text';
  $handler->display->display_options['fields']['php_3']['label'] = '';
  $handler->display->display_options['fields']['php_3']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php_3']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_3']['php_output'] = '<?php
$meeting_id = $row->nid_1;
$bp_id = $row->nid;

os2dagsorden_meeting_views_meeting_details_fields_bullet_point_attachments_with_text($meeting_id, $bp_id);
?>';
  $handler->display->display_options['fields']['php_3']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_3']['php_click_sortable'] = '';
  /* Field: bullet point print link */
  $handler->display->display_options['fields']['php_5']['id'] = 'php_5';
  $handler->display->display_options['fields']['php_5']['table'] = 'views';
  $handler->display->display_options['fields']['php_5']['field'] = 'php';
  $handler->display->display_options['fields']['php_5']['ui_name'] = 'bullet point print link';
  $handler->display->display_options['fields']['php_5']['label'] = '';
  $handler->display->display_options['fields']['php_5']['alter']['path'] = 'print/meeting/[nid_1]/bullet-point/[nid]/print';
  $handler->display->display_options['fields']['php_5']['element_class'] = 'print-bullet-point-link';
  $handler->display->display_options['fields']['php_5']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php_5']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_5']['php_output'] = '<?php
$meeting_id = $row->nid_1;
$bp_id = $row->nid;
os2dagsorden_meeting_views_meeting_details_fields_bullet_point_print_link($meeting_id, $bp_id);
?>';
  $handler->display->display_options['fields']['php_5']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_5']['php_click_sortable'] = '';
  /* Field: send to friend */
  $handler->display->display_options['fields']['php_6']['id'] = 'php_6';
  $handler->display->display_options['fields']['php_6']['table'] = 'views';
  $handler->display->display_options['fields']['php_6']['field'] = 'php';
  $handler->display->display_options['fields']['php_6']['ui_name'] = 'send to friend';
  $handler->display->display_options['fields']['php_6']['element_class'] = 'send-bullet-point-link';
  $handler->display->display_options['fields']['php_6']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_6']['php_output'] = '<?php os2dagsorden_meeting_views_meeting_details_fields_bullet_point_send_link($row->nid_1, $row->nid); ?>';
  $handler->display->display_options['fields']['php_6']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_6']['php_click_sortable'] = '';
  /* Field: speaker paper link */
  $handler->display->display_options['fields']['php_2']['id'] = 'php_2';
  $handler->display->display_options['fields']['php_2']['table'] = 'views';
  $handler->display->display_options['fields']['php_2']['field'] = 'php';
  $handler->display->display_options['fields']['php_2']['ui_name'] = 'speaker paper link';
  $handler->display->display_options['fields']['php_2']['label'] = '';
  $handler->display->display_options['fields']['php_2']['element_class'] = 'speaker-paper-link-container';
  $handler->display->display_options['fields']['php_2']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php_2']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_2']['php_output'] = '<?php
$meeting_id = $row->nid_1;
$bp_id = $row->nid;
$bp_title = $row->title;

os2dagsorden_meeting_views_meeting_details_fields_speaker_paper_link($meeting_id, $bp_id, $bp_title);
?>';
  $handler->display->display_options['fields']['php_2']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_2']['php_click_sortable'] = '';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'os2web_meetings_meeting' => 'os2web_meetings_meeting',
  );
  /* Filter criterion: Filter on closed/open bullet points, depending on current settings */
  $handler->display->display_options['filters']['php']['id'] = 'php';
  $handler->display->display_options['filters']['php']['table'] = 'views';
  $handler->display->display_options['filters']['php']['field'] = 'php';
  $handler->display->display_options['filters']['php']['ui_name'] = 'Filter on closed/open bullet points, depending on current settings';
  $handler->display->display_options['filters']['php']['use_php_setup'] = 0;
  $handler->display->display_options['filters']['php']['php_filter'] = 'return os2dagsorden_meeting_views_meeting_details_fields_filter_bullet_point($row->nid, false);';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );
  $handler->display->display_options['attachment_position'] = 'after';

  /* Display: Tillæg Print all speaker papers */
  $handler = $view->new_display('attachment', 'Tillæg Print all speaker papers', 'attachment_print_all_speaker_papers_tillaeg');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Print alle talepapirer';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    2 => '2',
  );
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['defaults']['header'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Tillæg */
  $handler->display->display_options['relationships']['reverse_field_os2web_meetings_addendum_node']['id'] = 'reverse_field_os2web_meetings_addendum_node';
  $handler->display->display_options['relationships']['reverse_field_os2web_meetings_addendum_node']['table'] = 'node';
  $handler->display->display_options['relationships']['reverse_field_os2web_meetings_addendum_node']['field'] = 'reverse_field_os2web_meetings_addendum_node';
  $handler->display->display_options['relationships']['reverse_field_os2web_meetings_addendum_node']['ui_name'] = 'Tillæg';
  $handler->display->display_options['relationships']['reverse_field_os2web_meetings_addendum_node']['required'] = TRUE;
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );
  $handler->display->display_options['attachment_position'] = 'after';

  /* Display: Tillæg Dagsorden */
  $handler = $view->new_display('attachment', 'Tillæg Dagsorden', 'attachment_8');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Dagsorden';
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['css_class'] = 'bullet-point-attachments';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'php';
  $handler->display->display_options['access']['php_access'] = 'return os2dagsorden_meeting_views_meeting_details_dagsorden_access();';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '0';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'nid_1' => 'nid_1',
    'nid' => 'nid',
    'nothing' => 'nothing',
    'title' => 'title',
    'php_4' => 'php_4',
    'php_3' => 'php_4',
    'php_6' => 'php_6',
    'php_5' => 'php_5',
    'php_2' => 'php_2',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'nid_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nothing' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'php_4' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'php_3' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'php_6' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'php_5' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'php_2' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Dagsorden header */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['ui_name'] = 'Dagsorden header';
  $handler->display->display_options['header']['area']['content'] = '<?php
os2dagsorden_meeting_views_meeting_details_fields_tilleags_dagsorden_header();
?>';
  $handler->display->display_options['header']['area']['format'] = 'php_code';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Tillæg */
  $handler->display->display_options['relationships']['reverse_field_os2web_meetings_addendum_node']['id'] = 'reverse_field_os2web_meetings_addendum_node';
  $handler->display->display_options['relationships']['reverse_field_os2web_meetings_addendum_node']['table'] = 'node';
  $handler->display->display_options['relationships']['reverse_field_os2web_meetings_addendum_node']['field'] = 'reverse_field_os2web_meetings_addendum_node';
  $handler->display->display_options['relationships']['reverse_field_os2web_meetings_addendum_node']['ui_name'] = 'Tillæg';
  $handler->display->display_options['relationships']['reverse_field_os2web_meetings_addendum_node']['required'] = TRUE;
  /* Relationship: bullet point */
  $handler->display->display_options['relationships']['field_os2web_meetings_bullets_target_id']['id'] = 'field_os2web_meetings_bullets_target_id';
  $handler->display->display_options['relationships']['field_os2web_meetings_bullets_target_id']['table'] = 'field_data_field_os2web_meetings_bullets';
  $handler->display->display_options['relationships']['field_os2web_meetings_bullets_target_id']['field'] = 'field_os2web_meetings_bullets_target_id';
  $handler->display->display_options['relationships']['field_os2web_meetings_bullets_target_id']['relationship'] = 'reverse_field_os2web_meetings_addendum_node';
  $handler->display->display_options['relationships']['field_os2web_meetings_bullets_target_id']['ui_name'] = 'bullet point';
  $handler->display->display_options['relationships']['field_os2web_meetings_bullets_target_id']['required'] = TRUE;
  /* Relationship: bullet point speaking paper */
  $handler->display->display_options['relationships']['reverse_field_os2web_meetings_bullets_node']['id'] = 'reverse_field_os2web_meetings_bullets_node';
  $handler->display->display_options['relationships']['reverse_field_os2web_meetings_bullets_node']['table'] = 'node';
  $handler->display->display_options['relationships']['reverse_field_os2web_meetings_bullets_node']['field'] = 'reverse_field_os2web_meetings_bullets_node';
  $handler->display->display_options['relationships']['reverse_field_os2web_meetings_bullets_node']['relationship'] = 'field_os2web_meetings_bullets_target_id';
  $handler->display->display_options['relationships']['reverse_field_os2web_meetings_bullets_node']['ui_name'] = 'bullet point speaking paper';
  $handler->display->display_options['relationships']['reverse_field_os2web_meetings_bullets_node']['label'] = 'bullet point speaking paper';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_os2web_meetings_attach_target_id']['id'] = 'field_os2web_meetings_attach_target_id';
  $handler->display->display_options['relationships']['field_os2web_meetings_attach_target_id']['table'] = 'field_data_field_os2web_meetings_attach';
  $handler->display->display_options['relationships']['field_os2web_meetings_attach_target_id']['field'] = 'field_os2web_meetings_attach_target_id';
  $handler->display->display_options['relationships']['field_os2web_meetings_attach_target_id']['relationship'] = 'field_os2web_meetings_bullets_target_id';
  $handler->display->display_options['relationships']['field_os2web_meetings_attach_target_id']['label'] = 'bullet point attachment';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Meeting id - hidden */
  $handler->display->display_options['fields']['nid_1']['id'] = 'nid_1';
  $handler->display->display_options['fields']['nid_1']['table'] = 'node';
  $handler->display->display_options['fields']['nid_1']['field'] = 'nid';
  $handler->display->display_options['fields']['nid_1']['ui_name'] = 'Meeting id - hidden';
  $handler->display->display_options['fields']['nid_1']['label'] = '';
  $handler->display->display_options['fields']['nid_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid_1']['element_label_colon'] = FALSE;
  /* Field: Bullet point id - hidden */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['relationship'] = 'field_os2web_meetings_bullets_target_id';
  $handler->display->display_options['fields']['nid']['ui_name'] = 'Bullet point id - hidden';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: hide show container */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'hide show container';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['element_class'] = 'hide_show_button_container';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Field: bullet point title [hidden], for speaker paper link */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'field_os2web_meetings_bullets_target_id';
  $handler->display->display_options['fields']['title']['ui_name'] = 'bullet point title [hidden], for speaker paper link';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Bullet point title - php */
  $handler->display->display_options['fields']['php_4']['id'] = 'php_4';
  $handler->display->display_options['fields']['php_4']['table'] = 'views';
  $handler->display->display_options['fields']['php_4']['field'] = 'php';
  $handler->display->display_options['fields']['php_4']['ui_name'] = 'Bullet point title - php';
  $handler->display->display_options['fields']['php_4']['label'] = '';
  $handler->display->display_options['fields']['php_4']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php_4']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_4']['php_output'] = '<?php
$title = $data->node_field_data_field_os2web_meetings_bullets_title;
$meeting_id = $row->nid_1;
$bp_id = $row->nid;

os2dagsorden_meeting_views_meeting_details_fields_bullet_point_title($title, $meeting_id, $bp_id);
?>';
  $handler->display->display_options['fields']['php_4']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_4']['php_click_sortable'] = '';
  /* Field: bullet point attachments with text */
  $handler->display->display_options['fields']['php_3']['id'] = 'php_3';
  $handler->display->display_options['fields']['php_3']['table'] = 'views';
  $handler->display->display_options['fields']['php_3']['field'] = 'php';
  $handler->display->display_options['fields']['php_3']['ui_name'] = 'bullet point attachments with text';
  $handler->display->display_options['fields']['php_3']['label'] = '';
  $handler->display->display_options['fields']['php_3']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php_3']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_3']['php_output'] = '<?php
$meeting_id = $row->nid_1;
$bp_id = $row->nid;

os2dagsorden_meeting_views_meeting_details_fields_bullet_point_attachments_with_text($meeting_id, $bp_id);
?>';
  $handler->display->display_options['fields']['php_3']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_3']['php_click_sortable'] = '';
  /* Field: send to friend */
  $handler->display->display_options['fields']['php_6']['id'] = 'php_6';
  $handler->display->display_options['fields']['php_6']['table'] = 'views';
  $handler->display->display_options['fields']['php_6']['field'] = 'php';
  $handler->display->display_options['fields']['php_6']['ui_name'] = 'send to friend';
  $handler->display->display_options['fields']['php_6']['label'] = '';
  $handler->display->display_options['fields']['php_6']['element_class'] = 'send-bullet-point-link';
  $handler->display->display_options['fields']['php_6']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php_6']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_6']['php_output'] = '<?php 
os2dagsorden_meeting_views_meeting_details_fields_bullet_point_send_link($row->nid_1, $row->nid); 
?>';
  $handler->display->display_options['fields']['php_6']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_6']['php_click_sortable'] = '';
  /* Field: bullet point print link */
  $handler->display->display_options['fields']['php_5']['id'] = 'php_5';
  $handler->display->display_options['fields']['php_5']['table'] = 'views';
  $handler->display->display_options['fields']['php_5']['field'] = 'php';
  $handler->display->display_options['fields']['php_5']['ui_name'] = 'bullet point print link';
  $handler->display->display_options['fields']['php_5']['label'] = '';
  $handler->display->display_options['fields']['php_5']['alter']['path'] = 'print/meeting/[nid_1]/bullet-point/[nid]/print';
  $handler->display->display_options['fields']['php_5']['element_class'] = 'print-bullet-point-link';
  $handler->display->display_options['fields']['php_5']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php_5']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_5']['php_output'] = '<?php
$meeting_id = $row->nid_1;
$bp_id = $row->nid;
os2dagsorden_meeting_views_meeting_details_fields_bullet_point_print_link($meeting_id, $bp_id);
?>';
  $handler->display->display_options['fields']['php_5']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_5']['php_click_sortable'] = '';
  /* Field: speaker paper link */
  $handler->display->display_options['fields']['php_2']['id'] = 'php_2';
  $handler->display->display_options['fields']['php_2']['table'] = 'views';
  $handler->display->display_options['fields']['php_2']['field'] = 'php';
  $handler->display->display_options['fields']['php_2']['ui_name'] = 'speaker paper link';
  $handler->display->display_options['fields']['php_2']['label'] = '';
  $handler->display->display_options['fields']['php_2']['element_class'] = 'speaker-paper-link-container';
  $handler->display->display_options['fields']['php_2']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php_2']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_2']['php_output'] = '<?php
$meeting_id = $row->nid_1;
$bp_id = $row->nid;
$bp_title = $row->title;

os2dagsorden_meeting_views_meeting_details_fields_speaker_paper_link($meeting_id, $bp_id, $bp_title);
?>';
  $handler->display->display_options['fields']['php_2']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_2']['php_click_sortable'] = '';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'os2web_meetings_meeting' => 'os2web_meetings_meeting',
  );
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );
  $handler->display->display_options['attachment_position'] = 'after';
  $translatables['meeting_details'] = array(
    t('Master'),
    t('Deltagerne'),
    t('more'),
    t('Apply'),
    t('Gendan'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('author'),
    t('Alle'),
    t('Page'),
    t('Mødedetaljer'),
    t('term from field_os2web_meetings_committee'),
    t('Møde'),
    t('Startdato'),
    t('Slutdato'),
    t('Udvalg'),
    t('Type'),
    t('Lokation'),
    t('Comments'),
    t('Kommentarer'),
    t('Bemærkninger'),
    t('Særlige Forhold'),
    t(' Særlige Forhold'),
    t('Deltagere'),
    t('Afbud / Fraværende'),
    t('Print all speaker papers'),
    t('Print alle talepapirer'),
    t('Dagsorden'),
    t('<?php
os2dagsorden_meeting_views_meeting_details_fields_dagsorden_header();
?>'),
    t('Content entity referenced from field_os2web_meetings_bullets'),
    t('bullet point speaking paper'),
    t('bullet point attachment'),
    t('Lukket Dagsorden'),
    t('<?php
os2dagsorden_meeting_views_meeting_details_fields_lukket_dagsorden_header();
?>'),
    t('PHP'),
    t('Tillæg Print all speaker papers'),
    t('field_os2web_meetings_addendum'),
    t('Tillæg Dagsorden'),
    t('<?php
os2dagsorden_meeting_views_meeting_details_fields_tilleags_dagsorden_header();
?>'),
  );
  $export['meeting_details'] = $view;

  $view = new view();
  $view->name = 'meetings_search';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Meetings search';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Mødesøgning';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    2 => '2',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Søg';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Gendan';
  $handler->display->display_options['pager']['type'] = 'mini';
  $handler->display->display_options['pager']['options']['items_per_page'] = '15';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '2';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹‹';
  $handler->display->display_options['pager']['options']['tags']['next'] = '››';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'nid' => 'nid',
    'php_4' => 'php_4',
    'php_5' => 'php_5',
    'php_8' => 'php_8',
    'php_1' => 'php_2',
    'php' => 'php_2',
    'php_2' => 'php_2',
    'php_7' => 'php_7',
    'field_os2web_meetings_date' => 'field_os2web_meetings_date',
    'php_6' => 'php_6',
    'php_9' => 'php_9',
    'php_3' => 'php_3',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'nid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'php_4' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'php_5' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'php_8' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'php_1' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'php' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'php_2' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'php_7' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'field_os2web_meetings_date' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'php_6' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'php_9' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'php_3' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Header: help text */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['ui_name'] = 'help text';
  $handler->display->display_options['header']['area']['empty'] = TRUE;
  $handler->display->display_options['header']['area']['content'] = '<?php
os2dagsorden_meeting_views_meetings_search_help_text();
?>';
  $handler->display->display_options['header']['area']['format'] = 'php_code';
  /* Header: breadcrumb override */
  $handler->display->display_options['header']['php']['id'] = 'php';
  $handler->display->display_options['header']['php']['table'] = 'views';
  $handler->display->display_options['header']['php']['field'] = 'php';
  $handler->display->display_options['header']['php']['ui_name'] = 'breadcrumb override';
  $handler->display->display_options['header']['php']['empty'] = TRUE;
  $handler->display->display_options['header']['php']['php_output'] = '<?php 
os2dagsorden_meeting_views_meetings_search_breadcrumb();
?>';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['content'] = 'Ingen møder er fundet';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  /* Relationship: Content: Committee (field_os2web_meetings_committee) */
  $handler->display->display_options['relationships']['field_os2web_meetings_committee_tid']['id'] = 'field_os2web_meetings_committee_tid';
  $handler->display->display_options['relationships']['field_os2web_meetings_committee_tid']['table'] = 'field_data_field_os2web_meetings_committee';
  $handler->display->display_options['relationships']['field_os2web_meetings_committee_tid']['field'] = 'field_os2web_meetings_committee_tid';
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: bullet_point_id - php */
  $handler->display->display_options['fields']['php_4']['id'] = 'php_4';
  $handler->display->display_options['fields']['php_4']['table'] = 'views';
  $handler->display->display_options['fields']['php_4']['field'] = 'php';
  $handler->display->display_options['fields']['php_4']['ui_name'] = 'bullet_point_id - php';
  $handler->display->display_options['fields']['php_4']['label'] = '';
  $handler->display->display_options['fields']['php_4']['exclude'] = TRUE;
  $handler->display->display_options['fields']['php_4']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php_4']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['php_4']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_4']['php_setup'] = '$static = array();
$static[] = "hello!";
$static["test"] = "test2";';
  $handler->display->display_options['fields']['php_4']['php_output'] = '<?php
$meta_data = $data->_field_data[\'nid\'][\'entity\']->field_os2web_meetings_searchdata[\'und\'][0][\'value\'];

os2dagsorden_meeting_views_meetings_search_fields_bp_id($meta_data);
?>';
  $handler->display->display_options['fields']['php_4']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_4']['php_click_sortable'] = '';
  /* Field: bpa_id - php */
  $handler->display->display_options['fields']['php_5']['id'] = 'php_5';
  $handler->display->display_options['fields']['php_5']['table'] = 'views';
  $handler->display->display_options['fields']['php_5']['field'] = 'php';
  $handler->display->display_options['fields']['php_5']['ui_name'] = 'bpa_id - php';
  $handler->display->display_options['fields']['php_5']['label'] = '';
  $handler->display->display_options['fields']['php_5']['exclude'] = TRUE;
  $handler->display->display_options['fields']['php_5']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php_5']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_5']['php_output'] = '<?php
$meta_data = $data->_field_data[\'nid\'][\'entity\']->field_os2web_meetings_searchdata[\'und\'][0][\'value\'];

os2dagsorden_meeting_views_meetings_search_fields_bpa_id($meta_data);
?>';
  $handler->display->display_options['fields']['php_5']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_5']['php_click_sortable'] = '';
  /* Field: indicator - has speaker paper */
  $handler->display->display_options['fields']['php_1']['id'] = 'php_1';
  $handler->display->display_options['fields']['php_1']['table'] = 'views';
  $handler->display->display_options['fields']['php_1']['field'] = 'php';
  $handler->display->display_options['fields']['php_1']['ui_name'] = 'indicator - has speaker paper';
  $handler->display->display_options['fields']['php_1']['label'] = '';
  $handler->display->display_options['fields']['php_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php_1']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_1']['php_output'] = '<?php
os2dagsorden_meeting_views_meetings_search_fields_meeting_has_sp($row->nid);
?>';
  $handler->display->display_options['fields']['php_1']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_1']['php_click_sortable'] = '';
  /* Field: indicator - has notes */
  $handler->display->display_options['fields']['php']['id'] = 'php';
  $handler->display->display_options['fields']['php']['table'] = 'views';
  $handler->display->display_options['fields']['php']['field'] = 'php';
  $handler->display->display_options['fields']['php']['ui_name'] = 'indicator - has notes';
  $handler->display->display_options['fields']['php']['label'] = '';
  $handler->display->display_options['fields']['php']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php']['php_output'] = '<?php
os2dagsorden_meeting_views_meetings_search_fields_meeting_has_notes($row->nid);
?>';
  $handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php']['php_click_sortable'] = '';
  /* Field: title - php */
  $handler->display->display_options['fields']['php_2']['id'] = 'php_2';
  $handler->display->display_options['fields']['php_2']['table'] = 'views';
  $handler->display->display_options['fields']['php_2']['field'] = 'php';
  $handler->display->display_options['fields']['php_2']['ui_name'] = 'title - php';
  $handler->display->display_options['fields']['php_2']['label'] = 'Møde';
  $handler->display->display_options['fields']['php_2']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['php_2']['alter']['path'] = 'meeting/[nid][php_4][php_5]';
  $handler->display->display_options['fields']['php_2']['element_label_class'] = 'views-field-field-title-short';
  $handler->display->display_options['fields']['php_2']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_2']['php_output'] = '<?php
os2dagsorden_meeting_views_meetings_search_fields_meeting_title($data);
?>';
  $handler->display->display_options['fields']['php_2']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_2']['php_click_sortable'] = '';
  /* Field: Content: Date */
  $handler->display->display_options['fields']['field_os2web_meetings_date']['id'] = 'field_os2web_meetings_date';
  $handler->display->display_options['fields']['field_os2web_meetings_date']['table'] = 'field_data_field_os2web_meetings_date';
  $handler->display->display_options['fields']['field_os2web_meetings_date']['field'] = 'field_os2web_meetings_date';
  $handler->display->display_options['fields']['field_os2web_meetings_date']['label'] = 'Dato';
  $handler->display->display_options['fields']['field_os2web_meetings_date']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_os2web_meetings_date']['alter']['path'] = 'meeting/[nid][php_4][php_5]';
  $handler->display->display_options['fields']['field_os2web_meetings_date']['empty'] = '&nbsp;';
  $handler->display->display_options['fields']['field_os2web_meetings_date']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['field_os2web_meetings_date']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'value',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Committee */
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['id'] = 'field_os2web_meetings_committee';
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['table'] = 'field_data_field_os2web_meetings_committee';
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['field'] = 'field_os2web_meetings_committee';
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['label'] = '';
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['alter']['path'] = 'meeting/[nid][php_4][php_5]';
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['alter']['max_length'] = '20';
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['empty'] = '&nbsp;';
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['type'] = 'taxonomy_term_reference_plain';
  /* Field: Taxonomy term: Name short */
  $handler->display->display_options['fields']['field_os2web_meetings_com_shname']['id'] = 'field_os2web_meetings_com_shname';
  $handler->display->display_options['fields']['field_os2web_meetings_com_shname']['table'] = 'field_data_field_os2web_meetings_com_shname';
  $handler->display->display_options['fields']['field_os2web_meetings_com_shname']['field'] = 'field_os2web_meetings_com_shname';
  $handler->display->display_options['fields']['field_os2web_meetings_com_shname']['relationship'] = 'field_os2web_meetings_committee_tid';
  $handler->display->display_options['fields']['field_os2web_meetings_com_shname']['label'] = 'Udvalg';
  $handler->display->display_options['fields']['field_os2web_meetings_com_shname']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_os2web_meetings_com_shname']['alter']['path'] = 'meeting/[nid][php_4][php_5]';
  $handler->display->display_options['fields']['field_os2web_meetings_com_shname']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_os2web_meetings_com_shname']['empty'] = '[field_os2web_meetings_committee]';
  /* Field: Placering - php */
  $handler->display->display_options['fields']['php_3']['id'] = 'php_3';
  $handler->display->display_options['fields']['php_3']['table'] = 'views';
  $handler->display->display_options['fields']['php_3']['field'] = 'php';
  $handler->display->display_options['fields']['php_3']['ui_name'] = 'Placering - php';
  $handler->display->display_options['fields']['php_3']['label'] = 'Placering';
  $handler->display->display_options['fields']['php_3']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['php_3']['alter']['path'] = 'meeting/[nid][php_4][php_5]';
  $handler->display->display_options['fields']['php_3']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['php_3']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['php_3']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_3']['php_output'] = '<?php
$meta_data = $data->_field_data[\'nid\'][\'entity\']->field_os2web_meetings_searchdata[\'und\'][0][\'value\'];

os2dagsorden_meeting_views_meetings_search_fields_placering($meta_data);
?>';
  $handler->display->display_options['fields']['php_3']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_3']['php_click_sortable'] = '';
  /* Field: Committee */
  $handler->display->display_options['fields']['php_6']['id'] = 'php_6';
  $handler->display->display_options['fields']['php_6']['table'] = 'views';
  $handler->display->display_options['fields']['php_6']['field'] = 'php';
  $handler->display->display_options['fields']['php_6']['ui_name'] = 'Committee';
  $handler->display->display_options['fields']['php_6']['label'] = 'Udvalg';
  $handler->display->display_options['fields']['php_6']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php_6']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_6']['php_output'] = '<?php
os2dagsorden_meeting_views_meetings_search_fields_committee($row->nid)
?>';
  $handler->display->display_options['fields']['php_6']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_6']['php_click_sortable'] = '';
  /* Sort criterion: Content: Date -  start date (field_os2web_meetings_date) */
  $handler->display->display_options['sorts']['field_os2web_meetings_date_value']['id'] = 'field_os2web_meetings_date_value';
  $handler->display->display_options['sorts']['field_os2web_meetings_date_value']['table'] = 'field_data_field_os2web_meetings_date';
  $handler->display->display_options['sorts']['field_os2web_meetings_date_value']['field'] = 'field_os2web_meetings_date_value';
  $handler->display->display_options['sorts']['field_os2web_meetings_date_value']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'os2web_meetings_meeting' => 'os2web_meetings_meeting',
  );
  /* Filter criterion: Content: Date -  start date (field_os2web_meetings_date) */
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['id'] = 'field_os2web_meetings_date_value';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['table'] = 'field_data_field_os2web_meetings_date';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['field'] = 'field_os2web_meetings_date_value';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['expose']['operator_id'] = 'field_os2web_meetings_date_value_op';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['expose']['label'] = 'Date -  start date (field_os2web_meetings_date)';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['expose']['operator'] = 'field_os2web_meetings_date_value_op';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['expose']['identifier'] = 'field_os2web_meetings_date_value';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['form_type'] = 'date_popup';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['year_range'] = '-0:+1';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['exposed_block'] = TRUE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: bullet_point_id - php */
  $handler->display->display_options['fields']['php_4']['id'] = 'php_4';
  $handler->display->display_options['fields']['php_4']['table'] = 'views';
  $handler->display->display_options['fields']['php_4']['field'] = 'php';
  $handler->display->display_options['fields']['php_4']['ui_name'] = 'bullet_point_id - php';
  $handler->display->display_options['fields']['php_4']['label'] = '';
  $handler->display->display_options['fields']['php_4']['exclude'] = TRUE;
  $handler->display->display_options['fields']['php_4']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php_4']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['php_4']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_4']['php_setup'] = '$static = array();
$static[] = "hello!";
$static["test"] = "test2";';
  $handler->display->display_options['fields']['php_4']['php_output'] = '<?php
$meta_data = $data->_field_data[\'nid\'][\'entity\']->field_os2web_meetings_searchdata[\'und\'][0][\'value\'];

os2dagsorden_meeting_views_meetings_search_fields_bp_id($meta_data);
?>';
  $handler->display->display_options['fields']['php_4']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_4']['php_click_sortable'] = '';
  /* Field: bpa_id - php */
  $handler->display->display_options['fields']['php_5']['id'] = 'php_5';
  $handler->display->display_options['fields']['php_5']['table'] = 'views';
  $handler->display->display_options['fields']['php_5']['field'] = 'php';
  $handler->display->display_options['fields']['php_5']['ui_name'] = 'bpa_id - php';
  $handler->display->display_options['fields']['php_5']['label'] = '';
  $handler->display->display_options['fields']['php_5']['exclude'] = TRUE;
  $handler->display->display_options['fields']['php_5']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php_5']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_5']['php_output'] = '<?php
$meta_data = $data->_field_data[\'nid\'][\'entity\']->field_os2web_meetings_searchdata[\'und\'][0][\'value\'];

os2dagsorden_meeting_views_meetings_search_fields_bpa_id($meta_data);
?>';
  $handler->display->display_options['fields']['php_5']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_5']['php_click_sortable'] = '';
  /* Field: Search param - php */
  $handler->display->display_options['fields']['php_8']['id'] = 'php_8';
  $handler->display->display_options['fields']['php_8']['table'] = 'views';
  $handler->display->display_options['fields']['php_8']['field'] = 'php';
  $handler->display->display_options['fields']['php_8']['ui_name'] = 'Search param - php';
  $handler->display->display_options['fields']['php_8']['label'] = '';
  $handler->display->display_options['fields']['php_8']['exclude'] = TRUE;
  $handler->display->display_options['fields']['php_8']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php_8']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_8']['php_output'] = '<?php
os2dagsorden_meeting_views_meetings_search_fields_search_param();
?>';
  $handler->display->display_options['fields']['php_8']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_8']['php_click_sortable'] = '';
  /* Field: Status */
  $handler->display->display_options['fields']['php_7']['id'] = 'php_7';
  $handler->display->display_options['fields']['php_7']['table'] = 'views';
  $handler->display->display_options['fields']['php_7']['field'] = 'php';
  $handler->display->display_options['fields']['php_7']['ui_name'] = 'Status';
  $handler->display->display_options['fields']['php_7']['label'] = 'Status';
  $handler->display->display_options['fields']['php_7']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['php_7']['alter']['path'] = 'meeting/[nid][php_4][php_5]';
  $handler->display->display_options['fields']['php_7']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_7']['php_output'] = '<?php
 os2dagsorden_meeting_views_meetings_search_fields_status($row->nid);
?>';
  $handler->display->display_options['fields']['php_7']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_7']['php_click_sortable'] = '';
  /* Field: title - php */
  $handler->display->display_options['fields']['php_2']['id'] = 'php_2';
  $handler->display->display_options['fields']['php_2']['table'] = 'views';
  $handler->display->display_options['fields']['php_2']['field'] = 'php';
  $handler->display->display_options['fields']['php_2']['ui_name'] = 'title - php';
  $handler->display->display_options['fields']['php_2']['label'] = 'Møde';
  $handler->display->display_options['fields']['php_2']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['php_2']['alter']['path'] = 'meeting/[nid][php_4][php_5][php_8]';
  $handler->display->display_options['fields']['php_2']['element_label_class'] = 'views-field-field-title-short';
  $handler->display->display_options['fields']['php_2']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_2']['php_output'] = '<?php
os2dagsorden_meeting_views_meetings_search_fields_meeting_title($data);
?>';
  $handler->display->display_options['fields']['php_2']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_2']['php_click_sortable'] = '';
  /* Field: Committee */
  $handler->display->display_options['fields']['php_6']['id'] = 'php_6';
  $handler->display->display_options['fields']['php_6']['table'] = 'views';
  $handler->display->display_options['fields']['php_6']['field'] = 'php';
  $handler->display->display_options['fields']['php_6']['ui_name'] = 'Committee';
  $handler->display->display_options['fields']['php_6']['label'] = 'Udvalg';
  $handler->display->display_options['fields']['php_6']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['php_6']['alter']['path'] = 'meeting/[nid][php_4][php_5][php_8]';
  $handler->display->display_options['fields']['php_6']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php_6']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_6']['php_output'] = '<?php
os2dagsorden_meeting_views_meetings_search_fields_committee($row->nid);
?>';
  $handler->display->display_options['fields']['php_6']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_6']['php_click_sortable'] = '';
  /* Field: Content: Date */
  $handler->display->display_options['fields']['field_os2web_meetings_date']['id'] = 'field_os2web_meetings_date';
  $handler->display->display_options['fields']['field_os2web_meetings_date']['table'] = 'field_data_field_os2web_meetings_date';
  $handler->display->display_options['fields']['field_os2web_meetings_date']['field'] = 'field_os2web_meetings_date';
  $handler->display->display_options['fields']['field_os2web_meetings_date']['label'] = 'Dato';
  $handler->display->display_options['fields']['field_os2web_meetings_date']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_os2web_meetings_date']['alter']['path'] = 'meeting/[nid][php_4][php_5][php_8]';
  $handler->display->display_options['fields']['field_os2web_meetings_date']['empty'] = '&nbsp;';
  $handler->display->display_options['fields']['field_os2web_meetings_date']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['field_os2web_meetings_date']['settings'] = array(
    'format_type' => 'date_only',
    'fromto' => 'value',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Location */
  $handler->display->display_options['fields']['php_9']['id'] = 'php_9';
  $handler->display->display_options['fields']['php_9']['table'] = 'views';
  $handler->display->display_options['fields']['php_9']['field'] = 'php';
  $handler->display->display_options['fields']['php_9']['ui_name'] = 'Location';
  $handler->display->display_options['fields']['php_9']['label'] = 'Lokation';
  $handler->display->display_options['fields']['php_9']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['php_9']['alter']['path'] = 'meeting/[nid][php_4][php_5][php_8]';
  $handler->display->display_options['fields']['php_9']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_9']['php_output'] = '<?php
os2dagsorden_meeting_views_meetings_search_fields_location($row->nid);
?>';
  $handler->display->display_options['fields']['php_9']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_9']['php_click_sortable'] = '';
  /* Field: Placering - php */
  $handler->display->display_options['fields']['php_3']['id'] = 'php_3';
  $handler->display->display_options['fields']['php_3']['table'] = 'views';
  $handler->display->display_options['fields']['php_3']['field'] = 'php';
  $handler->display->display_options['fields']['php_3']['ui_name'] = 'Placering - php';
  $handler->display->display_options['fields']['php_3']['label'] = 'Placering';
  $handler->display->display_options['fields']['php_3']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['php_3']['alter']['path'] = 'meeting/[nid][php_4][php_5][php_8]';
  $handler->display->display_options['fields']['php_3']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['php_3']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['php_3']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_3']['php_output'] = '<?php
$meta_data = $data->_field_data[\'nid\'][\'entity\']->field_os2web_meetings_searchdata[\'und\'][0][\'value\'];

os2dagsorden_meeting_views_meetings_search_fields_placering($meta_data);
?>';
  $handler->display->display_options['fields']['php_3']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_3']['php_click_sortable'] = '';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'os2web_meetings_meeting' => 'os2web_meetings_meeting',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Date -  start date (field_os2web_meetings_date) */
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['id'] = 'field_os2web_meetings_date_value';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['table'] = 'field_data_field_os2web_meetings_date';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['field'] = 'field_os2web_meetings_date_value';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['operator'] = '>=';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['group'] = 1;
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['expose']['operator_id'] = 'field_os2web_meetings_date_value_op';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['expose']['label'] = 'Fra dato:';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['expose']['operator'] = 'field_os2web_meetings_date_value_op';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['expose']['identifier'] = 'from_date';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['expose']['remember_roles'] = array(
    2 => 0,
    4 => '4',
    1 => 0,
    5 => 0,
    3 => 0,
  );
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['form_type'] = 'date_popup';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['default_date'] = 'now';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['year_range'] = '2011:+1';
  /* Filter criterion: Content: Date -  start date (field_os2web_meetings_date) */
  $handler->display->display_options['filters']['field_os2web_meetings_date_value_1']['id'] = 'field_os2web_meetings_date_value_1';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value_1']['table'] = 'field_data_field_os2web_meetings_date';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value_1']['field'] = 'field_os2web_meetings_date_value';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value_1']['operator'] = '<=';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value_1']['group'] = 1;
  $handler->display->display_options['filters']['field_os2web_meetings_date_value_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_os2web_meetings_date_value_1']['expose']['operator_id'] = 'field_os2web_meetings_date_value_1_op';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value_1']['expose']['label'] = 'Til dato:';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value_1']['expose']['operator'] = 'field_os2web_meetings_date_value_1_op';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value_1']['expose']['identifier'] = 'to_date';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value_1']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['field_os2web_meetings_date_value_1']['expose']['remember_roles'] = array(
    2 => 0,
    4 => '4',
    1 => 0,
    5 => 0,
    3 => 0,
  );
  $handler->display->display_options['filters']['field_os2web_meetings_date_value_1']['group_info']['label'] = 'Date -  start date (field_os2web_meetings_date)';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value_1']['group_info']['identifier'] = 'field_os2web_meetings_date_value_1';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value_1']['group_info']['remember'] = FALSE;
  $handler->display->display_options['filters']['field_os2web_meetings_date_value_1']['group_info']['group_items'] = array(
    1 => array(),
    2 => array(),
    3 => array(),
  );
  $handler->display->display_options['filters']['field_os2web_meetings_date_value_1']['form_type'] = 'date_popup';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value_1']['default_date'] = 'now + 1 month';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value_1']['year_range'] = '2011:+1';
  /* Filter criterion: Content: Committee (field_os2web_meetings_committee) */
  $handler->display->display_options['filters']['field_os2web_meetings_committee_tid']['id'] = 'field_os2web_meetings_committee_tid';
  $handler->display->display_options['filters']['field_os2web_meetings_committee_tid']['table'] = 'field_data_field_os2web_meetings_committee';
  $handler->display->display_options['filters']['field_os2web_meetings_committee_tid']['field'] = 'field_os2web_meetings_committee_tid';
  $handler->display->display_options['filters']['field_os2web_meetings_committee_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_os2web_meetings_committee_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_os2web_meetings_committee_tid']['expose']['operator_id'] = 'field_os2web_meetings_committee_tid_op';
  $handler->display->display_options['filters']['field_os2web_meetings_committee_tid']['expose']['label'] = 'Udvalg:';
  $handler->display->display_options['filters']['field_os2web_meetings_committee_tid']['expose']['operator'] = 'field_os2web_meetings_committee_tid_op';
  $handler->display->display_options['filters']['field_os2web_meetings_committee_tid']['expose']['identifier'] = 'field_os2web_meetings_committee_tid';
  $handler->display->display_options['filters']['field_os2web_meetings_committee_tid']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['field_os2web_meetings_committee_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    4 => 0,
    5 => 0,
    3 => 0,
  );
  $handler->display->display_options['filters']['field_os2web_meetings_committee_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_os2web_meetings_committee_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_os2web_meetings_committee_tid']['vocabulary'] = 'os2web_meetings_tax_committee';
  /* Filter criterion: Content: Search meta data (field_os2web_meetings_searchdata) */
  $handler->display->display_options['filters']['field_os2web_meetings_searchdata_value']['id'] = 'field_os2web_meetings_searchdata_value';
  $handler->display->display_options['filters']['field_os2web_meetings_searchdata_value']['table'] = 'field_data_field_os2web_meetings_searchdata';
  $handler->display->display_options['filters']['field_os2web_meetings_searchdata_value']['field'] = 'field_os2web_meetings_searchdata_value';
  $handler->display->display_options['filters']['field_os2web_meetings_searchdata_value']['operator'] = 'allwords';
  $handler->display->display_options['filters']['field_os2web_meetings_searchdata_value']['group'] = 1;
  $handler->display->display_options['filters']['field_os2web_meetings_searchdata_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_os2web_meetings_searchdata_value']['expose']['operator_id'] = 'field_os2web_meetings_searchdata_value_op';
  $handler->display->display_options['filters']['field_os2web_meetings_searchdata_value']['expose']['label'] = 'Fritekst:';
  $handler->display->display_options['filters']['field_os2web_meetings_searchdata_value']['expose']['operator'] = 'field_os2web_meetings_searchdata_value_op';
  $handler->display->display_options['filters']['field_os2web_meetings_searchdata_value']['expose']['identifier'] = 'search_params';
  $handler->display->display_options['filters']['field_os2web_meetings_searchdata_value']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['field_os2web_meetings_searchdata_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    4 => 0,
    5 => 0,
    3 => 0,
  );
  /* Filter criterion: Additional agenda filter */
  $handler->display->display_options['filters']['php']['id'] = 'php';
  $handler->display->display_options['filters']['php']['table'] = 'views';
  $handler->display->display_options['filters']['php']['field'] = 'php';
  $handler->display->display_options['filters']['php']['ui_name'] = 'Additional agenda filter';
  $handler->display->display_options['filters']['php']['use_php_setup'] = 0;
  $handler->display->display_options['filters']['php']['php_filter'] = 'return os2dagsorden_meeting_views_meetings_search_filter_additional_agendas($row->nid);';
  $handler->display->display_options['path'] = 'meetings-search';
  $translatables['meetings_search'] = array(
    t('Master'),
    t('Mødesøgning'),
    t('more'),
    t('Søg'),
    t('Gendan'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹‹'),
    t('››'),
    t('last »'),
    t('<?php
os2dagsorden_meeting_views_meetings_search_help_text();
?>'),
    t('Ingen møder er fundet'),
    t('term from field_os2web_meetings_committee'),
    t('Møde'),
    t('Dato'),
    t('&nbsp;'),
    t('Udvalg'),
    t('[field_os2web_meetings_committee]'),
    t('Placering'),
    t('Date -  start date (field_os2web_meetings_date)'),
    t('Page'),
    t('Status'),
    t('Lokation'),
    t('Fra dato:'),
    t('Til dato:'),
    t('Udvalg:'),
    t('Fritekst:'),
  );
  $export['meetings_search'] = $view;

  $view = new view();
  $view->name = 'seneste_8_m_der_i_de_st_ende_politiske_udvalg_';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Seneste 8 møder i de stående politiske udvalg:';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Seneste 8 møder i mine udvalg';
  $handler->display->display_options['css_class'] = 'front-page-content-block';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'php';
  $handler->display->display_options['access']['php_access'] = 'return os2dagsorden_meeting_views_last_8_meetings_block_my_meetings_access();';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Gendan';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '8';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'nid' => 'nid',
    'tid' => 'tid',
    'field_os2web_meetings_type' => 'field_os2web_meetings_type',
    'php' => 'php_2',
    'php_1' => 'php_2',
    'php_2' => 'php_2',
    'field_os2web_meetings_date' => 'field_os2web_meetings_date',
    'php_4' => 'php_4',
    'php_3' => 'php_3',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'nid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'tid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_os2web_meetings_type' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'php' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'php_1' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'php_2' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'field_os2web_meetings_date' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'php_4' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'php_3' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
  );
  /* Header: help button */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['ui_name'] = 'help button';
  $handler->display->display_options['header']['area']['empty'] = TRUE;
  $handler->display->display_options['header']['area']['content'] = '<?php
os2dagsorden_meeting_views_last_8_meetings_help_text();
?>';
  $handler->display->display_options['header']['area']['format'] = 'php_code';
  /* Relationship: Content: Committee (field_os2web_meetings_committee) */
  $handler->display->display_options['relationships']['field_os2web_meetings_committee_tid']['id'] = 'field_os2web_meetings_committee_tid';
  $handler->display->display_options['relationships']['field_os2web_meetings_committee_tid']['table'] = 'field_data_field_os2web_meetings_committee';
  $handler->display->display_options['relationships']['field_os2web_meetings_committee_tid']['field'] = 'field_os2web_meetings_committee_tid';
  /* Relationship: Taxonomy term: User using Is part of Committee */
  $handler->display->display_options['relationships']['reverse_field_user_committee_user']['id'] = 'reverse_field_user_committee_user';
  $handler->display->display_options['relationships']['reverse_field_user_committee_user']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['relationships']['reverse_field_user_committee_user']['field'] = 'reverse_field_user_committee_user';
  $handler->display->display_options['relationships']['reverse_field_user_committee_user']['relationship'] = 'field_os2web_meetings_committee_tid';
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: committee tid */
  $handler->display->display_options['fields']['tid']['id'] = 'tid';
  $handler->display->display_options['fields']['tid']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['tid']['field'] = 'tid';
  $handler->display->display_options['fields']['tid']['relationship'] = 'field_os2web_meetings_committee_tid';
  $handler->display->display_options['fields']['tid']['ui_name'] = 'committee tid';
  $handler->display->display_options['fields']['tid']['label'] = '';
  $handler->display->display_options['fields']['tid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['tid']['element_label_colon'] = FALSE;
  /* Field: Content: Type */
  $handler->display->display_options['fields']['field_os2web_meetings_type']['id'] = 'field_os2web_meetings_type';
  $handler->display->display_options['fields']['field_os2web_meetings_type']['table'] = 'field_data_field_os2web_meetings_type';
  $handler->display->display_options['fields']['field_os2web_meetings_type']['field'] = 'field_os2web_meetings_type';
  $handler->display->display_options['fields']['field_os2web_meetings_type']['label'] = 'Status';
  $handler->display->display_options['fields']['field_os2web_meetings_type']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_os2web_meetings_type']['alter']['path'] = 'meeting/[nid]';
  $handler->display->display_options['fields']['field_os2web_meetings_type']['empty'] = '&nbsp;';
  $handler->display->display_options['fields']['field_os2web_meetings_type']['hide_alter_empty'] = FALSE;
  /* Field: indicator - has speaker paper */
  $handler->display->display_options['fields']['php']['id'] = 'php';
  $handler->display->display_options['fields']['php']['table'] = 'views';
  $handler->display->display_options['fields']['php']['field'] = 'php';
  $handler->display->display_options['fields']['php']['ui_name'] = 'indicator - has speaker paper';
  $handler->display->display_options['fields']['php']['label'] = '';
  $handler->display->display_options['fields']['php']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php']['php_output'] = '<?php
os2dagsorden_meeting_views_last_8_meetings_fields_meeting_has_sp($row->nid);
?>';
  $handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php']['php_click_sortable'] = '';
  /* Field: indicator - has notes */
  $handler->display->display_options['fields']['php_1']['id'] = 'php_1';
  $handler->display->display_options['fields']['php_1']['table'] = 'views';
  $handler->display->display_options['fields']['php_1']['field'] = 'php';
  $handler->display->display_options['fields']['php_1']['ui_name'] = 'indicator - has notes';
  $handler->display->display_options['fields']['php_1']['label'] = '';
  $handler->display->display_options['fields']['php_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php_1']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_1']['php_output'] = '<?php
os2dagsorden_meeting_views_last_8_meetings_fields_meeting_has_notes($row->nid);
?>';
  $handler->display->display_options['fields']['php_1']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_1']['php_click_sortable'] = '';
  /* Field: title - php */
  $handler->display->display_options['fields']['php_2']['id'] = 'php_2';
  $handler->display->display_options['fields']['php_2']['table'] = 'views';
  $handler->display->display_options['fields']['php_2']['field'] = 'php';
  $handler->display->display_options['fields']['php_2']['ui_name'] = 'title - php';
  $handler->display->display_options['fields']['php_2']['label'] = 'Møde';
  $handler->display->display_options['fields']['php_2']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['php_2']['alter']['path'] = 'meeting/[nid]';
  $handler->display->display_options['fields']['php_2']['element_class'] = 'views-field-field-title-short';
  $handler->display->display_options['fields']['php_2']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php_2']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_2']['php_output'] = '<?php
os2dagsorden_meeting_views_last_8_meetings_fields_meeting_title($data);
?>';
  $handler->display->display_options['fields']['php_2']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_2']['php_click_sortable'] = '';
  /* Field: Content: Date */
  $handler->display->display_options['fields']['field_os2web_meetings_date']['id'] = 'field_os2web_meetings_date';
  $handler->display->display_options['fields']['field_os2web_meetings_date']['table'] = 'field_data_field_os2web_meetings_date';
  $handler->display->display_options['fields']['field_os2web_meetings_date']['field'] = 'field_os2web_meetings_date';
  $handler->display->display_options['fields']['field_os2web_meetings_date']['label'] = 'Dato';
  $handler->display->display_options['fields']['field_os2web_meetings_date']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_os2web_meetings_date']['alter']['path'] = 'meeting/[nid]';
  $handler->display->display_options['fields']['field_os2web_meetings_date']['empty'] = '&nbsp;';
  $handler->display->display_options['fields']['field_os2web_meetings_date']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'value',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Lokation */
  $handler->display->display_options['fields']['field_os2web_meetings_location']['id'] = 'field_os2web_meetings_location';
  $handler->display->display_options['fields']['field_os2web_meetings_location']['table'] = 'field_data_field_os2web_meetings_location';
  $handler->display->display_options['fields']['field_os2web_meetings_location']['field'] = 'field_os2web_meetings_location';
  $handler->display->display_options['fields']['field_os2web_meetings_location']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_os2web_meetings_location']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_os2web_meetings_location']['alter']['path'] = 'meeting/[nid]';
  $handler->display->display_options['fields']['field_os2web_meetings_location']['empty'] = '&nbsp;';
  $handler->display->display_options['fields']['field_os2web_meetings_location']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['field_os2web_meetings_location']['type'] = 'taxonomy_term_reference_plain';
  /* Field: Location */
  $handler->display->display_options['fields']['php_4']['id'] = 'php_4';
  $handler->display->display_options['fields']['php_4']['table'] = 'views';
  $handler->display->display_options['fields']['php_4']['field'] = 'php';
  $handler->display->display_options['fields']['php_4']['ui_name'] = 'Location';
  $handler->display->display_options['fields']['php_4']['label'] = 'Lokation';
  $handler->display->display_options['fields']['php_4']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['php_4']['alter']['path'] = 'meeting/[nid]';
  $handler->display->display_options['fields']['php_4']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['php_4']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_4']['php_output'] = '<?php
os2dagsorden_meeting_views_last_8_meetings_fields_meeting_location($row->nid)
?>';
  $handler->display->display_options['fields']['php_4']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_4']['php_click_sortable'] = '';
  /* Field: Content: Committee */
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['id'] = 'field_os2web_meetings_committee';
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['table'] = 'field_data_field_os2web_meetings_committee';
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['field'] = 'field_os2web_meetings_committee';
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['label'] = '';
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['alter']['path'] = 'meeting/[nid]';
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['alter']['max_length'] = '20';
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['empty'] = '&nbsp;';
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['type'] = 'taxonomy_term_reference_plain';
  /* Field: Committe */
  $handler->display->display_options['fields']['php_3']['id'] = 'php_3';
  $handler->display->display_options['fields']['php_3']['table'] = 'views';
  $handler->display->display_options['fields']['php_3']['field'] = 'php';
  $handler->display->display_options['fields']['php_3']['ui_name'] = 'Committe';
  $handler->display->display_options['fields']['php_3']['label'] = 'Udvalg';
  $handler->display->display_options['fields']['php_3']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['php_3']['alter']['path'] = 'meeting/[nid]';
  $handler->display->display_options['fields']['php_3']['alter']['max_length'] = '15';
  $handler->display->display_options['fields']['php_3']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['php_3']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php_3']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_3']['php_output'] = '<?php
    os2dagsorden_meeting_views_last_8_meetings_fields_meeting_committee($row->nid);
?>';
  $handler->display->display_options['fields']['php_3']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_3']['php_click_sortable'] = '';
  /* Sort criterion: Content: Date -  start date (field_os2web_meetings_date) */
  $handler->display->display_options['sorts']['field_os2web_meetings_date_value']['id'] = 'field_os2web_meetings_date_value';
  $handler->display->display_options['sorts']['field_os2web_meetings_date_value']['table'] = 'field_data_field_os2web_meetings_date';
  $handler->display->display_options['sorts']['field_os2web_meetings_date_value']['field'] = 'field_os2web_meetings_date_value';
  $handler->display->display_options['sorts']['field_os2web_meetings_date_value']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'os2web_meetings_meeting' => 'os2web_meetings_meeting',
  );
  /* Filter criterion: Content: Date -  start date (field_os2web_meetings_date) */
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['id'] = 'field_os2web_meetings_date_value';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['table'] = 'field_data_field_os2web_meetings_date';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['field'] = 'field_os2web_meetings_date_value';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['operator'] = '<';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['default_date'] = 'tomorrow';
  /* Filter criterion: Content: Tillæg til (field_os2web_meetings_addendum) */
  $handler->display->display_options['filters']['field_os2web_meetings_addendum_nid']['id'] = 'field_os2web_meetings_addendum_nid';
  $handler->display->display_options['filters']['field_os2web_meetings_addendum_nid']['table'] = 'field_data_field_os2web_meetings_addendum';
  $handler->display->display_options['filters']['field_os2web_meetings_addendum_nid']['field'] = 'field_os2web_meetings_addendum_nid';
  $handler->display->display_options['filters']['field_os2web_meetings_addendum_nid']['operator'] = 'empty';

  /* Display: Block all meetings */
  $handler = $view->new_display('block', 'Block all meetings', 'block');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Aktuelle møder';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'php';
  $handler->display->display_options['access']['php_access'] = 'return os2dagsorden_meeting_views_last_8_meetings_block_all_meetings_access();';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '8';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: help button */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['ui_name'] = 'help button';
  $handler->display->display_options['header']['area']['empty'] = TRUE;
  $handler->display->display_options['header']['area']['content'] = '<?php
os2dagsorden_meeting_views_last_8_meetings_help_text("all_meetings");
?>';
  $handler->display->display_options['header']['area']['format'] = 'php_code';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: committee ID */
  $handler->display->display_options['fields']['tid']['id'] = 'tid';
  $handler->display->display_options['fields']['tid']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['tid']['field'] = 'tid';
  $handler->display->display_options['fields']['tid']['relationship'] = 'field_os2web_meetings_committee_tid';
  $handler->display->display_options['fields']['tid']['ui_name'] = 'committee ID';
  $handler->display->display_options['fields']['tid']['label'] = '';
  $handler->display->display_options['fields']['tid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['tid']['element_label_colon'] = FALSE;
  /* Field: Content: Type */
  $handler->display->display_options['fields']['field_os2web_meetings_type']['id'] = 'field_os2web_meetings_type';
  $handler->display->display_options['fields']['field_os2web_meetings_type']['table'] = 'field_data_field_os2web_meetings_type';
  $handler->display->display_options['fields']['field_os2web_meetings_type']['field'] = 'field_os2web_meetings_type';
  $handler->display->display_options['fields']['field_os2web_meetings_type']['label'] = 'Status';
  $handler->display->display_options['fields']['field_os2web_meetings_type']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_os2web_meetings_type']['alter']['path'] = 'meeting/[nid]';
  $handler->display->display_options['fields']['field_os2web_meetings_type']['empty'] = '&nbsp;';
  $handler->display->display_options['fields']['field_os2web_meetings_type']['hide_alter_empty'] = FALSE;
  /* Field: title - php */
  $handler->display->display_options['fields']['php_2']['id'] = 'php_2';
  $handler->display->display_options['fields']['php_2']['table'] = 'views';
  $handler->display->display_options['fields']['php_2']['field'] = 'php';
  $handler->display->display_options['fields']['php_2']['ui_name'] = 'title - php';
  $handler->display->display_options['fields']['php_2']['label'] = 'Møde';
  $handler->display->display_options['fields']['php_2']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['php_2']['alter']['path'] = 'meeting/[nid]';
  $handler->display->display_options['fields']['php_2']['element_class'] = 'views-field-field-title-short';
  $handler->display->display_options['fields']['php_2']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php_2']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_2']['php_output'] = '<?php
os2dagsorden_meeting_views_last_8_meetings_fields_meeting_title($data);
?>';
  $handler->display->display_options['fields']['php_2']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_2']['php_click_sortable'] = '';
  /* Field: Content: Date */
  $handler->display->display_options['fields']['field_os2web_meetings_date']['id'] = 'field_os2web_meetings_date';
  $handler->display->display_options['fields']['field_os2web_meetings_date']['table'] = 'field_data_field_os2web_meetings_date';
  $handler->display->display_options['fields']['field_os2web_meetings_date']['field'] = 'field_os2web_meetings_date';
  $handler->display->display_options['fields']['field_os2web_meetings_date']['label'] = 'Dato';
  $handler->display->display_options['fields']['field_os2web_meetings_date']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_os2web_meetings_date']['alter']['path'] = 'meeting/[nid]';
  $handler->display->display_options['fields']['field_os2web_meetings_date']['empty'] = '&nbsp;';
  $handler->display->display_options['fields']['field_os2web_meetings_date']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'value',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Location */
  $handler->display->display_options['fields']['php_4']['id'] = 'php_4';
  $handler->display->display_options['fields']['php_4']['table'] = 'views';
  $handler->display->display_options['fields']['php_4']['field'] = 'php';
  $handler->display->display_options['fields']['php_4']['ui_name'] = 'Location';
  $handler->display->display_options['fields']['php_4']['label'] = 'Lokation';
  $handler->display->display_options['fields']['php_4']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['php_4']['alter']['path'] = 'meeting/[nid]';
  $handler->display->display_options['fields']['php_4']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['php_4']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_4']['php_output'] = '<?php
os2dagsorden_meeting_views_last_8_meetings_fields_meeting_location($row->nid);
?>';
  $handler->display->display_options['fields']['php_4']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_4']['php_click_sortable'] = '';
  /* Field: Committe */
  $handler->display->display_options['fields']['php_3']['id'] = 'php_3';
  $handler->display->display_options['fields']['php_3']['table'] = 'views';
  $handler->display->display_options['fields']['php_3']['field'] = 'php';
  $handler->display->display_options['fields']['php_3']['ui_name'] = 'Committe';
  $handler->display->display_options['fields']['php_3']['label'] = 'Udvalg';
  $handler->display->display_options['fields']['php_3']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['php_3']['alter']['path'] = 'meeting/[nid]';
  $handler->display->display_options['fields']['php_3']['alter']['max_length'] = '15';
  $handler->display->display_options['fields']['php_3']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['php_3']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php_3']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_3']['php_output'] = '<?php
    os2dagsorden_meeting_views_last_8_meetings_fields_meeting_committee($row->nid);
?>';
  $handler->display->display_options['fields']['php_3']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_3']['php_click_sortable'] = '';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'os2web_meetings_meeting' => 'os2web_meetings_meeting',
  );
  /* Filter criterion: Content: Date -  start date (field_os2web_meetings_date) */
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['id'] = 'field_os2web_meetings_date_value';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['table'] = 'field_data_field_os2web_meetings_date';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['field'] = 'field_os2web_meetings_date_value';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['operator'] = '<';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['default_date'] = 'tomorrow';
  /* Filter criterion: Content: Tillæg til (field_os2web_meetings_addendum) */
  $handler->display->display_options['filters']['field_os2web_meetings_addendum_nid']['id'] = 'field_os2web_meetings_addendum_nid';
  $handler->display->display_options['filters']['field_os2web_meetings_addendum_nid']['table'] = 'field_data_field_os2web_meetings_addendum';
  $handler->display->display_options['filters']['field_os2web_meetings_addendum_nid']['field'] = 'field_os2web_meetings_addendum_nid';
  $handler->display->display_options['filters']['field_os2web_meetings_addendum_nid']['operator'] = 'empty';
  /* Filter criterion: os2dagsorden limited - my meetings */
  $handler->display->display_options['filters']['php']['id'] = 'php';
  $handler->display->display_options['filters']['php']['table'] = 'views';
  $handler->display->display_options['filters']['php']['field'] = 'php';
  $handler->display->display_options['filters']['php']['ui_name'] = 'os2dagsorden limited - my meetings';
  $handler->display->display_options['filters']['php']['use_php_setup'] = 0;
  $handler->display->display_options['filters']['php']['php_filter'] = 'return os2dagsorden_meeting_views_last_8_meetings_all_meetings_filter_in_my_list($row->tid);';

  /* Display: Block my meetings */
  $handler = $view->new_display('block', 'Block my meetings', 'block_1');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'php';
  $handler->display->display_options['access']['php_access'] = 'return os2dagsorden_meeting_views_last_8_meetings_block_my_meetings_access();';
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: help button */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['ui_name'] = 'help button';
  $handler->display->display_options['header']['area']['empty'] = TRUE;
  $handler->display->display_options['header']['area']['content'] = '<?php
os2dagsorden_meeting_views_last_8_meetings_help_text("my_meetings");
?>';
  $handler->display->display_options['header']['area']['format'] = 'php_code';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Content: Committee (field_os2web_meetings_committee) */
  $handler->display->display_options['relationships']['field_os2web_meetings_committee_tid']['id'] = 'field_os2web_meetings_committee_tid';
  $handler->display->display_options['relationships']['field_os2web_meetings_committee_tid']['table'] = 'field_data_field_os2web_meetings_committee';
  $handler->display->display_options['relationships']['field_os2web_meetings_committee_tid']['field'] = 'field_os2web_meetings_committee_tid';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: committee tid */
  $handler->display->display_options['fields']['tid']['id'] = 'tid';
  $handler->display->display_options['fields']['tid']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['tid']['field'] = 'tid';
  $handler->display->display_options['fields']['tid']['relationship'] = 'field_os2web_meetings_committee_tid';
  $handler->display->display_options['fields']['tid']['ui_name'] = 'committee tid';
  $handler->display->display_options['fields']['tid']['label'] = '';
  $handler->display->display_options['fields']['tid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['tid']['element_label_colon'] = FALSE;
  /* Field: Content: Type */
  $handler->display->display_options['fields']['field_os2web_meetings_type']['id'] = 'field_os2web_meetings_type';
  $handler->display->display_options['fields']['field_os2web_meetings_type']['table'] = 'field_data_field_os2web_meetings_type';
  $handler->display->display_options['fields']['field_os2web_meetings_type']['field'] = 'field_os2web_meetings_type';
  $handler->display->display_options['fields']['field_os2web_meetings_type']['label'] = 'Status';
  $handler->display->display_options['fields']['field_os2web_meetings_type']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_os2web_meetings_type']['alter']['path'] = 'meeting/[nid]';
  $handler->display->display_options['fields']['field_os2web_meetings_type']['empty'] = '&nbsp;';
  $handler->display->display_options['fields']['field_os2web_meetings_type']['hide_alter_empty'] = FALSE;
  /* Field: title - php */
  $handler->display->display_options['fields']['php_2']['id'] = 'php_2';
  $handler->display->display_options['fields']['php_2']['table'] = 'views';
  $handler->display->display_options['fields']['php_2']['field'] = 'php';
  $handler->display->display_options['fields']['php_2']['ui_name'] = 'title - php';
  $handler->display->display_options['fields']['php_2']['label'] = 'Møde';
  $handler->display->display_options['fields']['php_2']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['php_2']['alter']['path'] = 'meeting/[nid]';
  $handler->display->display_options['fields']['php_2']['element_class'] = 'views-field-field-title-short';
  $handler->display->display_options['fields']['php_2']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php_2']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_2']['php_output'] = '<?php
os2dagsorden_meeting_views_last_8_meetings_fields_meeting_title($data);
?>';
  $handler->display->display_options['fields']['php_2']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_2']['php_click_sortable'] = '';
  /* Field: Content: Date */
  $handler->display->display_options['fields']['field_os2web_meetings_date']['id'] = 'field_os2web_meetings_date';
  $handler->display->display_options['fields']['field_os2web_meetings_date']['table'] = 'field_data_field_os2web_meetings_date';
  $handler->display->display_options['fields']['field_os2web_meetings_date']['field'] = 'field_os2web_meetings_date';
  $handler->display->display_options['fields']['field_os2web_meetings_date']['label'] = 'Dato';
  $handler->display->display_options['fields']['field_os2web_meetings_date']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_os2web_meetings_date']['alter']['path'] = 'meeting/[nid]';
  $handler->display->display_options['fields']['field_os2web_meetings_date']['empty'] = '&nbsp;';
  $handler->display->display_options['fields']['field_os2web_meetings_date']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'value',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Lokation */
  $handler->display->display_options['fields']['field_os2web_meetings_location']['id'] = 'field_os2web_meetings_location';
  $handler->display->display_options['fields']['field_os2web_meetings_location']['table'] = 'field_data_field_os2web_meetings_location';
  $handler->display->display_options['fields']['field_os2web_meetings_location']['field'] = 'field_os2web_meetings_location';
  $handler->display->display_options['fields']['field_os2web_meetings_location']['label'] = 'Mødested';
  $handler->display->display_options['fields']['field_os2web_meetings_location']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_os2web_meetings_location']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_os2web_meetings_location']['alter']['path'] = 'meeting/[nid]';
  $handler->display->display_options['fields']['field_os2web_meetings_location']['empty'] = '&nbsp;';
  $handler->display->display_options['fields']['field_os2web_meetings_location']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['field_os2web_meetings_location']['type'] = 'taxonomy_term_reference_plain';
  /* Field: Location */
  $handler->display->display_options['fields']['php_4']['id'] = 'php_4';
  $handler->display->display_options['fields']['php_4']['table'] = 'views';
  $handler->display->display_options['fields']['php_4']['field'] = 'php';
  $handler->display->display_options['fields']['php_4']['ui_name'] = 'Location';
  $handler->display->display_options['fields']['php_4']['label'] = 'Lokation';
  $handler->display->display_options['fields']['php_4']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['php_4']['alter']['path'] = 'meeting/[nid]';
  $handler->display->display_options['fields']['php_4']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['php_4']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_4']['php_output'] = '<?php
os2dagsorden_meeting_views_last_8_meetings_fields_meeting_location($row->nid)
?>';
  $handler->display->display_options['fields']['php_4']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_4']['php_click_sortable'] = '';
  /* Field: Content: Committee */
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['id'] = 'field_os2web_meetings_committee';
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['table'] = 'field_data_field_os2web_meetings_committee';
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['field'] = 'field_os2web_meetings_committee';
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['label'] = '';
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['alter']['path'] = 'meeting/[nid]';
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['alter']['max_length'] = '20';
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['empty'] = '&nbsp;';
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['type'] = 'taxonomy_term_reference_plain';
  /* Field: Committe */
  $handler->display->display_options['fields']['php_3']['id'] = 'php_3';
  $handler->display->display_options['fields']['php_3']['table'] = 'views';
  $handler->display->display_options['fields']['php_3']['field'] = 'php';
  $handler->display->display_options['fields']['php_3']['ui_name'] = 'Committe';
  $handler->display->display_options['fields']['php_3']['label'] = 'Udvalg';
  $handler->display->display_options['fields']['php_3']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['php_3']['alter']['path'] = 'meeting/[nid]';
  $handler->display->display_options['fields']['php_3']['alter']['max_length'] = '15';
  $handler->display->display_options['fields']['php_3']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['php_3']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php_3']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_3']['php_output'] = '<?php
    os2dagsorden_meeting_views_last_8_meetings_fields_meeting_committee($row->nid);
?>';
  $handler->display->display_options['fields']['php_3']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_3']['php_click_sortable'] = '';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'os2web_meetings_meeting' => 'os2web_meetings_meeting',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Date -  start date (field_os2web_meetings_date) */
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['id'] = 'field_os2web_meetings_date_value';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['table'] = 'field_data_field_os2web_meetings_date';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['field'] = 'field_os2web_meetings_date_value';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['operator'] = '<';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['group'] = 1;
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['default_date'] = 'tomorrow';
  /* Filter criterion: Content: Tillæg til (field_os2web_meetings_addendum) */
  $handler->display->display_options['filters']['field_os2web_meetings_addendum_nid']['id'] = 'field_os2web_meetings_addendum_nid';
  $handler->display->display_options['filters']['field_os2web_meetings_addendum_nid']['table'] = 'field_data_field_os2web_meetings_addendum';
  $handler->display->display_options['filters']['field_os2web_meetings_addendum_nid']['field'] = 'field_os2web_meetings_addendum_nid';
  $handler->display->display_options['filters']['field_os2web_meetings_addendum_nid']['operator'] = 'empty';
  $handler->display->display_options['filters']['field_os2web_meetings_addendum_nid']['group'] = 1;
  /* Filter criterion: filter in users list */
  $handler->display->display_options['filters']['php']['id'] = 'php';
  $handler->display->display_options['filters']['php']['table'] = 'views';
  $handler->display->display_options['filters']['php']['field'] = 'php';
  $handler->display->display_options['filters']['php']['ui_name'] = 'filter in users list';
  $handler->display->display_options['filters']['php']['group'] = 1;
  $handler->display->display_options['filters']['php']['use_php_setup'] = 0;
  $handler->display->display_options['filters']['php']['php_filter'] = 'return os2dagsorden_meeting_views_last_8_meetings_filter_in_my_list($row->tid);';
  $translatables['seneste_8_m_der_i_de_st_ende_politiske_udvalg_'] = array(
    t('Master'),
    t('Seneste 8 møder i mine udvalg'),
    t('more'),
    t('Apply'),
    t('Gendan'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('<?php
os2dagsorden_meeting_views_last_8_meetings_help_text();
?>'),
    t('term from field_os2web_meetings_committee'),
    t('field_user_committee'),
    t('.'),
    t(','),
    t('Status'),
    t('&nbsp;'),
    t('Møde'),
    t('Dato'),
    t('Lokation'),
    t('Udvalg'),
    t('Block all meetings'),
    t('Aktuelle møder'),
    t('<?php
os2dagsorden_meeting_views_last_8_meetings_help_text("all_meetings");
?>'),
    t('Block my meetings'),
    t('<?php
os2dagsorden_meeting_views_last_8_meetings_help_text("my_meetings");
?>'),
    t('Mødested'),
  );
  $export['seneste_8_m_der_i_de_st_ende_politiske_udvalg_'] = $view;

  $view = new view();
  $view->name = 'speaking_paper';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Speaking paper (bullet point details)';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Dagsordenspunkt';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'php';
  $handler->display->display_options['access']['php_access'] = 'return os2dagsorden_meeting_views_bullet_point_page_access();';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Gendan';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['inline'] = array(
    'edit_node' => 'edit_node',
    'delete_node' => 'delete_node',
  );
  /* Header: breadcrumb override */
  $handler->display->display_options['header']['php']['id'] = 'php';
  $handler->display->display_options['header']['php']['table'] = 'views';
  $handler->display->display_options['header']['php']['field'] = 'php';
  $handler->display->display_options['header']['php']['ui_name'] = 'breadcrumb override';
  $handler->display->display_options['header']['php']['php_output'] = '<?php 
os2dagsorden_meeting_views_bullet_point_breadcrumb();
?>';
  /* Header: print and send to friend buttons */
  $handler->display->display_options['header']['php_1']['id'] = 'php_1';
  $handler->display->display_options['header']['php_1']['table'] = 'views';
  $handler->display->display_options['header']['php_1']['field'] = 'php';
  $handler->display->display_options['header']['php_1']['ui_name'] = 'print and send to friend buttons';
  $handler->display->display_options['header']['php_1']['php_output'] = '<?php
os2dagsorden_meeting_views_bullet_point_print_send_to_friend();
?>';
  /* Footer: Global: PHP */
  $handler->display->display_options['footer']['php']['id'] = 'php';
  $handler->display->display_options['footer']['php']['table'] = 'views';
  $handler->display->display_options['footer']['php']['field'] = 'php';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['content'] = '<?php
global $base_url;
$q = $_GET[\'q\'];
print \'<a href="\' . $base_url . \'?q=node/add/speaker-paper&edit[field_ref_bullet_point][und][0][target_id]=\' . [title_1] . \' (\' . %1 . \')&destination=\' . $q . \'">Opret et nye talepapir</a>\';
?>
';
  $handler->display->display_options['empty']['area']['format'] = 'php_code';
  $handler->display->display_options['empty']['area']['tokenize'] = TRUE;
  /* Relationship: Entity Reference: Referencing entity */
  $handler->display->display_options['relationships']['reverse_field_os2web_meetings_sp_bullet_node']['id'] = 'reverse_field_os2web_meetings_sp_bullet_node';
  $handler->display->display_options['relationships']['reverse_field_os2web_meetings_sp_bullet_node']['table'] = 'node';
  $handler->display->display_options['relationships']['reverse_field_os2web_meetings_sp_bullet_node']['field'] = 'reverse_field_os2web_meetings_sp_bullet_node';
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['relationship'] = 'reverse_field_os2web_meetings_sp_bullet_node';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['field_ref_attachment']['id'] = 'field_ref_attachment';
  $handler->display->display_options['fields']['field_ref_attachment']['table'] = 'field_data_field_ref_attachment';
  $handler->display->display_options['fields']['field_ref_attachment']['field'] = 'field_ref_attachment';
  $handler->display->display_options['fields']['field_ref_attachment']['label'] = '';
  $handler->display->display_options['fields']['field_ref_attachment']['element_label_colon'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'node';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  $handler->display->display_options['fields']['title_1']['relationship'] = 'field_ref_speaker_paper_target_id';
  $handler->display->display_options['fields']['title_1']['label'] = '';
  $handler->display->display_options['fields']['title_1']['element_label_colon'] = FALSE;
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['relationship'] = 'field_ref_speaker_paper_target_id';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Global: Null */
  $handler->display->display_options['arguments']['null']['id'] = 'null';
  $handler->display->display_options['arguments']['null']['table'] = 'views';
  $handler->display->display_options['arguments']['null']['field'] = 'null';
  $handler->display->display_options['arguments']['null']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['null']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['null']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['null']['summary_options']['items_per_page'] = '25';
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid_1']['id'] = 'nid_1';
  $handler->display->display_options['arguments']['nid_1']['table'] = 'node';
  $handler->display->display_options['arguments']['nid_1']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid_1']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid_1']['default_argument_type'] = 'raw';
  $handler->display->display_options['arguments']['nid_1']['default_argument_options']['index'] = '3';
  $handler->display->display_options['arguments']['nid_1']['default_argument_skip_url'] = TRUE;
  $handler->display->display_options['arguments']['nid_1']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid_1']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid_1']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'os2web_meetings_bullet' => 'os2web_meetings_bullet',
  );
  /* Filter criterion: User: Current */
  $handler->display->display_options['filters']['uid_current']['id'] = 'uid_current';
  $handler->display->display_options['filters']['uid_current']['table'] = 'users';
  $handler->display->display_options['filters']['uid_current']['field'] = 'uid_current';
  $handler->display->display_options['filters']['uid_current']['relationship'] = 'uid_1';
  $handler->display->display_options['filters']['uid_current']['value'] = '1';
  /* Filter criterion: User: Current */
  $handler->display->display_options['filters']['uid_current_1']['id'] = 'uid_current_1';
  $handler->display->display_options['filters']['uid_current_1']['table'] = 'users';
  $handler->display->display_options['filters']['uid_current_1']['field'] = 'uid_current';
  $handler->display->display_options['filters']['uid_current_1']['relationship'] = 'uid_1';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'nid_1' => 'nid_1',
    'php_1' => 'php_1',
    'php' => 'php_1',
    'body' => 'php_1',
    'php_2' => 'php_1',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'nid_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'php_1' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'php' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'body' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'php_2' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['footer'] = FALSE;
  $handler->display->display_options['defaults']['empty'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: bullet point id */
  $handler->display->display_options['fields']['nid_1']['id'] = 'nid_1';
  $handler->display->display_options['fields']['nid_1']['table'] = 'node';
  $handler->display->display_options['fields']['nid_1']['field'] = 'nid';
  $handler->display->display_options['fields']['nid_1']['ui_name'] = 'bullet point id';
  $handler->display->display_options['fields']['nid_1']['label'] = '';
  $handler->display->display_options['fields']['nid_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid_1']['element_label_colon'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_type'] = 'h3';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_wrapper_type'] = 'div';
  $handler->display->display_options['fields']['title']['element_wrapper_class'] = 'view-header';
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Title - PHP */
  $handler->display->display_options['fields']['php_1']['id'] = 'php_1';
  $handler->display->display_options['fields']['php_1']['table'] = 'views';
  $handler->display->display_options['fields']['php_1']['field'] = 'php';
  $handler->display->display_options['fields']['php_1']['ui_name'] = 'Title - PHP';
  $handler->display->display_options['fields']['php_1']['label'] = '';
  $handler->display->display_options['fields']['php_1']['element_type'] = 'h3';
  $handler->display->display_options['fields']['php_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php_1']['element_wrapper_type'] = 'div';
  $handler->display->display_options['fields']['php_1']['element_wrapper_class'] = 'view-header';
  $handler->display->display_options['fields']['php_1']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_1']['php_output'] = '<?php
os2dagsorden_meeting_views_bullet_point_fields_title_navigation_buttons($row->nid_1);
?>';
  $handler->display->display_options['fields']['php_1']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_1']['php_click_sortable'] = '';
  /* Field: indicator - bullet point has notes */
  $handler->display->display_options['fields']['php']['id'] = 'php';
  $handler->display->display_options['fields']['php']['table'] = 'views';
  $handler->display->display_options['fields']['php']['field'] = 'php';
  $handler->display->display_options['fields']['php']['ui_name'] = 'indicator - bullet point has notes';
  $handler->display->display_options['fields']['php']['label'] = '';
  $handler->display->display_options['fields']['php']['exclude'] = TRUE;
  $handler->display->display_options['fields']['php']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php']['php_output'] = '<?php
os2dagsorden_meeting_views_bullet_point_fields_indicator_bullet_point_has_notes($row->nid_1);
?>';
  $handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php']['php_click_sortable'] = '';
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  /* Field: attachments and attachments&#039; content */
  $handler->display->display_options['fields']['php_2']['id'] = 'php_2';
  $handler->display->display_options['fields']['php_2']['table'] = 'views';
  $handler->display->display_options['fields']['php_2']['field'] = 'php';
  $handler->display->display_options['fields']['php_2']['ui_name'] = 'attachments and attachments\' content';
  $handler->display->display_options['fields']['php_2']['label'] = '';
  $handler->display->display_options['fields']['php_2']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php_2']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_2']['php_output'] = '<?php
$q = explode(\'/\',$_GET[\'q\']);
$meeting_id = $q[\'1\'];
$bp_id = $row->nid_1;

os2dagsorden_meeting_views_bullet_point_fields_attachments_and_content($meeting_id, $bp_id);
?>';
  $handler->display->display_options['fields']['php_2']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_2']['php_click_sortable'] = '';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'os2web_meetings_bullet' => 'os2web_meetings_bullet',
  );
  $handler->display->display_options['path'] = 'meeting/%/bullet-point/%';

  /* Display: Speaker paper */
  $handler = $view->new_display('attachment', 'Speaker paper', 'attachment_1');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['defaults']['header'] = FALSE;
  $handler->display->display_options['defaults']['footer'] = FALSE;
  /* Footer: Create new speaker paper */
  $handler->display->display_options['footer']['php']['id'] = 'php';
  $handler->display->display_options['footer']['php']['table'] = 'views';
  $handler->display->display_options['footer']['php']['field'] = 'php';
  $handler->display->display_options['footer']['php']['ui_name'] = 'Create new speaker paper';
  $handler->display->display_options['footer']['php']['empty'] = TRUE;
  $handler->display->display_options['footer']['php']['php_output'] = '<?php
os2dagsorden_meeting_views_bullet_point_fields_create_new_speaker_paper();
?>
';
  $handler->display->display_options['defaults']['empty'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_user'] = FALSE;
  /* Field: User: Full name */
  $handler->display->display_options['fields']['field_user_full_name']['id'] = 'field_user_full_name';
  $handler->display->display_options['fields']['field_user_full_name']['table'] = 'field_data_field_user_full_name';
  $handler->display->display_options['fields']['field_user_full_name']['field'] = 'field_user_full_name';
  $handler->display->display_options['fields']['field_user_full_name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['field_user_full_name']['label'] = '';
  $handler->display->display_options['fields']['field_user_full_name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_user_full_name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_user_full_name']['empty'] = '[name]';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'node';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  $handler->display->display_options['fields']['title_1']['relationship'] = 'reverse_field_os2web_meetings_sp_bullet_node';
  $handler->display->display_options['fields']['title_1']['label'] = '';
  $handler->display->display_options['fields']['title_1']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title_1']['alter']['text'] = 'talepapir - [title_1]. forfatter: [field_user_full_name]';
  $handler->display->display_options['fields']['title_1']['alter']['path'] = '#';
  $handler->display->display_options['fields']['title_1']['alter']['prefix'] = 'Talepapir -';
  $handler->display->display_options['fields']['title_1']['element_type'] = 'h3';
  $handler->display->display_options['fields']['title_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title_1']['element_wrapper_type'] = 'div';
  $handler->display->display_options['fields']['title_1']['element_wrapper_class'] = 'view-header';
  $handler->display->display_options['fields']['title_1']['link_to_node'] = FALSE;
  /* Field: Print Link */
  $handler->display->display_options['fields']['php']['id'] = 'php';
  $handler->display->display_options['fields']['php']['table'] = 'views';
  $handler->display->display_options['fields']['php']['field'] = 'php';
  $handler->display->display_options['fields']['php']['ui_name'] = 'Print Link';
  $handler->display->display_options['fields']['php']['label'] = '';
  $handler->display->display_options['fields']['php']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php']['php_output'] = '<?php
$bp_id = $data->nid;
$sp_id = $row->body;

os2dagsorden_meeting_views_bullet_point_fields_print_link($bp_id, $sp_id);
?>';
  $handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php']['php_click_sortable'] = '';
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['relationship'] = 'reverse_field_os2web_meetings_sp_bullet_node';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['alter']['nl2br'] = TRUE;
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['element_wrapper_class'] = 'main-text';
  $handler->display->display_options['fields']['body']['settings'] = array(
    'trim_length' => '600',
  );
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['relationship'] = 'reverse_field_os2web_meetings_sp_bullet_node';
  $handler->display->display_options['fields']['edit_node']['label'] = '';
  $handler->display->display_options['fields']['edit_node']['element_label_colon'] = FALSE;
  /* Field: Content: Delete link */
  $handler->display->display_options['fields']['delete_node']['id'] = 'delete_node';
  $handler->display->display_options['fields']['delete_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['delete_node']['field'] = 'delete_node';
  $handler->display->display_options['fields']['delete_node']['relationship'] = 'reverse_field_os2web_meetings_sp_bullet_node';
  $handler->display->display_options['fields']['delete_node']['label'] = '';
  $handler->display->display_options['fields']['delete_node']['element_label_colon'] = FALSE;
  /* Field: PHP - shared with */
  $handler->display->display_options['fields']['php_1']['id'] = 'php_1';
  $handler->display->display_options['fields']['php_1']['table'] = 'views';
  $handler->display->display_options['fields']['php_1']['field'] = 'php';
  $handler->display->display_options['fields']['php_1']['ui_name'] = 'PHP - shared with';
  $handler->display->display_options['fields']['php_1']['label'] = '';
  $handler->display->display_options['fields']['php_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php_1']['element_wrapper_class'] = 'shared-with';
  $handler->display->display_options['fields']['php_1']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_1']['php_output'] = '<?php
os2dagsorden_meeting_views_bullet_point_fields_shared_with($row->body);
?>';
  $handler->display->display_options['fields']['php_1']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_1']['php_click_sortable'] = '';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['filter_groups']['groups'] = array(
    1 => 'AND',
    2 => 'OR',
  );
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'os2web_meetings_bullet' => 'os2web_meetings_bullet',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: filtering depending on the settings state */
  $handler->display->display_options['filters']['php']['id'] = 'php';
  $handler->display->display_options['filters']['php']['table'] = 'views';
  $handler->display->display_options['filters']['php']['field'] = 'php';
  $handler->display->display_options['filters']['php']['ui_name'] = 'filtering depending on the settings state';
  $handler->display->display_options['filters']['php']['use_php_setup'] = 0;
  $handler->display->display_options['filters']['php']['php_filter'] = 'return os2dagsorden_meeting_views_bullet_point_fields_filter($row->body);';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );
  $handler->display->display_options['attachment_position'] = 'after';
  $translatables['speaking_paper'] = array(
    t('Master'),
    t('Dagsordenspunkt'),
    t('more'),
    t('Apply'),
    t('Gendan'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('<?php
global $base_url;
$q = $_GET[\'q\'];
print \'<a href="\' . $base_url . \'?q=node/add/speaker-paper&edit[field_ref_bullet_point][und][0][target_id]=\' . [title_1] . \' (\' . %1 . \')&destination=\' . $q . \'">Opret et nye talepapir</a>\';
?>
'),
    t('Content referencing Content from field_os2web_meetings_sp_bullet'),
    t('author'),
    t('All'),
    t('Page'),
    t('Speaker paper'),
    t('[name]'),
    t('talepapir - [title_1]. forfatter: [field_user_full_name]'),
    t('Talepapir -'),
  );
  $export['speaking_paper'] = $view;

  return $export;
}
