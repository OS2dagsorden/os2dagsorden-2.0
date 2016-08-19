<?php

/**
 * os2dagsorden_speaker_paper
 *
 * PHP version 5
 *
 * @category OS2Dagsorden
 * @package  OS2Dagsorden_Speaker_papaer
 * @file     The speaker paper module help functions
 * @author   Stanislav Kutasevits <stan@bellcom.dk>
 * @license  http://www.gnu.org/licenses/gpl-2.0.html GNU General Public License, version 2
 * @link     http://bellcom.dk
 *
 */

/**
 * Returns true if the message has been sent, false otherwise
 *
 * @param $uid
 * @param $nid
 */
function _os2dagsorden_speaker_paper_is_message_sent($uid, $nid) {
  $query = db_select('os2dagsorden_speaker_paper_notification_emails', 'ne');
  $query->fields('ne')
    ->condition('uid', $uid)
    ->condition('speaker_paper_id', $nid);
  $result = $query->execute();

  return ($result->rowCount() > 0);
}

/**
 * Sends the message to a user that the following speaker paper is now shared with him.
 *
 * @param $uid
 * @param $node
 */
function _os2dagsorden_speaker_paper_send_message($uid, $node) {
  global $base_url;

  $user = user_load($uid);

  $bullet_point = node_load($node->field_os2web_meetings_sp_bullet['und'][0]['target_id']);
  $meeting = os2dagsorden_access_helper_get_meeting_by_bullet_point($bullet_point->nid);
  $committee_id = $meeting->field_os2web_meetings_committee['und'][0]['tid'];

  $cName = taxonomy_term_load($committee_id)->name;
  $mName = check_plain($meeting->title);
  $mDate = check_plain($meeting->field_os2web_meetings_date['und'][0]['value']);
  $bpName = check_plain($bullet_point->title);
  $spName = check_plain($node->title);
  $spLink = $base_url . '/meeting/' . $meeting->nid . '/bullet-point/' . $bullet_point->nid;
  $uName = empty($user->field_user_full_name['und'][0]['value']) ? $user->name : $user->field_user_full_name['und'][0]['value'];
  $author = user_load($node->uid);
  $authorName = empty($author->field_user_full_name['und'][0]['value']) ? $author->name : $author->field_user_full_name['und'][0]['value'];

  //getting subject and body
  $subject_template = variable_get('os2dagsorden_speaper_paper_email_subject', '!author har delt talepapiret "!speaker_paper_name" med dig');
  $body_template = variable_get('os2dagsorden_speaper_paper_email_body', 'Til !user' . PHP_EOL . PHP_EOL .
    '!author har delt talepapiret "!speaker_paper_name" med dig' . PHP_EOL . 'Du kan læse/ændre dette talepapir her: !speaker_paper_link');

  //composing search/replace
  $search = array(
    '!committee',
    '!meeting_name',
    '!meeting_date',
    '!bullet_point_name',
    '!speaker_paper_name',
    '!speaker_paper_link',
    '!user',
    '!author',
    PHP_EOL
  );
  $replace = array($cName, $mName, $mDate, $bpName, $spName, $spLink, $uName, $authorName, '<br/>');

  //making replacements
  $subject = str_replace($search, $replace, $subject_template);
  $subject = ucfirst($subject);
  $body = str_replace($search, $replace, $body_template);
  $body = ucfirst($body);

  $from = variable_get('system_mail');
  $message = array(
    'to' => $user->mail,
    'subject' => $subject,
    'body' => $body,
    'headers' => array(
      'MIME-Version' => '1.0',
      'From' => $from,
      'Sender' => $from,
      'Return-Path' => $from,
      'Content-Type' => 'text/html;charset=utf-8',
    ),
  );
  $system = drupal_mail_system("os2dagsorden_speaker_paper", "");

  // The format function must be called before calling the mail function.
  //$message = $system->format($message);
  $system->mail($message);

  //setting the database entry about sent email
  db_insert('os2dagsorden_speaker_paper_notification_emails')
    ->fields(array(
      'uid' => $uid,
      'speaker_paper_id' => $node->nid,
      'date' => gmdate("Y-m-d H:i:s", REQUEST_TIME),
    ))
    ->execute();
}

/**
 * Functions that retus the uids of all the users that are part of the speaker paper group with that tid.
 *
 * @param $tid - speaker paper group tid
 * @return array - array of user uids
 */
function _os2dagsorden_speaker_paper_fetch_group_users($tid) {
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'user')
    ->fieldCondition('field_user_sp_groups', 'tid', $tid, '=');
  $result = $query->execute();
  if (isset($result['user'])) {
    return array_keys($result['user']);
  }
}
