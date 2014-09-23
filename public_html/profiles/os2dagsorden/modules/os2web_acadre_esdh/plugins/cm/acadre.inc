<?php

/**
 * @file
 * This file describes the CM plugin as implemented by Acadre
 */

/**
 * Plugin definition with callbacks
 */
$plugin = array(
  'description' => t('Acadre ESDH CM Backend'),
  'version' => 1,
  'test' => 'ops2web_acadre_esdh_test',
  'get_document' => 'ops2web_acadre_esdh_get_document',
  'get_document_file' => 'ops2web_acadre_esdh_get_document_file',
  'get_case_docs' => 'ops2web_acadre_esdh_get_case_docs',
  'get_case_data' => 'ops2web_acadre_esdh_get_case_data',
  'lookup_doc' => 'ops2web_acadre_esdh_lookup_doc',
  'lookup_case' => 'ops2web_acadre_esdh_lookup_case',
  'available' => 'ops2web_acadre_esdh_available',
);

/**
 * Test method to verify plugin operationability.
 */
function ops2web_acadre_esdh_test($stuff) {
  return 'Test successful. Recieved: ' . $stuff;
}

/**
 * This opreation check for proper operation.
 *
 * Called often, so static cache is acceptable.
 *
 * @access public
 * @return bool
 *   True if the service is available.
 */
function ops2web_acadre_esdh_available() {
  $drush = function_exists('drush_log');
  $ws = &drupal_static(__FUNCTION__, FALSE);
  if ($ws === FALSE) {
    $pws = _ops2web_acadre_esdh_get_pws_instance();
    $ws['v4'] = $pws->getClient();
    $ws['v6'] = $pws->getClient6();
    $ws['ss'] = $pws->getClientSearch();
  }
  if ($drush) {
    drush_log('Acadre PWS v4 endpoint available: ', $ws['v4'] ? 'ok' : 'error');
    drush_log('Acadre PWS v6 endpoint available: ', $ws['v6'] ? 'ok' : 'error');
    drush_log('SOFD search service available: ', $ws['ss'] ? 'ok' : 'error');
  }

  return $ws['v4'] && $ws['v6'] && $ws['ss'];
}

/**
 * Return data relating to a given Document.
 *
 * @param mixed $doc_id
 *   Docuement ID og string with query.
 *
 * @return array
 *   Document structure
 *
 * @TODO: Rework into generic datatypes for return value
 */
function ops2web_acadre_esdh_get_document($doc_id) {
  $pws = _ops2web_acadre_esdh_get_pws_instance();
  $doc_id = trim($doc_id);
  // Translate the SSSSSS/YY serial into database identifier.
  if (!is_numeric($doc_id)) {
    $doc_id = ops2web_acadre_esdh_lookup_doc($doc_id);
  }
  $doc_data = $pws->getDocument($doc_id);
  if ($doc_data === FALSE) {
    return FALSE;
  }
  $doc = array(
    'id' => $doc_id,
    'case_reference' => $doc_data->Record->CaseFileReference,
    'title' => $doc_data->Document->DocumentTitleText,
    'last_update' => $doc_data->Record->RecordLatestUpdateDate,
    'access_code' => $doc_data->Record->AccessCode,
    'publication_indicator' => $doc_data->Record->PublicationIndicator,
    'lock_status' => $pws->getDocLock($doc_id),
  );
  $doc += os2web_esdh_provider_default_document();
  return $doc;
}

/**
 * Return the actual file object for a given document.
 *
 * @param mixed $doc_id
 *   Docuement ID og string with query.
 *
 * @return object
 *   Drupal file structure
 */
function ops2web_acadre_esdh_get_document_file($doc_id) {
  $pws = _ops2web_acadre_esdh_get_pws_instance();
  $doc_id = trim($doc_id);
  // Translate the SSSSSS/YY serial into database identifier.
  if (!is_numeric($doc_id)) {
    $doc_id = ops2web_acadre_esdh_lookup_doc($doc_id);
  }
  if ($doc_id > 0) {
    $file = $pws->getDocData($doc_id);
    return $file;
  }
  else {
    return (object) NULL;
  }
}

/**
 * Returns a list of documents for a given case.
 *
 * @param mixed $case_id
 *   Case ID og string with query.
 *
 * @return array
 *   List of database ids of the documents related to the case.
 */
function ops2web_acadre_esdh_get_case_docs($case_id) {
  $pws = _ops2web_acadre_esdh_get_pws_instance();
  $case_id = trim($case_id);
  // Translate the SSSSSS/YY serial into database identifier.
  if (!is_numeric($case_id)) {
    $case_id = ops2web_acadre_esdh_lookup_case($case_id);
  }


  $docids = array();
  if ($docs = $pws->getCaseDocs($case_id)) {
    foreach ($docs as $doc) {
      $docids[] = (int) $doc->Document->DocumentIdentifier;
    }
  }
 return $docids;
 }
 


/**
 * Looks up a case if neccesary and return the metadata related to this case.
 *
 * @param mixed $case_id
 *   Case ID og string with query.
 *
 * @return array
 *   Case data structure
 */
function ops2web_acadre_esdh_get_case_data($case_id) {
  $pws = _ops2web_acadre_esdh_get_pws_instance();
  $case_id = trim($case_id);
  // Translate the SSSSSS/YY serial into database identifier.
  if (!is_numeric($case_id)) {
    $case_id = ops2web_acadre_esdh_lookup_case($case_id);
  }

  $case_data = $pws->fetchCase($case_id);
  if ($case_data === FALSE) {
    return FALSE;
  }
  $case = array(
    'id' => $case_id,
    'access_code' => $case_data->AccessCode,
    'restricted_from_public' => $case_data->RestrictedFromPublicText,
  );
  $case += os2web_esdh_provider_default_case();
  return $case;
}

/**
 * Looks up a document query string.
 *
 * @param string $search_id
 *   Query string
 *
 * @return int
 *   Document ID
 */
function ops2web_acadre_esdh_lookup_doc($search_id) {
  $pws = _ops2web_acadre_esdh_get_pws_instance();
  return $pws->lookupDoc(trim($search_id));
}

/**
 * Looks up a case query string.
 *
 * @param string $search_id
 *   Query string
 *
 * @return int
 *   Case ID
 */
function ops2web_acadre_esdh_lookup_case($search_id) {
  $pws = _ops2web_acadre_esdh_get_pws_instance();
  return $pws->lookupCase(trim($search_id));
}

/**
 * Gets the current instance of the WS class.
 *
 * @return AcadrePWS
 *   Facade object for the webservices.
 */
function _ops2web_acadre_esdh_get_pws_instance() {
  $obj = &drupal_static(__FUNCTION__);
  if (is_object($obj)) {
    return $obj;
  }
  module_load_include('inc', 'os2web_acadre_esdh', 'AcadrePWS.class');
  return $obj = new AcadrePWS();
}
