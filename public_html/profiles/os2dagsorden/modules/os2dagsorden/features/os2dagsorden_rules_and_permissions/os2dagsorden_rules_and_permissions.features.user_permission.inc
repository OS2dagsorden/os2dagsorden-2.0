<?php
/**
 * @file
 * os2dagsorden_rules_and_permissions.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function os2dagsorden_rules_and_permissions_user_default_permissions() {
  $permissions = array();

  // Exported permission: access PDF version.
  $permissions['access PDF version'] = array(
    'name' => 'access PDF version',
    'roles' => array(
      0 => 'authenticated user',
    ),
    'module' => 'print_pdf',
  );

  // Exported permission: access administration pages.
  $permissions['access administration pages'] = array(
    'name' => 'access administration pages',
    'roles' => array(
      0 => 'administrator+',
      1 => 'administrator++',
    ),
    'module' => 'system',
  );

  // Exported permission: access content.
  $permissions['access content'] = array(
    'name' => 'access content',
    'roles' => array(
      0 => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: access content overview.
  $permissions['access content overview'] = array(
    'name' => 'access content overview',
    'roles' => array(
      0 => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: access print.
  $permissions['access print'] = array(
    'name' => 'access print',
    'roles' => array(
      0 => 'authenticated user',
    ),
    'module' => 'print',
  );

  // Exported permission: access toolbar.
  $permissions['access toolbar'] = array(
    'name' => 'access toolbar',
    'roles' => array(
      0 => 'administrator+',
      1 => 'administrator++',
    ),
    'module' => 'toolbar',
  );

  // Exported permission: access user profiles.
  $permissions['access user profiles'] = array(
    'name' => 'access user profiles',
    'roles' => array(
      0 => 'administrator++',
    ),
    'module' => 'user',
  );

  // Exported permission: administer menu.
  $permissions['administer menu'] = array(
    'name' => 'administer menu',
    'roles' => array(
      0 => 'administrator++',
    ),
    'module' => 'menu',
  );
  
  $permissions['administer nodes'] = array(
    'name' => 'administer nodes',
    'roles' => array(
      0 => 'administrator++',
    ),
    'module' => 'node',
  );

  // Exported permission: administer os2web.
  $permissions['administer os2web'] = array(
    'name' => 'administer os2web',
    'roles' => array(
      0 => 'administrator++',
    ),
    'module' => 'os2web_settings',
  );

  // Exported permission: administer permissions.
  $permissions['administer permissions'] = array(
    'name' => 'administer permissions',
    'roles' => array(),
    'module' => 'user',
  );

  // Exported permission: administer taxonomy.
  $permissions['administer taxonomy'] = array(
    'name' => 'administer taxonomy',
    'roles' => array(
      0 => 'administrator+',
      1 => 'administrator++',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: administer ultimate cron.
  $permissions['administer ultimate cron'] = array(
    'name' => 'administer ultimate cron',
    'roles' => array(
      0 => 'administrator++',
    ),
    'module' => 'ultimate_cron',
  );

  // Exported permission: administer users.
  $permissions['administer users'] = array(
    'name' => 'administer users',
    'roles' => array(
      0 => 'administrator+',
      1 => 'administrator++',
    ),
    'module' => 'user',
  );

  // Exported permission: create os2web_meetings_spaper content.
  $permissions['create os2web_meetings_spaper content'] = array(
    'name' => 'create os2web_meetings_spaper content',
    'roles' => array(
      0 => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own os2web_meetings_spaper content.
  $permissions['delete own os2web_meetings_spaper content'] = array(
    'name' => 'delete own os2web_meetings_spaper content',
    'roles' => array(
      0 => 'authenticated user',
    ),
    'module' => 'node',
  );
  
  // Exported permission: edit any os2web_meetings_meeting content.
  $permissions['edit any os2web_meetings_meeting content'] = array(
    'name' => 'edit any os2web_meetings_meeting content',
    'roles' => array(
      0 => 'administrator++',
    ),
   'module' => 'node',
  );

  // Exported permission: edit context.
  $permissions['edit context'] = array(
    'name' => 'edit context',
    'roles' => array(
      0 => 'administrator++',
    ),
    'module' => 'context_permissions',
  );

  // Exported permission: edit own os2web_meetings_spaper content.
  $permissions['edit own os2web_meetings_spaper content'] = array(
    'name' => 'edit own os2web_meetings_spaper content',
    'roles' => array(
      0 => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own user account.
  $permissions['edit own user account'] = array(
    'name' => 'edit own user account',
    'roles' => array(
      0 => 'os2dagsorden',
    ),
    'module' => 'edit_own_user_account_permission',
  );

  // Exported permission: list context.
  $permissions['list context'] = array(
    'name' => 'list context',
    'roles' => array(
      0 => 'administrator++',
    ),
    'module' => 'context_permissions',
  );

  // Exported permission: use text format filtered_html.
  $permissions['use text format filtered_html'] = array(
    'name' => 'use text format filtered_html',
    'roles' => array(
      0 => 'administrator++',
      1 => 'authenticated user',
    ),
    'module' => 'filter',
  );

  // Exported permission: use text format full_html.
  $permissions['use text format full_html'] = array(
    'name' => 'use text format full_html',
    'roles' => array(),
    'module' => 'filter',
  );

  // Exported permission: view the administration theme.
  $permissions['view the administration theme'] = array(
    'name' => 'view the administration theme',
    'roles' => array(
      0 => 'administrator+',
      1 => 'administrator++',
    ),
    'module' => 'system',
  );

  return $permissions;
}
