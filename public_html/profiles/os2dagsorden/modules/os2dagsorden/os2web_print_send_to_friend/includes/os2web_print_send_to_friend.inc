<?php

/**
 * Creates a light version of the bullet point for printing
 *
 * @param int $bullet_point_id bullet point id
 * @param bool $show_commitee
 */
function os2web_print_send_to_friend_print_bullet_point($meeting_id, $bullet_point_id, $show_commitee = TRUE) {
  module_load_include('inc', 'os2dagsorden_meeting_views', 'os2dagsorden_meeting_views_common_fields' );  
  $bullet_point = node_load($bullet_point_id);
 
  if (strcmp($bullet_point->type, 'os2web_meetings_bullet') == 0) {     
    if (variable_get('os2dagsorden_print_pdf_show_commitee', FALSE) && $show_commitee){
     $meeting = node_load($meeting_id);
     $date = field_get_items('node', $meeting, 'field_os2web_meetings_date');
     $meeting_committee=field_get_items('node', $meeting, 'field_os2web_meetings_committee');
     $short_name=taxonomy_term_load($meeting_committee[0]["tid"])->field_os2web_meetings_com_shname['und'][0]['value'];
     if (!empty($short_name))
       $commitee = taxonomy_term_load($meeting_committee[0]["tid"])->field_os2web_meetings_com_shname['und'][0]['value'];
     else
       $commitee =  taxonomy_term_load($meeting_committee[0]["tid"])->name;
     $meeting_date =format_date(strtotime($date[0]["value"]), $type = 'short', '', $date[0]['timezone']);
     $html = '<h2>' . $bullet_point->title . ' (' . $commitee . ' ' . $meeting_date . ')</h2>';
    }     
    else 
     $html = '<h2>' . $bullet_point->title . '</h2>';
    //eliminating duplicates in bullet points attachments
    $attachments = array();
    if ($bullet_point->field_os2web_meetings_attach['und']) {
      foreach ($bullet_point->field_os2web_meetings_attach['und'] as $attachment_id) {
        $hash = $attachment_id['target_id'];
        $attachments[$hash] = $attachment_id;
      }
    }
    foreach ($attachments as $attachment_id) {
      $attachment = node_load($attachment_id['target_id']);
      if (!empty($attachment->field_os2web_meetings_bpa_body['und'][0]['value'])) {
        $html .= '<h3>' . $attachment->title . '</h3>';
        $html.=preg_match("|^<p>(.*)</p>|", $attachment->field_os2web_meetings_bpa_body['und'][0]['value']) ? $attachment->field_os2web_meetings_bpa_body['und'][0]['value'] : "<p>" . $attachment->field_os2web_meetings_bpa_body['und'][0]['value'] . "</p>";
      }
    }
  }
  return ('<div class="node" id="content">' . $html . '</div>');
}
/**
 * Return tiltle of bullet point for printing
 *
 * @param int $bullet_point_id bullet point id
 *
 */
function os2web_print_send_to_friend_print_bullet_point_title($bullet_point_id) {
  $bullet_point = node_load($bullet_point_id);
  if (strcmp($bullet_point->type, 'os2web_meetings_bullet') == 0) {
    $html = '<h2>' . $bullet_point->title . '</h2>';

  }
  return ('<div class="node" id="content">' . $html . '</div>');
}

function os2web_print_send_to_friend_print_bullet_point_attachments($bullet_point_id) {
  $bullet_point = node_load($bullet_point_id);
  if (strcmp($bullet_point->type, 'os2web_meetings_bullet') == 0) {
    $attachments = array();
    if ($bullet_point->field_os2web_meetings_attach['und']) {
      foreach ($bullet_point->field_os2web_meetings_attach['und'] as $attachment_id) {
        $hash = $attachment_id['target_id'];
        $attachments[$hash] = $attachment_id;
      }
    }
    $files = array();
    foreach ($attachments as $attachment_id) {
      $attachment = node_load($attachment_id['target_id']);
      if (!empty($attachment->field_os2web_meetings_bpa_file['und'])) {
        $file = file_load($attachment->field_os2web_meetings_bpa_file['und'][0]['fid']);
        $files[]= array(
          'filecontent' => file_get_contents(drupal_realpath($file->uri)),
          'filename' => $file->filename,
          'filemime' => $file->filemime
        );

      }
    }
    return $files;
  }
}

/**
 * Creates a form that allows to send the content of the bullet point to an email addess.
 *
 * @param int $meeting_id      meeting id
 * @param int $bullet_point_id bullet point id
 *
 */
