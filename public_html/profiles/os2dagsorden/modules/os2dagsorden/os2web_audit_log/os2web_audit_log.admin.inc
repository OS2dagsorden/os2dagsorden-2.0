<?php 

/*
 *
 * @author Stanislav Kutasevits <stan@bellcom.dk>
 * @copyright Bellcom Open Source aps.
 */
 
/**
 * Audit trail configuration form.
 */
function os2web_audit_log_admin_configure($form, $form_state) {
  $form = array();

  $form[] = array(
    '#markup' => '<h2>OS2web audit log setting</h2>',
  );
  
  $node_types = node_type_get_types();
  $options = array();
  foreach ($node_types as $type){
    $options[$type->type] = $type->name;
  }
  $form['os2web_audit_log_nodes'] = array(
    '#title' => t('Node types to keep log of:'),
    '#type' => 'checkboxes',
    '#options' => $options,
    '#default_value' => variable_get('os2web_audit_log_nodes', array()),
  );
  
  return system_settings_form($form);
}

/**
 * Page callback that shows all logged events.
 */
function os2web_audit_log_overview_page_form($form, $form_state) {
  $form = array();
  
  $form['filter'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Filter option')
  );

  $form['filter'][] = array(
    '#markup' => '<div style="float:left; padding:10px;">',
  );
  
  $form['filter']['time_from'] = array(
    '#type' => 'date_popup',
    '#title' => t('Time from'),
    '#size' => 15,
    '#date_format' => 'd-m-Y H:i',
  );
  
  $form['filter']['time_until'] = array(
    '#type' => 'date_popup',
    '#title' => t('Time until'),
    '#size' => 15,
    '#date_format' => 'd-m-Y H:i',
  );
  
  $form['filter'][] = array(
    '#markup' => '</div>',
  );

  $form['filter'][] = array(
    '#markup' => '<div style="float:left; padding:10px;">',
  );
  
  $form['filter']['user'] = array(
    '#type' => 'textfield',
    '#title' => t('Username'),
    '#size' => 15,
  );

  $form['filter']['user_ip'] = array(
    '#type' => 'textfield',
    '#title' => t('User IP'),
    '#size' => 15,
  );
  
  $form['filter'][] = array(
    '#markup' => '</div>',
  );
  
  $form['filter'][] = array(
    '#markup' => '<div style="float:left; padding:10px;">',
  );
  
  
  $form['filter']['node'] = array(
    '#type' => 'textfield',
    '#title' => t('Node'),
    '#size' => 15,
  );
  
  $form['filter']['node_type'] = array(
    '#type' => 'textfield',
    '#title' => t('Node type'),
    '#size' => 15,
  );
  
  $form['filter']['action'] = array(
    '#type' => 'textfield',
    '#title' => t('Action'),
    '#size' => 15,
  );

  $form['filter'][] = array(
    '#markup' => '</div>',
  );

  $form['filter'][] = array(
    '#markup' => '<div class="clearfix"></div>',
  );
  
  $form['filter']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Filter'),
  );

  $header = array(
    array('data' => 'time', 'field' => 'time'),
    array('data' => 'user', 'field' => 'uid'),
    array('data' => 'user ip', 'field' => 'user_ip'),
    array('data' => 'node', 'field' => 'nid'),
    array('data' => 'node type', 'field' => 'node_type'),
    array('data' => 'action', 'field' => 'action'),
    array('data' => 'info', 'field' => 'information'),
  );

  $query = db_select('os2web_audit_log', 'al')
    ->fields('al')
    ->extend('TableSort')
    ->orderByHeader($header)
    ->extend('PagerDefault')
    ->limit(50);
  
  //setting params from GET if form values are empty
  $form_state['values']['time_from'] = empty($form_state['values']['time_from'])? check_plain($_GET['time_from']) : $form_state['values']['time_from'];
  $form_state['values']['time_until'] = empty($form_state['values']['time_until'])? check_plain($_GET['time_until']) : $form_state['values']['time_until'];
  $form_state['values']['user'] = empty($form_state['values']['user'])? check_plain($_GET['user']) : $form_state['values']['user'];
  $form_state['values']['user_ip'] = empty($form_state['values']['user_ip'])? check_plain($_GET['user_ip']) : $form_state['values']['user_ip'];
  $form_state['values']['node'] = empty($form_state['values']['node'])? check_plain($_GET['node']) : $form_state['values']['node'];
  $form_state['values']['node_type'] = empty($form_state['values']['node_type'])? check_plain($_GET['node_type']) : $form_state['values']['node_type'];
  $form_state['values']['action'] = empty($form_state['values']['action'])? check_plain($_GET['action']) : $form_state['values']['action'];
  
  //time from filter field
  if (!empty($form_state['values']['time_from'])) {
    $filter_time_from = $form_state['values']['time_from'];
    $form['filter']['time_from']['#default_value'] = $filter_time_from;
    $_GET['time_from'] = $filter_time_from;
    
    $query->condition('time', $filter_time_from, ">=");
  }
  
  //time until filter field
  if (!empty($form_state['values']['time_until'])) {
    $filter_time_until = $form_state['values']['time_until'];
    $form['filter']['time_until']['#default_value'] = $filter_time_until;
    $_GET['time_until'] = $filter_time_until;
    
    $query->condition('time', $filter_time_until, "<=");
  }
  
  //user filter field
  if (!empty($form_state['values']['user'])) {
    $filter_user = $form_state['values']['user'];
    $form['filter']['user']['#default_value'] = $filter_user;
    $_GET['user'] = $filter_user;
    
    $users = db_select('users', 'u')
      ->fields('u', array('uid'))
      ->condition('u.name', '%' . db_like($filter_user) . '%', 'LIKE')
      ->execute();
    
    $or = null;
    while($user = $users->fetchAssoc()) {
	if ($or == null)
	  $or = db_or();
        $or->condition('uid', $user['uid'], '=');
    }

    if ($or)
      $query->condition($or);
    else
      $query->condition('uid', 0, '=');//non existing user
  }
  
  //user ip filter field
  if (!empty($form_state['values']['user_ip'])) {
    $filter_user_ip = $form_state['values']['user_ip'];
    $form['filter']['user_ip']['#default_value'] = $filter_user_ip;
    $_GET['user_ip'] = $filter_user_ip;
    
    $query->condition('user_ip', '%' . db_like($filter_user_ip) . '%', 'LIKE');
  }
  
  //node filter field
  if (!empty($form_state['values']['node'])) {
    $filter_node = $form_state['values']['node'];
    $form['filter']['node']['#default_value'] = $filter_node;
    $_GET['node'] = $filter_node;
    
    $nodes = db_select('node', 'n')
      ->fields('n', array('nid'))
      ->condition('n.title', '%' . db_like($filter_node) . '%', 'LIKE')
      ->execute();
    
    $or = null;
    while($node = $nodes->fetchAssoc()) {
	if ($or == null)
	  $or = db_or();
        $or->condition('nid', $node['nid'], '=');
    }

    if ($or)
      $query->condition($or);
    else
      $query->condition('nid', 0, '=');//non existing node
  }
  
  //node type field
  if (!empty($form_state['values']['node_type'])) {
    $filter_node_type = $form_state['values']['node_type'];
    $form['filter']['node_type']['#default_value'] = $filter_node_type;
    $_GET['node_type'] = $filter_node_type;
    
    $query->condition('node_type', '%' . db_like($filter_node_type) . '%', 'LIKE');
  }
  
  //action field
  if (!empty($form_state['values']['action'])) {
    $filter_action = $form_state['values']['action'];
    $form['filter']['action']['#default_value'] = $filter_action;
    $_GET['action'] = $filter_action;
    
    $query->condition('action', '%' . db_like($filter_action) . '%', 'LIKE');
  }

  $result = $query->execute();
  
  $rows = array();
  foreach ($result as $record) {
    if (!empty($record->uid)) {
      $account = user_load($record->uid);
    }
    else {
      $account = NULL;
    }
    $node = node_load($record->nid);
    $rows[] = array(
      array('data' => check_plain($record->time)),
      array('data' => (empty($account) ? '' : l($account->name, 'user/' . $account->uid))),
      array('data' => check_plain($record->user_ip)),
      array('data' => l($node->title, 'node/' . $record->nid)),
      array('data' => check_plain($record->node_type)),
      array('data' => check_plain($record->action)),
      array('data' => check_plain($record->information)),
    );
  }

  $form['table'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
    '#empty' => t('No events yet')
  );
  
  $form['pager'] = array('#markup' => theme('pager'));

  return $form;
}

function os2web_audit_log_overview_page_form_submit($form, &$form_state){
  $form_state['rebuild'] = TRUE;
}