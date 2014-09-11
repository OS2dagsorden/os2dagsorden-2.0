<?php
/**
 * @file
 * os2dagsorden_ultimate_cron_configuration.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function os2dagsorden_ultimate_cron_configuration_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "ultimate_cron" && $api == "default_ultimate_cron_functions") {
    return array("version" => "1");
  }
}
