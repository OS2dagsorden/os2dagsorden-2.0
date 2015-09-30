<?php

/**
 * @file
 * Handler include for StreamHandler include.
 */

use Monolog\Handler\MySQLHandler;

/**
 * Monolog loader callback; Loads a MySQLHandler handler.
 *
 * @return HandlerInterface
 */
function os2web_print_send_to_friend_handler_loader($options) {

  return new MySQLHandler(Database::getConnection(), 'os2web_print_send_to_friend_log', array('uid', 'text'), $options['level'], $options['bubble']);
}
/**
 * Monolog settings form; Settings for the MySQLHandler handler.
 */
function os2web_print_send_to_friend_handler_settings(&$form, &$form_state) {
  
}

