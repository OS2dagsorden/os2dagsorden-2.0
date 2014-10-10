<?php
/**
 * @file
 * Integrates piwik statistics with drush.
 */

/**
 * Implements hook_drush_command().
 * 
 * @See drush_parse_command() for a list of recognized keys.
 *
 * @return
 *   An associative array describing your command(s).
 */
function piwik_stats_drush_command() {
  $items = array();
  $items['piwik-stats-fill'] = array (
    'description' => "Update piwik stats fields.",
    'aliases' => array('psf'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_DATABASE,
  );
  return $items;
}

/**
 * Implements hook_drush_help().
 */
function piwik_stats_drush_help($section) {
  switch ($section) {
    case 'drush:psf':
      return dt("Fills all piwik stats fields with recent data.");
  }
}

/**
 * Command Callback: Update piwik stats fields.
 */
function drush_piwik_stats_fill() {
  // We want some fresh data here, remove cached data.
  db_delete('cache')->condition('cid', 'piwik_stats:xml:%', 'LIKE')->execute();
  // Get the queue of fields to fill.
  $queue = piwik_stats_get_queue_items();

  // Process each item.
  foreach ($queue as $item) {
    piwik_stats_process_queue_item($item) ;
  }
  cache_clear_all();

  drush_log(dt('Successfully updated piwik fields.'), 'success');
}
