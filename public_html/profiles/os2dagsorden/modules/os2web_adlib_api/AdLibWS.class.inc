<?php

/**
 * @file
 * This file implements a facade class for using the AdLib webservice
 */

define('ADLIB_JOBTYPE_PDF', 0);
define('ADLIB_JOBTYPE_HTML', 1);
define('ADLIB_DISABLED', !variable_get('os2web_adlib_api_is_allowed', 0));


/**
 * Description of AdLibWS
 *
 * @author jm
 */
class AdLibWS {

  protected $client;
  // Private static $base_path = 'd:\\wwwroot\\';
  protected static $basePath = 'C:\\InetPub\\wwwroot\\';
  protected static $baseUrl = 'http://10.1.1.180/';

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
   * Initializes connector.
   */
  public function __construct() {
    if (ADLIB_DISABLED) {
      // error_log('MARK - ' . basename(__FILE__) . ':' . __LINE__ . ' - AdLib presently disabled.');
      return;
    }
    if (!isset($this->client)) {
      $options = array(
        'soapversion' => SOAP_1_2,
        'trace' => TRUE,
      );
      if (variable_get('os2web_pws_proxy', FALSE)) {
        $options['proxy_host'] = variable_get('os2web_pws_proxy_host');
        $options['proxy_port'] = variable_get('os2web_pws_proxy_port');
      }
      $url = variable_get('os2web_adlib_url', FALSE);
      if ($this->checkUrl($url)) {
        if (function_exists('xdebug_disable')) {
          xdebug_disable();
        }
        try {
          if (FALSE !== $url) {
            $this->client = new SoapClient($url, $options);
          }
        } catch (Exception $exc) {
          watchdog('adlib_api', 'Error creating AdLib client, message: %var', array('%var' => $exc->getMessage()), WATCHDOG_ERROR);
        }
        if (function_exists('xdebug_enable')) {
          xdebug_enable();
        }
      }
    }
  }

  /**
   * Starts a job on the adlib server.
   *
   * @param array $file_info
   *   Fileinfo structure
   */
  public function addJob($file_info, $type = ADLIB_JOBTYPE_PDF, $priority = 3) {
    if (ADLIB_DISABLED) {
      return FALSE;
    }
    if (!isset($this->client)) {
      return FALSE;
    }
    $job_info = '<?xml version="1.0" encoding="UTF-8"?>
<JobInfo>
  <JobSettings JobID="" UserJobID="" JobPriority="!priority" AdlibServer="" AdlibServerGroup=""/>
  <JobFileMsg Count=""/>
  <JobFileList>
    <JobFile Filename="" Folder=""/>
  </JobFileList>
</JobInfo>';
    $job_info = format_string($job_info, array('!priority' => $priority));
    $job_ticket = '<?xml version="1.0" encoding="UTF-8"?>
<?AdlibExpress applanguage="USA" appversion="2.5" dtdversion="1.0" ?>
<!DOCTYPE JOBS SYSTEM "C:\Adlib Express\DTD\AdlibExpress.dtd">
<JOBS xmlns:JOBS="http://www.Adlibsoftware.com" xmlns:JOB="http://www.Adlibsoftware.com">
  <JOB>
    <JOB:DOCINPUTS>
      <JOB:DOCINPUT FILENAME="!infile" FOLDER="!infolder" />
    </JOB:DOCINPUTS>
    <JOB:DOCOUTPUTS>
      <JOB:DOCOUTPUT FILENAME="!outfile" FOLDER="!outfolder" DOCTYPE="!jobtype" />
    </JOB:DOCOUTPUTS>
    <JOB:SETTINGS>
      <JOB:HEADER ENABLED="Yes" TEXTRIGHT="&amp;[Page] of &amp;[Pages]" LAYER="Foreground" />
      <JOB:NATIVEAPPSETTINGS>
        <JOB:MSOUTLOOK CONVERSIONMODE="IFTS" PROCESSATTACHMENTS="No"/>
      </JOB:NATIVEAPPSETTINGS>
    </JOB:SETTINGS>
  </JOB>
</JOBS>';
    $job_ticket = format_string($job_ticket, array(
      '!infile' => $this->safeFilename($file_info['filename']),
      '!infolder' => self::$basePath . $file_info['in_folder'],
      '!outfile' => $this->safeFilename($file_info['out_filename']),
      '!outfolder' => self::$basePath . $file_info['out_folder'],
      '!jobtype' => ($type == ADLIB_JOBTYPE_HTML ? 'HTML' : 'PDF'),
        ));
    $result = simplexml_load_string($this->client->addJob(array('jobInfo' => $job_info, 'jobTicket' => $job_ticket))->AddJobResult);
    if (is_object($result) && isset($result->JobSettings['JobID'])) {
      return $result;
    }
    else {
      $msg = (string) array_pop($result->xpath('//@Message'));
      if ($msg == '') {
        $msg = 'Unknown reason.';
      }
      error_log(basename(__FILE__) . ':' . __LINE__ . " jm@bellcom.dk: Failed to add job. Reason: " . $msg);
      return FALSE;
    }
  }

