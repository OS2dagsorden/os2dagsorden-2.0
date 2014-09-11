<?php

/**
 * @file
 * This file describes the Content pushing plugin as implemented by Acadre
 */

/**
 * Plugin definition with callbacks
 */
$plugin = array(
  'description' => t('Acadre ESDH Case Pushing backend'),
  'version' => 1,
  'test' => 'acadre_esdh_cp_test',
  'handle_request' => 'acadre_esdh_cp_handle_request',
);

/**
 * For plugin testing purposes.
 */
function acadre_esdh_cp_test($stuff) {
  return 'Test successful. Recieved: ' . $stuff;
}

/**
 * This functions handles a request on the webservice API.
 */
function acadre_esdh_cp_handle_request() {
  if (isset($_GET['wsdl'])) {
    _acadre_esdh_cp_get_wsdl();
  }
  if (!lock_acquire(__FUNCTION__, 5)) {
    lock_wait(__FUNCTION__);
    return acadre_esdh_cp_handle_request();
  }

  /**
   * Published a given input type.
   *
   * Delegates actual node creation to worker functions.
   *
   * @param mixed $info
   *   Info block from request.
   * @param mixed $parent_item_id
   *   Parent ID from request.
   */
  function publish($info, $parent_item_id) {
    $meta = $info->Metadata;
    // File was decoded to utf-8 data, so charset will break.
    $meta = preg_replace('/(<\?xml[^?]+?)utf-16/i', '$1utf-8', $meta);
    $meta = simplexml_load_string($meta) or soap_error(2);
    $info->Metadata = (object) $meta;

    $type = $meta->getName();
    switch (strtolower($type)) {
      case 'publishedcase':
        return _acadre_esdh_cp_process_case($info);

      default:
        error_log("Unhandled request: \$type = " . print_r($type, 1));
        soap_error(4);
    }
    return 'Ilde request';
  }

  /**
   * Unpublishes a given ItemId.
   *
   * @param mixed $item_id
   *   Item ID from request
   * @param mixed $location_id
   *   Location ID from request. Currently unused.
   */
  function unpublish($item_id, $location_id) {
    $nids = _os2web_acadre_arp_find_item($item_id);
    if (empty($nids)) {
      return 'Success. No nodes removed.';
    }
    else {
      foreach ($nids as $nid) {
        node_delete($nid);
      }
      return 'Success. Removed node-id(s): ' . implode(',', $nids);
    }
  }

  ini_set("soap.wsdl_cache_enabled", "0");
  $server = new SoapServer(drupal_get_path('module', 'acadre_esdh') . '/soap_server.wsdl');
  $server->AddFunction('publish');
  $server->AddFunction('unpublish');
  $server->handle();
}

/**
 * Process case info and generate API arrays.
 *
 * @param array $info
 *   Info block from request.
 */
function _acadre_esdh_cp_process_case($info) {
  $item_id = $info->ItemId;
  $meta = $info->Metadata;
  $node = (object) NULL;
  $node->type = 'arp_case';
  $node->uid = 0;
  $node->status = 1;
  $node->comment = 0;
  $node->promote = 0;
  $node->moderate = 0;
  $node->sticky = 0;
  $node->language = LANGUAGE_NONE;
  $arp_year = $meta->Year % 100;
  node_object_prepare($node);

  $node->title = (string) $meta->Title;
  $node->field_itemid[LANGUAGE_NONE][]['value'] = $item_id;
  $node->body[LANGUAGE_NONE][]['value'] = (string) $meta->CaseContent;
  $node->field_arp_case_type[LANGUAGE_NONE][]['value'] = (string) $meta->CaseType;

  $tid = db_query('SELECT tid FROM  `taxonomy_term_data` WHERE  `name` LIKE  :term', array(
    ':term' => $meta->JournalizingCode[0]->FieldValue . '%',
      ))->fetchField();
  if (is_numeric($tid)) {
    $node->field_termref_kle[LANGUAGE_NONE][]['tid'] = $tid;
  }

  $responsible = $meta->CaseResponsibleUser;
  $node->field_arp_case_handler_ini[LANGUAGE_NONE][]['value'] = $responsible->UserInitials;
  $node->field_arp_casehandler_name[LANGUAGE_NONE][]['value'] = $responsible->UserName;
  $node->field_arp_case_created[LANGUAGE_NONE][]['value'] = strtotime((string) $meta->CreationDate);
  $node->field_arp_case_last_modified[LANGUAGE_NONE][]['value'] = strtotime((string) $meta->CreationDate);
  $node->field_case[LANGUAGE_NONE][]['case_ident'] = $arp_year . '/' . (string) $meta->SequenceNumber;
  $node->field_arp_case_id[LANGUAGE_NONE][]['value'] = $arp_year . '/' . (string) $meta->SequenceNumber;

  node_submit($node);
  node_save($node);
  if (is_numeric($node->nid)) {
    return "Success: Node-id = " . $node->nid;
  }
  else {
    soap_error(3);
  }
}

/**
 * Locates nids with a given ItemId.
 *
 * @param string $item_id
 *   Item ID to locate.
 *
 * @return array
 *   List of nids
 */
function _acadre_esdh_cp_find_item($item_id) {
  $query = new EntityFieldQuery();
  $result = $query
      ->entityCondition('entity_type', 'node')
      ->propertyCondition('type', array('arp_case', 'arp_document'))
      ->propertyCondition('status', 1)
      ->fieldCondition('field_itemid', 'value', $item_id, '=')
      ->execute();
  $nids = array_keys($result['node']);
  return $nids;
}

/**
 * Dumps the wsdl for the serivce.
 */
function _acadre_esdh_cp_get_wsdl() {
  $filename = drupal_get_path('module', 'acadre_esdh') . '/soap_server.wsdl';
  $handle = fopen($filename, 'r');
  $contents = fread($handle, filesize($filename));
  fclose($handle);

  drupal_add_http_header('Connection', 'close', FALSE);
  drupal_add_http_header('Content-Length', drupal_strlen($contents), TRUE);
  drupal_add_http_header('Content-Type', 'text/plain; charset=utf-8', TRUE);
  drupal_add_http_header('Date', date('r'), TRUE);

  $replacements = array(
    '!endpointurl' => 'http' . ($_SERVER['HTTPS'] === 'on' ? 's' : '') . '://' . $_SERVER['SERVER_NAME'] . str_replace('?wsdl', '', request_uri()),
  );
  echo format_string($contents, $replacements);
  exit;
}
