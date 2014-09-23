<?php

/**
 * @file
 * The Class which implements the ARP service.
 *
 * @author Jesper Mathiassen <jm@bellcom.dk>
 * @copyright Bellcom Open Source aps.
 */

/**
 * Class that holds the service.
 */
class TraenPublishingDestinationSystemService {

  /**
   * Dumps the wsdl for the serivce.
   */
  public static function getWSDL($wsdl = FALSE) {
    if ($wsdl) {
      $wsdl = str_replace('wsdl', '', $wsdl);
      $filename = 'plugins/cp/TraenPublishingDestinationSystemService' . check_plain($wsdl + 1) . '.wsdl';
    }
    else {
      $filename = 'plugins/cp/TraenPublishingDestinationSystemService.wsdl';
    }
    self::echoFile($filename);
  }

  /**
   * Dumps an xsd for the serivce.
   */
  public static function getXSD($xsd = FALSE) {
    if ($xsd) {
      $xsd = str_replace('xsd', '', $xsd);
      $filename = 'plugins/cp/TraenPublishingDestinationSystemService' . check_plain($xsd + 1) . '.xsd';
    }
    else {
      $filename = 'plugins/cp/TraenPublishingDestinationSystemService.xsd';
    }
    self::echoFile($filename);
  }

  /**
   * Echoes specified file.
   */
  private static function echoFile($filename) {
    $filename = drupal_get_path('module', 'os2web_acadre_esdh') . '/' . $filename;
    if (!file_exists($filename)) {
      drupal_not_found();
    }
    $handle = fopen($filename, 'r');
    $contents = fread($handle, filesize($filename));
    fclose($handle);

    drupal_add_http_header('Connection', 'close', FALSE);
    drupal_add_http_header('Content-Length', drupal_strlen($contents), TRUE);
    drupal_add_http_header('Content-Type', 'text/plain; charset=utf-8', TRUE);
    drupal_add_http_header('Date', date('r'), TRUE);

    echo format_string($contents, array(
      '!endpointurl' => 'http' . ((isset($_SERVER['HTTPS']) && $_SERVER['HTTPS'] === 'on') ? 's' : '') . '://' . $_SERVER['SERVER_NAME'] . '/' . request_path(),
    ));
    exit;
  }

  // *********** PUBLIC API ***************//

  public function RecievedEntityLayout($data) {
    error_log(basename(__FILE__) . ':' . __LINE__ . ' Var: $data = ' . print_r($data, 1));
    return FALSE;
  }

  public function RecievedItemUnPublished($data) {
    $success = FALSE;
    if (isset($data->entityItem->Key->Field->Value)) {
      $function = 'os2web_cp_service_delete';
      if (function_exists($function)) {
        $success = call_user_func($function, $data->entityItem->Key->Field->Value);
      }
    }
    return array('RecievedItemUnPublishedResult' => (bool) $success);
  }

  public function RecievedConfiguration($data) {
    // Function used to handle the configuration.
    $function = 'os2web_cp_service_alter_configuration';
    if (function_exists($function)) {
      foreach ($data->configuration as $configuration_key => $value) {
        if (!empty($value)) {
          call_user_func($function, $configuration_key, $value);
        }
      }
    }
    return array('RecievedConfigurationResult' => TRUE);
  }

  public function RecievedItemPublished($data) {
    switch (strtolower($data->entityItem->EntityName)) {
      case 'sag':
        $type = 'case';
        break;

      case 'dokument':
        $type = 'document';
        break;

      default:
        error_log(__FUNCTION__ . ' unknown EntityName');
        $type = 'unknown';
    }
    $function = 'os2web_cp_service_create_' . $type;
    if (function_exists($function)) {
      $publication = array();
      foreach ($data->entityItem->Fields->Field as $field) {
        if (trim($field->Value) && trim($field->Name)) {
          $publication['fields'][$field->Name] = $field->Value;
        }
      }

      $field = $data->entityItem->Key->Field;
      if (trim($field->Value) && trim($field->Name)) {
        $publication['fields'][$field->Name] = $field->Value;
      }

      // If there only are ONE rule, xml will not return an array.
      if (!is_array($data->entityItem->TriggerRules)) {
        $rule = $data->entityItem->TriggerRules->TriggerRule;
        if ($rule->ID && trim($rule->Name)) {
          $publication['rules'][$rule->ID] = array(
            'name' => $rule->Name,
            'tag' => $rule->Tag,
          );
        }
      }
      else {
        foreach ($data->entityItem->TriggerRules as $rule) {
          if (trim($rule->ID) && trim($rule->Name) && trim($rule->Tag)) {
            $publication['rules'][$rule->ID] = array(
              'name' => $rule->Name,
              'tag' => $rule->Tag,
            );
          }
        }
      }
      $publication['type'] = $type;
      $publication['status'] = $data->entityItem->Status;

      return array('RecievedItemPublishedResult' => (bool) call_user_func($function, $publication));
    }
    else {
      return array('RecievedItemPublishedResult' => FALSE);
    }
  }

  public function __call($name, $arguments) {
    watchdog('os2web_acadre_esdh', 'Unsupported request recieved: %req', array('%req' => $name), WATCHDOG_NOTICE);
    error_log(basename(__FILE__) . ':' . __LINE__ . " Unsupported request recieved: $name");
  }

}
