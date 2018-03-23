<?php
/**
 * @file
 * os2dagsorden_piwik.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function os2dagsorden_piwik_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'piwik_pages';
  $strongarm->value = 'admin
admin/*
batch
node/add*
node/*/*
user/*/*';
  $export['piwik_pages'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'piwik_stats_cron_fill';
  $strongarm->value = 0;
  $export['piwik_stats_cron_fill'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'piwik_visibility_pages';
  $strongarm->value = 0;
  $export['piwik_visibility_pages'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'piwik_visibility_roles';
  $strongarm->value = 0;
  $export['piwik_visibility_roles'] = $strongarm;

  return $export;
}
