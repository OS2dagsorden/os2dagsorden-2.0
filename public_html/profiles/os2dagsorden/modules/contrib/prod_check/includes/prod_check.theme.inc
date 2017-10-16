<?php

/**
 * Returns HTML for the status report.
 *
 * @param $variables
 *   An associative array containing:
 *   - requirements: An array of requirements.
 *
 * @ingroup themeable
 */
function theme_prod_check_status_report($variables) {
  $requirements = $variables['requirements'];

  $severities = array(
    PROD_CHECK_REQUIREMENT_INFO => array(
      'title' => t('Info'),
      'class' => 'info',
    ),
    PROD_CHECK_REQUIREMENT_OK => array(
      'title' => t('OK'),
      'class' => 'ok',
    ),
    PROD_CHECK_REQUIREMENT_WARNING => array(
      'title' => t('Warning'),
      'class' => 'warning',
    ),
    PROD_CHECK_REQUIREMENT_ERROR => array(
      'title' => t('Error'),
      'class' => 'error',
    ),
  );
  $output = '<table class="system-status-report">';

  foreach ($requirements as $requirement) {
    if (empty($requirement['#type'])) {
      $severity = $severities[isset($requirement['severity']) ? (int) $requirement['severity'] : 0];
      $severity['icon'] = '<div title="' . $severity['title'] . '"><span class="element-invisible">' . $severity['title'] . '</span></div>';

      // Output table row(s)
      if (!empty($requirement['description'])) {
        $output .= '<tr class="' . $severity['class'] . ' merge-down"><td class="status-icon">' . $severity['icon'] . '</td><td class="status-title">' . $requirement['title'] . '</td><td class="status-value">' . $requirement['value'] . '</td></tr>';
        $output .= '<tr class="' . $severity['class'] . ' merge-up"><td colspan="3" class="status-description">' . $requirement['description'] . '</td></tr>';
      }
      else {
        $output .= '<tr class="' . $severity['class'] . '"><td class="status-icon">' . $severity['icon'] . '</td><td class="status-title">' . $requirement['title'] . '</td><td class="status-value">' . $requirement['value'] . '</td></tr>';
      }
    }
  }

  $output .= '</table>';
  return $output;
}

/**
 * Theme database status page.
 *
 * @param $variables
 *   An associative array containing:
 *   - title: title string to display.
 *   - status: string with status summary.
 *   - details: associative array of associative arrays containing detailed
 *     status info.
 *
 * @ingroup themeable
 */
function theme_prod_check_dbstatus($variables) {
  $title = $variables['title'];
  $status = $variables['status'];
  $details = $variables['details'];

  $output = '';

  // DB system and version.
  $output .= '<h2>' . $title . '</h2>';
  // Basic status info.
  $output .= '<div>' . $status . '</div><p>&nbsp;</p>';

  // Add detailed statuses.
  foreach ($details as $type) {
    if ($type) {
      $caption = '<h2>' . $type['title'] . '</h2>';
      $output .= theme('table', array('header' => $type['header'], 'rows' => $type['rows'], 'caption' => $caption));
    }
  }

  return $output;
}
