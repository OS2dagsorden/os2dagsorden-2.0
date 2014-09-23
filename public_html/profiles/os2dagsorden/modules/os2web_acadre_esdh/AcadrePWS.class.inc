<?php

/**
 * @file
 * This file implements a facade class for the PWS webservices
 */

define('PWS_CACHE_TIMEOUT', 3600 * 4);
define('ACADRE_CM_DEFAULT_DOC_CACHE_PATH', 'public://pws_documents/');

class AcadrePWS {

  private $client;
  private $client6;
  private $clientSearch;

  /**
   * Heuristic to validate url availability.
   */
  private function checkUrl($url) {
    $handle = curl_init($url);
    curl_setopt($handle, CURLOPT_RETURNTRANSFER, TRUE);
    curl_setopt($handle, CURLOPT_CONNECTTIMEOUT, 2);
    curl_exec($handle);
    $http_code = curl_getinfo($handle, CURLINFO_HTTP_CODE);
    curl_close($handle);
    // Since this is just a heuristic, we allow access denied (401) for further check.
    return in_array($http_code, array(200, 401));
  }

  /**
   * Basic setup for SOAP connections.
   */
  private function getBaseWSSetup() {
    $user = variable_get('os2web_pws_user');
    $password = variable_get('os2web_pws_password');

    $proxy = variable_get('os2web_pws_proxy', FALSE);
    $proxy_host = variable_get('os2web_pws_proxy_host');
    $proxy_port = variable_get('os2web_pws_proxy_port');
    $options['trace'] = FALSE;
    $options['exceptions'] = TRUE;
    $options['login'] = $user;
    $options['cache_wsdl'] = WSDL_CACHE_BOTH;
    $options['password'] = $password;
    $options['soap_version'] = SOAP_1_1;
    if ($proxy) {
      $options['proxy_host'] = $proxy_host;
      $options['proxy_port'] = $proxy_port;
    }
    return $options;
  }

  /**
   * Initializes the v4 client interface.
   */
  public function getClient() {
    $this->client = &drupal_static('os2web_acadre_pws_client', NULL);
    if (!$this->client) {
      $url = variable_get('os2web_pws_url');
      $url = trim($url);
      if ($url == '') {
        drupal_set_message(t('Error, no endpoint url set for v4soap.'), 'error');
      }
      else {
        if ($this->checkUrl($url)) {
          // FIXME: Use a wellformed WSDL for V4 services.
          $options = $this->getBaseWSSetup();
          $options['location'] = $url;
          $options['uri'] = 'http://www.traen.com/2007/09/06/';
          if (function_exists('xdebug_disable')) {
            xdebug_disable();
          }
          try {
            $this->client = new SoapClient(NULL, $options);
          }
          catch (Exception $e) {
            drupal_set_message(t('Error connecting to PWSv4 endpoint'), 'error');
            return FALSE;
          }
          if (function_exists('xdebug_enable')) {
            xdebug_enable();
          }
        }
      }
    }
    return isset($this->client);
  }

  /**
   * Initializes the v5 client.
   */
  public function getClient6() {
    $this->client6 = &drupal_static('os2web_acadre_pws_client6');
    if (!$this->client6) {
      $url = variable_get('os2web_pws_url_v6');
      $url = trim($url);
      if ($url == '') {
        drupal_set_message(t('Error, no endpoint url set for v6.'), 'error');
      }
      else {
        if ($this->checkUrl($url)) {
          $options = $this->getBaseWSSetup();
          if (function_exists('xdebug_disable')) {
            xdebug_disable();
          }
          try {
            $this->client6 = new SoapClient($url . '?WSDL', $options);
          }
          catch (Exception $sf) {
            drupal_set_message(t('Error connecting to PWSv6 endpoint'), 'error');
            return FALSE;
          }
          if (function_exists('xdebug_enable')) {
            xdebug_enable();
          }
        }
      }
    }
    return isset($this->client6);
  }

