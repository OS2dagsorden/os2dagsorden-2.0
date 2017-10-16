<?php
/**
 * @file
 * Template that renders a google graph. Feel free to override it if you prefer
 * another graphing mechanism by placing it in your themes folder.
 *
 * Available variables:
 *  $data contains raw data fetched from the prod_monitor_performance table.
 *  $graphs contains preprocessed data to allow (more) easy output.
 *
 * TODO: add preloader element to the Graphs div so the users see something is
 *       loading.
 */

  // Output all graphs.
  $scripts = '';
  foreach ($graphs as $module => $data) {
?>
<h2><?php print $data['title'] ?></h2>

<?php
    unset($data['title']);
    if (isset($data['message'])) {
      print $data['message'];
    }
    else {
      foreach ($data as $unit => $numbers) {
        $unit = strtolower($unit);
?>
<div id="<?php print $module . (!empty($unit) ? '-' . $unit : ''); ?>" style="width: 960px; height: 300px; text-align: center;" class="performance-data"><img style="padding-top: 140px;" src="<?php print base_path() . drupal_get_path('module', 'prod_monitor'); ?>/images/spinner.gif" width="20" height="20" /></div>
<?php
  $scripts .= '  Drupal.behaviors.prod_monitor_performance.' . $module . (!empty($unit) ? '_' . $unit : '') . " = function() {\n";
  $scripts .= '    var data = new google.visualization.DataTable();'."\n";
  $scripts .= "    data.addColumn('datetime', 'Date');\n";

  // Add columns.
  foreach ($numbers['cols'] as $col) {
    $scripts .= "    data.addColumn('number', '$col');\n";
  }

  // Add column data.
  $scripts .= '    data.addRows(['."\n";
  foreach ($numbers['rows'] as $time => $row) {
    $scripts .= '      [new Date(' . date('Y, n, j, G, i, s', $time) . '), ' . implode(', ', $row ) . "],\n";
  }
  $scripts .= "    ]);\n\n";

  $scripts .= "    var chart = new google.visualization.AnnotatedTimeLine(document.getElementById('". $module . (!empty($unit) ? '-' . $unit : '') . "'));\n";
  $scripts .= '    chart.draw(data, {displayAnnotations: false});'."\n";
  $scripts .= "  }\n\n";
?>
<p>&nbsp;</p>

<?php
      }
    }
  }
  // Actually add the JS files to the page. Order is important!
  drupal_add_js(drupal_get_path('module', 'prod_monitor') . '/js/prod-monitor.performance.js', array('type' => 'file', 'weight' => 1));
  drupal_add_js($scripts, array('type' => 'inline', 'weight' => 2));
?>
