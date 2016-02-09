<?php

/**
 * @file
 * Views integration for the Login Tracker module.
 */

/**
 * Implements hook_views_data().
 */
function login_tracker_views_data() {
  $data = array();
  $data['login_tracker']['table']['group'] = t('Login tracker');
  $data['login_tracker']['table']['base'] = array(
    'title' => t('Login tracker'),
    'help' => t('Contains data about user logins.'),
  );
  $data['login_tracker']['table']['join'] = array(
    'users' => array(
      'left_field' => 'uid',
      'field' => 'uid',
    ),
  );
  // The UID field.
  $data['login_tracker']['uid'] = array(
    'title'  => t('UID'),
    'help'   => t("The user's UID."),
    'field'  => array(
      'handler'        => 'views_handler_field_user',
      'click sortable' => TRUE,
    ),
    'sort'   => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'relationship' => array(
      'base' => 'users',
      'base field' => 'uid',
      'relationship field' => 'uid',
      'handler' => 'views_handler_relationship',
      'label' => t('Tracked logins for a user'),
    ),
  );
  // The login timestamp field.
  $data['login_tracker']['login_timestamp'] = array(
    'title'  => t('Login timestamp'),
    'help'   => t('The timestamp that the user logged in at.'),
    'field'  => array(
      'handler' => 'views_handler_field_date',
    ),
    'sort'   => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );
  return $data;
}
