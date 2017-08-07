<?php
/**
 * @file
 * os2logging.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function os2logging_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "monolog" && $api == "monolog") {
    return array("version" => "1");
  }
}
