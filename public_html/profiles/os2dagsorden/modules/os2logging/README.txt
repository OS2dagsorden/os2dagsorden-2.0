README.txt
==========

INSTALLATION:

Enable OS2Logging module in '/admin/structure/features'
Run command 'drush composer-manager install'
To use watchdog, enable 'Monolog Logging' module

SETUP:

Monolog settings    - '/admin/config/development/monolog'
Set Watchdog chanel profile to watchdog

OS2Logging settings - '/admin/config/os2logging/settings'
You could define node type to log

To use separate log files per watchdog message types you need:
1) Enable 'Use the watchdog type as the channel name' checkbox on the '/admin/config/development/monolog/watchdog'
2) Implement hook_monolog_channel_info() in you module.

Code example:
================================================
function os2logging_monolog_channel_info() {
  $channels = array();

$my_module_name = basename(__FILE__, '.module');
  $channels[$my_module_name] = array(
      'label' => t($my_module_name),
      'description' => t('The default channel that os2logging messages are routed through.'),
      'default profile' => '$my_module_name',
  );

  return $channels;
}
================================================

3) On monolog setup page '/admin/config/development/monolog/profile' add a new profile. Profile name is you module name.
4) Add a handlers to you profile.