function os2web_print_send_to_friend_send_to_friend_form($meeting_id, $bullet_point_id) {
  //adding css that tweaks the elements for the modal window
  drupal_add_css(drupal_get_path('module', 'os2web_print_send_to_friend') . '/css/os2web_print_send_to_friend.css');

  drupal_add_js(drupal_get_path('module', 'os2web_print_send_to_friend') . '/js/os2web_print_send_to_friend.js');
  $bullet_point = node_load($bullet_point_id);
  $confirm_popup = '';
  if ($bullet_point->field_os2web_meetings_bul_closed['und'][0]['value'] == 1)
    $confirm_popup = 'onclick ="if(!confirm(\'Du er ved at sende indhold fra et lukket dagsordenspunkt. Vil du stadig sende mailen?\')){return false;}"';
  $html .= t('Udfyld felterne herunder og tryk "Send", når du vil sende beskeden.');
  $html .= '<form id="send_to_friend_form">';
  $html .= '<label>' . t('Dit navn') . ':</label><input type="text" name="name" />';
  $html .= '<label>' . t('Besked') . ':</label><textarea name="message"></textarea>';
  $html .= '<label>' . t('Modtagers email') . ':</label><input type="text" name="email" id="field_send_to_friend_email" />';
  $html .= '<input type="hidden" name="base_url" id="field_base_url" value="' . $GLOBALS['base_url'] . '" />';
  $html .= '<input type="hidden" name="meeting_id" id="field_meeting_id" value="' . $meeting_id . '" />';
  $html .= '<input type="hidden" name="bullet_point_id" id="field_bullet_point_id" value="' . $bullet_point_id . '" />';
  $html .= '<button type="submit" class="form-submit" id="btn_send_to_friend"' .  $confirm_popup . '>Send</button>';
  $html .= '<div class="throbber"></div>';
  $html .= '</form>';

  return '<div class="node"><div class="bullet-point-send-to-friend-form ajax-progress">' . $html . '</div></div>';
}

/**
 * Does the actual sending to the provided email
 *
 * @param int    $bullet_point_id bullet point id
 * @patam string $email           email
 *
 */
function os2web_print_send_to_friend_send_to_friend($meeting_id, $bullet_point_id) {
  global $user;
  $bullet_point = node_load($bullet_point_id);
  $subject = 'Dagsorden Punkt: ' . $bullet_point->title;

  $name = check_plain(trim($_POST['name']));
  $message = check_plain(trim($_POST['message']));
  $to_email = check_plain($_POST['email']);

  $body = "<html><body>";

  $body .= $name . " har sendt dig et dagsordenspunkt med beskeden:<br/>" . $message . "<br/><br/>";

  $body .= os2web_print_send_to_friend_print_bullet_point($meeting_id, $bullet_point_id);

  $body .= "</body></html>";

  $from = variable_get('system_mail');
  $params = array(
    'subject' => $subject,
    'body' => $body,
    'params' => array (
      'attachments' => os2web_print_send_to_friend_print_bullet_point_attachments($bullet_point_id)
    )
  );
  var_dump($params['params']['attachments']);
  drupal_mail('os2web_print_send_to_friend', 'send_to_friend_', $to_email, language_default(), $params, $from);
  //$system->mail($message);
  $bullet_point_uri = $GLOBALS['base_url'] . '/meeting/' . $meeting_id . '/bullet-point/' . $bullet_point_id;
  if (module_exists('os2dagsorden_logging'))
    os2web_print_send_to_friend_add_to_log('Bullet point %title (%uri) was sent to %to', array( '%title' => $subject, '%uri' => $bullet_point_uri, '%to' => $to_email), WATCHDOG_INFO, 
      array('uid' => $user->uid, 
        'text' => check_plain(trim($_POST['message'])),
      ));
 // watchdog('Send to friend', 'Bullet point %title (%uri) was send to %to', array( '%title' => $subject, '%uri' => $bullet_point_uri, '%to' => $to_email), WATCHDOG_INFO);
}


function os2web_print_send_to_friend_mail($key, &$message, $params) {
   $message['subject'] = $params['subject'];
   $message['body'][] = $params['body'];
   $message['params']['attachments']=  $params['params']['attachments'];
 }

/**
 * Prepares the pring version of meeting and all its bullet point and bullet point attachments.
 *
 * @param int    $meeting_id
 *   meeting id
 */
function os2web_print_send_to_friend_print_dagsorden($meeting_id) {
  //hiding regions not needed for printing
  //drupal_add_css(drupal_get_path('theme', 'rubik') . '/css/style.css');
  //drupal_add_css('.view-display-id-attachment_2{ display: none;}', 'inline');
  drupal_add_css('.view-display-id-attachment_1{ display: none;}', 'inline');
  drupal_add_css('.view-display-id-attachment_5{ display: none;}', 'inline');
  drupal_add_css('.lukket-dagsorden{ display: none;}', 'inline');
  //drupal_add_css('.view-display-id-attachment_4{ display: none;}', 'inline');
  drupal_add_css('.hide-on-print{ display: none; }', 'inline');
  drupal_add_css('.form-submit {display: none; }', 'inline');
  //changing table width, overrriding styles to match website representation

  drupal_add_css('table{ width: 100%; border:none!important}', 'inline');
  $overriden_css = 'td,tr { background: none !important; border:none !important}
    th {padding: 7px 5px; text-align:left;
    background-color: #B5B5B5;
    color: #000;}
    td {border: none!important; background-color: #DCDCDC;}
    table {margin: 1.2em 0;}
    ';
  drupal_add_css($overriden_css, 'inline');

  $view = views_get_view('meeting_details');
  $view->set_display('page');
  $view->set_arguments(array($meeting_id));
  $view->execute();
  //print $view->render();
  $html .= $view->render();
  $meeting = node_load($meeting_id);
  if (isset($meeting->field_os2web_meetings_bullets['und'])) {
    foreach ($meeting->field_os2web_meetings_bullets['und'] as $bullet_point) {
      if (os2dagsorden_access_helper_check_user_can_see_bullet_point($meeting_id, $bullet_point['target_id']))
        $html .= os2web_print_send_to_friend_print_bullet_point($meeting_id, $bullet_point['target_id'], FALSE);
      else
        $html .=  os2web_print_send_to_friend_print_bullet_point_title($meeting_id, $bullet_point['target_id']);
    }
  }

  return $html;
}
 
