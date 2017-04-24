<?php
/**
 * @file
 * os2dagsorden_fields_and_content_types.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function os2dagsorden_fields_and_content_types_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function os2dagsorden_fields_and_content_types_node_info() {
  $items = array(
    'os2web_meetings_spaper' => array(
      'name' => t('Talepapir'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Titel'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
