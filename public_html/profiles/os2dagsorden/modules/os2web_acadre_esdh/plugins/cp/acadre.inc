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
  'handle_request' => 'os2web_acadre_esdh_cp_handle_request',
);

/**
 * This functions handles a request on the webservice API.
 */
function os2web_acadre_esdh_cp_handle_request() {
  module_load_include('inc', 'os2web_acadre_esdh', 'plugins/cp/ArpService.class');
  if (isset($_GET['wsdl'])) {
    TraenPublishingDestinationSystemService::getWSDL($_GET['wsdl']);
  }
  if (isset($_GET['xsd'])) {
    TraenPublishingDestinationSystemService::getXSD($_GET['xsd']);
  }
  if (!lock_acquire(__FUNCTION__, 5)) {
    lock_wait(__FUNCTION__);
    return os2web_acadre_esdh_cp_handle_request();
  }

  global $HTTP_RAW_POST_DATA;
  $data = $HTTP_RAW_POST_DATA;
  file_unmanaged_save_data($data, 'public://soap/request-' . time() . '-' . uniqid() . '.xml', FILE_EXISTS_REPLACE);

  ini_set("soap.wsdl_cache_enabled", "1");
  $server = new SoapServer('http' . ((isset($_SERVER['HTTPS']) && $_SERVER['HTTPS'] === 'on') ? 's' : '') . '://' . $_SERVER['SERVER_NAME'] . '/' . request_path() . '/?wsdl', array());
  $server->setObject(new TraenPublishingDestinationSystemService());
  $server->handle();
  lock_release(__FUNCTION__);
}
