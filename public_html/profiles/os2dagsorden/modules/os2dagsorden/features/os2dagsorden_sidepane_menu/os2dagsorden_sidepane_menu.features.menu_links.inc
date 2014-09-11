<?php
/**
 * @file
 * os2dagsorden_sidepane_menu.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function os2dagsorden_sidepane_menu_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-sidepane-menu:<front>
  $menu_links['menu-sidepane-menu:<front>'] = array(
    'menu_name' => 'menu-sidepane-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Hjem',
    'options' => array(
      'attributes' => array(
        'id' => 'menu-home',
        'class' => array(
          0 => 'menu-sidepane',
        ),
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '1',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-50',
  );
  // Exported menu link: menu-sidepane-menu:meetings/print
  $menu_links['menu-sidepane-menu:meetings/print'] = array(
    'menu_name' => 'menu-sidepane-menu',
    'link_path' => 'meetings/print',
    'router_path' => 'meetings/print',
    'link_title' => 'Halvårs-kalender',
    'options' => array(
      'attributes' => array(
        'id' => 'menu-print-kalendar',
        'class' => array(
          0 => 'menu-sidepane',
        ),
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-49',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Halvårs-kalender');
  t('Hjem');


  return $menu_links;
}
