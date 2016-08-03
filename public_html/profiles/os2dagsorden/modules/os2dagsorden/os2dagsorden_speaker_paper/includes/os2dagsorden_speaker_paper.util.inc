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
  $user = user_load($uid);

  $cName = taxonomy_term_load($committee_id)->name;
  os2dagsorden_acce_helper_
  $mName = check_plain($node->title);
  $mDate = check_plain($node->field_os2web_meetings_date['und'][0]['value']);

  //getting subject and body
  $subject_template = variable_get('os2dagsorden_send_email_subject', '!meeting_type til !committee er publiceret');
  $body_template = variable_get('os2dagsorden_send_email_body', 'Til !user' . PHP_EOL . PHP_EOL .
    'Du abonnerer på !committee.' . PHP_EOL . 'Der er publiceret !meeting_type til !meeting_name !meeting_date.');

  $uName = empty($user->field_user_full_name['und'][0]['value']) ? $user->name : $user->field_user_full_name['und'][0]['value'];

  //composing search/replace
  $search = array(
    '!committee',
    '!meeting_name',
    '!meeting_date',
    '!bullet_point_name',
    '!speaker_paper_name',
    '!speaker_paper_link',
    '!user',
    '!author!',
    PHP_EOL
  );
  $replace = array($cName, $mName, $mDate, $uName, '<br/>');

  //making replacements
  //$subject = str_replace($search, $replace, $subject_template);
  //$subject = ucfirst($subject);
  //$body = str_replace($search, $replace, $body_template);
  //$body = ucfirst($body);

  $from = variable_get('system_mail');
  $message = array(
    'to' => $user->mail,
    'subject' => 'SHARED SP', //$subject,
    'body' => 'congrats', //$body,
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
