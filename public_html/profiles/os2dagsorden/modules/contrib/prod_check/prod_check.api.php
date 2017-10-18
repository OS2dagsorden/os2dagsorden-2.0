<?php

/**
 * @file
 * Documentation for hooks defined by prod_check.
 */


/**
 * hook_prod_check_alter()
 *
 * You can implement hook_prod_check_alter() in your own module to add
 * additional checks or modify the core checks.
 * The hook receives the default functions divided into 7 categories:
 *
 *  - settings
 *  - server
 *  - performance
 *  - security
 *  - modules
 *  - seo
 *  - prod_mon
 *  - perf_data
 *
 * 'prod_mon' & 'perf_data' are special categories that will only be used by the
 * accompanying Production monitor module.
 *
 * Your function that implements the actual check must accept 1 string parameter
 * and return an array using the prod_check_execute_check() function.
 *
 * An example implementation (note the pass by reference in the hook!):
 */

/**
 * Implements hook_prod_check_alter()
 * @param array reference to an associative array of all available checks
 */
function my_module_prod_check_alter(&$checks) {
  // Add custom check to the server category:
  //  function_name => title
  // Do not use t() for the title!
  $checks['server']['functions']['my_module_additional_check'] = 'Additional check title';

  // Add custom check for Production Monitor only
  $checks['prod_mon']['functions']['my_module_prod_mon_check'] = 'My Production Monitor only check';

  // Gather performance data
  $checks['perf_data']['functions']['my_module_prod_check_return_data'] = 'Performance logging';

  // Add entirely new category.
  $checks['my_category'] = array(
    'title' => 'Custom category',
    'description' => 'Collection of checks I find important.',
    'functions' => array(
      'my_module_check_stuff' => 'Check stuff',
      'my_module_check_more_stuff' => 'Check more stuff',
    ),
  );
}

/**
 * Custom function to check some things.
 * @param string the caller of the function, defaults to 'internal' but can also
 *        be 'xmlrpc' or 'nagios'
 * @return array you _must_ return prod_check_execute_check($check, $caller) as
 *         per the example below to insure a proper status array is returned.
 */
function my_module_additional_check($caller = 'internal') {
  $check = array();

  $title = 'My modules settings';
  $setting1 = t('Enable debug info');
  $setting2 = t('Disable debug info');
  $path = 'admin/config/system/my-module-settings-page';
  if ($caller != 'internal') {
    $path = PRODCHECK_BASEURL . $path;
  }

  $check['my_module_additional_check'] = array(
    '#title' => t($title),
    '#state' => variable_get('my_module_debug', 1) != 1,
    '#severity' => ($caller == 'nagios') ? NAGIOS_STATUS_CRITICAL : PROD_CHECK_REQUIREMENT_ERROR,
    '#value_ok'  => $setting2,
    '#value_nok'  => $setting1,
    '#description_ok'  => prod_check_ok_title($title, $path),
    '#description_nok' => t('Your !link settings are set to %setting1, they should be set to %setting2 on a producion environment!',
      array(
        '!link' => '<em>' . l(t($title), $path, array('attributes' => array('title' => t($title)))) . '</em>',
        '%setting1' => $setting1,
        '%setting2' => $setting2,
      )
    ),
    '#nagios_key' => 'MYCHCK',
    '#nagios_type' => 'state',
  );

  return prod_check_execute_check($check, $caller);
}

function my_module_check_stuff($caller = 'internal') {
  [...]

  return prod_check_execute_check($check, $caller);
}

function my_module_check_more_stuff($caller = 'internal') {
  [...]

  return prod_check_execute_check($check, $caller);
}

/**
 * Custom callback for a prod_mon only check. Note the additional parameter in
 * the prod_check_execute_check() call!
 */
function my_module_prod_mon_check($caller = 'internal') {
  [...]

  return prod_check_execute_check($check, $caller, 'prod_mon');
}

/**
 * Return performance data to Production Monitor.
 */
function my_module_prod_check_return_data() {
  $data = my_module_gather_summary_data();

  if (!$data) {
    return array(
      'my_module' => array (
        'title' => 'Performance logging',
        'data' => 'No performance data found.',
       ),
    );
  }

  return array(
    'my_module' => array (
      'title' => 'Performance logging',
      'data' => array(
        'Total number of page accesses' => array($data['total_accesses']),
        'Average duration per page' => array($data['ms_avg'], 'ms'),
        'Average memory per page' => array($data['mb_avg'], 'MB'),
        'Average querycount' => array($data['query_count']),
        'Average duration per query' => array($data['ms_query'], 'ms'),
      ),
    ),
  );
}

/**
 * hook_prod_check_disabled_modules_whitelist()
 *
 * Check for updates for these modules even if they are disabled. Some modules
 * (f.e. cache backends) are included directly but don't necessarily have the
 * module enabled in the module list. This list can be extended by other modules
 * or updated with other commonly used modules that are used in such a way.
 */

/**
 * Implements hook_prod_check_disabled_modules_whitelist().
 */
function my_module_prod_check_disabled_modules_whitelist() {
  return array('apc', 'memcache', 'varnish');
}

/**
 * hook_prod_check_disabled_modules_whitelist_alter()
 *
 * Allow other modules to add or delete modules to force check.
 */

/**
 * Implements hook_prod_check_disabled_modules_whitelist_alter().
 */
function my_module_prod_check_disabled_modules_whitelist_alter(&$modules) {
  // Remove apc module from the whitelist.
  if ($pos = array_search('apc', $modules)) {
    unset($modules[$pos]);
  }
}
