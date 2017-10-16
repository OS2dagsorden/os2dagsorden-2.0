<?php

/**
 * ALL code here is taken from the Drupal core's update module and MODIFIED for
 * integration with prod_monitor. prod_check recommends that you turn the update
 * module off. prod_check provides the VERY BASIC functionality to get a list of
 * the installed modules with version info and transfer this to prod_monitor
 * over XMLRPC (alot of data here!) so that prod_monitor can do all the update
 * checking locally.
 */

/**
 * Taken from D6 Core(!): modules/update/update.fetch.inc, line 25 and MODIFIED!
 * We chose to stick with the regular process instead of the more optimised D7
 * way. The D7 way is perfect when the update.module checks the site it is
 * running on, but we need to check several sites on an entirely different setup.
 *
 * Fetch project info via XML from a central server.
 */
function _prod_monitor_update_refresh($id, $projects, $site_key) {
  global $base_url;
  $fail = &drupal_static(__FUNCTION__, array());

  // contains update_xml_parser class
  module_load_include('inc', 'update', 'update.fetch');

  $available = array();

  // As replacement for DRUPAL_CORE_COMPATIBILITY since prod_check and
  // prod_monitor should be site independant.
  $core = explode('.', $projects['drupal']['info']['version']);
  $core = $core[0] . '.x';

  $max_fetch_attempts = UPDATE_MAX_FETCH_ATTEMPTS;

  // Prepare object to store generated data to DB.
  $modules = new stdClass();
  $modules->id = $id;

  foreach ($projects as $key => $project) {
    $url = _prod_monitor_update_build_fetch_url($project, $site_key, $core);
    $fetch_url_base = _prod_monitor_update_get_fetch_url_base($project);
    if (empty($fail[$fetch_url_base]) || count($fail[$fetch_url_base]) < $max_fetch_attempts) {
      $xml = drupal_http_request($url);
      if (isset($xml->data)) {
        $data = update_parse_xml($xml->data);
        $available[$data['short_name']] = $data;
      }
      else {
        // Connection likely broken; prepare to give up.
        $fail[$fetch_url_base][$key] = 1;
      }
    }
    else {
      // Didn't bother trying to fetch.
      $fail[$fetch_url_base][$key] = 1;
    }
  }

  if (!empty($available) && is_array($available)) {
    // Record the projects where we failed to fetch data.
    foreach ($fail as $fetch_url_base => $failures) {
      foreach ($failures as $key => $value) {
        $available[$key]['project_status'] = 'not-fetched';
      }
    }
    $modules->available = serialize($available);
    watchdog('prod_monitor', 'Fetched information about all available new releases and updates for %link.', array('%link' => _prod_monitor_get_url($id)), WATCHDOG_NOTICE, l(t('view'), 'admin/reports/prod-monitor/site/' . $id . '/view/updates'));
  }
  else {
    watchdog('prod_monitor', 'Unable to fetch any information about available new releases and updates for %link.', array('%link' => _prod_monitor_get_url($id)), WATCHDOG_ERROR, l(t('view'), 'admin/reports/prod-monitor/site/' . $id . '/view/updates'));
  }
  // Whether this worked or not, we did just (try to) check for updates.
  $modules->lastupdate = time();
  $result = drupal_write_record('prod_monitor_site_modules', $modules, array('id'));
  if (!$result) {
    watchdog('prod_monitor', 'Could not update module data for %link', array('%link' => _prod_monitor_get_url($id)), WATCHDOG_ERROR);
  }

  return $available;
}

/**
 * Taken from Core: modules/update/update.fetch.inc, line 266 and MODIFIED!
 *
 * This figures out the right URL to use, based on the project's .info file
 * and the global defaults. Appends optional query arguments when the site is
 * configured to report usage stats.
 *
 * @param $project
 *   The array of project information from update_get_projects().
 * @param $site_key
 *   The anonymous site key hash (optional).
 *
 * @see update_fetch_data()
 * @see _update_process_fetch_task()
 * @see update_get_projects()
 */
