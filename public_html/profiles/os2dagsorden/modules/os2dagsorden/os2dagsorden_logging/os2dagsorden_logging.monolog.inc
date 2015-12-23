<?php
/**
 * @file
 * os2dagsorden_logging.monolog.inc
 */

/**
 * Implements hook_default_monolog_profiles().
 */
function os2dagsorden_logging_default_monolog_profiles() {
  $export = array();

  $profile = new stdClass();
  $profile->disabled = FALSE; /* Edit this to true to make a default profile disabled initially */
  $profile->api_version = 1;
  $profile->name = 'os2dagsorden_logging_development';
  $profile->options = array(
    'handlers' => array(
      'rotating_file_handler' => array(
        'weight' => 1,
        'label' => 'Rotating File Handler',
        'level' => '200',
        'bubble' => 1,
        'filepath' => 'public://monolog/import.log',
        'max_files' => '30',
        'handler' => 'rotating_file',
      ),
      'native_mail_handler' => array(
        'weight' => '1',
        'label' => 'Native Mail Handler',
        'level' => '500',
        'bubble' => '1',
        'to' => 'juulia@bellcom.ee',
        'subject' => 'Log message sent by OS2Dagsorden TEST',
        'from' => '<site-mail>',
        'handler' => 'native_mailer',
      ),
    ),
    'label' => 'Os2dagsorden logging development',
  );
  $export['os2dagsorden_logging_development'] = $profile;

  $profile = new stdClass();
  $profile->disabled = FALSE; /* Edit this to true to make a default profile disabled initially */
  $profile->api_version = 1;
  $profile->name = 'os2dagsorden_logging_production';
  $profile->options = array(
    'handlers' => array(
      'native_mail_handler' => array(
        'weight' => 1,
        'label' => 'Native Mail Handler',
        'level' => '500',
        'bubble' => 1,
        'to' => 'juulia@bellcom.ee',
        'subject' => 'Log message sent by OS2Dagsorden TEST',
        'from' => '<site-mail>',
        'handler' => 'native_mailer',
      ),
      'rotating_file_handler' => array(
        'weight' => 1,
        'label' => 'Rotating File Handler',
        'level' => '500',
        'bubble' => 1,
        'filepath' => 'public://monolog/import.log',
        'max_files' => '30',
        'handler' => 'rotating_file',
      ),
    ),
    'label' => 'Os2dagsorden logging production',
  );
  $export['os2dagsorden_logging_production'] = $profile;

  $profile = new stdClass();
  $profile->disabled = FALSE; /* Edit this to true to make a default profile disabled initially */
  $profile->api_version = 1;
  $profile->name = 'os2web_send_to_friend';
  $profile->options = array(
    'handlers' => array(
      'rotating_file_handler' => array(
        'weight' => 1,
        'label' => 'Rotating File Handler',
        'level' => '200',
        'bubble' => 1,
        'filepath' => 'public://monolog/sendto.log',
        'max_files' => '30',
        'handler' => 'rotating_file',
      ),
      'send_to_friend_database_' => array(
        'weight' => 1,
        'label' => 'Send to friend (database)',
        'level' => '200',
        'bubble' => 1,
        'handler' => 'send_to_friend_db',
      ),
    ),
    'label' => 'Os2web send to friend',
  );
  $export['os2web_send_to_friend'] = $profile;

  return $export;
}
