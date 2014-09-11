<?php
/**
 * @file
 * os2dagsorden_content_types.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function os2dagsorden_content_types_taxonomy_default_vocabularies() {
  return array(
    'committee' => array(
      'name' => 'Committee',
      'machine_name' => 'committee',
      'description' => 'Udvalg',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '0',
    ),
    'lokation' => array(
      'name' => 'Lokation',
      'machine_name' => 'lokation',
      'description' => '',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '0',
    ),
    'user_position' => array(
      'name' => 'User position',
      'machine_name' => 'user_position',
      'description' => '',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '0',
    ),
  );
}
