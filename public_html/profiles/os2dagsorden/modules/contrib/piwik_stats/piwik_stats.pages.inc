<?php
/**
 * @file
 * Some page callbacks for piwik_stats module.
 */

/**
 * Page callback to show statistical information on local task tabs.
 */
function piwik_stats_tab_page($entity_type, $entity) {
  $tables = array();

  // Some default options needed for _field_invoke_get_instances().
  $options = array(
    'default' => FALSE,
    'deleted' => FALSE,
    'language' => NULL,
  );

  // Determine the list of field instances to iterate on.
  list(, , $bundle) = entity_extract_ids($entity_type, $entity);
  $instances = _field_invoke_get_instances($entity_type, $bundle, $options);

  // Iterate through all field instances of the entity, check if they are
  // piwik statistical fields in order to render a table of their contents.
  foreach ($instances as $field_name => $instance) {

    // Get information about the field instance.
    $field_info = field_info_field($field_name);

    // Check if we've got a piwik stats field here.
    if ($field_info['type'] == 'piwik_stats') {
      if (!$field_info['settings']['show_in_statistics_page']) {
        // Jump over fields that have been disabled to show on the stat page.
        continue;
      }

      // Grab it's contents.
      $field = $entity->$field_name;
      $field_contents = (isset($field[LANGUAGE_NONE][0])) ? $field[LANGUAGE_NONE][0] : array();

      // Set table caption, headers and some other needed default values.
      $tables[$field_name] = array(
        'header' => array(
          t('Description'),
          t('Value'),
        ),
        'caption' => t('@field-label (period: %period)', array(
          '@field-label' => $instance['label'],
          '%period' => $field_info['settings']['period'],
          )
        ),
        'colgroups' => array(),
        'sticky' => FALSE,
        'empty' => t('Sorry, no data available yet.'),
        'attributes' => array('piwik-statistics', $field_name),
        'rows' => array(),
      );

      // Get definitions for piwik value keys.
      $definitions = piwik_stats_definitions();
      // Iterate trough all values and build the table.
      foreach ($field_contents as $key => $value) {
        // Set the describing value.
        $tables[$field_name]['rows'][$key][] = $definitions[$key]['title'];
        // Set the statistical value depending on its format.
        $tables[$field_name]['rows'][$key][] = piwik_stats_format_value($value, $definitions[$key]['format']);
      }
    }
  }

  // If there are no tables, there were no piwik fields.
  if (empty($tables)) {
    $output = array('#markup' => t('You have to add at least one piwik field to this entity.'));
  }
  else {
    $output = '';
    // Render each table.
    foreach ($tables as $table) {
      $output .= theme_table($table);
    }
  }
  return $output;
}
