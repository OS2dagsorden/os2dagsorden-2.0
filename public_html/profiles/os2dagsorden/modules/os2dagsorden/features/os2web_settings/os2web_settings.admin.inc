<?php
/**
 * @file
 * This file describes the admin form for os2web
 */

function os2web_settings_settings_form($form, $form_state) {
  $form['dummy'] = array(
    '#type' => 'markup',
    '#value' => 'Placeholder until more settings are needed.',
  );

  return system_settings_form($form);
}
