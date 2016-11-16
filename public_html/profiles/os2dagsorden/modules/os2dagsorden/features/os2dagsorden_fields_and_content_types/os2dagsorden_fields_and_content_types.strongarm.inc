<?php
/**
 * @file
 * os2dagsorden_fields_and_content_types.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function os2dagsorden_fields_and_content_types_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'chosen_disabled_themes';
  $strongarm->value = array(
    'os2dagsorden_theme' => 0,
  );
  $export['chosen_disabled_themes'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'chosen_disable_search';
  $strongarm->value = 0;
  $export['chosen_disable_search'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'chosen_disable_search_threshold';
  $strongarm->value = '0';
  $export['chosen_disable_search_threshold'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'chosen_jquery_selector';
  $strongarm->value = '.node-os2web_meetings_spaper-form select:visible';
  $export['chosen_jquery_selector'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'chosen_minimum_multiple';
  $strongarm->value = '0';
  $export['chosen_minimum_multiple'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'chosen_minimum_single';
  $strongarm->value = '0';
  $export['chosen_minimum_single'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'chosen_minimum_width';
  $strongarm->value = '500';
  $export['chosen_minimum_width'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'chosen_no_results_text';
  $strongarm->value = 'Ingen resultater';
  $export['chosen_no_results_text'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'chosen_placeholder_text_multiple';
  $strongarm->value = 'Vælg nogle';
  $export['chosen_placeholder_text_multiple'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'chosen_placeholder_text_single';
  $strongarm->value = 'Vælg en';
  $export['chosen_placeholder_text_single'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'chosen_search_contains';
  $strongarm->value = 1;
  $export['chosen_search_contains'] = $strongarm;

  return $export;
}
