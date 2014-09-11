<?php
/**
 * @file
 * os2dagsorden_meetings_calendar_view.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function os2dagsorden_meetings_calendar_view_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function os2dagsorden_meetings_calendar_view_views_api() {
  return array("version" => "3.0");
}
