<?php

/**
 * This function adds a meeting entry to the database
 *
 * @param $meeting
 */
function os2web_esdh_provider_index_meeting($meeting){
  $manifest = simplexml_load_file(drupal_realpath($meeting['uri']));

  drupal_set_message(print_r($meeting,1));
}