  /**
   * Initializes the case lookup service.
   */
  public function getClientSearch() {
    $this->clientSearch = &drupal_static('os2web_acadre_pws_client_search');
    if (!$this->clientSearch) {
      $url = variable_get('os2web_pws_url_search');
      $url = trim($url);
      if ($url == '') {
        drupal_set_message(t('Error, no endpoint url set for document search searvice.'), 'error');
      }
      else {
        if ($this->checkUrl($url)) {
          $options = $this->getBaseWSSetup();
          if (function_exists('xdebug_disable')) {
            xdebug_disable();
          }
          try {
            $this->clientSearch = new SoapClient($url . '?WSDL', $options);
            return TRUE;
          }
          catch (SoapFault $sf) {
            drupal_set_message(t('Error connecting to PWS document search service endpoint'), 'error');
            return FALSE;
          }
          if (function_exists('xdebug_enable')) {
            xdebug_enable();
          }
        }
      }
    }
    return isset($this->clientSearch);
  }

  /**
   * Looks up a journaling entry and returns the id of a case.
   *
   * FIXME: Make this a TRUE call to webservice.
   *
   * @param string $query
   *   A case journaling number, ie. 11/14293
   */
  public function lookupCase($query) {
    $cid = __FUNCTION__ . $query;
    $result = &drupal_static($cid, FALSE);
    if ($result != FALSE) {
      return $result;
    }
    if (($cache = cache_get($cid, 'cache_os2web_pws')) && !empty($cache->data) && (time() < $cache->expire)) {
      $result = $cache->data;
    }
    elseif ($this->getClientSearch()) {
      $query = str_replace('-', '/', $query);
      $query = explode('/', $query);
      if (is_numeric($query[0]) && is_numeric($query[1])) {
        try {
          $result = (int) $this->clientSearch->getCaseSystemIdByYearAndSerial(array('year' => $query[0], 'serial' => $query[1]))->GetCaseSystemIdByYearAndSerialResult;
          cache_set($cid, $result, 'cache_os2web_pws', time() + PWS_CACHE_TIMEOUT);
        }
        catch (SoapFault $sf) {
          $trace = $this->clientSearch->__getLastRequest();
          error_log(basename(__FILE__) . ':' . __LINE__ . ' Var: $trace = ' . print_r($trace, 1));
          $result = $sf;
        }
      }
    }
    return $result;
  }

  /**
   * Looks up a journaling entry and returns the id of a document.
   *
   * @param string $query
   *   A case journaling number, ie. 14293/11
   */
  public function lookupDoc($query) {
    $cid = __FUNCTION__ . $query;
    $result = &drupal_static($cid, FALSE);
    if ($result != FALSE) {
      return $result;
    }
    if (($cache = cache_get($cid, 'cache_os2web_pws')) && !empty($cache->data) && (time() < $cache->expire)) {
      $result = $cache->data;
    }
    elseif ($this->getClientSearch()) {
      $query = str_replace('-', '/', $query);
      $query = explode('/', $query);
      if (is_numeric($query[0]) && is_numeric($query[1])) {
        try {
          $result = (int) $this->clientSearch->getDocumentSystemIdByYearAndSerial(array('year' => $query[1], 'serial' => $query[0]))->GetDocumentSystemIdByYearAndSerialResult;
          $result = $result != -1 ? $result : FALSE;
          cache_set($cid, $result, 'cache_os2web_pws', time() + PWS_CACHE_TIMEOUT);
        }
        catch (SoapFault $sf) {
          $result = $sf;
        }
      }
    }
    return $result;
  }

  /**
   * Get metadata for a case by id.
   *
   * @param int $id
   *   Case identifier
   *
   * @return mixed
   *   array with info on success, FALSE otherwise
   */
  public function fetchCase($id) {
    $cid = __FUNCTION__ . $id;
    $result = &drupal_static($cid, FALSE);
    if ($result != FALSE) {
      return $result;
    }
    if (($cache = cache_get($cid, 'cache_os2web_pws')) && !empty($cache->data) && (time() < $cache->expire)) {
      $result = $cache->data;
    }
    elseif ($this->getClient6()) {
      try {
        $result = $this->client6->getCase($id);
        cache_set($cid, $result, 'cache_os2web_pws', time() + PWS_CACHE_TIMEOUT);
      }
      catch (SoapFault $exc) {
        // TODO: Handle exception better...
        error_log("Var: \$exc = " . print_r($exc, 1));
        return FALSE;
      }
    }
    return $result;
  }

