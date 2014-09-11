<?php

/**
 * @file
 * This file implements administration menus and functionality for
 * the provider module.
 */

/**
 * Page callback. Displays status page.
 */
function _os2web_esdh_provider_status() {
  $apis = array_keys(os2web_esdh_provider_ctools_plugin_type());
  $head = array('API name', 'Description', 'module', 'status');
  $rows = array();
  foreach ($apis as $api) {
    $info = ctools_plugin_get_info('os2web_esdh_provider', $api);
    $plugins = ctools_get_plugins('os2web_esdh_provider', $api);
    if (count($plugins) > 0) {
      foreach ($plugins as $plugin) {
        $rows[] = array(
          $api,
          $plugin['description'],
          $plugin['module'],
          os2web_esdh_provider_has_api($api) ? 'Working' : 'Error',
        );
      }
    }
    else {
      $rows[] = array($api, 'Unavailable', 'Not enabled.', 'Error');
    }
  }
  return '<h2>' . t('ESDH Provider API plugin status') . '</h2>' .
      theme('table', array('header' => $head, 'rows' => $rows)) .
      '<h2>' . t('Import of MM Based ESDH documents. (Last import was run at %time)', array('%time' => format_date(variable_get('os2web_esdh_provider_last_import', 0)))) . '</h2>' .
      drupal_render(drupal_get_form('os2web_esdh_provider_import_form'));
}

/**
 * Import form.
 */
function os2web_esdh_provider_import_form() {
  $form = array();
  $form['run_import'] = array(
    '#type' => 'submit',
    '#value' => t('Run import'),
  );
  $form['group'] = array(
    '#type' => 'fieldset',
    '#title' => t('Extended options.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['group']['force'] = array(
    '#type' => 'checkbox',
    '#title' => t('Force recreation of nodes'),
    '#default_value' => FALSE,
    '#description' => t('WARNING: This will destroy existing nodes and replace with freshly imported. All node-id\s will change'),
  );
  $form['group']['focus'] = array(
    '#type' => 'textfield',
    '#title' => t('Focused import id'),
    '#description' => t('Ie. 1577 to reimport XML_1577.xml.'),
  );
  return $form;
}

/**
 * Implements hook_FORM_submit().
 */
function os2web_esdh_provider_import_form_submit(&$form_state, $form) {
  if (!os2web_esdh_provider_has_api('mm')) {
    drupal_set_message(t('ERROR: No valid MM importer plugin active!'), 'error');
    return;
  }
  $force = $form['values']['force'] == 1;
  $focus = (int) $form['values']['focus'];

  $batch = array(
    'title' => 'Dagsorden import',
    'operations' => array(),
    'file' => drupal_get_path('module', 'os2web_esdh_provider') . '/os2web_esdh_provider.mmapi.inc',
  );
  $meetings = os2web_esdh_provider_invoke('mm', 'get_import_list');
  foreach ($meetings as $meeting) {
    if ($focus === 0 || $focus === $meeting['id']) {
      $batch['operations'][] = array(
        '_os2web_esdh_provider_import_meeting',
        array($meeting, $force));
    }
  }
  if (os2web_esdh_provider_supports('mm', 'post_import_process')) {
    $batch['operations'][] = array(
      'os2web_esdh_provider_invoke',
      array('mm', 'post_import_process'));
  }
  batch_set($batch);
}