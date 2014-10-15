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

  $export['version'] = '2.0';

  $export['user-login'] = array(
    'cache' => -1,
    'custom' => '0',
    'delta' => 'login',
    'module' => 'user',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(
      'anonymous user' => '1',
    ),
    'themes' => array(
      'os2dagsorden_theme' => array(
        'region' => 'content',
        'status' => '1',
        'theme' => 'os2dagsorden_theme',
        'weight' => '0',
      ),
    ),
    'title' => '',
    'visibility' => '0',
  );

  $export['views--exp-meetings_search-page'] = array(
    'cache' => -1,
    'custom' => '0',
    'delta' => '-exp-meetings_search-page',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(
      'authenticated user' => '2',
    ),
    'themes' => array(
      'os2dagsorden_theme' => array(
        'region' => 'sidebar_second',
        'status' => '1',
        'theme' => 'os2dagsorden_theme',
        'weight' => '-16',
      ),
    ),
    'title' => 'Søg',
    'visibility' => '0',
  );

  $export['views-0293ca2a3a9d3ff12dd399cf7b0b4333'] = array(
    'cache' => -1,
    'custom' => '0',
    'delta' => '0293ca2a3a9d3ff12dd399cf7b0b4333',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '<front>',
    'roles' => array(
      'authenticated user' => '2',
    ),
    'themes' => array(
      'os2dagsorden_theme' => array(
        'region' => 'content',
        'status' => '1',
        'theme' => 'os2dagsorden_theme',
        'weight' => '0',
      ),
    ),
    'title' => '',
    'visibility' => '1',
  );

  $export['views-bae826754ab8812775bd594878d7fdb1'] = array(
    'cache' => -1,
    'custom' => '0',
    'delta' => 'bae826754ab8812775bd594878d7fdb1',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '<front>',
    'roles' => array(
      'authenticated user' => '2',
    ),
    'themes' => array(
      'os2dagsorden_theme' => array(
        'region' => 'content',
        'status' => '1',
        'theme' => 'os2dagsorden_theme',
        'weight' => '0',
      ),
    ),
    'title' => '',
    'visibility' => '1',
  );

  $export['views-c8c6c91b397acf23018fcefd40a1fa29'] = array(
    'cache' => -1,
    'custom' => '0',
    'delta' => 'c8c6c91b397acf23018fcefd40a1fa29',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '<front>',
    'roles' => array(
      'authenticated user' => '2',
    ),
    'themes' => array(
      'os2dagsorden_theme' => array(
        'region' => 'content',
        'status' => '1',
        'theme' => 'os2dagsorden_theme',
        'weight' => '0',
      ),
    ),
    'title' => '',
    'visibility' => '1',
  );

  $export['views-events-block_1'] = array(
    'cache' => -1,
    'custom' => '0',
    'delta' => 'events-block_1',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(
      'authenticated user' => '2',
    ),
    'themes' => array(
      'os2dagsorden_theme' => array(
        'region' => 'sidebar_second',
        'status' => '1',
        'theme' => 'os2dagsorden_theme',
        'weight' => '-19',
      ),
    ),
    'title' => '',
    'visibility' => '0',
  );

  $export['views-events-block_2'] = array(
    'cache' => -1,
    'custom' => '0',
    'delta' => 'events-block_2',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '<front>',
    'roles' => array(
      'authenticated user' => '2',
    ),
    'themes' => array(
      'os2dagsorden_theme' => array(
        'region' => 'content',
        'status' => '1',
        'theme' => 'os2dagsorden_theme',
        'weight' => '0',
      ),
    ),
    'title' => '',
    'visibility' => '1',
  );

  $export['views-user_committee-block_1'] = array(
    'cache' => -1,
    'custom' => '0',
    'delta' => 'user_committee-block_1',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(
      'authenticated user' => '2',
    ),
    'themes' => array(
      'os2dagsorden_theme' => array(
        'region' => 'sidebar_second',
        'status' => '1',
        'theme' => 'os2dagsorden_theme',
        'weight' => '-18',
      ),
    ),
    'title' => '',
    'visibility' => '0',
  );

  $export['views-user_follow_committees-block_1'] = array(
    'cache' => '-1',
    'custom' => '0',
    'delta' => 'user_follow_committees-block_1',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(
      'authenticated user' => '2',
    ),
    'themes' => array(
      'os2dagsorden_theme' => array(
        'region' => 'sidebar_second',
        'status' => '1',
        'theme' => 'os2dagsorden_theme',
        'weight' => '-17',
      ),
    ),
    'title' => '',
    'visibility' => '0',
  );

  $export['views-user_logout_menu-block'] = array(
    'cache' => '-1',
    'custom' => '0',
    'delta' => 'user_logout_menu-block',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(
      'authenticated user' => '2',
    ),
    'themes' => array(
      'os2dagsorden_theme' => array(
        'region' => 'menu',
        'status' => '1',
        'theme' => 'os2dagsorden_theme',
        'weight' => '-21',
      ),
    ),
    'title' => '',
    'visibility' => '0',
  );

  return $export;
}