  /**
   * Invokes deleteJob.
   *
   * @param string $id
   *   Job id
   *
   * @return object
   *   Result and status
   */
  public function deleteJob($id) {
    if (ADLIB_DISABLED) {
      $return->status = 'Disabled';
      $return->result = '';
      return $return;
    }
    if (isset($id->JobSettings['JobID'])) {
      $id = $id->JobSettings['JobID'];
    }
    if (isset($this->client)) {
      $this->client->deleteJob(array('jobID' => $id, 'isUserJobID' => FALSE));
    }
  }

  /**
   * Invokes deleteFolder.
   *
   * @param string $id
   *   Folder id
   *
   * @return object
   *   False on error
   */
  public function deleteJobFolder($id) {
    if (ADLIB_DISABLED) {
      return FALSE;
    }
    if (isset($this->client)) {
      $reply = $this->client->deleteJobFolder(array('JobFolder' => $id));
      return $reply;
    }
  }

  /**
   * Gets a list of connectors and their status.
   *
   * @return string
   *   Connector status message
   */
  public function getConnectorStatusList() {
    if (ADLIB_DISABLED) {
      return 'Adblib connection disabled.';
    }
    if (isset($this->client)) {
      $result = $this->client->getConnectorStatusList()->GetConnectorStatusListResult;
      $result = simplexml_load_string($result);
      if (is_object($result)) {
        return $result->xpath('//Server');
      }
      else {
        return 'Invalid response from AdLib.';
      }
    }
    return 'AdLib connection failed.';
  }

  /**
   * Invokes getJobStatus.
   *
   * @param string $id
   *   Job id
   *
   * @return object
   *   Result and status
   */
  public function getJobStatus($id) {
    if (ADLIB_DISABLED) {
      $return->status = 'Disabled';
      $return->result = '';
      return $return;
    }
    if (isset($id->JobSettings['JobID'])) {
      $id = $id->JobSettings['JobID'];
    }
    if (isset($this->client)) {
      $result = $this->client->getJobStatus(array('jobID' => $id, 'isUserJobID' => FALSE))->GetJobStatusResult;
      $return = (object) array();
      if (strncmp('<', $result, 1) === 0) {
        $return->status = (string) simplexml_load_string($result)->CurrentJobStatus['Status'];
        $return->result = simplexml_load_string($result);
      }
      else {
        $return->status = 'Not found';
        $return->result = $result;
      }
    }
    else {
      $return->status = 'Not found';
    }
    if ($return->status === '') {
      $message = (string) $return->result->ServerInfo[0]->Error['Message'];
      error_log(basename(__FILE__) . ':' . __LINE__ . ' AdLib Error: ' . $message);
      $return->status = 'Not Available';
    }
    elseif ($return->status === 'Pending') {
      // error_log("ConnectorStatus is " . $return->result->CurrentJobStatus['ConnectorStatus']);
    }
    else {
      // error_log(basename(__FILE__) . ':' . __LINE__ . " jm@bellcom.dk: Looked up status for job: " . $id . " Status: " . $return->status);
    }
    return $return;
  }

