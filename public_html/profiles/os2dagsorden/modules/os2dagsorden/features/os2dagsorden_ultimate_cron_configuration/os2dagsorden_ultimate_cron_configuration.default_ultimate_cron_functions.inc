<?php
/**
 * @file
 * os2dagsorden_ultimate_cron_configuration.default_ultimate_cron_functions.inc
 */

/**
 * Implements hook_default_ultimate_cron_function().
 */
function os2dagsorden_ultimate_cron_configuration_default_ultimate_cron_function() {
  $export = array();

  $function = new stdClass();
  $function->disabled = FALSE; /* Edit this to true to make a default function disabled initially */
  $function->api_version = 1;
  $function->function = 'os2dagsorden_access_helper_cron';
  $function->settings = array(
    'enabled' => 1,
    'rules' => array(
      0 => '0 4 1 */1 *',
    ),
    'catch_up' => '',
    'service_group' => '',
  );
  $export['os2dagsorden_access_helper_cron'] = $function;

  return $export;
}
