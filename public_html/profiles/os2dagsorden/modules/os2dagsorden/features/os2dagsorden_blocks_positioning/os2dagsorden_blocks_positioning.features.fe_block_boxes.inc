<?php
/**
 * @file
 * os2dagsorden_blocks_positioning.features.fe_block_boxes.inc
 */

/**
 * Implements hook_default_fe_block_boxes().
 */
function os2dagsorden_blocks_positioning_default_fe_block_boxes() {
  $export = array();

  $fe_block_boxes = new stdClass();
  $fe_block_boxes->info = 'Os2dagsorden version number';
  $fe_block_boxes->format = 'php_code';
  $fe_block_boxes->machine_name = 'os2dagsorden_version_number';
  $fe_block_boxes->body = '<?php 
os2dagsorden_blocks_positioning_show_git_version();
?>';

  $export['os2dagsorden_version_number'] = $fe_block_boxes;

  return $export;
}
