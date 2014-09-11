<?php
/**
 * @file
 * os2dagsorden_rules_and_permissions.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function os2dagsorden_rules_and_permissions_user_default_roles() {
  $roles = array();

  // Exported role: os2dagsorden.
  $roles['os2dagsorden'] = array(
    'name' => 'os2dagsorden',
    'weight' => '2',
  );

  // Exported role: os2dagsorden admin.
  $roles['os2dagsorden admin'] = array(
    'name' => 'os2dagsorden admin',
    'weight' => '3',
  );

  return $roles;
}
