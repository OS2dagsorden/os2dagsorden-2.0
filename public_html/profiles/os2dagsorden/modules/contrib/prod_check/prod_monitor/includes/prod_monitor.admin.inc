<?php

/**
 * Build status page.
 */
function prod_monitor_status($id) {
  $site = _prod_monitor_get_site($id, 'all');

  if (!$site) {
    // See https://api.drupal.org/api/drupal/includes!common.inc/function/drupal_not_found/7
    return MENU_NOT_FOUND;
  }


  drupal_set_title(t('Production monitor status for') . ' ' . _prod_monitor_sanitize_url($site['url']));

  $functions = $site['settings']['functions'];
  $nodata = t('No data recieved yet.');

  $output = '';

  // General status block
  $modules = _prod_monitor_get_site_modules($id);
  if(!empty($modules) && isset($site['data']['prod_mon'])) {
    $prod_mon = $site['data']['prod_mon'];
    $output .= _prod_monitor_status_general($prod_mon, $modules);
  }
  unset($site['data']['prod_mon']);
  // Performance data not needed here.
  unset($site['data']['perf_data']);

  // Display results of all checks.
  foreach ($functions as $set => $data) {
    if (isset($site['data'][$set])) {
      $output .= '<h2>' . t($data['title']) . '</h2>' . "\n";
      $output .= '<div class="description"><p><em>' . t($data['description']) . '</em></p></div>'."\n";
      if (!empty($site['data'][$set])) {
        $output .= theme('prod_monitor_status_report', array('requirements' => $site['data'][$set]));
      }
      else  {
        $output .= '<p>' . $nodata . '</p><p>&nbsp;</p>';
      }
    }
  }

  if (empty($output)) {
    $output = '<p>' . $nodata . '</p><p>&nbsp;</p>';
  }

  // TODO: do not use drupal_render but change this so that hook_page_alter can
  // be used as well.
  $form = drupal_get_form('_prod_monitor_update_data_form', $id, $site);
  $output .= drupal_render($form);

  return $output;
}

/**
 * Helper function to provide general status block on status overview page
 */
function _prod_monitor_status_general($prod_mon, $modules) {
  $updates = _prod_monitor_generate_updates_link($modules['id'], $modules['updates']);

  $output = '<h2>' . t('Overall status') . '</h2>' . "\n";
  $rows = array(
    array(
      array('data' => t('Drupal core version'), 'header' => TRUE),
      $modules['projects']['drupal']['info']['version'],
    ),
  );

  if (isset($prod_mon['prod_check_cron_last'])) {
    $rows[] = array(
      array('data' => t('Last cron run'), 'header' => TRUE),
      format_date($prod_mon['prod_check_cron_last'], 'large'),
    );
  }

  // Add dbconnect check info if configured.
  if (isset($prod_mon['prod_check_dbconnect'])) {
    $dbconnect = $prod_mon['prod_check_dbconnect'];
    $class = array();
    $title = t('DB connection status');
    if (stripos($dbconnect, '200') === FALSE) {
      $class = array('error');
      $title = '<strong>' . $title . '</strong>';
      $dbconnect = '<strong>' . $dbconnect . '</strong>';
    }

    $rows[] = array(
      'data' => array(
        array(
          'data' => $title, 'header' => TRUE,
          'class' => $class,
        ),
        array(
          'data' => $dbconnect,
          'class' => $class,
        ),
      ),
      'class' => $class,
    );
  }

  $rows[] = array(
    array('data' => t('Update status'), 'header' => TRUE),
    $updates,
  );
  $output .= theme('table', array('prod_monitor_id' => 'status_general', 'header' => array(), 'rows' => $rows));

  return $output;
}

/**
 * Helper function to generate update status link for tables
 */
