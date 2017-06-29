<?php
/**
 * @file
 * os2dagsorden_blocks_positioning.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function os2dagsorden_blocks_positioning_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
