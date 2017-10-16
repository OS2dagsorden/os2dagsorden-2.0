<?php

/**
 * Implementation of hook_drush_command().
 */
function prod_monitor_drush_command() {
  $items = array();

  $items['prod-monitor'] = array(
    'callback' => 'drush_prod_monitor_statusdetail',
    'description' => 'Display the Production Monitor status page',
    'aliases' => array('pmon'),
    'arguments' => array(
      'id' => "ID of the site to view it's status in detail.",
    ),
  );
  $items['prod-monitor-updates'] = array(
    'callback' => 'drush_prod_monitor_updates',
    'description' => 'Display the update module status page',
    'aliases' => array('pmon-up'),
    'arguments' => array(
      'id' => 'ID of the site to view module updates for.',
    ),
    'options' => array(
      'check' => 'Check for module updates.',
      'security-only' => 'Only show modules that have security updates available.',
    ),
  );
  $items['prod-monitor-fetch'] = array(
    'callback' => 'drush_prod_monitor_fetch',
    'description' => 'Fetch the status information from a given remote site.',
    'aliases' => array('pmon-fe'),
    'arguments' => array(
      'id' => 'Space delemited list of site IDs to fetch all data for.',
    ),
  );
  $items['prod-monitor-flush'] = array(
    'callback' => 'drush_prod_monitor_flush',
    'description' => "Remove all fetched data for a given site.",
    'aliases' => array('pmon-fl'),
    'arguments' => array(
      'id' => 'Space delemited list of site IDs to be flushed.',
    ),
  );
  $items['prod-monitor-delete'] = array(
    'callback' => 'drush_prod_monitor_delsite',
    'description' => 'Completemy remove a site and all its data.',
    'aliases' => array('pmon-rm'),
    'arguments' => array(
      'id' => 'Space delemited list of site IDs to be deleted.',
    ),
  );

  return $items;
}

/**
 * Fetch data callback.
 */
function drush_prod_monitor_fetch() {
  $args = func_get_args();

  // Fetch ALL.
  if (empty($args)) {
    if (!drush_confirm(dt('Do you really want to fetch the data for ALL remote sites?'))) {
      drush_set_error('prod_monitor', dt('Aborting.'));
      return;
    }
    else {
      module_load_include('inc', 'prod_monitor', 'includes/prod_monitor.admin');
      // Batch process data fetching.
      _prod_monitor_fetch_all_data_batcher_create(TRUE, FALSE, FALSE);
      drush_backend_batch_process();
    }
  }
  // Fetch one or more sites as requested.
  else {
    foreach($args as $arg) {
      $site = _prod_monitor_get_site($arg);
      if (!empty($site['url'])) {
        $result = _prod_monitor_retrieve_data($arg, $site);
        $site['url'] = _prod_monitor_sanitize_url(rtrim($site['url'], '/'));
        if ($result === FALSE) {
          drush_print("\033[1;31m" . dt('Error:') . " \033[0m" . dt('Unable to fetch data for') . ' ' . $site['url'] . '!');
        }
        else {
          _prod_monitor_db_connect_check($arg, $site);
          drush_print(dt('Sucessfully fetched data for') . ' ' . $site['url'] . '.');
        }
      }
      else {
        drush_print("\033[1;31m" . dt('Error:') . " \033[0m" . dt('No site found with ID') . ' ' . $arg . '!');
      }
    }
  }
}

/**
 * Flush data callback.
 */
function drush_prod_monitor_flush() {
  $args = func_get_args();
  foreach ($args as $arg) {
    $url = _prod_monitor_get_url($arg);
    if (!empty($url)) {
      if (!drush_confirm(dt('Do you really want to flush all data for') . ' ' . $url . '?')) {
        drush_die('Aborting.');
      }
      $result = _prod_monitor_flush_data($arg);
      if ($result === FALSE) {
        drush_print("\033[1;31m" . dt('Error:') . " \033[0m" . dt('Unable to flush data!'));
      }
      else {
        drush_print(dt('Stored data successfully flushed.'));
      }
    }
    else {
      drush_print("\033[1;31m" . dt('Error:') . " \033[0m" . dt('No site found with ID') . ' ' . $arg . '!');
    }
  }
}

/**
 * Delete site callback.
 */
function drush_prod_monitor_delsite() {
  $args = func_get_args();
  foreach ($args as $arg) {
    $url = _prod_monitor_get_url($arg);
    if (!empty($url)) {
      if (!drush_confirm(dt("Do you really want to delete") . ' ' . $url . ' ' . dt('and all its data?'))) {
        drush_die('Aborting.');
      }
      $result = _prod_monitor_delete_site($arg);
      if ($result === FALSE) {
        drush_print("\033[1;31m" . dt('Error:') . " \033[0m" . dt('Unable to delete') . $url . '!');
      }
      else {
        drush_print(dt('Website successfully deleted.'));
      }
    }
    else {
      drush_print("\033[1;31m" . dt('Error:') . " \033[0m" . dt('No site found with ID') . ' ' . $arg . '!');
    }
  }
}