  /**
   * Returns the document id's for a given case.
   *
   * @param int $id
   *   Case ID
   *
   * @return mixed
   *   Return FALSE on error, else array of documents
   */
  public function getCaseDocs($id) {
    $result = &drupal_static(__FUNCTION__ . $id, FALSE);
    if ($result != FALSE) {
      return $result;
    }
    if (($cache = cache_get(__FUNCTION__ . $id, 'cache_os2web_pws')) && !empty($cache->data) && (time() < $cache->expire)) {
      $result = $cache->data;
    }
    else {
      if ($this->getClient()) {
        $request = '<?xml version="1.0" encoding="utf-8"?>
          <soap:Envelope xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:soap="http://schemas.xmlsoap.org/soap/envelope/">
          <soap:Body>
          <CaseFileIdentifier xmlns="http://www.traen.com/2007/09/06/schema">!CaseID</CaseFileIdentifier>
          </soap:Body>
          </soap:Envelope> ';
        $request = format_string($request, array('!CaseID' => $id));
        try {
          $result = $this->client->__doRequest($request, $this->client->location, $this->client->uri . 'GetAllDocuments', SOAP_1_1);
          cache_set(__FUNCTION__ . $id, $result, 'cache_os2web_pws', time() + PWS_CACHE_TIMEOUT);
        }
        catch (SoapFault $sf) {
          error_log(basename(__FILE__) . ':' . __LINE__ . ' Var: $sf = ' . print_r($sf, 1));
          return FALSE;
        }
      }
    }
    if (is_string($result)) {
      $result = simplexml_load_string($result)->xpath('//soap:Body[1]/*/*');
    }
    else {
      return FALSE;
    }
    return $result;
  }

  /**
   * Returns the lock status for a document.
   *
   * @param int $id
   *   Document ID
   *
   * @return bool
   *   True is case is locked, else false.
   */
  public function getDocLock($id) {
    $cid = __FUNCTION__ . $id;
    $result = &drupal_static($cid, FALSE);
    if ($result != FALSE) {
      return $result;
    }
    if (($cache = cache_get($cid, 'cache_os2web_pws')) && !empty($cache->data) && (time() < $cache->expire)) {
      $result = $cache->data;
    }
    elseif ($this->getClient()) {
      $request = '<?xml version="1.0" encoding="utf-8"?>
<soap:Envelope xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:soap="http://schemas.xmlsoap.org/soap/envelope/">
  <soap:Body>
    <GetLockStatusDocumentId xmlns="http://www.traen.com/2007/09/06/schema">[DocID]</GetLockStatusDocumentId>
  </soap:Body>
</soap:Envelope>';
      try {
        $result = $this->client->__doRequest(t($request, array('[DocID]' => $id)), $this->client->location, $this->client->uri . 'GetLockStatus', SOAP_1_1);
        $result = simplexml_load_string($result);
        if (is_object($result)) {
          if ('' !== (string) array_pop($result->xpath('//soap:Fault/faultcode'))) {
            // This will indicate fault.
            $result = FALSE;
          }
          else {
            $result = $result->xpath('//soap:Body');
            $result = ('true' === (string) $result[0]->DocumentLockStatus) ? TRUE : FALSE;
          }
        }
      }
      catch (SoapFault $sf) {

      }
      cache_set($cid, $result, 'cache_os2web_pws', time() + PWS_CACHE_TIMEOUT);
    }
    return $result;
  }

  /**
   * Returns an info block for a document.
   *
   * @param int $id
   *   Document ID
   *
   * @return mixed
   *   False on error, otherwise a valid document structure.
   */
  public function getDocInfo($id) {
    $cid = __FUNCTION__ . $id;
    $result = &drupal_static($cid, FALSE);
    if ($result != FALSE) {
      return $result;
    }
    if (($cache = cache_get($cid, 'cache_os2web_pws')) && !empty($cache->data) && (time() < $cache->expire)) {
      $result = $cache->data;
    }
    elseif ($this->getClientSearch()) {
      try {
        $result = $this->clientSearch->getDocumentById(array('id' => $id));
        $result = $result->GetDocumentByIdResult;
        cache_set($cid, $result, 'cache_os2web_pws', time() + PWS_CACHE_TIMEOUT);
      }
      catch (SoapFault $sf) {
        $result = FALSE;
      }
    }
    return $result;
  }

