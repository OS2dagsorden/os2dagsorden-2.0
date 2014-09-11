<?php
/**
 * @file
 * ldap_rk.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ldap_rk_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "ldap_servers" && $api == "ldap_servers") {
    return array("version" => "1");
  }
}
