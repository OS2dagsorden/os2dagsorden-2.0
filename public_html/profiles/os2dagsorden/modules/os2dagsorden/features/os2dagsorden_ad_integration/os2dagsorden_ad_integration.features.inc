<?php
/**
 * @file
 * os2dagsorden_ad_integration.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function os2dagsorden_ad_integration_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "ldap_authorization" && $api == "ldap_authorization") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "ldap_servers" && $api == "ldap_servers") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
