<?php

/**
 * @file
 * Simple database connection check that can be placed anywhere within a Drupal
 * installation. Does NOT need to be in the root where index.php resides!
 */

/**
 * Locate the actual Drupal root. Based on drush_locate_root().
 */
function locate_root() {
  $drupal_root = FALSE;

  $start_path = isset($_SERVER['PWD']) ? $_SERVER['PWD'] : '';
  if (empty($start_path)) {
    $start_path = getcwd();
  }

  foreach (array(TRUE, FALSE) as $follow_symlinks) {
    $path = $start_path;
    if ($follow_symlinks && is_link($path)) {
      $path = realpath($path);
    }
    // Check the start path.
    if (valid_root($path)) {
      $drupal_root = $path;
      break;
    }
    else {
      // Move up dir by dir and check each.
      while ($path = shift_path_up($path)) {
        if ($follow_symlinks && is_link($path)) {
          $path = realpath($path);
        }
        if (valid_root($path)) {
          $drupal_root = $path;
          break 2;
        }
      }
    }
  }

  return $drupal_root;
}

/**
 * Based on the DrupalBoot*::valid_root() from Drush.
 */
function valid_root($path) {
  if (!empty($path) && is_dir($path) && file_exists($path . '/index.php')) {
    $candidate = 'includes/common.inc';
    if (file_exists($path . '/' . $candidate) && file_exists($path . '/misc/drupal.js')) {
      return TRUE;
    }
  }
  return FALSE;
}

/**
 * Based on _drush_shift_path_up().
 */
function shift_path_up($path) {
  if (empty($path)) {
    return FALSE;
  }
  $path = explode('/', $path);
  // Move one directory up.
  array_pop($path);
  return implode('/', $path);
}

/**
 * Do the actual database connection check.
 */
define('DRUPAL_ROOT', locate_root());
require_once DRUPAL_ROOT . '/includes/bootstrap.inc';
drupal_bootstrap(DRUPAL_BOOTSTRAP_DATABASE);

$result = db_query('SELECT COUNT(filename) FROM {system}')->fetchField();

if ($result) {
  $msg = 'OK';
  http_response_code(200);
}
else {
  http_response_code(500);
  $msg = 'NOK';
}

exit($msg);
