<?php
/**
 * @file
 * os2web_meetings_content_types.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function os2web_meetings_content_types_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function os2web_meetings_content_types_node_info() {
  $items = array(
    'os2web_meeting_search_status' => array(
      'name' => t('Meeting search status'),
      'base' => 'node_content',
      'description' => t('Det nyeste element af dette indhold vises på dagsordens søge siden.'),
      'has_title' => '1',
      'title_label' => t('Overskrift'),
      'help' => '',
    ),
    'os2web_meetings_bullet' => array(
      'name' => t('Bullet Point'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Titel'),
      'help' => '',
    ),
    'os2web_meetings_bullet_attach' => array(
      'name' => t('Bullet Point Attachment'),
      'base' => 'node_content',
      'description' => t('is an attachment to bullet point'),
      'has_title' => '1',
      'title_label' => t('Titel'),
      'help' => '',
    ),
    'os2web_meetings_meeting' => array(
      'name' => t('Meeting'),
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
