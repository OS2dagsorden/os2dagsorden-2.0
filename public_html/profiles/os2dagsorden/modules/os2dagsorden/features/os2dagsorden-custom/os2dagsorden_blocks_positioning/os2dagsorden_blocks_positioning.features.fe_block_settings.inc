<?php
/**
 * @file
 * os2dagsorden_blocks_positioning.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function os2dagsorden_blocks_positioning_default_fe_block_settings() {
  $export = array();

  $export['version'] = '1.0';

  // Theme independent visibility settings.
  $export['visibility'] = array(
    'views--exp-meetings_search-page' => array(
      'delta' => '-exp-meetings_search-page',
      'module' => 'views',
    ),
  );

  // os2dagsorden_theme
  $theme = array();

  $theme['views--exp-meetings_search-page'] = array(
    'module' => 'views',
    'delta' => '-exp-meetings_search-page',
    'theme' => 'os2dagsorden_theme',
    'status' => 0,
    'weight' => '0',
    'region' => '',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => 'Søg',
    'cache' => -1,
  );

  $export['theme']['os2dagsorden_theme'] = $theme;

  $theme_default = variable_get('theme_default', 'garland');
  $themes = list_themes();
  foreach ($export as $theme_key => $settings) {
    if ($theme_key != $theme_default && empty($themes[$theme_key]->status)) {
      unset($export['theme'][$theme_key]);
    }
  }
  return $export;
}
