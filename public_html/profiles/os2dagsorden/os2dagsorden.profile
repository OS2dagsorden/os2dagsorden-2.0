<?php

/**
 * @file
 * This file includes all hooks to proper set up profile during install
 */

/**
 * Name of profile; visible in profile selection form.
 */
define('PROFILE_NAME', 'os2dagsorden');

/**
 * Description of profile; visible in profile selection form.
 */
define('PROFILE_DESCRIPTION', 'Generisk Installation OS2Dagsorden.');

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * Allows the profile to alter the site configuration form.
 */
function os2dagsorden_form_install_configure_form_alter(&$form, $form_state) {
  // Pre-populate the site name with the server name.
  $form['site_information']['site_name']['#default_value'] = 'OS2Dagsorden';
  $form['update_notifications']['update_status_module']['#default_value'] = array(0,0);
  $form['server_settings']['site_default_country']['#default_value'] = 'DK';
  $form['admin_account']['account']['name']['#default_value'] = 'admin';
}
