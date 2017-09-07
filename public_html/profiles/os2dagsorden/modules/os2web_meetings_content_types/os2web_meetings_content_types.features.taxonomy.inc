<?php
/**
 * @file
 * os2web_meetings_content_types.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function os2web_meetings_content_types_taxonomy_default_vocabularies() {
  return array(
    'os2web_meetings_tax_committee' => array(
      'name' => 'Committee',
      'machine_name' => 'os2web_meetings_tax_committee',
      'description' => 'Udvalg',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
    'os2web_meetings_tax_location' => array(
      'name' => 'Lokation',
      'machine_name' => 'os2web_meetings_tax_location',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
    'os2web_meetings_tax_status' => array(
      'name' => 'Meeting status',
      'machine_name' => 'os2web_meetings_tax_status',
      'description' => 'represents the current of the meeting',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