function _prod_monitor_update_build_fetch_url($project, $site_key = '', $core) {
  $name = $project['name'];
  $url = _prod_monitor_update_get_fetch_url_base($project);
  $url .= '/' . $name . '/' . $core;
  // Only append a site_key and the version information if we have a site_key
  // in the first place, and if this is not a disabled module or theme. We do
  // not want to record usage statistics for disabled code.
  if (!empty($site_key) && (strpos($project['project_type'], 'disabled') === FALSE)) {
    $url .= (strpos($url, '?') === TRUE) ? '&' : '?';
    $url .= 'site_key=';
    $url .= rawurlencode($site_key);
    if (!empty($project['info']['version'])) {
      $url .= '&version=';
      $url .= rawurlencode($project['info']['version']);
    }
  }
  return $url;
}

/**
 * Taken from Core: modules/update/update.fetch.inc, line 297 and MODIFIED!
 *
 * Return the base of the URL to fetch available update data for a project.
 *
 * @param $project
 *   The array of project information from update_get_projects().
 * @return
 *   The base of the URL used for fetching available update data. This does
 *   not include the path elements to specify a particular project, version,
 *   site_key, etc.
 *
 * @see _update_build_fetch_url()
 */
function _prod_monitor_update_get_fetch_url_base($project) {
  return isset($project['info']['project status url']) ? $project['info']['project status url'] : UPDATE_DEFAULT_URL;
}

/**
 * Taken from Core: modules/update/update.compare.inc, line 300 and MODIFIED!
 *
 * Calculate the current update status of all projects on the site.
 *
 * The results of this function are expensive to compute, especially on sites
 * with lots of modules or themes, since it involves a lot of comparisons and
 * other operations. Therefore, we cache the results into the {cache_update}
 * table using the 'update_project_data' cache ID. However, since this is not
 * the data about available updates fetched from the network, it is ok to
 * invalidate it somewhat quickly. If we keep this data for very long, site
 * administrators are more likely to see incorrect results if they upgrade to
 * a newer version of a module or theme but do not visit certain pages that
 * automatically clear this cache.
 *
 * @param array $available
 *   Data about available project releases.
 *
 * @see update_get_available()
 * @see update_get_projects()
 * @see update_process_project_info()
 * @see update_project_cache()
 */
function _prod_monitor_calculate_project_data($id, $projects, $available) {
  module_load_include('inc', 'update', 'update.compare');
  update_process_project_info($projects);
  foreach ($projects as $project => $project_info) {
    if (isset($available[$project])) {
      update_calculate_project_update_status($project, $projects[$project], $available[$project]);
    }
    else {
      $projects[$project]['status'] = UPDATE_UNKNOWN;
      $projects[$project]['reason'] = t('No available releases found');
    }
  }

  // Handle the ignored modules.
  if (($ignored = _prod_monitor_get_site_ignored($id))
    && !empty($ignored['updates'])) {
    foreach ($ignored['updates'] as $project_name) {
      if (isset($projects[$project_name])) {
        $projects[$project_name]['ignored'] = TRUE;
        $projects[$project_name]['status'] = UPDATE_UNKNOWN;
      }
    }
  }

  drupal_alter('prod_monitor_project_data', $id, $projects, $available);

  // Check if we need to flag a security update warning.
  // Prepare object to store generated data to DB.
  $modules = new stdClass();
  $modules->id = $id;
  // Assume there are no updates.
  $modules->updates = 1;
  // Check final status of each project.
  foreach ($projects as $project => $project_info) {
    switch ($project_info['status']) {
      case UPDATE_NOT_SECURE:
      case UPDATE_NOT_SUPPORTED:
      case UPDATE_REVOKED:
        $modules->updates = 3;
        // Stop the foreach loop as well.
        break 2;
      case UPDATE_NOT_CURRENT:
        if ($modules->updates < 2) {
          $modules->updates = 2;
        }
        break;
    }
  }

  $result = drupal_write_record('prod_monitor_site_modules', $modules, array('id'));
  if (!$result) {
    watchdog('prod_monitor', 'Could not update module security status for %link', array('%link' => _prod_monitor_get_url($id)), WATCHDOG_ERROR);
  }

  return $projects;
}