  /**
   * Returns document meta-data.
   *
   * @param int $id
   *   Document ID
   *
   * @return bool
   *   False on error, otherwise a document XML block.
   */
  public function getDocument($id) {
    $cid = __FUNCTION__ . $id;
    $result = &drupal_static($cid, FALSE);
    if ($result != FALSE) {
      return $result;
    }
    if (($cache = cache_get($cid, 'cache_os2web_pws')) && !empty($cache->data) && (time() < $cache->expire)) {
      $result = $cache->data;
    }
    elseif ($this->getClient6()) {
      try {
        $result = $this->client6->getMainDocument($id);
        cache_set($cid, $result, 'cache_os2web_pws', time() + PWS_CACHE_TIMEOUT);
      }
      catch (SoapFault $sf) {
        $result = FALSE;
      }
    }
    return $result;
  }

  /**
   * Returns the document reference and version.
   *
   * @param int $id
   *   Document ID
   *
   * @return bool
   *   False on error, otherwise an array with reference and version.
   */
  public function getDocRef($id) {
    $doc = $this->getDocument($id);
    if (isset($doc->DocumentVersion->DocumentFileReference) && isset($doc->DocumentVersion->VersionNumber)) {
      return array(
        'ref' => $doc->DocumentVersion->DocumentFileReference,
        'ver' => $doc->DocumentVersion->VersionNumber,
      );
    }
    else {
      return FALSE;
    }
  }

  /**
   * Gets the filename for a document.
   *
   * @param int $ref
   *   Document reference, or document ID
   * @param int $ver
   *   Document version, if $ref is reference, otherwise ommited.
   *
   * @return string
   *   Document filename
   */
  public function getDocFileName($ref, $ver = FALSE) {
    $result = FALSE;
    if (!is_numeric($ver)) {
      $info = $this->getDocRef($ref);
      $ref = $info['ref'];
      $ver = $info['ver'];
    }
    $cid = __FUNCTION__ . $ref . $ver;
    if (($cache = cache_get($cid, 'cache_os2web_pws')) && !empty($cache->data) && (time() < $cache->expire)) {
      $result = $cache->data;
    }
    elseif ($this->getClient()) {
      $request = '<?xml version="1.0" encoding="utf-8"?>
<soap:Envelope xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:soap="http://schemas.xmlsoap.org/soap/envelope/">
  <soap:Body>
    <FileVersionReference1 xmlns="http://www.traen.com/2007/09/06/schema">
      <FileReference>@FileRef</FileReference>
      <Version>@Version</Version>
    </FileVersionReference1>
  </soap:Body>
</soap:Envelope>';
      try {
        $result = $this->client->__doRequest(t($request, array('@FileRef' => $ref, '@Version' => $ver)), $this->client->location, $this->client->uri . 'GetFileName', SOAP_1_1);
        if (is_object($result = simplexml_load_string($result))) {
          $result = (string) array_shift($result->xpath('//soap:Body'))->FileName1;
          // Use md5sum to avoid long  and guessable filenames.
          $info = pathinfo($result);
          $result = md5('adlibsalt' . $info['basename']) . '.' . $info['extension'];
          cache_set($cid, $result, 'cache_os2web_pws', time() + PWS_CACHE_TIMEOUT);
        }
      }
      catch (SoapFault $sf) {
        error_log("Var: \$sf = " . print_r($sf, 1));
      }
    }
    return $result;
  }

