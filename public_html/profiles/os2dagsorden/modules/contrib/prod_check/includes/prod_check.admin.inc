<?php

/**
 * Build status page.
 */
function prod_check_status() {
  drupal_set_title(t('Production check status'));

  $output = '';

  // Execute all functions per set as defined in the functions array in
  // _prod_check_functions().
  $functions = _prod_check_functions();
  // Not needed here.
  unset($functions['prod_mon']);
  unset($functions['perf_data']);

  foreach ($functions as $set => $data) {
    $result = array();
    foreach ($data['functions'] as $function => $title) {
      $check = call_user_func($function);
      if (is_array($check) && !empty($check)) {
        $result = array_merge($result, $check);
      }
    }
    $output .= '<h2>' . t($data['title']) . '</h2>' . "\n";
    $output .= '<div class="description"><p><em>' . t($data['description']) . '</em></p></div>' . "\n";
    $output .= theme('prod_check_status_report', array('requirements' => $result));
  }

  return $output;
}

/**
 * Build settings form.
 */
function prod_check_settings_form($form, &$form_state) {
  drupal_set_title(t('Production check settings'));
  $form = array();

  // Add stylesheets & CSS.
  $base = drupal_get_path('module', 'prod_check');
  $form['#attached'] = array(
    'css' => array(
      'type' => 'file',
      'data' => $base . '/css/prod-check.css',
    ),
    'js' => array(
      array (
        'type' => 'file',
        'data' => $base . '/js/jquery.equalheights.js',
      ),
      array (
        'type' => 'file',
        'data' => $base . '/js/jquery.maskedinput.min.js',
      ),
      array (
        'type' => 'file',
        'data' => $base . '/js/prod-check.js',
      ),
    ),
  );

  // E-mail settings.
  $form['prod_check_general'] = array(
    '#type' => 'fieldset',
    '#title' => t('General settings'),
    '#description' => t('Settings to allow certain checks to function properly.'),
    '#collapsible' => FALSE,
  );
  $form['prod_check_general']['prod_check_sitemail'] = array(
    '#type' => 'textfield',
    '#title' => t('Mail check'),
    '#default_value' => variable_get('prod_check_sitemail', ''),
    '#size' => 60,
    '#description' => t('Enter (part of) the e-mail address you always <strong>use when developing</strong> a website. This is used in a regular expression in the "Site e-mail", Contact and Webform modules check.'),
    '#required' => FALSE,
  );
  if (module_exists('dblog')) {
    $form['prod_check_general']['prod_check_dblog_php'] = array(
      '#type' => 'select',
      '#title' => t('Minimal watchdog severity for PHP errors'),
      '#default_value' => variable_get('prod_check_dblog_php', WATCHDOG_WARNING),
      '#options' => watchdog_severity_levels(),
      '#description' => t('Select the severity level from which to start reporting PHP errors being logged to the watchdog table.'),
      '#required' => TRUE,
    );
    $form['prod_check_general']['prod_check_dblog_php_threshold'] = array(
      '#type' => 'textfield',
      '#title' => t('Threshold for PHP errors'),
      '#size' => 2,
      '#default_value' => variable_get('prod_check_dblog_php_threshold', 1),
      '#description' => t('Enter the number of times a PHP error needs to occur before reporting a problem. E.g. entering 3 here will allow 2 occurences of the exact same PHP error without an error being reported.'),
      '#required' => TRUE,
    );
  }

  $form['prod_check_apc'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced APC/OPcache settings'),
    '#description' => t('These settings are used in the !link functionality.', prod_check_link_array('advanced APC', 'admin/reports/status/apc-opc')),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  // Cache full count threshold
  $form['prod_check_apc']['prod_check_apc_expunge'] = array(
    '#type' => 'textfield',
    '#title' => t('APC/OPcache cache full count threshold'),
    '#default_value' => variable_get('prod_check_apc_expunge', 0),
    '#size' => 2,
    '#description' => t('Issue a critical error when the cache full count is greater than the number entered here.'),
    '#required' => FALSE,
  );

  // APC user.
  $form['prod_check_apc']['prod_check_apcuser'] = array(
    '#type' => 'textfield',
    '#title' => t('APC advanced features username'),
    '#default_value' => variable_get('prod_check_apcuser', 'apc'),
    '#size' => 60,
    '#description' => t('The username for logging in to the APC settings page.'),
    '#required' => FALSE,
  );
  // APC password.
  $form['prod_check_apc']['prod_check_apcpass'] = array(
    '#type' => 'password_confirm',
    '#title' => t('APC advanced features password'),
    '#size' => 60,
    '#description' => t('The password for logging in to the APC settings page.'),
    '#required' => FALSE,
  );

  // Disabled module settings
  $form['prod_check_disabled'] = array(
    '#type' => 'fieldset',
    '#title' => t('Disabled modules'),
    '#description' => t('You can choose to disable checking for updates for disabled modules here.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['prod_check_disabled']['prod_check_exclude_disabled_modules'] = array(
    '#type' => 'checkbox',
    '#title' => t("Don't check for updates for disabled modules"),
    '#default_value' => variable_get('prod_check_exclude_disabled_modules', 0),
    '#description' => t('When checked, only enabled modules will be reported. Note that this can cause some modules that are used but not enabled (f.e. APC, memcache, domain,...) to get skipped. See the documentation on how to add disabled modules on a whitelist.'),
    '#required' => FALSE,
  );
  $modules = implode(', ', _prod_check_get_disabled_modules_whitelist());
  $form['prod_check_disabled']['prod_check_disabled_modules_whitelist'] = array(
    '#markup' => t('Currently these modules will be forcefully checked even when they are disabled: %modules', array('%modules' => $modules)),
  );

  // XMLRPC settings.
  $form['prod_check_xmlrpc'] = array(
    '#type' => 'fieldset',
    '#title' => t('Production monitor integration.'),
    '#description' => t('You can set up integration with the Production monitor module here.'),
    '#collapsible' => FALSE,
  );
  $form['prod_check_xmlrpc']['prod_check_enable_xmlrpc'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable XMLRPC API'),
    '#default_value' => variable_get('prod_check_enable_xmlrpc', 0),
    '#description' => t('Tick this box if you would like to the module to open up the XMLRPC api so that it can be queried externally to supply information to a base site for monitoring purposes.'),
    '#ajax' => array(
      'callback' => 'prod_check_enable_xmlrpc',
      'wrapper' => 'prod-check-xmlrpc',
      'effect' => 'fade',
    ),
    '#required' => FALSE,
  );
  // The #value here is necessary for the markup field to be rendered :-(
  $form['prod_check_xmlrpc']['xmlrpc'] = array(
    '#type' => 'markup',
    '#prefix' => '<div id="prod-check-xmlrpc">',
    '#suffix' => '</div>',
  );
  // Only show when the checkbox above is selected.
  if (!isset($form_state['values']['prod_check_enable_xmlrpc'])) {
    $form_state['values']['prod_check_enable_xmlrpc'] = variable_get('prod_check_enable_xmlrpc', 0);
  }
  if ($form_state['values']['prod_check_enable_xmlrpc']) {
    $form['prod_check_xmlrpc']['xmlrpc']['prod_check_xmlrpc_key'] = array(
      '#type' => 'textfield',
      '#title' => t('API key'),
      '#default_value' => variable_get('prod_check_xmlrpc_key', prod_check_generate_key()),
      '#maxlength' => 128,
      '#size' => 60,
      '#description' => t('Enter a key here to ensure secure transfer of data over the API. Use a mixture of alphanumeric and special characters for increased security.'),
      '#required' => FALSE,
    );
    $form['prod_check_xmlrpc']['xmlrpc']['prod_check_module_list_day'] = array(
      '#type' => 'select',
      '#title' => t('Report module list every'),
      '#options' => array(t('Sunday'), t('Monday'), t('Tuesday'), t('Wednesday'), t('Thursday'), t('Friday'), t('Saturday')),
      '#default_value' => variable_get('prod_check_module_list_day', 0),
      '#description' => t('Defines which day the module list will be fetchable by Production monitor for an update status check.'),
      '#required' => FALSE,
    );
    $form['prod_check_xmlrpc']['xmlrpc']['prod_check_module_list_time'] = array(
      '#type' => 'textfield',
      '#title' => t('at this time'),
      '#default_value' => variable_get('prod_check_module_list_time', '03:00'),
      '#maxlength' => 5,
      '#size' => 5,
      '#description' => t('Defines what time (HH:MM) the module list will be fetchable by Production monitor for an update status check.'),
      '#required' => FALSE,
    );
    // See http://drupal.org/node/1058896#comment-5594076 .
    if (variable_get('prod_check_module_list_lastrun', 0) != -1) {
      $form['prod_check_xmlrpc']['xmlrpc']['reset'] = array(
        '#prefix' => '<div class="clear">',
        '#type' => 'submit',
        '#value' => t('Force immediate module list reporting'),
        '#postfix' => '</div>',
      );
    }
    else {
      $form['prod_check_xmlrpc']['xmlrpc']['reset'] = array(
        '#markup' => '<div class="description clear">' . t('Production monitor will fetch the module list on next cron run or when manually invoked for this site!') . '</div>',
      );
    }
  }

  // Nagios settings.
  if (module_exists('nagios')) {
    $form['prod_check_nagios'] = array(
      '#type' => 'fieldset',
      '#title' => t('Nagios integration.'),
      '#description' => t('You can set up integration with the !link module here.', prod_check_link_array('Nagios', 'http://drupal.org/project/nagios')),
      '#collapsible' => FALSE,
    );
    $form['prod_check_nagios']['prod_check_enable_nagios'] = array(
      '#type' => 'checkbox',
      '#title' =>   t('Enable Nagios integration'),
      '#description' => t('Tick this box if you want to enable integration with Nagios. The !link module is required for this to function.', array('!link' => l(t('Nagios'), 'http://drupal.org/project/nagios', array('attributes' => array('title' => t('Nagios')))))),
      '#default_value' => variable_get('prod_check_enable_nagios', 0),
      '#ajax' => array(
        'callback' => 'prod_check_enable_nagios',
        'wrapper' => 'prod-check-nagios',
        'effect' => 'fade',
      ),
      '#required' => FALSE,
    );

    // The #value here is necessary for the markup field to be rendered :-(
    $form['prod_check_nagios']['nagios'] = array(
      '#type' => 'markup',
      '#prefix' => '<div id="prod-check-nagios">',
      '#suffix' => '</div>',
    );
    // Only show when the checkbox above is selected.
    if (!isset($form_state['values']['prod_check_enable_nagios'])) {
      $form_state['values']['prod_check_enable_nagios'] = variable_get('prod_check_enable_nagios', 0);
    }
    // TODO: find a way to detect when this is rendered so we can adjust the
    // prod-check.js and apply equalheights/width
    if ($form_state['values']['prod_check_enable_nagios']) {
      $form['prod_check_nagios']['nagios']['settings'] = _prod_check_functions_as_form();
      $options = variable_get('prod_check_nagios_checks', array());
      if (!empty($options)) {
        // Just to increase readability of the source here.
        $monitor_settings = &$form['prod_check_nagios']['nagios']['settings']['prod_check_settings']['monitor_settings'];
        // Set default values to last saved state
        foreach (element_children($monitor_settings) as $set) {
          if (isset($options[$set])) {
            $monitor_settings[$set]['#default_value'] = $options[$set];
          }
          else {
            // No settings available, so uncheck all.
            $monitor_settings[$set]['#default_value'] = array();
          }
        }
      }

      $form['prod_check_nagios']['nagios']['settings']['prod_check_nagios_unique'] = array(
        '#type' => 'select',
        '#title' => t('When Nagios unique ID not recieved'),
        '#description' => t('Select what should happen when the Nagios unique ID is not recieved by the nagios page.'),
        '#options' => array(
          'default' => t('default Nagios module behavior'),
          '404' => t('throw a 404 error'),
          'home' => t('redirect to homepege'),
        ),
        '#default_value' => variable_get('prod_check_nagios_unique', 'default'),
        '#required' => FALSE,
      );
      $form['prod_check_nagios']['nagios']['settings']['prod_check_nagios_takeover'] = array(
        '#markup' => '<p>' . t(
          'If you want prod_check to take over the Nagios status page, you can edit the !settings and enter %callback. Only then will the setting above have any effect!',
          array(
            '!settings' => l(t('Nagios page callback'), 'admin/config/system/nagios'),
            '%callback' => 'prod_check_nagios_status_page',
          )
        ) . '</p>',
      );

      $form['prod_check_nagios']['nagios']['settings']['prod_check_nagios_verbose'] = array(
        '#type' => 'checkbox',
        '#title' => t('Show verbose status info'),
        '#description' => t('Tick this box if you want to see detailed information about every check. Useful for debugging or first setup, but <strong>not recommended for production use!</strong>'),
        '#default_value' => variable_get('prod_check_nagios_verbose', 0),
        '#required' => FALSE,
      );
    }
  }

  // Submit buttons.
  // Markup field for proper styling.
  $form['buttons'] = array(
    '#type' => 'markup',
    '#prefix' => '<div class="form-actions">',
    '#suffix' => '</div>',
  );
  $form['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );
  $form['buttons']['reset'] = array(
    '#type' => 'submit',
    '#value' => t('Reset to defaults'),
  );

  return $form;
}

/**
 * Parse the functions array and return a form fieldset with different sets of
 * checkboxes so it can be inserted 'as is' in another form array for rendering.
 * This is primlarily still here for integration with Nagios. Though not in use
 * now since Nagios would create far too much needless variables in my personal
 * opinion. It's left in for easy future integration with the
 * hook_nagios_settings().
 */
function _prod_check_functions_as_form($compatibility = 'all') {
  $form = array();

  $form['prod_check_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Configure what data you wish to monitor with <strong>Nagios</strong> for this site.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['prod_check_settings']['monitor_settings'] = array(
    '#type' => 'markup',
    '#prefix' => '<div id="prod-check-settings">',
    '#suffix' => '</div>',
    '#tree' => TRUE,
  );

  $i = 1;
  $functions = _prod_check_functions();
  if ($compatibility == 'all') {
    unset($functions['prod_mon']);
    unset($functions['perf_data']);
  }
  foreach ($functions as $set => $data) {
    $rest = $i % 2;
    $form['prod_check_settings']['monitor_settings'][$set] = array(
      '#type' => 'checkboxes',
      '#title' => t($data['title']),
      '#description' => t($data['description']),
      '#options' => $data['functions'],
      '#default_value' => array_keys($data['functions']),
      '#prefix' => '<div class="prod-check-settings ' . (($rest) ? 'odd' : 'even') . '">',
      '#suffix' => '</div>',
    );
    $i++;
  }

  return $form;
}

/**
 * Callback to add xmlrpc settings.
 */
function prod_check_enable_xmlrpc($form, &$form_state) {
  return $form['prod_check_xmlrpc']['xmlrpc'];
}

/**
 * Callback to add nagios settings.
 */
function prod_check_enable_nagios($form, &$form_state) {
  return $form['prod_check_nagios']['nagios'];
}

/**
 * Validation for settings form.
 */
function prod_check_settings_form_validate($form, &$form_state) {
  // Had to add CSS again here since it was lost on form errors. Weird, doesn't
  // seem logical...
  $base = drupal_get_path('module', 'prod_check');
  drupal_add_css($base . '/css/prod-check.css');
  drupal_add_js($base . '/js/jquery.equalheights.js');
  drupal_add_js($base . '/js/jquery.maskedinput.min.js');
  drupal_add_js($base . '/js/prod-check.js');

  if (module_exists('dblog')) {
    if (!is_numeric($form_state['values']['prod_check_dblog_php_threshold'])) {
      form_set_error('prod_check_dblog_php_threshold', t('The PHP error threshold should be numeric!'));
    }
  }

  if ($form_state['values']['prod_check_enable_xmlrpc']) {
    if (empty($form_state['values']['prod_check_xmlrpc_key'])) {
      form_set_error('prod_check_xmlrpc_key', t('When enabling the XPLRPC API, you <strong>must</strong> enter an API key!'));
    }
  }

  if (!empty($form_state['values']['prod_check_module_list_time'])) {
    // This check in case JavaScript is not enabled / malfunctioning.
    if (strpos($form_state['values']['prod_check_module_list_time'], ':') != 2) {
      form_set_error('prod_check_module_list_time', t('Time must be input in 24 hour format: HH:MM!'));
    }
    else {
      $time = explode(':', $form_state['values']['prod_check_module_list_time']);
      if (intval($time[0]) > 23) {
        form_set_error('prod_check_module_list_time', t('Hours must range from 00 (midnight) to 23!'));
      }
      if (intval($time[1]) > 59) {
        form_set_error('prod_check_module_list_time', t('Minutes must range from 00 to 59!'));
      }
    }
  }

  if (!is_numeric($form_state['values']['prod_check_apc_expunge'])) {
    form_set_error('prod_check_apc_expunge', t('APC/OPcache Cache full count threshold should be numeric!'));
  }

  if (isset($form_state['values']['prod_check_enable_nagios']) && $form_state['values']['prod_check_enable_nagios']) {
    $checks = array();
    foreach ($form_state['values']['monitor_settings'] as $set => $data) {
      foreach ($data as $check => $value) {
        if ($value) {
          $checks[$set][] = $value;
        }
      }
    }
    if (empty($checks)) {
      form_set_error('monitor_settings', t('When enabling Nagios support, you <strong>must</strong> tick at least one of the checkboxes!'));
    }
  }
}

/**
 * Submit for settings form.
 *
 * TODO: is it better to split all of these in separate functions and use
 * buttons with the #submit property? The latter is better readability wise I
 * guess.
 */
function prod_check_settings_form_submit($form, &$form_state) {
  switch ($form_state['values']['op']) {
    case t('Force immediate module list reporting'):
      variable_set('prod_check_module_list_lastrun', -1);
      break;
    case t('Save configuration'):
      variable_set('prod_check_sitemail', $form_state['values']['prod_check_sitemail']);
      // PHP errors.
      if (module_exists('dblog')) {
        variable_set('prod_check_dblog_php', $form_state['values']['prod_check_dblog_php']);
        variable_set('prod_check_dblog_php_threshold', $form_state['values']['prod_check_dblog_php_threshold']);
      }
      // APC/OPcache.
      variable_set('prod_check_apc_expunge', $form_state['values']['prod_check_apc_expunge']);
      variable_set('prod_check_apcuser', $form_state['values']['prod_check_apcuser']);
      if (!empty($form_state['values']['prod_check_apcpass'])) {
        variable_set('prod_check_apcpass', $form_state['values']['prod_check_apcpass']);
      }
      else {
        variable_set('prod_check_apcpass', 'password');
      }
      variable_set('prod_check_exclude_disabled_modules', $form_state['values']['prod_check_exclude_disabled_modules']);
      if ($form_state['values']['prod_check_enable_xmlrpc']) {
        // Enable.
        variable_set('prod_check_enable_xmlrpc', $form_state['values']['prod_check_enable_xmlrpc']);
        variable_set('prod_check_xmlrpc_key', $form_state['values']['prod_check_xmlrpc_key']);
        variable_set('prod_check_module_list_day', $form_state['values']['prod_check_module_list_day']);
        variable_set('prod_check_module_list_time', $form_state['values']['prod_check_module_list_time']);
      }
      else {
        // Disable.
        variable_set('prod_check_enable_xmlrpc', 0);
      }
      // This is why we didn't use a system_settings_form().
      if (isset($form_state['values']['prod_check_enable_nagios']) && $form_state['values']['prod_check_enable_nagios']) {
        $checks = array();
        foreach ($form_state['values']['monitor_settings'] as $set => $data) {
          foreach ($data as $check => $value) {
            if ($value) {
              $checks[$set][] = $value;
            }
          }
        }
        // Enable.
        variable_set('prod_check_enable_nagios', $form_state['values']['prod_check_enable_nagios']);
        variable_set('prod_check_nagios_checks', $checks);
        variable_set('prod_check_nagios_unique', $form_state['values']['prod_check_nagios_unique']);
        variable_set('prod_check_nagios_verbose', $form_state['values']['prod_check_nagios_verbose']);
      }
      else {
        // Disable.
        variable_set('prod_check_enable_nagios', 0);
      }
      drupal_set_message(t('The configuration options have been saved.'));
      break;
    case t('Reset to defaults'):
      // This beats multiple variable_del() calls.
      // Don't delete prod_check_module_list_lastrun!
      // DELETE FROM {variable} WHERE name LIKE "prod_check\_%" AND name <> "prod_check_module_list_lastrun"'
      db_delete('variable')
        ->condition('name', 'prod_check\_%', 'LIKE')
        ->condition('name', 'prod_check_module_list_lastrun', '<>')
        ->execute();
      cache_clear_all('variables', 'cache_bootstrap');
      drupal_set_message(t('The configuration options have been reset to their default values.'));
      break;
  }
}

/**
 * Setup site for production mode.
 */
function prod_check_prod_mode_form() {
  drupal_set_title(t('Switch to production mode'));

  $form = array();

  // Put this in hook_help() first but some themes hide the help text. It's too
  // important to be hidden, so moved it here.
  $form['help'] = array(
    '#markup' => '<p>' . t('Submitting this form will switch this website to <em>production mode</em>. This means that various settings will be adjusted in order to fix most of the problems reported on the status page. <strong>Some modules will be disabled as well!</strong>') . '</p>',
  );

  $form['site_mail'] = array(
    '#type' => 'textfield',
    '#title' => t('Site e-mail address'),
    '#description' => t('This field is optional and will be used to setup the default e-mail address of this site. <strong>Currently set to %mail.</strong>', array('%mail' => variable_get('site_mail', '[not set]'))),
  );

  if (module_exists('webform')) {
    $form['webform_default_from_address'] = array(
      '#type' => 'textfield',
      '#title' => t('Webform default from e-mail address'),
      '#description' => t('This field is optional and will be used to setup the default from e-mail address for <em>Webform</em>. <strong>Currently set to %mail.</strong>', array('%mail' => variable_get('webform_default_from_address', '[not set]'))),
    );
  }

  if (module_exists('googleanalytics')) {
    $form['googleanalytics_account'] = array(
      '#type' => 'textfield',
      '#title' => t('Google Analytics Web Property ID'),
      '#description' => t('This field is optional and will be used to setup the <em>Google Analytics</em> account. <strong>Currently set to %account.</strong>', array('%account' => variable_get('googleanalytics_account', '[not set]'))),
    );
  }

  $form['block_cache'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable <em>Block cache</em>'),
    '#description' => t("If ticked, this will enable block caching. <strong>This can cause unwanted results if custom blocks don't handle caching well!</strong>"),
  );

  if (module_exists('dblog')) {
    $form['dblog'] = array(
      '#type' => 'checkbox',
      '#title' => t('Disable <em>Database logging</em>'),
      '#description' => t('If ticked, this will disable the <em>dblog</em> module wich could generate too much overhead on high traffic sites.'),
    );
  }

  $form['nagios'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable <em>Nagios</em>'),
    '#description' => t('If ticked, this will enable the <em>Nagios</em> monitoring module if it is present.'),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Enable production mode'),
  );

  return $form;
}

/**
 * Setup site for production mode: validation.
 */
function prod_check_prod_mode_form_validate($form, &$form_state) {
  $checks = array('site_mail', 'webform_default_from_address');

  foreach ($checks as $field) {
    if (!empty($form_state['values'][$field])) {
      if (!valid_email_address($form_state['values'][$field])) {
        form_set_error($field, t('The e-mail address %mail is not valid.', array('%mail' => $form_state['values'][$field])));
      }
    }
  }

  // Google analytics.
  if (!empty($form_state['values']['googleanalytics_account'])) {
    if (!preg_match('/^UA-\d{4,}-\d+$/', $form_state['values']['googleanalytics_account'])) {
      form_set_error('googleanalytics_account', t('A valid Google Analytics Web Property ID is case sensitive and formatted like UA-xxxxxxx-yy.'));
    }
  }
}

// TODO: add confirm form here? In the form of:
// The following actions will be performed: [...] Are you sure you want to
// continue?

/**
 * Setup site for production mode: submit.
 */
function prod_check_prod_mode_form_submit($form, &$form_state) {
  // Adjust settings.
  $variables = prod_check_prod_mode_settings($form_state['values']);
  drupal_set_message(t('The following settings have been changed: %variables.', array('%variables' => implode(', ', array_keys($variables)))));

  // Enable / disable modules.
  $modules = prod_check_prod_mode_modules($form_state['values']);
  if (!empty($modules['disable'])) {
    drupal_set_message(t('The following modules have been <strong>disabled</strong>: %modules.', array('%modules' => implode(', ', $modules['disable']))));
  }
  if (!empty($modules['enable'])) {
    drupal_set_message(t('The following modules have been <strong>enabled</strong>: %modules.', array('%modules' => implode(', ', $modules['enable']))));
  }

  $form_state['redirect'] = 'admin/reports/prod-check';
}

/**
 * Helper function to adjust settings. Also used by Drush.
 */
function prod_check_prod_mode_settings($options) {
  $variables = array(
    // Error messages to display.
    'error_level' => ERROR_REPORTING_HIDE,
    // Cache pages for anonymous users.
    'cache' => 1,
    // Aggregate and compress CSS files.
    'preprocess_css' => 1,
    // Aggregate JavaScript files.
    'preprocess_js' => 1,
  );

  // No page compression when running Varnish.
  if (!module_exists('varnish') && !module_exists('steroids')) {
    // Compress cached pages.
    $variables['page_compression'] = 1;
  }

  // Site e-mail address.
  if (isset($options['site_mail']) && !empty($options['site_mail'])) {
    $variables['site_mail'] = $options['site_mail'];
  }

  // Webform default from e-mail address.
  if (isset($options['webform_default_from_address']) && !empty($options['webform_default_from_address'])) {
    $variables['webform_default_from_address'] = $options['webform_default_from_address'];
  }

  // Google analytics account.
  if (isset($options['googleanalytics_account']) && !empty($options['googleanalytics_account'])) {
    $variables['googleanalytics_account'] = $options['googleanalytics_account'];
  }

  // Cache blocks.
  if (isset($options['block_cache']) && !empty($options['block_cache'])) {
    $variables['block_cache'] = 1;
  }

  // Set variables. Wanted to do this in one query, but that was impossible due
  // to the fact that it is possible a variable does not exist in the database
  // yet and still have a value. Damn that default value in variable_get()!
  foreach ($variables as $variable => $value) {
    variable_set($variable, $value);
  }

  // Clear caches like the system_performance_settings() form does.
  drupal_clear_css_cache();
  drupal_clear_js_cache();
  // Instead of calling system_clear_page_cache_submit()
  cache_clear_all('*', 'cache_page', TRUE);

  return $variables;
}

/**
 * Helper function to enable / disable modules. Also used by Drush.
 */
function prod_check_prod_mode_modules($options) {
  $modules['disable'] = array(
    'devel',
    'devel_generate',
    'devel_node_access',
    'devel_themer',
    'update',
  );

  if (isset($options['dblog']) && $options['dblog']) {
    $modules['disable'][] = 'dblog';
  }

  // We do this primarily to prepare feedback to the user. module_disable() will
  // do a module_exists() check as well but only provides feedback using
  // watchdog().
  foreach ($modules['disable'] as $id => $module) {
    if (!module_exists($module)) {
      unset($modules['disable'][$id]);
    }
  }

  if (!empty($modules['disable'])) {
    module_disable($modules['disable']);
  }

  $modules['enable'] = array();

  if ($options['nagios']) {
    $modules['enable'][] = 'nagios';
  }

  // We cannot check if a module is available on the file system. At least,
  // there is not a function in Drupal that I know of to do this and I could not
  // find one. Hence this approach, until there's a better way.
  if (!empty($modules['enable'])) {
    module_enable($modules['enable']);
    foreach($modules['enable'] as $id => $module) {
      if (!module_exists($module)) {
        unset($modules['enable'][$id]);
      }
    }
  }

  return $modules;
}

/**
 * Generate default key if none is present.
 */
function prod_check_generate_key($length = 25) {
  $chars = 'abcdefghijklmnopqrstuxyvwzABCDEFGHIJKLMNOPQRSTUXYVWZ+-*#&@!?';
  $size = strlen($chars);
  $key = '';
  for ($i = 0; $i < $length; $i++) {
    $key .= $chars[rand(0, $size - 1)];
  }

  return $key;
}

/**
 * Database status page.
 */
function prod_check_dbstatus() {
  // Get active connection.
  $pdo = Database::getConnection();
  // Get database driver.
  $db_type = $pdo->getAttribute(PDO::ATTR_DRIVER_NAME);

  $details = array(
    'status' => array(),
    'tables' => array(),
    'databases' => array(),
  );

  $add_js = FALSE;

  $title = '';
  $db = $db_type;
  switch($db_type) {
    case 'pgsql':
      // Set title & version.
      $server = db_query('SELECT version()')->fetchField();
      $title = t('Running @version', array('@version' => $server));
      // Get detailed status.
      $details = _prod_check_dbstatus_pgsql($details);
      break;
    case 'mysql':
      $db = 'MySQL';
      // Get detailed status.
      $details = _prod_check_dbstatus_mysql($details);
      // NO break here!
    default:
      // Set title & version.
      $server = $pdo->getAttribute(PDO::ATTR_SERVER_VERSION);
      $title = t('Running @db @version', array('@db' => $db, '@version' => $server));
      break;
  }

  // Get basic status.
  $status = '';
  try {
    $status = $pdo->getAttribute(PDO::ATTR_SERVER_INFO);
    if (is_array($status)) {
      $status = implode("<br />\n", $status);
    }
    else {
      $status = str_replace('  ', "<br />\n", $status);
    }
  } catch(Exception $e) {}

  // Get additional status.
  $additional = '';
  $attributes = array(
    'AUTOCOMMIT' => 'Auto commit',
    'PREFETCH' => 'Prefetch',
    'TIMEOUT' => 'Timeout',
    'ERRMODE' => 'Error mode',
    'CLIENT_VERSION' => 'Client version',
    'CONNECTION_STATUS' => 'Connection status',
    'CASE' => 'Case',
    'CURSOR_NAME' => 'Cursor name',
    'CURSOR' => 'Cursor',
    'ORACLE_NULLS' => 'Oracle nulls',
    'PERSISTENT' => 'Persistent',
    'STATEMENT_CLASS' => 'Statement class',
    'FETCH_CATALOG_NAMES' => 'Fatch catalog names',
    'FETCH_TABLE_NAMES' => 'Fetch table names',
    'STRINGIFY_FETCHES' => 'Stringify fetches',
    'MAX_COLUMN_LEN' => 'Max column length',
    'DEFAULT_FETCH_MODE' => 'Default fetch mode',
    'EMULATE_PREPARES' => 'Emulate prepares',
  );
  foreach ($attributes as $constant => $name) {
    try {
      $result = $pdo->getAttribute(constant("PDO::ATTR_$constant"));
      if (is_bool($result)) {
        $result = $result ? 'TRUE' : 'FALSE';
      }
      elseif (is_array($result) || is_object($result)) {
        $add_js = TRUE;
        include_once DRUPAL_ROOT . '/includes/utility.inc';

        $class = strtolower(str_replace('_', '-', $constant));

        $link = l(
          t('Show details'),
          'admin/reports/status/database',
          array(
            'attributes' => array(
              'class' => array('show-more'),
              'data-details' => $class
            )
          )
        );

        // Seemed a bit overkill to create a css file only for this display:none
        // thingy.
        $result = $link . '<pre class="' . $class . '" style="display:none;">' . drupal_var_export($result) . '</pre>';
      }
      $additional .= $name . ': ' . $result . "<br />\n";
    } catch (Exception $e) {}
  }
  $status = "$additional<br />\n$status";

  if ($add_js) {
    $base = drupal_get_path('module', 'prod_check');
    drupal_add_js($base . '/js/prod-check-database.js');
  }

  return theme('prod_check_dbstatus', array('title' => $title, 'status' => $status, 'details' => $details));
}

/**
 * Helper function to return MySQL detailed status info.
 */
function _prod_check_dbstatus_mysql($details) {
  $db_name = '';
  // Feels like there should be a better way of getting the current database
  // name.
  $db_setting = Database::getConnectionInfo();
  foreach($db_setting as $params) {
    if(isset($params['database'])) {
      // We get the first name we find.
      $db_name = $params['database'];
      break;
    }
  }

  // Get detailed status.
  $rows = array();
  try {
    $result = db_query('SHOW STATUS');
    foreach ($result as $row) {
      $rows[] = array($row->Variable_name, $row->Value);
    }
  } catch (Exception $e) {}
  if ($rows) {
    $details['status'] = array(
      'title' => t('Detailed status'),
      'header' => array(
        t('Variable'),
        t('Value'),
      ),
      'rows' => $rows,
    );
  }

  // Get all tables.
  $rows = array();
  try {
    // We cannot use the standard db_query with arguments here as the argument
    // should NOT be enclosed in quotes.
    $result = db_query(sprintf('SHOW TABLES FROM %s', $db_name));
    $property = 'Tables_in_' . $db_name;
    foreach ($result as $row) {
      $rows[] = array($row->$property);
    }
  } catch (Exception $e) {}
  if ($rows) {
    $details['tables'] = array(
      'title' => t('Tables for active database %name', array('%name' => $db_name)),
      'header' => array(
        t('Table'),
      ),
      'rows' => $rows,
    );
  }

  // Get all databases.
  $rows = array();
  try {
    $result = db_query('SHOW DATABASES');
    foreach ($result as $row) {
      $rows[] = array($row->Database);
    }
  } catch (Exception $e) {}
  if ($rows) {
    $details['databases'] = array(
      'title' => t('Available databases'),
      'header' => array(
        t('Database'),
      ),
      'rows' => $rows,
    );
  }

  return $details;
}

/**
 * Helper function to return PostgreSQL status info.
 *
 * Useful links for possible expansion:
 *  http://www.php.net/manual/en/book.pgsql.php
 *  http://www.alberton.info/postgresql_meta_info.html#.UbXmAFQW3eU
 *  http://www.postgresql.org/docs/devel/static/catalog-pg-statistic.html
 *  http://www.postgresql.org/docs/9.0/static/functions-info.html
 *  http://www.postgresql.org/docs/9.0/static/functions-admin.html
 */
function _prod_check_dbstatus_pgsql($db_name, $details) {
  // Get detailed status.
  $rows = array();
  try {
    // See http://www.postgresql.org/docs/9.0/static/view-pg-settings.html
    $result = db_query('SELECT * FROM pg_settings');
    foreach ($result as $row) {
    /* TODO: add some more detail here? This is available:

         Column   | Type | Modifiers | Storage  | Description
      ------------+------+-----------+----------+-------------
       name       | text |           | extended |
       setting    | text |           | extended |
       unit       | text |           | extended |
       category   | text |           | extended |
       short_desc | text |           | extended |
       extra_desc | text |           | extended |
       context    | text |           | extended |
       vartype    | text |           | extended |
       source     | text |           | extended |
       min_val    | text |           | extended |
       max_val    | text |           | extended | */
      $rows[] = array($row->name, $row->setting);
    }
  } catch (Exception $e) {}
  if ($rows) {
    $details['status'] = array(
      'title' => t('Detailed status'),
      'header' => array(
        t('Name'),
        t('Setting'),
      ),
      'rows' => $rows,
    );
  }

  // Get all tables.
  $rows = array();
  try {
    // See http://www.postgresql.org/docs/9.0/static/catalog-pg-class.html
    // relclass: r = ordinary table, i = index, S = sequence, v = view, c = composite type, t = TOAST table
    $result = db_query("SELECT relname FROM pg_class WHERE relname !~ '^(pg_|sql_)' AND relkind = 'r'");
    foreach ($result as $row) {
      $rows[] = array($row->relname);
    }
  } catch (Exception $e) {}
  if ($rows) {
    $details['tables'] = array(
      'title' => t('Tables for active database %name', array('%name' => $db_name)),
      'header' => array(
        t('Table'),
      ),
      'rows' => $rows,
    );
  }

  // Get all databases.
  $rows = array();
  try {
    $result = db_query('SELECT datname FROM pg_database');
    foreach ($result as $row) {
      $rows[] = array($row->datname);
    }
  } catch (Exception $e) {}
  if ($rows) {
    $details['databases'] = array(
      'title' => t('Available databases'),
      'header' => array(
        t('Database'),
      ),
      'rows' => $rows,
    );
  }

  return $details;
}

/**
 * Integration of the APC status page.
 */
function prod_check_apc_opc() {
  // APC.
  if (function_exists('apc_cache_info')) {
    define('ADMIN_USERNAME', variable_get('prod_check_apcuser', 'apc'));
    define('ADMIN_PASSWORD', variable_get('prod_check_apcpass', 'password'));
    include(drupal_get_path('module', 'prod_check') . '/includes/prod_check.apc.inc');
    exit;
  }
  // OPcache.
  elseif (function_exists('opcache_get_status')) {
    include(drupal_get_path('module', 'prod_check') . '/includes/prod_check.opcache.inc');
    exit;
  }
  else {
    return t('APC nor OPcache is installed on this webserver!');
  }
}

/**
 * Integration of the Memcache status page.
 */
function prod_check_memcache() {
  // Memcache module defaults to 127.0.0.1:11211
  $memcache_servers = variable_get('memcache_servers', array('127.0.0.1:11211' => 'default'));

  global $MEMCACHE_SERVERS;
  $MEMCACHE_SERVERS = array_keys($memcache_servers);
  include(drupal_get_path('module', 'prod_check') . '/includes/prod_check.memcache.inc');

  exit;
}
