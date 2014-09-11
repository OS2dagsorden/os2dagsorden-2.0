<?php
/**
 * os2dagsorden_adlib_api
 *
 * PHP version 5
 *
 * @category OS2Dagsorden
 * @package  OS2Dagsorden_Adlib_Api
 * @file     The connection to Adlib service.
 * @author   Jesper Mathiassen <jm@bellcom.dk>
 * @license  http://www.gnu.org/licenses/gpl-2.0.html GNU General Public License, version 2
 * @link     http://bellcom.dk
 */

define('ADLIB_JOBTYPE_PDF', 0);
define('ADLIB_JOBTYPE_HTML', 1);
define('ADLIB_DISABLED', FALSE);

/**
 * Description of AdLibWS
 * 
 * @category OS2Dagsorden
 * @package  OS2Dagsorden_Adlib_Api
 * @file     The connection to Adlib service.
 * @author   Jesper Mathiassen <jm@bellcom.dk>
 * @license  http://www.gnu.org/licenses/gpl-2.0.html GNU General Public License, version 2
 * @link     http://bellcom.dk
 */
class AdLibWS {

  private $client;
  //private static $base_path = 'd:\\wwwroot\\';
  private static $base_path = 'C:\\InetPub\\wwwroot\\';
  private static $base_url = 'http://10.1.1.180/';

  public function __construct() {
    if (ADLIB_DISABLED)
      return;
    if (!isset($this->client)) {
      $options = array(
          'soapversion' => SOAP_1_2,
          'trace' => TRUE,
      );
      if (variable_get('os2web_pws_proxy', FALSE)) {
        $options['proxy_host'] = variable_get('os2web_pws_proxy_host');
        $options['proxy_port'] = variable_get('os2web_pws_proxy_port');
      }
      $url = variable_get('os2web_adlib_url', 'http://706CAR01/ExponentWSA/ExponentWSA.asmx?wsdl');
      $url = preg_replace('/([fhtps]{3,5}):\/\/(.+?)\//', self::$base_url, $url);
      preg_match('%http://.+?/%', $url, $matches);
      self::$base_url = array_shift($matches);
      if (function_exists('xdebug_disable'))
        xdebug_disable();
      try {
        $this->client = new SoapClient($url, $options);
        //error_log(basename(__FILE__) . ':' . __LINE__ . " jm@bellcom.dk: Created SOAP client.");
      } catch (Exception $exc) {
	watchdog('adlib_api', 'Error creating AdLib client, message: %var', array('%var' => $exc->getMessage()), WATCHDOG_ERROR);
       }
      }
  }

  /**
    * Starts a job on the adlib server
    *
    * @param array $fileInfo fileinfo structure
    * @param mixed $type     type of the job
    * 
    * @return type
    */
  public function addJob($fileInfo, $type = ADLIB_JOBTYPE_PDF, $priority = 3) {
    if (ADLIB_DISABLED)
      return false;
    if (!isset($this->client)) {
      return false;
    }
    $jobInfo = '<JobInfo>
        <JobSettings JobID="" UserJobID="" JobPriority="' . $priority . '" AdlibServer="" AdlibServerGroup=""/>
        <JobFileMsg Count=""/>
        <JobFileMsg Count=""/>
        <JobFileList>
          <JobFile Filename="" Folder=""/>
        </JobFileList>
      </JobInfo>';
    $jobTicket = '<?xml version="1.0" encoding="UTF-8"?>
        <?AdlibExpress applanguage="USA" appversion="2.5" dtdversion="1.0" ?>
        <!DOCTYPE JOBS SYSTEM "C:\Adlib Express\DTD\AdlibExpress.dtd">
        <JOBS xmlns:JOBS="http://www.Adlibsoftware.com" xmlns:JOB="http://www.Adlibsoftware.com">
          <JOB>
            <JOB:DOCINPUTS>
               <JOB:DOCINPUT FILENAME="' . $this->safeFilename($fileInfo['filename']) . '" FOLDER="' . self::$base_path . $fileInfo['in_folder'] . '" />
            </JOB:DOCINPUTS>
            <JOB:DOCOUTPUTS>
              <JOB:DOCOUTPUT FILENAME="' . $this->safeFilename($fileInfo['out_filename']) . '" FOLDER="' . self::$base_path . $fileInfo['out_folder'] . '" DOCTYPE="' . ($type == ADLIB_JOBTYPE_HTML ? 'HTML' : 'PDF') . '" />
            </JOB:DOCOUTPUTS>
            <JOB:SETTINGS>
              <JOB:HEADER ENABLED="Yes" TEXTRIGHT="&amp;[Page] of &amp;[Pages]" LAYER="Foreground" />
              <JOB:HTMLMSEXCEL ENABLED="Yes" />
              <JOB:NATIVEAPPSETTINGS>
                <JOB:MSOUTLOOK CONVERSIONMODE="IFTS" />  
              </JOB:NATIVEAPPSETTINGS>
            </JOB:SETTINGS>
          </JOB>
        </JOBS>';
    $result = simplexml_load_string($this->client->addJob(array('jobInfo' => $jobInfo, 'jobTicket' => $jobTicket))->AddJobResult);
    if (is_object($result) && isset($result->JobSettings['JobID'])) {
      return $result;
    } else {
      error_log(basename(__FILE__) . ':' . __LINE__ . " jm@bellcom.dk: Failed to add job.");
    }
  }
  /**
    * Deletes the job on Adlib server
    *
    * @param int $id Job id 
    * 
    * @return none
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
      $this->client->deleteJob(array('jobID' => $id, 'isUserJobID' => false));
    }
  }

  /**
    * Deletes the job folder on Adlib Server
    *
    * @param int $id Job folder id 
    * 
    * @return reply
    */
  public function deleteJobFolder($id) {
    if (ADLIB_DISABLED) {
      return false;
    }
    if (isset($this->client)) {
      $reply = $this->client->deleteJobFolder(array('JobFolder' => $id));
      return $reply;
    }
  }

