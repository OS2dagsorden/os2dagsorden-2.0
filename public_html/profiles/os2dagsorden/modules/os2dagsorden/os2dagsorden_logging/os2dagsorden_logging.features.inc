<?php
/**
 * @file
 * os2dagsorden_logging_feature.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function os2dagsorden_logging_feature_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "monolog" && $api == "monolog") {
    return array("version" => "1");
  }
}
