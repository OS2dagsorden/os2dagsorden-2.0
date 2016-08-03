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
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'users';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['label'] = '';
  $handler->display->display_options['fields']['views_bulk_operations']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['views_bulk_operations']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::user_block_user_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 1,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_user_cancel_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 1,
      'label' => 'Delete',
    ),
    'action::views_bulk_operations_delete_revision' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_script_action' => array(
      'selected' => 0,
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
  /* Felt: Bruger: Aktiv */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'users';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['not'] = 0;
  /* Felt: Bruger: Organization */
  $handler->display->display_options['fields']['field_user_organization']['id'] = 'field_user_organization';
  $handler->display->display_options['fields']['field_user_organization']['table'] = 'field_data_field_user_organization';
  $handler->display->display_options['fields']['field_user_organization']['field'] = 'field_user_organization';
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
  $handler->display->display_options['filters']['field_user_organization_value']['expose']['label'] = 'Organization';
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
    t('No users available.'),
    t('- Choose an operation -'),
    t('Delete'),
    t('Change value'),
    t('Change user roles'),
    t('Batch edit committees'),
    t('Send e-mail'),
    t('Navn'),
    t('Full name'),
    t('Aktiv'),
    t('Organization'),
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
