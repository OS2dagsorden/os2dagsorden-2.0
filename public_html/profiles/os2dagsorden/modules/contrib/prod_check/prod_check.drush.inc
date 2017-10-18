<?php

/**
 * Implementation of hook_drush_command().
 */
function prod_check_drush_command() {
  $items = array();

  $items['prod-check'] = array(
    'callback' => 'drush_prod_check_status',
    'description' => 'Display the Production Check status page.',
    'aliases' => array('pchk'),
  );

  $items['prod-check-prodmode'] = array(
    'callback' => 'drush_prod_check_prod_mode',
    'description' => 'Switch the site to production mode.',
    'options' => array(
      'config' => 'Ask for additional options before switching to production mode.',
    ),
    'aliases' => array('pchk-pmode'),
  );

  return $items;
}

/**
 * Status page callback
 */
function drush_prod_check_status() {
  // Map error codes to shell colours.
  $severity = array (
    PROD_CHECK_REQUIREMENT_INFO => '1',
    PROD_CHECK_REQUIREMENT_OK => '1;32',
    PROD_CHECK_REQUIREMENT_WARNING => '1;33',
    PROD_CHECK_REQUIREMENT_ERROR => '1;31',
  );
  $error = 0;

  $functions = _prod_check_functions();
  // Not needed here.
  unset($functions['prod_mon']);
  unset($functions['perf_data']);

  foreach ($functions as $set => $data) {
    $rows[] = array('');
    $rows[] = array("\033[1m" . dt($data['title'])."\033[0m");
    foreach ($data['functions'] as $function => $title) {
      $result = call_user_func($function);
      $func = ltrim($function, '_');
      if (is_array($result) && !empty($result)) {
        $rows[] = array(
          $result[$func]['title'],
          "\033[" . $severity[$result[$func]['severity']] . 'm' . strip_tags($result[$func]['value']) . "\033[0m",
        );
        if ($error < $result[$func]['severity']) {
          $error = $result[$func]['severity'];
        }
      }
    }
  }
  drush_print("\033[1m" . dt('Production Check status')."\033[0m", 1);
  drush_print_table($rows);
  if ($error > 0) {
    // Would be cool if we could prefix the admin path with http://<host>/ so it
    // will become a clickable link in some terminals. Any ideas?
    drush_print("\033[1m" . dt('Some errors were reported!') . "\033[0m " . dt('Check the full status page on') . " \033[1m" . 'admin/reports/prod-check' . "\033[0m " . dt('for details.'));
  }
}

/**
 * Switch to production mode.
 */
function drush_prod_check_prod_mode() {
  $options = array();

  // Ask extra input when the --config option is used.
  if (drush_get_option('config', FALSE)) {
    $options['site_mail'] = drush_prompt(dt('Site e-mail address'));

    if (module_exists('webform')) {
      $options['webform_default_from_address'] = drush_prompt(dt('Webform default from e-mail address'));
    }

    if (module_exists('googleanalytics')) {
      $options['googleanalytics_account'] = drush_prompt(dt('Google Analytics Web Property ID'));
    }

    $options['block_cache'] = drush_confirm(dt('Enable Block cache'));

    if (module_exists('dblog')) {
      $options['dblog'] = drush_confirm(dt('Disable Database logging'));
    }

    $options['nagios'] = drush_confirm(dt('Enable Nagios monitoring contrib module'));
  }

  // Adjust settings.
  module_load_include('inc', 'prod_check', 'includes/prod_check.admin');
  $variables = prod_check_prod_mode_settings($options);
  drush_print(dt('The following settings have been changed: !variables.', array('!variables' => implode(', ', array_keys($variables)))));

  // Enable / disable modules.
  $modules = prod_check_prod_mode_modules($options);
  if (!empty($modules['disable'])) {
    drush_print(dt('The following modules have been disabled: !modules.', array('!modules' => implode(', ', $modules['disable']))));
  }
  if (!empty($modules['enable'])) {
    drush_print(dt('The following modules have been enabled: !modules.', array('!modules' => implode(', ', $modules['enable']))));
  }
}
