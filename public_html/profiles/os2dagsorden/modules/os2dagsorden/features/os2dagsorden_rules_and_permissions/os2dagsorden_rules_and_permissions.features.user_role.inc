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

  // Exported role: administrator+.
  $roles['administrator+'] = array(
    'name' => 'administrator+',
    'weight' => '5',
  );

  // Exported role: administrator++.
  $roles['administrator++'] = array(
    'name' => 'administrator++',
    'weight' => '4',
  );

  // Exported role: os2dagsorden.
  $roles['os2dagsorden'] = array(
    'name' => 'os2dagsorden',
    'weight' => '3',
  );

  // Exported role: os2dagsorden limited.
  $roles['os2dagsorden limited'] = array(
    'name' => 'os2dagsorden limited',
    'weight' => '1',
  );

  return $roles;
}
