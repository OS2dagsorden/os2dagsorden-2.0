<?php
/**
 * @file
 * os2dagsorden_sidepane_menu.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function os2dagsorden_sidepane_menu_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: menu-sidepane-menu.
  $menus['menu-sidepane-menu'] = array(
    'menu_name' => 'menu-sidepane-menu',
    'title' => 'Sidepane menu',
    'description' => '',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Sidepane menu');


  return $menus;
}
