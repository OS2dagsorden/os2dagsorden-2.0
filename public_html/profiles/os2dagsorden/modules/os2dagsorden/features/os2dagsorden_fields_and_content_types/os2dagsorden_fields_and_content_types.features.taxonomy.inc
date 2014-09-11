<?php
/**
 * @file
 * os2dagsorden_fields_and_content_types.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function os2dagsorden_fields_and_content_types_taxonomy_default_vocabularies() {
  return array(
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