/**
 * Status page callback
 */
function drush_prod_monitor_statusdetail() {
  $args = func_get_args();

  if (empty($args)) {
    _drush_prod_monitor_overview();
  }
  elseif (is_numeric($args[0])) {
    _drush_prod_monitor_detail($args[0]);
  }
}

function _drush_prod_monitor_overview() {
  $sites = _prod_monitor_get_sites();

  // Map error codes to shell colours.
  $severity = array (
    'ok' => '1;32',
    'warning' => '1;33',
    'error' => '1;31',
  );

  $rows = array(array(
    dt('ID'),
    dt('URL'),
    dt('Data'),
    dt('Date added'),
    dt('Last update'),
    dt('Status'),
  ));

  // TODO: check why the colour coding messes up the tabs for the table
  // Worked around this by placing the status column last
  foreach ($sites as $id => $site_info) {
    $rows[] = array(
      $id,
      _prod_monitor_sanitize_url(rtrim($site_info['url'], '/')),
      (!$site_info['data']) ? dt('Empty') : t('Stored'),
      $site_info['added'],
      (!$site_info['lastupdate']) ? dt('Not yet updated') : $site_info['lastupdate'],
      "\033[" . $severity[$site_info['status']] . 'm' . ucwords($site_info['status']) . "\033[0m",
    );
  }
  drush_print("\033[1m" . dt('Production Monitor status') . "\033[0m\n", 1);
  if (count($rows) > 1) {
    drush_print_table($rows, TRUE);
    drush_print(dt('Use drush prod-monitor [id] to view the details of a specific site.'));
  }
  else {
    drush_print(dt('No sites added yet! Yo can add sites on admin/reports/prod-monitor.'), 1);
  }
}

function _drush_prod_monitor_detail($id) {
  $site = _prod_monitor_get_site($id, 'all');
  if (!isset($site['url'])) {
    drush_print("\033[1;31m" . dt('Error:') . " \033[0m" . dt('No site found with ID') . ' ' . $id . '!');
    return;
  }

  // Overall status block
  $block = array();
  $modules = _prod_monitor_get_site_modules($id);
  if(!empty($modules)) {
    $prod_mon = $site['data']['prod_mon'];

    $cron = dt('Unknown');
    if (isset($prod_mon['prod_check_cron_last'])) {
      $cron = format_date($prod_mon['prod_check_cron_last'], 'large');
    }

    $title = dt('Unknown');
    $color = "\033[0m";
    if ($modules['updates'] > 0) {
      switch ($modules['updates']) {
        case 1:
          $title = dt('None');
          break;
        case 2:
          $color = "\033[1;33m";
          $title = dt('Available');
          break;
        case 3:
          $color = "\033[1;31m";
          $title = dt('Security risk!');
          break;
      }
    }
    $updates = $color . $title . "\033[0m";

    // Construct block
    $block[] = array("\033[1m" . dt('Overall status') . "\033[0m");
    $block[] = array(
      dt('Drupal core version'),
      $modules['projects']['drupal']['info']['version'],
    );
    $block[] = array(
      dt('Last cron run'),
      $cron,
    );
    $block[] = array(
      dt('Updates'),
      $updates,
    );
  }
  // cleanup
  unset($site['data']['prod_mon']);
  unset($modules);

  $functions = $site['settings']['functions'];
  $nodata = dt('No data recieved yet.');
  $url = rtrim($site['url'], '/');
  // Map error codes to shell colours.
  $severity = array (
    REQUIREMENT_INFO => '1',
    REQUIREMENT_OK => '1;32',
    REQUIREMENT_WARNING => '1;33',
    REQUIREMENT_ERROR => '1;31',
  );
  $error = 0;
  $rows = array();


  foreach ($functions as $set => $data) {
    if (isset($site['data'][$set])) {
      $rows[] = array('');
      $rows[] = array("\033[1m" . dt($data['title']) . "\033[0m");
      if (!empty($site['data'][$set])) {
        foreach ($site['data'][$set] as $check => $result) {
          $rows[] = array(
            $result['title'],
            "\033[" . $severity[$result['severity']] . 'm' . strip_tags($result['value']) . "\033[0m",
          );
          if ($error < $result['severity']) {
            $error = $result['severity'];
          }
        }
      }
      else {
        $rows[] = array($nodata);
      }
    }
  }

  // Actual printing.
  drush_print("\033[1m" . dt('Production Monitor status for') . ' ' . _prod_monitor_sanitize_url($url) . "\033[0m", 1);
  if (!empty($block)) {
    drush_print_table($block);
  }
  if (!empty($rows)) {
    drush_print_table($rows);
  }
  else {
    drush_print($nodata, 1);
  }
  if ($error > 0) {
    // Would be cool if we could prefix the admin path with http://<host>/ so it
    // will become a clickable link in some terminals. Any ideas?
    drush_print("\033[1m" . dt('Some errors were reported!') . "\033[0m " . dt('Check the full status page on') . " \033[1m" . 'admin/reports/prod-monitor/' . $id . '/view' . "\033[0m " . dt('for details.'));
  }
}

