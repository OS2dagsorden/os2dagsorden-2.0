<?php
/**
 * @file
 * os2dagsorden_blocks_positioning.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function os2dagsorden_blocks_positioning_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'block_title';
  $strongarm->value = 'automatic logout in';
  $export['block_title'] = $strongarm;

  return $export;
}
