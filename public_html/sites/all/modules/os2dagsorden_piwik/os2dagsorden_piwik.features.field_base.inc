<?php
/**
 * @file
 * os2dagsorden_piwik.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function os2dagsorden_piwik_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_os2web_meetings_bpa_piwik'.
  $field_bases['field_os2web_meetings_bpa_piwik'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_os2web_meetings_bpa_piwik',
    'indexes' => array(
      'hits' => array(
        0 => 'nb_hits',
        1 => 'entry_nb_actions',
      ),
      'rate' => array(
        0 => 'bounce_rate',
        1 => 'exit_rate',
      ),
      'visits' => array(
        0 => 'nb_visits',
        1 => 'entry_nb_visits',
        2 => 'exit_nb_visits',
      ),
    ),
    'locked' => 0,
    'module' => 'piwik_stats',
    'settings' => array(
      'period' => 'day',
      'show_in_statistics_page' => 1,
    ),
    'translatable' => 0,
    'type' => 'piwik_stats',
  );

  // Exported field_base: 'field_os2web_meetings_bul_piwik'.
  $field_bases['field_os2web_meetings_bul_piwik'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_os2web_meetings_bul_piwik',
    'indexes' => array(
      'hits' => array(
        0 => 'nb_hits',
        1 => 'entry_nb_actions',
      ),
      'rate' => array(
        0 => 'bounce_rate',
        1 => 'exit_rate',
      ),
      'visits' => array(
        0 => 'nb_visits',
        1 => 'entry_nb_visits',
        2 => 'exit_nb_visits',
      ),
    ),
    'locked' => 0,
    'module' => 'piwik_stats',
    'settings' => array(
      'period' => 'day',
      'show_in_statistics_page' => 1,
    ),
    'translatable' => 0,
    'type' => 'piwik_stats',
  );

  // Exported field_base: 'field_os2web_meetings_piwik'.
  $field_bases['field_os2web_meetings_piwik'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_os2web_meetings_piwik',
    'indexes' => array(
      'hits' => array(
        0 => 'nb_hits',
        1 => 'entry_nb_actions',
      ),
      'rate' => array(
        0 => 'bounce_rate',
        1 => 'exit_rate',
      ),
      'visits' => array(
        0 => 'nb_visits',
        1 => 'entry_nb_visits',
        2 => 'exit_nb_visits',
      ),
    ),
    'locked' => 0,
    'module' => 'piwik_stats',
    'settings' => array(
      'period' => 'day',
      'show_in_statistics_page' => 1,
    ),
    'translatable' => 0,
    'type' => 'piwik_stats',
  );

  return $field_bases;
}
