<?php
/**
 * @file
 * os2dagsorden_content_types.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function os2dagsorden_content_types_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function os2dagsorden_content_types_node_info() {
  $items = array(
    'bullet_point' => array(
      'name' => t('Bullet Point'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Titel'),
      'help' => '',
    ),
    'bullet_point_attachment' => array(
      'name' => t('Bullet Point Attachment'),
      'base' => 'node_content',
      'description' => t('is an attachment to bullet point'),
      'has_title' => '1',
      'title_label' => t('Titel'),
      'help' => '',
    ),
    'meeting' => array(
      'name' => t('Meeting'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Titel'),
      'help' => '',
    ),
    'page' => array(
      'name' => t('Side'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Titel'),
      'help' => '',
    ),
    'speaker_paper' => array(
      'name' => t('Talepapir'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Titel'),
      'help' => '',
    ),
  );
  return $items;
}