/**
 * Update status page callback.
 */
function drush_prod_monitor_updates() {
  $id = func_get_args();

  // Fetch ALL.
  if (empty($id)) {
    if (!drush_confirm(dt('Do you really want to check ALL sites for module updates?'))) {
      drush_set_error('prod_monitor', dt('Aborting.'));
      return;
    }
    else {
      module_load_include('inc', 'prod_monitor', 'includes/prod_monitor.admin');
      // Batch process update checking.
      _prod_monitor_fetch_all_data_batcher_create(FALSE, TRUE, FALSE);
      drush_backend_batch_process();
    }
  }
  // Fetch the site as requested.
  else {
    $id = $id['0'];

    // Get module info.
    $modules = _prod_monitor_get_site_modules($id);
    $url = _prod_monitor_get_url($id);
    if (empty($modules)) {
      if (empty($url)) {
        drush_set_error('prod_monitor', dt('No site found with ID') . ' ' . $id . '!');
        return;
      }
      else {
        drush_set_error('prod_monitor', dt('No module data found for') . ' ' . $url . '!');
        return;
      }
    }
    elseif (empty($modules['available'])) {
      drush_set_error('prod_monitor', dt('No update data found for') . ' ' . $url . '!');
      // No data, ask for refresh.
      _drush_prod_monitor_update_refresh($id, $modules);
    }

    // Refresh if user asked for it.
    if (drush_get_option('check')) {
      _drush_prod_monitor_update_refresh($id, $modules);
    }

    $security_only = drush_get_option('security-only');

    $last = $modules['lastupdate'];
    module_load_include('inc', 'prod_monitor', 'includes/prod_monitor.update');
    $projects = _prod_monitor_calculate_project_data($id, $modules['projects'], $modules['available']);
    // Cleanup.
    unset($modules);

    // Table headers.
    $rows[] = array(dt('Name'), dt('Installed version'), dt('Proposed version'), dt('Status'));

    // Process releases, notifying user of status and building a list of proposed updates
    drush_include_engine('update_info', 'drupal', NULL, DRUSH_BASE_PATH . '/commands/pm/update_info');
    drush_include(DRUSH_BASE_PATH . '/commands/pm', 'updatecode.pm');
    foreach ($projects as $project) {
      // Only show security updates if the user requested it.
      if ($security_only && $project['status'] !== UPDATE_NOT_SECURE) {
        continue;
      }
      // Add color to the status.
      $color = "\033[0m";
      switch ($project['status']) {
        case UPDATE_CURRENT:
          $color = "\033[1;32m";
          break;
        case UPDATE_NOT_CURRENT:
          $color = "\033[1;33m";
          break;
        case UPDATE_NOT_SECURE:
          $color = "\033[1;31m";
          break;
      }
      // Translate status to readable name and fill 'candidate_version'.
      $status = pm_update_filter($project);
      // Generate row.
      $rows[] = array(
        $project['name'],
        $project['existing_version'],
        $project['candidate_version'],
        $color . $status . "\033[0m",
      );
    }

    drush_print("\033[1m" . dt('Module update status for') . ' ' . $url . "\033[0m", 1);
    drush_print(dt('Update information last refreshed:') . ' ' . ($last  ? format_date($last) : dt('Never')) . "\n", 1);
    if (count($rows) > 1) {
      drush_print_table($rows, TRUE);
    }
    else {
      drush_print("\033[1m" . dt('No updates to show!') . "\033[0m", 1);
    }
  }
}

/**
 * Helper function to refresh update status data.
 */
function _drush_prod_monitor_update_refresh($id, &$modules) {
  if (!drush_confirm(dt('Would you like to check for module updates now?'))) {
    drush_die('Aborting.');
  }
  else {
    drush_print(dt('Refreshing update status information ...'));
    module_load_include('inc', 'prod_monitor', 'includes/prod_monitor.update');
    $result = _prod_monitor_update_refresh($id, $modules['projects'], $modules['sitekey']);
    if (!empty($result)) {
      drush_print();
      $modules['available'] = $result;
      $modules['lastupdate'] = time();
    }
    else {
      drush_set_error('prod_monitor', dt('Failed to refres update status information for') . ' ' . $url . '!');
      drush_die('Aborting.');
    }
  }
}
