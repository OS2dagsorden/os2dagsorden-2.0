<?php
/**
 * @file
 * os2dagsorden_sidepane_menu.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function os2dagsorden_sidepane_menu_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['block-show_hide_menu_block'] = array(
    'cache' => -1,
    'custom' => 0,
    'machine_name' => 'show_hide_menu_block',
    'module' => 'block',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(
      'authenticated user' => 2,
    ),
    'themes' => array(
      'os2dagsorden_theme' => array(
        'region' => 'menu',
        'status' => 1,
        'theme' => 'os2dagsorden_theme',
        'weight' => -20,
      ),
      'rubik' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'rubik',
        'weight' => -20,
      ),
    ),
    'title' => '<none>',
    'visibility' => 0,
  );

  $export['menu-menu-sidepane-menu'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'menu-sidepane-menu',
    'module' => 'menu',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(
      'authenticated user' => 2,
    ),
    'themes' => array(
      'os2dagsorden_theme' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'os2dagsorden_theme',
        'weight' => -20,
      ),
      'rubik' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'rubik',
        'weight' => -20,
      ),
    ),
    'title' => '<none>',
    'visibility' => 0,
  );

  return $export;
}
