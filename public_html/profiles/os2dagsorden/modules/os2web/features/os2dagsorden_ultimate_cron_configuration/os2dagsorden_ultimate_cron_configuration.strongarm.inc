<?php
/**
 * @file
 * os2dagsorden_ultimate_cron_configuration.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function os2dagsorden_ultimate_cron_configuration_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ultimate_cron_catch_up';
  $strongarm->value = '300';
  $export['ultimate_cron_catch_up'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ultimate_cron_cleanup_log';
  $strongarm->value = '2592000';
  $export['ultimate_cron_cleanup_log'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ultimate_cron_poorman';
  $strongarm->value = 1;
  $export['ultimate_cron_poorman'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ultimate_cron_queue_polling_latency';
  $strongarm->value = '';
  $export['ultimate_cron_queue_polling_latency'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ultimate_cron_rule';
  $strongarm->value = '0 */3 * * *';
  $export['ultimate_cron_rule'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ultimate_cron_simultaneous_connections';
  $strongarm->value = '40';
  $export['ultimate_cron_simultaneous_connections'] = $strongarm;

  return $export;
}