  /**
   * Gets a document as an actual file.
   *
   * @param int $id
   *   Document reference, or document ID
   * @param int $ver
   *   Document version, if $ref is reference, otherwise ommited.
   *
   * @return object
   *   Drupal file object.
   */
  public function getDocData($id, $ver = FALSE) {
    $dest = ACADRE_CM_DEFAULT_DOC_CACHE_PATH;
    $result = FALSE;
    if (!is_numeric($ver)) {
      $info = $this->getDocRef($id);
      $ref = $info['ref'];
      $ver = $info['ver'];
    }
    drupal_load('module', 'os2web_adlib_api');

    // Cache files unless there is a newer version available.
    $fid = os2web_adlib_api_get_fid($ref);
    if ($fid > 0 && ($result = file_load($fid)) && is_file(drupal_realpath($result->uri))) {
      // error_log(basename(__FILE__) . ':' . __LINE__ . " jm@bellcom.dk: File cached.");
      $ctime = filectime(drupal_realpath($result->uri));
      $info = $this->getDocInfo($id);
      if (is_object($info)) {
        $updated = strtotime($info->ChangedDateTime);
        if ($updated < $ctime) {
          $result = file_create_url($result->uri);
          return $result;
        }
      }
    }

    // Clean up failed files.
    if (is_object($result) && !is_file(drupal_realpath($result->uri))) {
      error_log('MARK - ' . basename(__FILE__) . ':' . __LINE__ . ' Failed file ' . $result->filename);
      file_delete($result, TRUE);
    }

    error_log(basename(__FILE__) . ':' . __LINE__ . " jm@bellcom.dk: Fetching file from WS. Ref: $ref");
    if ($this->getClient()) {
      $request = '<?xml version="1.0" encoding="utf-8"?>
<soap:Envelope xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:soap="http://schemas.xmlsoap.org/soap/envelope/">
  <soap:Body>
    <FileVersionReference xmlns="http://www.traen.com/2007/09/06/schema">
      <FileReference>@FileRef</FileReference>
      <Version>@Version</Version>
    </FileVersionReference>
  </soap:Body>
</soap:Envelope>';
      try {
        $result = $this->client->__doRequest(t($request, array('@FileRef' => $ref, '@Version' => $ver)), $this->client->location, $this->client->uri . 'GetPhysicalDocument', SOAP_1_1);
        if (is_object($result = simplexml_load_string($result))) {
          $result = (string) array_shift($result->xpath('//soap:Body'))->XMLBinary;
          if (file_prepare_directory($dest, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS)) {
            $filename = (string) $ref . '-' . (string) $ver . '-' . $this->getDocFileName($ref, $ver);
            if (isset($fid) && $fid > 0) {
              $unm_file = file_unmanaged_save_data(base64_decode($result), $dest . $filename, FILE_EXISTS_REPLACE);
              $file = file_load($fid);
              $file->uri = $unm_file;
              $file->filename = basename($unm_file);
              file_save($file);
            }
            else {
              $file = file_save_data(base64_decode($result), $dest . $filename, FILE_EXISTS_REPLACE);
            }
            if (FALSE != $file) {
              if (drupal_load('module', 'os2web_adlib_api')) {
                os2web_adlib_api_convert_to_pdf($file->fid, $ref);
              }
              $result = file_create_url($file->uri);
            }
            else {
              drupal_set_message(t('There was an error saving the file'), 'error');
            }
          }
          else {
            drupal_set_message(t('There was an error creating the file'), 'error');
          }
        }
        else {
          error_log('MARK - ' . basename(__FILE__) . ':' . __LINE__ . ' - Error parse output from WS.');
          return FALSE;
        }
      }
      catch (SoapFault $sf) {
        watchdog('acadre_pws', 'Error during SOAP call in ' . __FUNCTION__, NULL, WATCHDOG_WARNING);
      }
    }
    return $result;
  }

  /**
   * Gets the binary data for a document.
   *
   * @param int $ref
   *   Document reference, or document ID
   * @param int $ver
   *   Document version, if $ref is reference, otherwise ommited.
   *
   * @return string
   *   Document contents
   */
  public function getDocDataRaw($ref, $ver = FALSE) {
    $result = FALSE;
    if (!is_numeric($ver)) {
      $info = $this->getDocRef($ref);
      $ref = $info['ref'];
      $ver = $info['ver'];
    }
    $cid = __FUNCTION__ . $ref . $ver;
    if (($cache = cache_get($cid, 'cache_os2web_pws')) && !empty($cache->data) && (time() < $cache->expire)) {
      $result = $cache->data;
    }
    elseif ($this->getClient()) {
      $request = '<?xml version="1.0" encoding="utf-8"?>
<soap:Envelope xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:soap="http://schemas.xmlsoap.org/soap/envelope/">
  <soap:Body>
    <FileVersionReference xmlns="http://www.traen.com/2007/09/06/schema">
      <FileReference>@FileRef</FileReference>
      <Version>@Version</Version>
    </FileVersionReference>
  </soap:Body>
</soap:Envelope>';
      try {
        $result = $this->client->__doRequest(t($request, array('@FileRef' => $ref, '@Version' => $ver)), $this->client->location, $this->client->uri . 'GetPhysicalDocument', SOAP_1_1);
        $result = (string) array_shift(simplexml_load_string($result)->xpath('//soap:Body'))->XMLBinary;
        cache_set($cid, $result, 'cache_os2web_pws', time() + PWS_CACHE_TIMEOUT);
      }
      catch (SoapFault $sf) {
        return FALSE;
      }
    }
    return $result;
  }

}