  /**
   * Invokes addJobFolder.
   *
   * @return string
   *   Adlib folder
   */
  public function addJobFolder() {
    if (ADLIB_DISABLED) {
      return FALSE;
    }
    if ($this->client) {
      $reply = simplexml_load_string($this->client->addJobFolder()->AddJobFolderResult);
      $folder_info = $reply;
      $result = 'ExponentJobs\\' . ((string) $folder_info['FolderID']);
      watchdog('adlib_api', 'Added a folder: %folder', array('%folder' => $result), WATCHDOG_DEBUG);
      return $result;
    }
  }

  /**
   * This method uploads a file to AdLib server.
   *
   * @param string $filename
   *   Filename
   * @param mixed $data
   *   Binary contents of data
   * @param string $folder
   *   Optional. Adlib folder, if ommited, new folder is created.
   *
   * @return mixed
   *   False if call failed, otherwise a fileinfo structure
   */
  public function uploadData($filename, $data, $type = ADLIB_JOBTYPE_PDF, $folder = NULL) {
    if (ADLIB_DISABLED) {
      return FALSE;
    }
    if (!isset($this->client)) {
      return FALSE;
    }
    switch ($type) {
      case ADLIB_JOBTYPE_HTML:
        $jobtype = 'HTML';
        $jobext = 'htm';
        break;

      default:
        $jobtype = 'PDF';
        $jobext = 'pdf';
        break;
    }
    if (!isset($folder)) {
      $folder = $this->addJobFolder();
    }
    if (!$folder) {
      error_log('MARK - ' . basename(__FILE__) . ':' . __LINE__ . ' in ' . __FUNCTION__ . '() - Adding folder failed.');
      return FALSE;
    }
    $payload = '
      <JobFiles>
        <JobFile FileName="' . $this->safeFilename($filename) . '" Data="' . base64_encode($data) . '" Length="' . strlen($data) . '" />
      </JobFiles>';
    $result = $this->client->AddJobFilesAsStream(array(
          'JobFolder' => $folder . '\\Input',
          'XmlStream' => $payload,
        ))->AddJobFilesAsStreamResult;
    $status = (string) simplexml_load_string($result)->System['Status'];
    if (strcmp($status, 'Success') == 0) {
      error_log(basename(__FILE__) . ':' . __LINE__ . " jm@bellcom.dk: Uploaded file: " . $filename);
      return array(
        'basefolder' => $folder,
        'in_folder' => $folder . '\\Input',
        'out_folder' => $folder . '\\Output',
        'out_url' => self::$baseUrl . str_replace('\\', '/', $folder . '/Output/') . rawurlencode($this->safeFilename(pathinfo($filename, PATHINFO_FILENAME) . '.' . $jobext)),
        'filename' => $filename,
        'job_type' => $jobtype,
        'out_filename' => pathinfo($filename, PATHINFO_FILENAME) . '.' . $jobext,
      );
    }
    else {
      error_log(basename(__FILE__) . ':' . __LINE__ . " jm@bellcom.dk: Failed to upload: " . $filename);
      watchdog('adlib_api', 'Upload of %filename failed with message: %msg', array('%file' => $filename, '%msg' => $result), WATCHDOG_ERROR);
      $folder = explode('\\', $folder);
      $this->deleteJobFolder($folder[1]);
      return FALSE;
    }
  }

  /**
   * Encrypts filename, making is safe for use on AdLib.
   *
   * @param string $fname
   *   File name
   *
   * @return string
   *   Encrypted file name
   */
  protected function safeFilename($fname) {
    $pi = pathinfo($fname);
    $safe_name = md5($pi['filename']);
    if (isset($pi['extension'])) {
      $safe_name .= '.' . $pi['extension'];
    }
    return $safe_name;
  }

}