  /**
  * Gets the status of the connector
  * 
  * @return string status
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
      } else {
        return 'Invalid response from AdLib.';
      }
    }
    return 'AdLib connection failed.';
  }

  /**
  * Gets the status of the job
  *
  * @param int $id Job id 
  * 
  * @return status
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
      $result = $this->client->getJobStatus(array('jobID' => $id, 'isUserJobID' => false))->GetJobStatusResult;
      $return = (object) array();
      if (strncmp('<', $result, 1) === 0) {
        $return->status = (string) simplexml_load_string($result)->CurrentJobStatus['Status'];
        $return->result = simplexml_load_string($result);
      } else {
        $return->status = 'Not found';
        $return->result = $result;
      }
    } else {
      $return->status = 'Not found';
    }
    if ($return->status === '') {
      $message = (string) $return->result->ServerInfo[0]->Error['Message'];
      error_log(basename(__FILE__) . ':' . __LINE__ . ' AdLib Error: ' . $message);
      $return->status = 'Not Available';
    } elseif ($return->status === 'Pending') {
      //error_log("ConnectorStatus is " . $return->result->CurrentJobStatus['ConnectorStatus']);
    } else {
      //error_log(basename(__FILE__) . ':' . __LINE__ . " jm@bellcom.dk: Looked up status for job: " . $id . " Status: " . $return->status);
    }
    return $return;
  }

  /**
  * Adds the job folder
  * 
  * @return job folder name
  */
  public function addJobFolder() {
    if (ADLIB_DISABLED)
      return false;
    if ($this->client) {
      $reply = simplexml_load_string($this->client->addJobFolder()->AddJobFolderResult);
      $folder_info = $reply;
      $result = 'ExponentJobs\\' . ((string) $folder_info['FolderID']);
      watchdog('adlib_api', 'Added a folder: %folder', array('%folder' => $result), WATCHDOG_DEBUG);
      return $result;
    }
  }

  /**
  * This method uploads a file to AdLib server
  *
  * @param string $filename Filename
  * @param mixed  $data     Binary contents of data
  * @param mixed  $type     Type of the job
  * @param string $folder   Optional
  * 
  * @return mixed False if call failed, otherwise a fileinfo structure
  */
  public function uploadData($filename, $data, $type = ADLIB_JOBTYPE_PDF, $folder = NULL) {
    if (ADLIB_DISABLED)
      return false;
    if (!isset($this->client)) {
      return false;
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
      return false;
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
          'out_url' => self::$base_url . str_replace('\\', '/', $folder . '/Output/') . rawurlencode($this->safeFilename(pathinfo($filename, PATHINFO_FILENAME) . '.' . $jobext)),
          'filename' => $filename,
          'job_type' => $jobtype,
          'out_filename' => pathinfo($filename, PATHINFO_FILENAME) . '.' . $jobext,
      );
    } else {
      error_log(basename(__FILE__) . ':' . __LINE__ . " jm@bellcom.dk: Failed to upload: " . $filename);
      watchdog('adlib_api', 'Upload of %filename failed with message: %msg', array('%file' => $filename, '%msg' => $result), WATCHDOG_ERROR);
      $folder = explode('\\', $folder);
      $this->deleteJobFolder($folder[1]);
      return false;
    }
  }

  /**
    * Wraps xml in CDATA tag
    *
    * @param string $data Binary contents of data
    * 
    * @return string
    */
  private function cdataPack($data) {
    return '<![CDATA[' . $data . ']]>';
  }

  /**
    * Gets the trace of last request and response
    * 
    * @return array
    */
  public function getTrace() {
    return array(
        'request' => $this->client->__getLastRequest(),
        'response' => $this->client->__getLastResponse(),
    );
  }

  private function safeFilename($fname) {
    $pi = pathinfo($fname);
    $safe_name = md5($pi['filename']);
    if (isset($pi['extension']))
      $safe_name .= '.' . $pi['extension'];
    return $safe_name;
  }
  
}