function _prod_monitor_generate_updates_link($id, $update_status) {
  $updates = t('Unknown');
  if ($update_status > 0) {
    switch ($update_status) {
      case 1:
        $class = '';
        $title = t('None');
        break;
      case 2:
        $class = 'warning';
        $title = t('Available');
        break;
      case 3:
        $class = 'error';
        $title = t('Security risk!');
        break;
    }
    $updates = array('data' => '<strong>' . l($title, 'admin/reports/prod-monitor/site/' . $id . '/view/updates', array('attributes' => array('title' => $title, 'class' => $class))) . '</strong>', 'class' => $class);
  }

  return $updates;
}

/**
 * Callback for performance page.
 */
function prod_monitor_performance($data) {
  drupal_set_title(t('Performance logs for') . ' ' . _prod_monitor_get_url($data['id']));

  // TODO: add 'get stats now' button.
  //$site = _prod_monitor_get_site($id, 'all');

  return array(
    'performance_data' => array(
      '#data' => $data['data'],
      '#theme' => 'prod_monitor_performance',
    ),
  );
}

/**
 * Callback for module update status page
 */
function prod_monitor_updates($modules) {
  $output = '';

  $id = $modules['id'];

  drupal_set_title(t('Module update status for') . ' ' . _prod_monitor_get_url($id));

  // Only show a report if the available updates have been fetched!
  if (!empty($modules) && !empty($modules['projects']) && !empty($modules['available'])) {
    module_load_include('inc', 'prod_monitor', 'includes/prod_monitor.update');
    $data = _prod_monitor_calculate_project_data($id, $modules['projects'], $modules['available']);
    $output .= theme('prod_monitor_update_report', array('id' => $id, 'last' => $modules['lastupdate'], 'data' => $data));
  }
  // No data, so report this to the user and instruct him/her on how to retrieve it.
  else {
    $destination = drupal_get_destination();
    $output .= theme('prod_monitor_update_report',
      array(
        'id' => $id,
        'last' => $modules['lastupdate'],
        'data' => t(
                    'No information is available about potential new releases for currently installed modules and themes. To check for updates, you may need to !cron or you can !check. Please note that checking for available updates can take a long time, so please be patient.',
                    array(
                      '!cron' => l(t('run cron'), 'admin/reports/status/run-cron', array('attributes' => array('title' => t('run cron')), 'query' => $destination)),
                      '!check' => l(t('check manually'), 'admin/reports/prod-monitor/site/' . $id . '/update-check', array('attributes' => array('title' => t('check manually')))),
                    )
                  )
      )
    );
  }

  return $output;
}

/**
 * Callback to refresh the module update status page
 */
function prod_monitor_updates_check($id) {
  // Get module data.
  $modules = _prod_monitor_get_site_modules($id);
  if (!empty($modules) && !empty($modules['projects'])) {
    module_load_include('inc', 'prod_monitor', 'includes/prod_monitor.update');
    // ALWAYS do a full refresh.
    $result = _prod_monitor_update_refresh($id, $modules['projects'], $modules['sitekey']);
    if (!empty($result)) {
      drupal_set_message(t('Information about all available new releases and updates sucessfully fetched.'));
    }
    else {
      drupal_set_message(t('Failed to fetch all available new releases and updates!'), 'error');
    }
  }
  else {
    drupal_set_message(t('No module data available: cannot check for updates!'), 'error');
  }
  drupal_goto('admin/reports/prod-monitor/site/' . $id . '/view/updates');
}

/**
 * Build settings form.
 */
