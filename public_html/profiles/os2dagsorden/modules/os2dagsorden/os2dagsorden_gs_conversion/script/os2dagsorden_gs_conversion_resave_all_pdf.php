<?php
/**
 * @author: Stanislav Kutasevits, stan@bellcom.dk
 **/
$time_start = microtime(TRUE);
print('==========================' . PHP_EOL);
print('Started os2dagsorden_gs_conversion_resave_all_pdf.php' . PHP_EOL);

$result = db_select('file_managed', 'f')
  ->fields('f', array('fid', 'filename', 'filemime', 'uri'))
  ->condition('f.filemime', 'application/pdf')
  ->execute()
  ->fetchAll();

foreach($result as $file) {
  file_save($file);
}

//os2dagsorden_gs_conversion_convert();

print('==========================' . PHP_EOL);
print('Finished os2dagsorden_gs_conversion_resave_all_pdf.php' . PHP_EOL);
print('Total execution time: ' . (microtime(TRUE) - $time_start) . ' seconds' . PHP_EOL);
print('==========================' . PHP_EOL);
