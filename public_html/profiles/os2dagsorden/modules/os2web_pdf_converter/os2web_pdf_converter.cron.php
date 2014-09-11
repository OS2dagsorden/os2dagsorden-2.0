<?php

/**
 * @file
 * This module is called from custom cron.
 * Does the legwork of converting documents.
 *
 * Because of performance issues this is done outside of Drupals bootstrap.
 *
 * Arguments:
 *   1: Path to files which should be converted. This should either be an
 *      relative path or an absolute.
 *
 *   2: Path to your Drupal instance. When providing a valid Drupal path, it
 *      tries to update the corrosponding file entity in Drupal with the new
 *      .pdf URI.
 */

if (php_sapi_name() !== 'cli') {
  print ('This script is ONLY allowed from commandline.');
  exit();
}

if (!shell_exec('which unoconv')) {
  print ('unoconv was not found. hint: sudo apt-get install unoconv');
  exit();
}

if (!shell_exec('which soffice')) {
  print ('soffice was not found. You need to install a pdf conversion tool like LibreOffice.');
  exit();
}

if (!shell_exec('which convert')) {
  print ('imagick was not found. Cannot convert .tiff files');
  exit();
}

if (!shell_exec('which mapitool') || !shell_exec('which munpack')) {
  print ('you need mapitool and munpack to unpack and convert .msg files.');
  exit();
}

if (!isset($_SERVER['argv'][1])) {
  print ('Usage: php os2web_pdf_converter.php "/path/to/files" "/path/to/drupal"');
  exit();
}
elseif (!is_dir($_SERVER['argv'][1])) {
  print ('The path is not a directory!');
  exit();
}
else {
  // Start unoconv if not started.
  if (!shell_exec('ps -ef | grep -v grep | grep "/unoconv -l"')) {
    exec('unoconv -l >/dev/null 2>/dev/null &');
  }

  $directory_root = $_SERVER['argv'][1];

  $tmp_directory = '/tmp/os2web_pdf_converter';
  if (!is_dir($tmp_directory)) {
    mkdir($tmp_directory);
  }
  putenv("MAGICK_TMPDIR=" . $tmp_directory);

  // Setup Drupal but only if provided.
  if (isset($_SERVER['argv'][2])) {
    if (!file_exists($_SERVER['argv'][2] . '/includes/bootstrap.inc')) {
      print ('No Drupal instance was found at ' . $_SERVER['argv'][2]);
      exit();
    }
    define('DRUPAL_ROOT', $_SERVER['argv'][2]);
    require_once DRUPAL_ROOT . '/includes/bootstrap.inc';
    drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);
  }
}


require 'lib/PDFConverter.php';


$allowed_extensions = PDFConverter::getAllowedExtenstions();

// Loop trough all files in the directory, only files of specific type allowed
// by the PDFConverter.
foreach (getFilesList($directory_root, '/.*\.(' . implode('|', $allowed_extensions) . ')$/i') as $file) {
  // Replaces the extension with ".pdf".
  $pdf_file = preg_replace('/\.(' . implode('|', $allowed_extensions) . ')$/i', '.pdf', $file);
  if (!file_exists($pdf_file)) {
    try {
      $file = new PDFConverter($file);
      if ($file->convert()) {
        if (defined('DRUPAL_ROOT')) {
          updateDrupalFile($file);
        }
      }

    }
    catch(Exception $e) {
      error_log($e->getMessage());
    }
  }
}

// Remove all temp files.
if (is_dir($tmp_directory)) {
  rrmdir($tmp_directory);
}

/**
 * Get a list of all matched files in folder. Recursivly.
 *
 * @param string $folder
 *   the folder
 * @param string $pattern
 *   regex pattern to search for
 *
 * @return array
 *   array of file paths
 */
function getFilesList($folder, $pattern) {
  $dir = new RecursiveDirectoryIterator($folder);
  $ite = new RecursiveIteratorIterator($dir);
  $files = new RegexIterator($ite, $pattern, RegexIterator::GET_MATCH);
  $file_list = array();
  foreach ($files as $file) {
    $file_list[] = $file[0];
  }
  return $file_list;
}

/**
 * Updates the file entry in file_managed in Drupal to the new uri.
 *
 * @param string $file
 *   The file path.
 */
function updateDrupalFile($file) {
  if (!file_exists($file->pdf)) {
    return FALSE;
  }

  $privatepath = NULL;
  $uri = 'private://';
  if ($wrapper = file_stream_wrapper_get_instance_by_uri($uri)) {
    $privatepath = $wrapper->realpath() . '/';
  }

  $file_parts = explode('sites/default/files/', $file->file);

  if (!isset($file_parts[1])) {
    $file_parts = explode($privatepath, $file->file);
    if (!isset($file_parts[1])){
      return FALSE;
    }
  }

  $public_file_uri = 'public://' . $file_parts[1];
  $private_file_uri = 'private://' . $file_parts[1];

  $query = db_query('SELECT f.fid, f.uri
                      FROM {file_managed} f
                      WHERE f.uri = :public_uri
                      OR f.uri = :private_uri
                      OR f.uri = :original_uri', array(
                        ':public_uri' => $public_file_uri,
                        ':private_uri' => $private_file_uri,
                        ':original_uri' => $file->file,
                      ));
  $d_file = $query->fetchAssoc();

  if ($d_file) {

    db_update('file_managed')
      ->fields(array(
        'uri' => preg_replace('/\.(' . implode('|', PDFConverter::getAllowedExtenstions()) . ')$/i', '.pdf', $d_file['uri']),
        'filename' => basename($file->pdf),
        'timestamp' => time(),
        'filesize' => filesize($file->pdf),
        'filemime' => 'application/pdf',
      ))
      ->condition('fid', $d_file['fid'])
      ->execute();
  }
}

/**
 * Recursively remove a directory.
 *
 * @param string $dir
 *   The dir to remove
 */
function rrmdir($dir) {
  foreach (glob($dir . '/*') as $file) {
    if (is_dir($file)) {
      rrmdir($file);
    }
    else {
      unlink($file);
    }
  }
  rmdir($dir);
}
