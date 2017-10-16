<?php
/**
 * @file
 * Documentation on api functions for prod_monitor.
 *
 * @ingroup prod_monitor
 * @{
 */

/**
 * Implements hook_prod_monitor_ignore().
 *
 * Allows modules to specify certain ignore directives, currently
 * a list of modules whose update status should be ignored.
 *
 * @see _prod_monitor_get_site_ignored().
 * @see _prod_monitor_calculate_project_data().
 */
function hook_prod_monitor_ignore($site_id) {
  $ignore = array('updates' => array());
  
  // Ignore this module (suppress warnings) because we cannot do anything
  // about it's update status as it has been abandoned and we are not going
  // to stop using it.
  if ($site_id == 12) {
    $ignore['updates'][] = 'node_embed';
  }

  return $ignore;
}

/**
 * Implements hook_prod_monitor_project_data_alter().
 *
 * Allows modules to alter the data being calculated for a project.
 *
 * @see _prod_monitor_calculate_project_data().
 */
function hook_prod_monitor_project_data_alter($site_id, &$data, $available) {

}