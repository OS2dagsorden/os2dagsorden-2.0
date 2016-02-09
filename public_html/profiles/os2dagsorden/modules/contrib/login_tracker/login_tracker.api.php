<?php

/**
 * @file
 * Hooks provided by the Login Tracker module.
 */

/**
 * Override whether a login request should be tracked or not.
 *
 * @param bool $track_login
 *   Boolean indicating whether to track the login (true), or not (false).
 * @param array $edit
 *   The array of form values submitted by the user.
 * @param object $account
 *   The user object on which the operation was just performed.
 *
 * @see login_tracker_user_login()
 */
function hook_login_tracker_track_login_alter(&$track_login, array $edit, $account) {
  // We only track login requests on the 1st of the month.
  if (date('d') != 1) {
    return FALSE;
  }
  else {
    return TRUE;
  }
}

/**
 * Supply, or modify custom data stored with the tracked login.
 *
 * @param array $data
 *   Associative array of custom data that will be stored with the login.
 * @param array $edit
 *   The array of form values submitted by the user.
 * @param object $account
 *   The user object on which the operation was just performed.
 *
 * @see login_tracker_user_login()
 */
function hook_login_tracker_login_data(array &$data, array $edit, $account) {
  // Store a random number between 1 and 10 with the tracked login.
  $data['my-random-number'] = rand(1, 10);
}
