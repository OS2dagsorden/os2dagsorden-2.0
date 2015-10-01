<?php

/**
 * @file
 * Administrative settings for the Os2dagsorden Logging module.
 */


/**
 * Implementation of settings form  OS2dagsorden logging system.
 *
 * @param $form       the settings form
 * @param $form_state the state of the form
 *
 * @return settings form.
 */
function os2dagsorden_logging_settings_settings_form($form, $form_state) {
  $type_array;
  $query = db_select('watchdog','w')->fields('w', array('type'))->distinct()->orderBy('type', 'ASC');
  $result = $query->execute();
  foreach ($result as $res) {
    $type_array[$res->type] = $res->type;
  }
  $form['os2dagsorden_logging_import'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Import logging settings'),
  );
  $form['os2dagsorden_logging_import']['os2dagsorden_logging_message_type'] = array(
     '#type' => 'select',
  	    '#multiple' => TRUE,
	    '#title' => t('Watchdog message type'),
        '#description' => t('Select the watchdog log type to monitor.'),
	    '#required' => FALSE,
	    '#options' => $type_array,
        '#size' => 10,
        '#default_value' => variable_get('os2dagsorden_logging_message_type', array("acadre MM"=> "acadre MM", "esdh provider" => "esdh provider")),
   );
  $form['os2dagsorden_logging_import']['os2dagsorden_logging_contexts'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Include contexts in record'),
    '#description' => t('Include the selected contexts in all log messages that are routed through Monolog from <code>watchdog()</code>.'),
    '#options' => array(
      'type' => t('The type of message for this entry.'),
      'uid' => t('The user ID for the user who was logged in when the event happened.'),
      'request_uri' => t('The request URI for the page the event happened in.'),
      'referer' => t('The page that referred the user to the page where the event occurred.'),
      'ip' => t('The IP address where the request for the page came from.'),
      'link' => t('An optional link provided by the module that called the watchdog() function.'),
      'request_id' => t('A unique identifier for the page request or PHP process to logically group log messages.'),
    ),
    '#default_value' => variable_get('os2dagsorden_logging_contexts', array(
      'uid' => 'uid',
      'request_uri' => 'request_uri',
      'referer' => 'referer',
      'ip' => 'ip',
      'link' => 'link',
    )),
  );
  $form['os2dagsorden_logging_send_to_friend'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Send to friend logging settings'),
  );
   $form['os2dagsorden_logging_send_to_friend']['os2dagsorden_logging_day_limit'] = array(
    '#type' => 'textfield',
    '#title' => t('"Send to friend" log messages  clearing interval'),
    '#default_value' => variable_get('os2dagsorden_logging_day_limit', 100),
    '#size' => 10,
    '#field_prefix' => 'Keep log messages for',
    '#field_suffix' => 'days'
  );
 return system_settings_form($form);
}