function prod_monitor_overview_form($form, &$form_state, $edit = FALSE) {
  drupal_set_title(t('Production monitor settings'));
  $base = drupal_get_path('module', 'prod_monitor');
  drupal_add_css($base . '/css/prod-monitor.css', 'file');
  drupal_add_js($base . '/js/jquery.equalheights.js', 'file');
  drupal_add_js($base . '/js/prod-monitor.js', 'file');

  $form = array();

  $collapsed = FALSE;

  if (!$edit) {
    // Button to initiate our fetch all batcher.
    $form['fetch_all_submit'] = array(
      '#weight' => -100,
      '#type' => 'submit',
      '#value' => t('Fetch all'),
      '#submit' => array('prod_monitor_fetch_all_submit'),
      '#limit_validation_errors' => array(),
    );

    // Add new site situation.
    $sites = _prod_monitor_get_sites();
    $dbconnect_path = $api_key = $url = '';
    $options = array();
    $button = t('Get settings');
    if (!empty($sites)) {
      $form['table'] = array(
        '#markup' => _prod_monitor_overview_form_table($sites),
      );
      $collapsed = TRUE;
    }
    if (!empty($form_state['storage']['get_settings'])) {
      // Second step of add new site situation.
      $api_key = $form_state['values']['api_key'];
      $dbconnect_path = $form_state['values']['dbconnect_path'];
      $url = $form_state['values']['url'];
      $button = t('Add site');
      $collapsed = FALSE;
      $msg = TRUE;
    }
  }
  else {
    // Edit site situation.
    $site = _prod_monitor_get_site($edit);
    $url = $site['url'];
    // Allow user to correct faulty url.
    if (isset($form_state['values']['url']) && $url != $form_state['values']['url']) {
      $url = $form_state['values']['url'];
    }
    drupal_set_title(t('Production monitor settings for !url', array('!url' => _prod_monitor_sanitize_url($url))));
    $api_key = $site['settings']['api_key'];
    $dbconnect_path = $site['settings']['dbconnect_path'];
    $options = $site['settings']['checks'];
    if (isset($site['settings']['checks']['perf_data'])) {
      $perf_enabled = $site['settings']['checks']['perf_data'];
    }
    $button = t('Save site');
    $msg = FALSE;
  }

  // Add/edit form.
  $form['sites'] = array(
    '#type' => 'fieldset',
    '#title' => t('Add a site to monitor'),
    '#description' => t('You can add sites here that you wish to monitor.'),
    '#collapsible' => TRUE,
    '#collapsed' => $collapsed,
  );

  $form['sites']['url'] = array(
    '#type' => 'textfield',
    '#title' => t('Website URL'),
    '#default_value' => $url,
    '#description' => t('Enter the <strong>full</strong> url of the website to be monitored. This site must be running the <em>Production check</em> module. This <strong>must</strong> include a protocol like <em>http://</em> or <em>https://</em>!'),
    '#size' => 60,
    '#required' => TRUE,
  );

  $form['sites']['api_key'] = array(
    '#type' => 'textfield',
    '#title' => t("The website's API key"),
    '#default_value' => $api_key,
    '#description' => t('Enter the API key you have configured for this site using the <em>Production check</em> module.'),
    '#size' => 60,
    '#maxlength' => 128,
    '#required' => TRUE,
  );

  $form['sites']['dbconnect_path'] = array(
    '#type' => 'textfield',
    '#title' => t('DB connect check script'),
    '#default_value' => $dbconnect_path,
    '#description' => t('Enter the relative path, starting from the Drupal root, to the <em>prod_check.dbconnect.php</em> on the remote site. This wil usually be something like sites/all/modules/contrib/prod_check/prod_check.dbconnect.php . <strong>Leave empty if you do not want do enable this check!</strong>'),
    '#size' => 60,
    '#maxlength' => 512,
  );

  // Only show on second step of add form or when editing.
  if (!empty($form_state['storage']['get_settings']) || $edit) {
    // Get the settings from the remote site. We always do this when the form is
    // displayed and don't store this locally. Logic here is that you won't be
    // editing these settings all that much.
    $functions = _prod_monitor_retrieve_functions($url, $api_key, $msg);
    // Parse the array of functions into a form.
    if ($functions) {
      // Save data to store in DB on submit.
      $form_state['storage']['functions'] = $functions;
      // Parse functions into form data
      $form['sites']['prod_check_settings'] = array(
        '#type' => 'fieldset',
        '#title' => t('Configure what data you wish to monitor for this site.'),
        '#collapsible' => TRUE,
        '#collapsed' => FALSE,
      );

      $form['sites']['prod_check_settings']['monitor_settings'] = array(
        '#type' => 'markup',
        '#prefix' => '<div id="prod-check-settings">',
        '#suffix' => '</div>',
        '#tree' => TRUE,
      );

      // Single out perf_data if present to treat differently.
      if (isset($functions['perf_data'])) {
        $performance = $functions['perf_data'];
        unset($functions['perf_data']);
      }

      $i = 1;
      foreach ($functions as $set => $data) {
        $rest = $i%2;
        $form['sites']['prod_check_settings']['monitor_settings'][$set] = array(
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
      if ($edit) {
        // Just to increase readability of the source code here.
        $monitor_settings = &$form['sites']['prod_check_settings']['monitor_settings'];
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

      // Add performance logging section.
      if (!empty($performance['functions'])) {
        $form['sites']['prod_check_performance'] = array(
          '#type' => 'fieldset',
          '#title' => t("Configure which module's performance data you wish to log."),
          '#collapsible' => TRUE,
          '#collapsed' => FALSE,
        );
        $perf_options = array();
        foreach ($performance['functions'] as $function => $title) {
          $perf_options[$function] = t($title);
        }
        $form['sites']['prod_check_performance']['performance'] = array(
          '#type' => 'checkboxes',
          '#options' => $perf_options,
          '#default_value' => array(),
          '#description' => t('Indicate which performance data you want to store. This data can be provided by the modules listed here.'),
        );
        if ($edit && isset($perf_enabled)) {
          $form['sites']['prod_check_performance']['performance']['#default_value'] = $perf_enabled;
        }
      }

      $form['sites']['fetch'] = array(
        '#type' => 'checkbox',
        '#title' => t('Fetch data immediately'),
        '#default_value' => 0,
        '#description' => t('Will attempt to fetch the data immediately when the site has been added.'),
      );
    }
    else {
      // Error, so show retry button.
      $button = t('Retry');
    }
  }

  if ($edit) {
    $form['site_id'] = array(
      '#type' => 'value',
      '#value' => $edit,
    );
  }

  $form['sites']['submit'] = array(
    '#type' => 'submit',
    '#value' => $button,
  );

  return $form;
}

/**
 * Helper function to theme all sites into a table
 */
function _prod_monitor_overview_form_table($sites) {
  $home = array('destination' => 'admin/reports/prod-monitor');

  // Set headers.
  $headers = array(
    t('URL'),
    t('Data'),
    t('Status'),
    t('Updates'),
    t('Date added'),
    t('Last update'),
    array('data' => t('Actions'), 'colspan' => 5),
  );

  // Compose rows.
  $rows = array();
  foreach ($sites as $id => $site_info) {
    // Set view and flush links.
    $view = t('View');
    $flush = t('Flush');
    if ($site_info['data']) {
      $view = l(t('View'), 'admin/reports/prod-monitor/site/' . $id, array('attributes' => array('title' => t('View'))));
      $flush = l(t('Flush'), 'admin/reports/prod-monitor/site/' . $id . '/flush', array('attributes' => array('title' => t('Flush'))));
    }

    $update_status = _prod_monitor_get_update_status($id);
    $updates = _prod_monitor_generate_updates_link($id, $update_status);

    if (!empty($site_info['status'])) {
      $title = t(ucwords($site_info['status']));
      $status = array('data' => '<strong>' . l($title, 'admin/reports/prod-monitor/site/' . $id, array('attributes' => array('title' => $title, 'class' => $site_info['status']))) . '</strong>', 'class' => array($site_info['status']));
    }
    else {
      $status = '';
    }

    // Actually compose the rows.
    $row = array(
      'data' => array(
        _prod_monitor_sanitize_url($site_info['url']),
        (!$site_info['data']) ? t('Not yet retrieved.') : t('Stored.'),
        $status,
        $updates,
        $site_info['added'],
        (!$site_info['lastupdate']) ? t('Not yet updated.') : $site_info['lastupdate'],
        /* Compose links. */
        $view,
        l(t('Edit'), 'admin/reports/prod-monitor/site/' . $id . '/edit', array('query' => $home, 'attributes' => array('title' => t('Edit')))),
        l(t('Fetch data'), 'admin/reports/prod-monitor/site/' . $id . '/fetch', array('attributes' => array('title' => t('Fetch & View')))),
        $flush,
        l(t('Delete'), 'admin/reports/prod-monitor/site/' . $id . '/delete', array('attributes' => array('title' => t('Delete')))),
      ),
      'class' => array($site_info['status']),
    );
    $rows[] = $row;
  }

  return theme('table', array('prod_monitor_id' => 'overview_form', 'header' => $headers, 'rows' => $rows));
}

/**
 * Validation function
 */
function prod_monitor_overview_form_validate($form, &$form_state) {
  if (!preg_match('/^https?:\/\/.*/i', $form_state['values']['url'])) {
    form_set_error('url', t('The url must start with a valid protocol: either http:// or https://'));
  }
}

/**
 * Submit function
 */
function prod_monitor_overview_form_submit($form, &$form_state) {
  switch ($form_state['values']['op']) {
    case t('Get settings'):
    case t('Retry'):
        // Make sure the storage is not empty so we go to step 2
        $form_state['storage']['get_settings'] = TRUE;
        $form_state['rebuild'] = TRUE;
      break;

    case t('Add site'):
    case t('Save site'):
      // Prevent from ending on step 2 again.
      unset($form_state['storage']['get_settings']);
      $site = new stdClass();

      // Edit situation, so force an update.
      if (isset($form_state['values']['site_id']) && is_numeric($form_state['values']['site_id'])) {
        $update = array('id');
        $site->id = $form_state['values']['site_id'];
      }
      else {
        // Add situation, insert.
        $update = array();
        $site->added = time();
      }

      $site->url = $form_state['values']['url'];

      // Get enabled checks.
      $checks = array();
      foreach ($form_state['values']['monitor_settings'] as $set => $data) {
        foreach ($data as $check => $value) {
          if ($value) {
            $checks[$set][] = $value;
          }
        }
      }

      // Get enabled performance logs.
      if (!empty($form_state['values']['performance'])) {
        $checks['perf_data'] = array();
        foreach ($form_state['values']['performance'] as $value) {
          if ($value) {
            $checks['perf_data'][] = $value;
          }
        }
      }

      // Prepare settings data.
      $site->settings = serialize(
        array(
          'api_key' => $form_state['values']['api_key'],
          // Trim spaces and / from left and right side.
          'dbconnect_path' => trim($form_state['values']['dbconnect_path'], ' /'),
          'functions' => $form_state['storage']['functions'],
          'checks' => $checks,
        )
      );

      $result = drupal_write_record('prod_monitor_sites', $site, $update);

      if ($result) {
        drupal_set_message(t('Website %url correctly saved.', array('%url' => $site->url)));
        if ($form_state['values']['fetch']) {
          $site_info = _prod_monitor_get_site($site->id, 'all');
          // First: all checks.
          _prod_monitor_retrieve_data($site->id, $site_info, TRUE);
          // MUST be second because of the status update!
          _prod_monitor_db_connect_check($site->id, $site_info);
          $form_state['redirect'] = 'admin/reports/prod-monitor/site/' . $site->id;
        }
      }
      else {
        drupal_set_message(t('Website %url not saved! Please try again.', array('%url' => $site->url)), 'error');
      }
      break;
  }
}

/**
 * Submit handler for the fetch all button.
 */
function prod_monitor_fetch_all_submit($form, &$form_state) {
  _prod_monitor_fetch_all_data_batcher_create();
}

/**
 * Function to create the batch process. Also used in Drush!
 */
function _prod_monitor_fetch_all_data_batcher_create($fetch_only = FALSE, $update_only = FALSE, $msg = TRUE) {
  $title = t('Fetching all site data and checking for updates...');

  if ($fetch_only) {
    $title = t('Fetching all site data...');
  }
  if ($update_only) {
    $title = t('Checking for updates...');
  }

  $batch = array(
    'operations' => array(
      array('prod_monitor_fetch_all_data_batcher', array($fetch_only, $update_only, $msg)),
    ),
    'title' => $title,
    'file' => drupal_get_path('module', 'prod_monitor') . '/includes/prod_monitor.admin.inc',
  );
  batch_set($batch);
}

/**
 * Batch fetching of all site info.
 */
function prod_monitor_fetch_all_data_batcher($fetch_only, $update_only, $msg, &$context) {
  $sandbox = &$context['sandbox'];
  if (empty($context['sandbox'])) {
    $sandbox['sites'] = array_keys(_prod_monitor_get_sites());
    $sandbox['count'] = count($sandbox['sites']);
  }

  // Get site info.
  $id = array_shift($sandbox['sites']);
  $site_info = _prod_monitor_get_site($id, 'all');

  if (!$update_only) {
    // First: all checks.
    _prod_monitor_retrieve_data($id, $site_info, $msg);
    // MUST be second because of the status update!
    _prod_monitor_db_connect_check($id, $site_info);
  }

  if (!$fetch_only) {
    // Module update status.
    $modules = prod_monitor_load($id);
    if (!empty($modules) && !empty($modules['projects'])) {
      module_load_include('inc', 'prod_monitor', 'includes/prod_monitor.update');
      _prod_monitor_update_refresh($id, $modules['projects'], $modules['sitekey']);
      _prod_monitor_calculate_project_data($id, $modules['projects'], $modules['available']);
    }
  }

  $context['message'] = t('Updating data for %url', array('%url' => $site_info['url']));
  $context['finished'] = empty($sandbox['sites']) ? 1 : (1 - count($sandbox['sites']) / $sandbox['count']);
}

/**
 * Callback to fetch site data
 */
function prod_monitor_fetch_data($id) {
  $site_info = _prod_monitor_get_site($id, 'all');
  // First: all checks.
  _prod_monitor_retrieve_data($id, $site_info, TRUE);
  // MUST be second because of the status update!
  _prod_monitor_db_connect_check($id, $site_info);
  drupal_goto('admin/reports/prod-monitor/site/' . $id);
}

/**
 * Form to delete a site's data
 */
function prod_monitor_flush_form($form, &$form_state, $id) {
  $form = array();

  $form['site_id'] = array(
    '#type' => 'value',
    '#value' => $id,
  );

  $url = _prod_monitor_get_url($id);

  $form['url'] = array(
    '#type' => 'value',
    '#value' => $url,
  );

  return confirm_form($form, t('Are you sure you wish to delete all fetched data for %url?', array('%url' => $url)), 'admin/reports/prod-monitor', t('Note that the module update status data will not be flushed!') . '<br />' . t('This action cannot be undone.'));
}

/**
 * Delete a site's data
 */
function prod_monitor_flush_form_submit($form, &$form_state) {
  if ($form_state['values']['site_id']) {
    $result = _prod_monitor_flush_data($form_state['values']['site_id']);
    if ($result === FALSE) {
      drupal_set_message(t('Unable to flush data for %url!', array('%url' => $form_state['values']['url'])), 'error');
    }
    else {
      drupal_set_message(t('Stored data for %url successfully flushed.', array('%url' => $form_state['values']['url'])));
    }
  }
  $form_state['redirect'] = 'admin/reports/prod-monitor';
}

/**
 * Form to delete a site
 */
function prod_monitor_delete_form($form, &$form_state, $id) {
  $form = array();

  $form['site_id'] = array(
    '#type' => 'value',
    '#value' => $id,
  );

  $url = _prod_monitor_get_url($id);

  $form['url'] = array(
    '#type' => 'value',
    '#value' => $url,
  );

  return confirm_form($form, t('Are you sure you wish to delete the website %url?', array('%url' => $url)), 'admin/reports/prod-monitor');
}

/**
 * Delete a site
 */
function prod_monitor_delete_form_submit($form, &$form_state) {
  if ($form_state['values']['site_id']) {
    $result = _prod_monitor_delete_site($form_state['values']['site_id']);
    if ($result) {
      drupal_set_message(t('Website %url successfully deleted.', array('%url' => $form_state['values']['url'])));
    }
    else {
      drupal_set_message(t('Unable to delete %url!', array('%url' => $form_state['values']['url'])), 'error');
    }
  }
  $form_state['redirect'] = 'admin/reports/prod-monitor';
}

function _prod_monitor_update_data_form($form, $form_state, $id, $site_info) {
  $form['site_id'] = array(
    '#type' => 'value',
    '#value' => $id,
  );

  $form['site_info'] = array(
    '#type' => 'value',
    '#value' => $site_info,
  );

  // Markup field for proper styling.
  $form['buttons'] = array(
    '#type' => 'markup',
    '#prefix' => '<div class="buttons">',
    '#value' => '&nbsp;',
    '#suffix' => '</div>',
  );

  $form['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Fetch data now'),
  );

  return $form;
}

function _prod_monitor_update_data_form_submit($form, &$form_state) {
  // First: all checks.
  _prod_monitor_retrieve_data($form_state['values']['site_id'], $form_state['values']['site_info'], TRUE);
  // MUST be second because of the status update!
  _prod_monitor_db_connect_check($form_state['values']['site_id'], $form_state['values']['site_info']);
}

/**
 * Callback for module lookup form.
 *
 */
function prod_monitor_module_lookup_form($form, &$form_state) {
  $form = array();

  // Show results.
  if (isset($form_state['projects'])) {

    $module = $form_state['values']['module'];

    $rows = array();
    foreach ($form_state['projects'] as $id => $project) {

      $application = db_select('prod_monitor_sites', 'pms')->fields('pms', array('url'))->condition('id', $id)->execute()->fetchField();
      $version = $project['info']['version'];

      $rows[] = array(
        $application,
        $version,
        l(t('View'), 'admin/reports/prod-monitor/site/' . $id),
      );
    }
    $form['title'] = array(
      '#theme' => 'html_tag',
      '#tag' => 'h2',
      '#value' => t('Applications where %module is used', array('%module' => $module)),
    );
    $form['table'] = array(
      '#theme' => 'table',
      '#rows' => $rows,
      '#header' => array(t('Application'), t('Version'), t('View')),
    );

    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Perform another lookup'),
    );
  }
  // Show lookup form.
  else {
    $form['module'] = array(
      '#type' => 'textfield',
      '#title' => t('Module name'),
      '#required' => TRUE,
    );
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Fetch Applications'),
    );
  }

  return $form;
}

/**
 * Submission handler for module lookup form
 */
function prod_monitor_module_lookup_form_submit(&$form, &$form_state) {
  if (isset($form_state['values']['module'])) {

    $projects = db_select('prod_monitor_site_modules', 'psm')
    ->fields('psm', array('id', 'projects'))
    ->condition('projects', '%' . db_like($form_state['values']['module']) . '%', 'LIKE')
    ->execute()->fetchAllAssoc('id');

    $form_state['rebuild'] = TRUE;

    if ($projects && !empty($projects)) {
      foreach($projects as $project) {

        $modules = unserialize($project->projects);
        if (isset($modules[$form_state['values']['module']])) {
          $form_state['projects'][$project->id] = $modules[$form_state['values']['module']];
        }
      }
    }
    if (!isset($form_state['projects'])) {
      drupal_set_message(t('No projects found for :module', array(':module' => $form_state['values']['module'])));
    }
  }
  else {
    unset($form_state['projects']);
  }
}
