<?php
/**
 * @file
 * os2dagsorden_automated_logout_configuration.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function os2dagsorden_automated_logout_configuration_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_enforce_admin';
  $strongarm->value = 1;
  $export['autologout_enforce_admin'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_max_timeout';
  $strongarm->value = '172800';
  $export['autologout_max_timeout'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_message';
  $strongarm->value = 'Du har været inaktiv i 120 minutter. Ønsker du at logge af eller forsætte med at anvende OS2dagsorden?';
  $export['autologout_message'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_padding';
  $strongarm->value = '1800';
  $export['autologout_padding'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_redirect_url';
  $strongarm->value = 'logout/';
  $export['autologout_redirect_url'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_role_2';
  $strongarm->value = 1;
  $export['autologout_role_2'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_role_2_timeout';
  $strongarm->value = '7200';
  $export['autologout_role_2_timeout'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_role_3';
  $strongarm->value = 1;
  $export['autologout_role_3'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_role_3_timeout';
  $strongarm->value = '7200';
  $export['autologout_role_3_timeout'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_role_4';
  $strongarm->value = 1;
  $export['autologout_role_4'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_role_4_timeout';
  $strongarm->value = '7200';
  $export['autologout_role_4_timeout'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_role_5';
  $strongarm->value = 1;
  $export['autologout_role_5'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_role_5_timeout';
  $strongarm->value = '7200';
  $export['autologout_role_5_timeout'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_role_logout';
  $strongarm->value = 0;
  $export['autologout_role_logout'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_timeout';
  $strongarm->value = '7200';
  $export['autologout_timeout'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autologout_use_watchdog';
  $strongarm->value = 1;
  $export['autologout_use_watchdog'] = $strongarm;

  return $export;
}
