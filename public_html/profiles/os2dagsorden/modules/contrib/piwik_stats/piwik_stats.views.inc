<?php
/**
 * @file
 * Handles views integration of piwik stats field.
 *
 * TODO This implementation is pretty dirty, there should be better ways.
 */

/**
 * Implements hook_field_views_data().
 */
function piwik_stats_field_views_data($field) {
  // Get the default views integration for our field.
  $data = field_views_field_default_views_data($field);

  // Override and extend the default integration.
  foreach ($data as $data_table => &$data_fields) {
    foreach ($data_fields as $data_field_fullname => &$data_field) {
      $data_field_name = str_replace($field['field_name'] . '_', '', $data_field_fullname);

      // Get piwik keyed descriptions.
      $definitions = piwik_stats_definitions();

      if (isset($definitions[$data_field_name])) {
        $definition = $definitions[$data_field_name];

        // Add field information, so views will regard this as usable field.
        $data_field['field'] = array(
          'table' => $data_table,
          'click sortable' => TRUE,
          'field_name' => $data_field_fullname,
          'real field' => $data_field_fullname,
          'is revision' => FALSE,
          'entity_tables' => array(
            'node' => 'node',
            'node_revisions' => 'node',
          ),
        );

        switch ($definition['format']) {
          case 'number':
            // Modify title field.
            $data_field['title'] = str_replace($field['field_name'] . ':' . $data_field_name, $definition['title'], $data_field['title']);
            $data_field['title short'] = $definition['title'];
            // Set the proper handler.
            $data_field['field']['handler'] = 'views_handler_field_numeric';
            break;

          case 'seconds':
            // Modify title field.
            $data_field['title'] = str_replace($field['field_name'] . ':' . $data_field_name, $definition['title'], $data_field['title']);
            $data_field['title short'] = $definition['title'];
            // Set the proper handler.
            $data_field['field']['handler'] = 'views_handler_field_time_interval';
            break;

          case 'percent':
            // Modify title field.
            $data_field['title'] = str_replace($field['field_name'] . ':' . $data_field_name, $definition['title'] . ' %', $data_field['title']);
            $data_field['title short'] = $definition['title'];
            // Set the proper handler.
            $data_field['field']['handler'] = 'views_handler_field_numeric';
            break;

        }
      }
    }
  }
  return $data;
}
