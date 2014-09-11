<?php
/**
 * @file
 * os2dagsorden_sidepane_menu.features.fe_block_boxes.inc
 */

/**
 * Implements hook_default_fe_block_boxes().
 */
function os2dagsorden_sidepane_menu_default_fe_block_boxes() {
  $export = array();

  $fe_block_boxes = new stdClass();
  $fe_block_boxes->info = 'show_hide_menu';
  $fe_block_boxes->format = 'full_html';
  $fe_block_boxes->machine_name = 'show_hide_menu_block';
  $fe_block_boxes->body = '<div id="show_hide_menu_container">
	<input class="button" id="show_hide_menu_button" type="button" value="⇐" /></div>
';

  $export['show_hide_menu_block'] = $fe_block_boxes;

  return $export;
}
