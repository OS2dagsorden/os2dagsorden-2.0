<?php
/**
 * @file
 * os2dagsorden_settings.features.filter.inc
 */

/**
 * Implements hook_filter_default_formats().
 */
function os2dagsorden_settings_filter_default_formats() {
  $formats = array();

  // Exported format: Emails.
  $formats['emails'] = array(
    'format' => 'emails',
    'name' => 'Emails',
    'cache' => 1,
    'status' => 1,
    'weight' => 0,
    'filters' => array(
      'filter_autop' => array(
        'weight' => 0,
        'status' => 1,
        'settings' => array(),
      ),
      'filter_url' => array(
        'weight' => 0,
        'status' => 1,
        'settings' => array(
          'filter_url_length' => 72,
        ),
      ),
    ),
  );

  return $formats;
}
