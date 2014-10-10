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
    'block-show_hide_menu_block' => array(
      'machine_name' => 'show_hide_menu_block',
      'module' => 'block',
    ),
    'user-login' => array(
      'delta' => 'login',
      'module' => 'user',
    ),
    'views--exp-meetings_search-page' => array(
      'delta' => '-exp-meetings_search-page',
      'module' => 'views',
    ),
    'views-0293ca2a3a9d3ff12dd399cf7b0b4333' => array(
      'delta' => '0293ca2a3a9d3ff12dd399cf7b0b4333',
      'module' => 'views',
    ),
    'views-bae826754ab8812775bd594878d7fdb1' => array(
      'delta' => 'bae826754ab8812775bd594878d7fdb1',
      'module' => 'views',
    ),
    'views-c8c6c91b397acf23018fcefd40a1fa29' => array(
      'delta' => 'c8c6c91b397acf23018fcefd40a1fa29',
      'module' => 'views',
    ),
    'views-events-block_1' => array(
      'delta' => 'events-block_1',
      'module' => 'views',
    ),
    'views-events-block_2' => array(
      'delta' => 'events-block_2',
      'module' => 'views',
    ),
    'views-user_committee-block_1' => array(
      'delta' => 'user_committee-block_1',
      'module' => 'views',
    ),
    'views-user_follow_committees-block_1' => array(
      'delta' => 'user_follow_committees-block_1',
      'module' => 'views',
    ),
    'views-user_logout_menu-block' => array(
      'delta' => 'user_logout_menu-block',
      'module' => 'views',
    ),
  );

  // os2dagsorden_theme
  $theme = array();

  $theme['block-show_hide_menu_block'] = array(
    'module' => 'block',
    'theme' => 'os2dagsorden_theme',
    'status' => '1',
    'weight' => '-20',
    'region' => 'menu',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '<none>',
    'cache' => -1,
    'machine_name' => 'show_hide_menu_block',
  );

  $theme['user-login'] = array(
    'module' => 'user',
    'delta' => 'login',
    'theme' => 'os2dagsorden_theme',
    'status' => '1',
    'weight' => '0',
    'region' => 'content',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => -1,
  );

  $theme['views--exp-meetings_search-page'] = array(
    'module' => 'views',
    'delta' => '-exp-meetings_search-page',
    'theme' => 'os2dagsorden_theme',
    'status' => '1',
    'weight' => '-16',
    'region' => 'sidebar_second',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => 'Søg',
    'cache' => -1,
  );

  $theme['views-0293ca2a3a9d3ff12dd399cf7b0b4333'] = array(
    'module' => 'views',
    'delta' => '0293ca2a3a9d3ff12dd399cf7b0b4333',
    'theme' => 'os2dagsorden_theme',
    'status' => '1',
    'weight' => '0',
    'region' => 'content',
    'custom' => '0',
    'visibility' => '1',
    'pages' => '<front>',
    'title' => '',
    'cache' => -1,
  );

  $theme['views-bae826754ab8812775bd594878d7fdb1'] = array(
    'module' => 'views',
    'delta' => 'bae826754ab8812775bd594878d7fdb1',
    'theme' => 'os2dagsorden_theme',
    'status' => '1',
    'weight' => '0',
    'region' => 'content',
    'custom' => '0',
    'visibility' => '1',
    'pages' => '<front>',
    'title' => '',
    'cache' => -1,
  );

  $theme['views-c8c6c91b397acf23018fcefd40a1fa29'] = array(
    'module' => 'views',
    'delta' => 'c8c6c91b397acf23018fcefd40a1fa29',
    'theme' => 'os2dagsorden_theme',
    'status' => '1',
    'weight' => '0',
    'region' => 'content',
    'custom' => '0',
    'visibility' => '1',
    'pages' => '<front>',
    'title' => '',
    'cache' => -1,
  );

  $theme['views-events-block_1'] = array(
    'module' => 'views',
    'delta' => 'events-block_1',
    'theme' => 'os2dagsorden_theme',
    'status' => '1',
    'weight' => '-19',
    'region' => 'sidebar_second',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => -1,
  );

  $theme['views-events-block_2'] = array(
    'module' => 'views',
    'delta' => 'events-block_2',
    'theme' => 'os2dagsorden_theme',
    'status' => '1',
    'weight' => '0',
    'region' => 'content',
    'custom' => '0',
    'visibility' => '1',
    'pages' => '<front>',
    'title' => '',
    'cache' => -1,
  );

  $theme['views-user_committee-block_1'] = array(
    'module' => 'views',
    'delta' => 'user_committee-block_1',
    'theme' => 'os2dagsorden_theme',
    'status' => '1',
    'weight' => '-18',
    'region' => 'sidebar_second',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => -1,
  );

  $theme['views-user_follow_committees-block_1'] = array(
    'module' => 'views',
    'delta' => 'user_follow_committees-block_1',
    'theme' => 'os2dagsorden_theme',
    'status' => '1',
    'weight' => '-17',
    'region' => 'sidebar_second',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
  );

  $theme['views-user_logout_menu-block'] = array(
    'module' => 'views',
    'delta' => 'user_logout_menu-block',
    'theme' => 'os2dagsorden_theme',
    'status' => '1',
    'weight' => '-21',
    'region' => 'menu',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
  );

  $export['theme']['os2dagsorden_theme'] = $theme;

  // os2dagsorden_theme_ballerup
  $theme = array();

  $theme['block-show_hide_menu_block'] = array(
    'module' => 'block',
    'theme' => 'os2dagsorden_theme_ballerup',
    'status' => '1',
    'weight' => '16',
    'region' => 'menu',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '<none>',
    'cache' => -1,
    'machine_name' => 'show_hide_menu_block',
  );

  $theme['user-login'] = array(
    'module' => 'user',
    'delta' => 'login',
    'theme' => 'os2dagsorden_theme_ballerup',
    'status' => '1',
    'weight' => '-19',
    'region' => 'content',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => -1,
  );

  $theme['views--exp-meetings_search-page'] = array(
    'module' => 'views',
    'delta' => '-exp-meetings_search-page',
    'theme' => 'os2dagsorden_theme_ballerup',
    'status' => '1',
    'weight' => '-21',
    'region' => 'content',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => 'Søg',
    'cache' => -1,
  );

  $theme['views-0293ca2a3a9d3ff12dd399cf7b0b4333'] = array(
    'module' => 'views',
    'delta' => '0293ca2a3a9d3ff12dd399cf7b0b4333',
    'theme' => 'os2dagsorden_theme_ballerup',
    'status' => '1',
    'weight' => '-17',
    'region' => 'content',
    'custom' => '0',
    'visibility' => '1',
    'pages' => '<front>',
    'title' => '',
    'cache' => -1,
  );

  $theme['views-bae826754ab8812775bd594878d7fdb1'] = array(
    'module' => 'views',
    'delta' => 'bae826754ab8812775bd594878d7fdb1',
    'theme' => 'os2dagsorden_theme_ballerup',
    'status' => '1',
    'weight' => '-18',
    'region' => 'content',
    'custom' => '0',
    'visibility' => '1',
    'pages' => '<front>',
    'title' => '',
    'cache' => -1,
  );

  $theme['views-c8c6c91b397acf23018fcefd40a1fa29'] = array(
    'module' => 'views',
    'delta' => 'c8c6c91b397acf23018fcefd40a1fa29',
    'theme' => 'os2dagsorden_theme_ballerup',
    'status' => '1',
    'weight' => '-16',
    'region' => 'content',
    'custom' => '0',
    'visibility' => '1',
    'pages' => '<front>',
    'title' => '',
    'cache' => -1,
  );

  $theme['views-events-block_1'] = array(
    'module' => 'views',
    'delta' => 'events-block_1',
    'theme' => 'os2dagsorden_theme_ballerup',
    'status' => '1',
    'weight' => '-21',
    'region' => 'sidebar_second',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => -1,
  );

  $theme['views-events-block_2'] = array(
    'module' => 'views',
    'delta' => 'events-block_2',
    'theme' => 'os2dagsorden_theme_ballerup',
    'status' => 0,
    'weight' => '10',
    'region' => '',
    'custom' => '0',
    'visibility' => '1',
    'pages' => '<front>',
    'title' => '',
    'cache' => -1,
  );

  $theme['views-user_committee-block_1'] = array(
    'module' => 'views',
    'delta' => 'user_committee-block_1',
    'theme' => 'os2dagsorden_theme_ballerup',
    'status' => '1',
    'weight' => '-19',
    'region' => 'sidebar_second',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => -1,
  );

  $theme['views-user_follow_committees-block_1'] = array(
    'module' => 'views',
    'delta' => 'user_follow_committees-block_1',
    'theme' => 'os2dagsorden_theme_ballerup',
    'status' => '1',
    'weight' => '-18',
    'region' => 'sidebar_second',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
  );

  $theme['views-user_logout_menu-block'] = array(
    'module' => 'views',
    'delta' => 'user_logout_menu-block',
    'theme' => 'os2dagsorden_theme_ballerup',
    'status' => '1',
    'weight' => '0',
    'region' => 'menu',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
  );

  $export['theme']['os2dagsorden_theme_ballerup'] = $theme;

  // os2dagsorden_theme_ringsted
  $theme = array();

  $theme['block-show_hide_menu_block'] = array(
    'module' => 'block',
    'theme' => 'os2dagsorden_theme_ringsted',
    'status' => '1',
    'weight' => '-21',
    'region' => 'menu',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '<none>',
    'cache' => -1,
    'machine_name' => 'show_hide_menu_block',
  );

  $theme['user-login'] = array(
    'module' => 'user',
    'delta' => 'login',
    'theme' => 'os2dagsorden_theme_ringsted',
    'status' => '1',
    'weight' => '0',
    'region' => 'content',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => -1,
  );

  $theme['views--exp-meetings_search-page'] = array(
    'module' => 'views',
    'delta' => '-exp-meetings_search-page',
    'theme' => 'os2dagsorden_theme_ringsted',
    'status' => '1',
    'weight' => '-21',
    'region' => 'content',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => 'Søg',
    'cache' => -1,
  );

  $theme['views-0293ca2a3a9d3ff12dd399cf7b0b4333'] = array(
    'module' => 'views',
    'delta' => '0293ca2a3a9d3ff12dd399cf7b0b4333',
    'theme' => 'os2dagsorden_theme_ringsted',
    'status' => '1',
    'weight' => '0',
    'region' => 'content',
    'custom' => '0',
    'visibility' => '1',
    'pages' => '<front>',
    'title' => '',
    'cache' => -1,
  );

  $theme['views-bae826754ab8812775bd594878d7fdb1'] = array(
    'module' => 'views',
    'delta' => 'bae826754ab8812775bd594878d7fdb1',
    'theme' => 'os2dagsorden_theme_ringsted',
    'status' => '1',
    'weight' => '0',
    'region' => 'content',
    'custom' => '0',
    'visibility' => '1',
    'pages' => '<front>',
    'title' => '',
    'cache' => -1,
  );

  $theme['views-c8c6c91b397acf23018fcefd40a1fa29'] = array(
    'module' => 'views',
    'delta' => 'c8c6c91b397acf23018fcefd40a1fa29',
    'theme' => 'os2dagsorden_theme_ringsted',
    'status' => '1',
    'weight' => '0',
    'region' => 'content',
    'custom' => '0',
    'visibility' => '1',
    'pages' => '<front>',
    'title' => '',
    'cache' => -1,
  );

  $theme['views-events-block_1'] = array(
    'module' => 'views',
    'delta' => 'events-block_1',
    'theme' => 'os2dagsorden_theme_ringsted',
    'status' => '1',
    'weight' => '-19',
    'region' => 'sidebar_second',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => -1,
  );

  $theme['views-events-block_2'] = array(
    'module' => 'views',
    'delta' => 'events-block_2',
    'theme' => 'os2dagsorden_theme_ringsted',
    'status' => '1',
    'weight' => '0',
    'region' => 'content',
    'custom' => '0',
    'visibility' => '1',
    'pages' => '<front>',
    'title' => '',
    'cache' => -1,
  );

  $theme['views-user_committee-block_1'] = array(
    'module' => 'views',
    'delta' => 'user_committee-block_1',
    'theme' => 'os2dagsorden_theme_ringsted',
    'status' => '1',
    'weight' => '-18',
    'region' => 'sidebar_second',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => -1,
  );

  $theme['views-user_follow_committees-block_1'] = array(
    'module' => 'views',
    'delta' => 'user_follow_committees-block_1',
    'theme' => 'os2dagsorden_theme_ringsted',
    'status' => '1',
    'weight' => '-17',
    'region' => 'sidebar_second',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
  );

  $theme['views-user_logout_menu-block'] = array(
    'module' => 'views',
    'delta' => 'user_logout_menu-block',
    'theme' => 'os2dagsorden_theme_ringsted',
    'status' => '1',
    'weight' => '0',
    'region' => 'menu',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => '-1',
  );

  $export['theme']['os2dagsorden_theme_ringsted'] = $theme;

  $theme_default = variable_get('theme_default', 'garland');
  $themes = list_themes();
  foreach ($export as $theme_key => $settings) {
    if ($theme_key != $theme_default && empty($themes[$theme_key]->status)) {
      unset($export['theme'][$theme_key]);
    }
  }
  return $export;
}
