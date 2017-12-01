<?php
/**
 * @file
 * os2dagsorden_admin_views.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function os2dagsorden_admin_views_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'os2dagsorden_meetings_overview';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'OS2Dagsorden Meetings overview';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    4 => '4',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Acceptér';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Gendan';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '30';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« første';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ forrige';
  $handler->display->display_options['pager']['options']['tags']['next'] = 'næste >';
  $handler->display->display_options['pager']['options']['tags']['last'] = 'sidste »';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'nid' => 'nid',
    'views_bulk_operations' => 'views_bulk_operations',
    'title' => 'title',
    'changed' => 'changed',
    'field_os2web_meetings_committee' => 'field_os2web_meetings_committee',
    'field_os2web_meetings_type' => 'field_os2web_meetings_type',
    'field_os2web_meetings_date' => 'field_os2web_meetings_date',
  );
  $handler->display->display_options['style_options']['default'] = 'changed';
  $handler->display->display_options['style_options']['info'] = array(
    'nid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'views_bulk_operations' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'changed' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_os2web_meetings_committee' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_os2web_meetings_type' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_os2web_meetings_date' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Felt: Indhold: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Felt: Bulk operations: Indhold */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['row_clickable'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::node_unpublish_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'skip_permission_check' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'skip_permission_check' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'log' => 0,
      ),
    ),
    'action::node_publish_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'skip_permission_check' => 0,
      'override_label' => 0,
      'label' => '',
    ),
  );
  /* Felt: Indhold: Titel */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['path'] = 'meeting/[nid]';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Felt: Indhold: Updated date */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'node';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['label'] = 'Opdateret';
  $handler->display->display_options['fields']['changed']['date_format'] = 'long';
  $handler->display->display_options['fields']['changed']['second_date_format'] = 'long';
  /* Felt: Indhold: Committee */
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['id'] = 'field_os2web_meetings_committee';
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['table'] = 'field_data_field_os2web_meetings_committee';
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['field'] = 'field_os2web_meetings_committee';
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['label'] = 'Udvalg';
  $handler->display->display_options['fields']['field_os2web_meetings_committee']['type'] = 'taxonomy_term_reference_plain';
  /* Felt: Indhold: Type */
  $handler->display->display_options['fields']['field_os2web_meetings_type']['id'] = 'field_os2web_meetings_type';
  $handler->display->display_options['fields']['field_os2web_meetings_type']['table'] = 'field_data_field_os2web_meetings_type';
  $handler->display->display_options['fields']['field_os2web_meetings_type']['field'] = 'field_os2web_meetings_type';
  $handler->display->display_options['fields']['field_os2web_meetings_type']['label'] = 'Status';
  /* Felt: Indhold: Date */
  $handler->display->display_options['fields']['field_os2web_meetings_date']['id'] = 'field_os2web_meetings_date';
  $handler->display->display_options['fields']['field_os2web_meetings_date']['table'] = 'field_data_field_os2web_meetings_date';
  $handler->display->display_options['fields']['field_os2web_meetings_date']['field'] = 'field_os2web_meetings_date';
  $handler->display->display_options['fields']['field_os2web_meetings_date']['label'] = 'Møde startdato';
  $handler->display->display_options['fields']['field_os2web_meetings_date']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_remaining_days' => 0,
  );
  /* Sort criterion: Indhold: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Indhold: Udgivet */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Indhold: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'os2web_meetings_meeting' => 'os2web_meetings_meeting',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Indhold: Titel */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'word';
  $handler->display->display_options['filters']['title']['group'] = 1;
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Titel';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    5 => 0,
    3 => 0,
    4 => 0,
    6 => 0,
  );
  /* Filter criterion: Indhold: Committee (field_os2web_meetings_committee) */
  $handler->display->display_options['filters']['field_os2web_meetings_committee_tid']['id'] = 'field_os2web_meetings_committee_tid';
  $handler->display->display_options['filters']['field_os2web_meetings_committee_tid']['table'] = 'field_data_field_os2web_meetings_committee';
  $handler->display->display_options['filters']['field_os2web_meetings_committee_tid']['field'] = 'field_os2web_meetings_committee_tid';
  $handler->display->display_options['filters']['field_os2web_meetings_committee_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_os2web_meetings_committee_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_os2web_meetings_committee_tid']['expose']['operator_id'] = 'field_os2web_meetings_committee_tid_op';
  $handler->display->display_options['filters']['field_os2web_meetings_committee_tid']['expose']['label'] = 'Udvalg';
  $handler->display->display_options['filters']['field_os2web_meetings_committee_tid']['expose']['operator'] = 'field_os2web_meetings_committee_tid_op';
  $handler->display->display_options['filters']['field_os2web_meetings_committee_tid']['expose']['identifier'] = 'field_os2web_meetings_committee_tid';
  $handler->display->display_options['filters']['field_os2web_meetings_committee_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_os2web_meetings_committee_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    5 => 0,
    3 => 0,
    4 => 0,
    6 => 0,
  );
  $handler->display->display_options['filters']['field_os2web_meetings_committee_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_os2web_meetings_committee_tid']['vocabulary'] = 'os2web_meetings_tax_committee';
  /* Filter criterion: Indhold: Type (field_os2web_meetings_type) */
  $handler->display->display_options['filters']['field_os2web_meetings_type_value']['id'] = 'field_os2web_meetings_type_value';
  $handler->display->display_options['filters']['field_os2web_meetings_type_value']['table'] = 'field_data_field_os2web_meetings_type';
  $handler->display->display_options['filters']['field_os2web_meetings_type_value']['field'] = 'field_os2web_meetings_type_value';
  $handler->display->display_options['filters']['field_os2web_meetings_type_value']['group'] = 1;
  $handler->display->display_options['filters']['field_os2web_meetings_type_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_os2web_meetings_type_value']['expose']['operator_id'] = 'field_os2web_meetings_type_value_op';
  $handler->display->display_options['filters']['field_os2web_meetings_type_value']['expose']['label'] = 'Status';
  $handler->display->display_options['filters']['field_os2web_meetings_type_value']['expose']['operator'] = 'field_os2web_meetings_type_value_op';
  $handler->display->display_options['filters']['field_os2web_meetings_type_value']['expose']['identifier'] = 'field_os2web_meetings_type_value';
  $handler->display->display_options['filters']['field_os2web_meetings_type_value']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_os2web_meetings_type_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    5 => 0,
    3 => 0,
    4 => 0,
    6 => 0,
  );
  /* Filter criterion: Indhold: Date -  start date (field_os2web_meetings_date) */
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['id'] = 'field_os2web_meetings_date_value';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['table'] = 'field_data_field_os2web_meetings_date';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['field'] = 'field_os2web_meetings_date_value';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['operator'] = '>=';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['group'] = 1;
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['expose']['operator_id'] = 'field_os2web_meetings_date_value_op';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['expose']['label'] = 'Startdato';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['expose']['operator'] = 'field_os2web_meetings_date_value_op';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['expose']['identifier'] = 'field_os2web_meetings_date_value';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    5 => 0,
    3 => 0,
    4 => 0,
    6 => 0,
  );
  $handler->display->display_options['filters']['field_os2web_meetings_date_value']['form_type'] = 'date_popup';
  /* Filter criterion: Indhold: Date - end date (field_os2web_meetings_date:value2) */
  $handler->display->display_options['filters']['field_os2web_meetings_date_value2']['id'] = 'field_os2web_meetings_date_value2';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value2']['table'] = 'field_data_field_os2web_meetings_date';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value2']['field'] = 'field_os2web_meetings_date_value2';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value2']['operator'] = '<=';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value2']['group'] = 1;
  $handler->display->display_options['filters']['field_os2web_meetings_date_value2']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_os2web_meetings_date_value2']['expose']['operator_id'] = 'field_os2web_meetings_date_value2_op';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value2']['expose']['label'] = 'Slutdato';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value2']['expose']['operator'] = 'field_os2web_meetings_date_value2_op';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value2']['expose']['identifier'] = 'field_os2web_meetings_date_value2';
  $handler->display->display_options['filters']['field_os2web_meetings_date_value2']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    5 => 0,
    3 => 0,
    4 => 0,
    6 => 0,
  );
  $handler->display->display_options['filters']['field_os2web_meetings_date_value2']['form_type'] = 'date_popup';

  /* Display: Side */
  $handler = $view->new_display('page', 'Side', 'page');
  $handler->display->display_options['path'] = 'admin/content/meetings';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'OS2Dagsorden meetings';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $translatables['os2dagsorden_meetings_overview'] = array(
    t('Master'),
    t('more'),
    t('Acceptér'),
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
    t('Indhold'),
    t('- Choose an operation -'),
    t('Titel'),
    t('Opdateret'),
    t('Udvalg'),
    t('Status'),
    t('Møde startdato'),
    t('Startdato'),
    t('Slutdato'),
    t('Side'),
  );
  $export['os2dagsorden_meetings_overview'] = $view;

  $view = new view();
  $view->name = 'os2dagsorden_users_view';
  $view->description = 'List, add, and edit users.';
  $view->tag = 'admin';
  $view->base_table = 'users';
  $view->human_name = 'OS2Dagsorden Users View';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['title'] = 'Brugere';
  $handler->display->display_options['css_class'] = 'admin-views-view';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'menu';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Acceptér';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Gendan';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = 50;
  $handler->display->display_options['pager']['options']['tags']['first'] = '« første';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ forrige';
  $handler->display->display_options['pager']['options']['tags']['next'] = 'næste >';
  $handler->display->display_options['pager']['options']['tags']['last'] = 'sidste »';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'uid' => 'uid',
    'views_bulk_operations' => 'views_bulk_operations',
    'name' => 'name',
    'mail' => 'name',
    'status' => 'status',
    'rid' => 'rid',
    'created' => 'created',
    'access' => 'access',
    'nothing' => 'nothing',
    'edit_node' => 'nothing',
    'cancel_node' => 'nothing',
  );
  $handler->display->display_options['style_options']['default'] = 'access';
  $handler->display->display_options['style_options']['info'] = array(
    'uid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'views_bulk_operations' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '<br />',
      'empty_column' => 0,
    ),
    'mail' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'rid' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'created' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'access' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nothing' => array(
      'align' => '',
      'separator' => '&nbsp;&nbsp;',
      'empty_column' => 0,
    ),
    'edit_node' => array(
      'align' => '',
      'separator' => '&emsp;',
      'empty_column' => 0,
    ),
    'cancel_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  $handler->display->display_options['style_options']['empty_table'] = TRUE;
  /* No results behavior: Global: Unfiltered text */
  $handler->display->display_options['empty']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['empty']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['empty'] = TRUE;
  $handler->display->display_options['empty']['area_text_custom']['content'] = 'No users available.';
  /* Felt: Bruger: Uid */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'users';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['label'] = '';
  $handler->display->display_options['fields']['uid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['uid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['uid']['link_to_user'] = FALSE;
  /* Felt: Bulk operations: Bruger */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'views_entity_user';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['label'] = '';
  $handler->display->display_options['fields']['views_bulk_operations']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['views_bulk_operations']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::views_bulk_operations_user_cancel_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_modify_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 1,
      'override_label' => 1,
      'label' => 'Change value',
      'settings' => array(
        'show_all_tokens' => 1,
        'display_values' => array(
          '_all_' => '_all_',
        ),
      ),
    ),
    'action::views_bulk_operations_user_roles_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 1,
      'label' => 'Change user roles',
    ),
    'action::views_bulk_operations_argument_selector_action' => array(
      'selected' => 1,
      'skip_confirmation' => 1,
      'override_label' => 1,
      'label' => 'Batch edit committees',
      'settings' => array(
        'url' => 'users-batch-simple-edit',
      ),
    ),
    'action::system_send_email_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 1,
      'label' => 'Send e-mail',
    ),
  );
  /* Felt: Bruger: Navn */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  /* Felt: Bruger: E-mail */
  $handler->display->display_options['fields']['mail']['id'] = 'mail';
  $handler->display->display_options['fields']['mail']['table'] = 'users';
  $handler->display->display_options['fields']['mail']['field'] = 'mail';
  $handler->display->display_options['fields']['mail']['label'] = '';
  $handler->display->display_options['fields']['mail']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['mail']['link_to_user'] = '0';
  /* Felt: Bruger: Full name */
  $handler->display->display_options['fields']['field_user_full_name']['id'] = 'field_user_full_name';
  $handler->display->display_options['fields']['field_user_full_name']['table'] = 'field_data_field_user_full_name';
  $handler->display->display_options['fields']['field_user_full_name']['field'] = 'field_user_full_name';
  $handler->display->display_options['fields']['field_user_full_name']['label'] = 'Fuldt navn';
  /* Felt: Bruger: Aktiv */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'users';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['not'] = 0;
  /* Felt: Bruger: Organization */
  $handler->display->display_options['fields']['field_user_organization']['id'] = 'field_user_organization';
  $handler->display->display_options['fields']['field_user_organization']['table'] = 'field_data_field_user_organization';
  $handler->display->display_options['fields']['field_user_organization']['field'] = 'field_user_organization';
  $handler->display->display_options['fields']['field_user_organization']['label'] = 'Organisation';
  /* Felt: Bruger: Roller */
  $handler->display->display_options['fields']['rid']['id'] = 'rid';
  $handler->display->display_options['fields']['rid']['table'] = 'users_roles';
  $handler->display->display_options['fields']['rid']['field'] = 'rid';
  $handler->display->display_options['fields']['rid']['type'] = 'ul';
  /* Felt: Bruger: Created date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'users';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Medlem i';
  $handler->display->display_options['fields']['created']['date_format'] = 'raw time ago';
  /* Felt: Bruger: Seneste tilgang */
  $handler->display->display_options['fields']['access']['id'] = 'access';
  $handler->display->display_options['fields']['access']['table'] = 'users';
  $handler->display->display_options['fields']['access']['field'] = 'access';
  $handler->display->display_options['fields']['access']['date_format'] = 'time ago';
  /* Felt: simple edit link */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'simple edit link';
  $handler->display->display_options['fields']['nothing']['label'] = 'Handlinger';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = 'redigér';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = 'user/[uid]/simple_edit';
  /* Felt: Bruger: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'users';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = 'Handlinger';
  $handler->display->display_options['fields']['edit_node']['exclude'] = TRUE;
  $handler->display->display_options['fields']['edit_node']['alter']['text'] = 'test';
  $handler->display->display_options['fields']['edit_node']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['edit_node']['alter']['path'] = 'user/%/simple_edit';
  /* Felt: Bruger: Cancel link */
  $handler->display->display_options['fields']['cancel_node']['id'] = 'cancel_node';
  $handler->display->display_options['fields']['cancel_node']['table'] = 'users';
  $handler->display->display_options['fields']['cancel_node']['field'] = 'cancel_node';
  $handler->display->display_options['fields']['cancel_node']['label'] = '';
  $handler->display->display_options['fields']['cancel_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['cancel_node']['hide_alter_empty'] = FALSE;
  /* Sort criterion: Bruger: Created date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'users';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Bruger: Name (raw) */
  $handler->display->display_options['filters']['name']['id'] = 'name';
  $handler->display->display_options['filters']['name']['table'] = 'users';
  $handler->display->display_options['filters']['name']['field'] = 'name';
  $handler->display->display_options['filters']['name']['operator'] = 'contains';
  $handler->display->display_options['filters']['name']['group'] = 1;
  $handler->display->display_options['filters']['name']['exposed'] = TRUE;
  $handler->display->display_options['filters']['name']['expose']['operator_id'] = 'name_op';
  $handler->display->display_options['filters']['name']['expose']['label'] = 'Brugernavn';
  $handler->display->display_options['filters']['name']['expose']['operator'] = 'name_op';
  $handler->display->display_options['filters']['name']['expose']['identifier'] = 'name';
  $handler->display->display_options['filters']['name']['expose']['remember'] = TRUE;
  /* Filter criterion: Bruger: Organization (field_user_organization) */
  $handler->display->display_options['filters']['field_user_organization_value']['id'] = 'field_user_organization_value';
  $handler->display->display_options['filters']['field_user_organization_value']['table'] = 'field_data_field_user_organization';
  $handler->display->display_options['filters']['field_user_organization_value']['field'] = 'field_user_organization_value';
  $handler->display->display_options['filters']['field_user_organization_value']['operator'] = 'contains';
  $handler->display->display_options['filters']['field_user_organization_value']['group'] = 1;
  $handler->display->display_options['filters']['field_user_organization_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_user_organization_value']['expose']['operator_id'] = 'field_user_organization_value_op';
  $handler->display->display_options['filters']['field_user_organization_value']['expose']['label'] = 'Organisation';
  $handler->display->display_options['filters']['field_user_organization_value']['expose']['operator'] = 'field_user_organization_value_op';
  $handler->display->display_options['filters']['field_user_organization_value']['expose']['identifier'] = 'field_user_organization_value';
  $handler->display->display_options['filters']['field_user_organization_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    5 => 0,
    3 => 0,
    4 => 0,
    6 => 0,
  );
  /* Filter criterion: Bruger: Is part of Committee (field_user_committee) */
  $handler->display->display_options['filters']['field_user_committee_tid']['id'] = 'field_user_committee_tid';
  $handler->display->display_options['filters']['field_user_committee_tid']['table'] = 'field_data_field_user_committee';
  $handler->display->display_options['filters']['field_user_committee_tid']['field'] = 'field_user_committee_tid';
  $handler->display->display_options['filters']['field_user_committee_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_user_committee_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_user_committee_tid']['expose']['operator_id'] = 'field_user_committee_tid_op';
  $handler->display->display_options['filters']['field_user_committee_tid']['expose']['label'] = 'Medlem af:';
  $handler->display->display_options['filters']['field_user_committee_tid']['expose']['operator'] = 'field_user_committee_tid_op';
  $handler->display->display_options['filters']['field_user_committee_tid']['expose']['identifier'] = 'field_user_committee_tid';
  $handler->display->display_options['filters']['field_user_committee_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    5 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['filters']['field_user_committee_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_user_committee_tid']['vocabulary'] = 'os2web_meetings_tax_committee';
  /* Filter criterion: Bruger: Follows committees (field_follows_committee) */
  $handler->display->display_options['filters']['field_follows_committee_tid']['id'] = 'field_follows_committee_tid';
  $handler->display->display_options['filters']['field_follows_committee_tid']['table'] = 'field_data_field_follows_committee';
  $handler->display->display_options['filters']['field_follows_committee_tid']['field'] = 'field_follows_committee_tid';
  $handler->display->display_options['filters']['field_follows_committee_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_follows_committee_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_follows_committee_tid']['expose']['operator_id'] = 'field_follows_committee_tid_op';
  $handler->display->display_options['filters']['field_follows_committee_tid']['expose']['label'] = 'Følger:';
  $handler->display->display_options['filters']['field_follows_committee_tid']['expose']['operator'] = 'field_follows_committee_tid_op';
  $handler->display->display_options['filters']['field_follows_committee_tid']['expose']['identifier'] = 'field_follows_committee_tid';
  $handler->display->display_options['filters']['field_follows_committee_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    5 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['filters']['field_follows_committee_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_follows_committee_tid']['vocabulary'] = 'os2web_meetings_tax_committee';
  /* Filter criterion: Bruger: Follows committees+ (field_follows_committee_plus) */
  $handler->display->display_options['filters']['field_follows_committee_plus_tid']['id'] = 'field_follows_committee_plus_tid';
  $handler->display->display_options['filters']['field_follows_committee_plus_tid']['table'] = 'field_data_field_follows_committee_plus';
  $handler->display->display_options['filters']['field_follows_committee_plus_tid']['field'] = 'field_follows_committee_plus_tid';
  $handler->display->display_options['filters']['field_follows_committee_plus_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_follows_committee_plus_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_follows_committee_plus_tid']['expose']['operator_id'] = 'field_follows_committee_plus_tid_op';
  $handler->display->display_options['filters']['field_follows_committee_plus_tid']['expose']['label'] = 'Følger+:';
  $handler->display->display_options['filters']['field_follows_committee_plus_tid']['expose']['operator'] = 'field_follows_committee_plus_tid_op';
  $handler->display->display_options['filters']['field_follows_committee_plus_tid']['expose']['identifier'] = 'field_follows_committee_plus_tid';
  $handler->display->display_options['filters']['field_follows_committee_plus_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    5 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['filters']['field_follows_committee_plus_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_follows_committee_plus_tid']['vocabulary'] = 'os2web_meetings_tax_committee';
  /* Filter criterion: Bruger: Follows committees++ (field_follows_committee_pp) */
  $handler->display->display_options['filters']['field_follows_committee_pp_tid']['id'] = 'field_follows_committee_pp_tid';
  $handler->display->display_options['filters']['field_follows_committee_pp_tid']['table'] = 'field_data_field_follows_committee_pp';
  $handler->display->display_options['filters']['field_follows_committee_pp_tid']['field'] = 'field_follows_committee_pp_tid';
  $handler->display->display_options['filters']['field_follows_committee_pp_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_follows_committee_pp_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_follows_committee_pp_tid']['expose']['operator_id'] = 'field_follows_committee_pp_tid_op';
  $handler->display->display_options['filters']['field_follows_committee_pp_tid']['expose']['label'] = 'Følger++:';
  $handler->display->display_options['filters']['field_follows_committee_pp_tid']['expose']['operator'] = 'field_follows_committee_pp_tid_op';
  $handler->display->display_options['filters']['field_follows_committee_pp_tid']['expose']['identifier'] = 'field_follows_committee_pp_tid';
  $handler->display->display_options['filters']['field_follows_committee_pp_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    5 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['filters']['field_follows_committee_pp_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_follows_committee_pp_tid']['vocabulary'] = 'os2web_meetings_tax_committee';

  /* Display: System */
  $handler = $view->new_display('system', 'System', 'system_1');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['hide_admin_links'] = TRUE;
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['path'] = 'admin/people';
  $translatables['os2dagsorden_users_view'] = array(
    t('Defaults'),
    t('Brugere'),
    t('more'),
    t('Acceptér'),
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
    t('No users available.'),
    t('- Choose an operation -'),
    t('Delete'),
    t('Change value'),
    t('Change user roles'),
    t('Batch edit committees'),
    t('Send e-mail'),
    t('Navn'),
    t('Fuldt navn'),
    t('Aktiv'),
    t('Organisation'),
    t('Roller'),
    t('Medlem i'),
    t('Seneste tilgang'),
    t('Handlinger'),
    t('redigér'),
    t('test'),
    t('Brugernavn'),
    t('Medlem af:'),
    t('Følger:'),
    t('Følger+:'),
    t('Følger++:'),
    t('System'),
  );
  $export['os2dagsorden_users_view'] = $view;

  return $export;
}
