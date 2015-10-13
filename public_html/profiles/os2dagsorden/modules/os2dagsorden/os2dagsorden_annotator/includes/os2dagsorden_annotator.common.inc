<?php

/**
 * os2dagsorden_annotator
 *
 * PHP version 5
 *
 * @category OS2Dagsorden
 * @package  OS2Dagsorden_Annotator
 * @file     The annotator module help functions, which might be used by another modules or views.
 * @author   Stanislav Kutasevits <stan@bellcom.dk>
 * @license  http://www.gnu.org/licenses/gpl-2.0.html GNU General Public License, version 2
 * @link     http://bellcom.dk
 *
 */

/**
 * Returns the notes using the attachment id.
 *
 * @param int $bilag_id attachment id
 *
 * @return array of notes.
 */
function os2dagsorden_annotator_get_notes_by_attachment_id($bilag_id) {
    global $user;
    
    $result = db_select('os2dagsorden_annotator_notes', 'notes')
	->fields('notes')
	->condition('uid', $user->uid,'=')
	->condition('bilag_id', $bilag_id,'=')
	->execute();


    //looping through notes, adding them to array
    $notes = array();
    while($record = $result->fetchAssoc()) {
      $note_arr = json_decode($record['note_info']);

      //adding missing fields
      $note_arr->id = $record['id'];
      $note_arr->bilag_id = $record['bilag_id'];
      $note_arr->bullet_point_id = $record['bullet_point_id'];
      $note_arr->meeting_id = $record['meeting_id'];

      $note_arr->user = $user->name;
      $note_arr->permissions = array();

      $notes[] = $note_arr;
    }

    return $notes;
}

/**
 * Returns the notes using the bullet point id.
 *
 * @param int $bullet_point_id bullet point id
 *
 * @return array of notes.
 */
function os2dagsorden_annotator_get_notes_by_bullet_point_id($bullet_point_id) {
    global $user;
    
    $result = db_select('os2dagsorden_annotator_notes', 'notes')
	->fields('notes')
	->condition('uid', $user->uid,'=')
	->condition('bullet_point_id', $bullet_point_id,'=')
	->execute();


    //looping through notes, adding them to array
    $notes = array();
    while($record = $result->fetchAssoc()) {
      $note_arr = json_decode($record['note_info']);

      //adding missing fields
      $note_arr->id = $record['id'];
      $note_arr->bilag_id = $record['bilag_id'];
      $note_arr->bullet_point_id = $record['bullet_point_id'];
      $note_arr->meeting_id = $record['meeting_id'];

      $note_arr->user = $user->name;
      $note_arr->permissions = array();

      $notes[] = $note_arr;
    }

    return $notes;
}

/**
 * Returns the notes using the meeting id.
 *
 * @param int $meeting_id meeting id
 *
 * @return array of notes.
 */
function os2dagsorden_annotator_get_notes_by_meeting_id($meeting_id) {
    global $user;
    
    $notes = array();
    $possible_meetings = os2dagsorden_access_helper_get_meeting_and_tillaegs_meetings($meeting_id);

    foreach($possible_meetings as $nid){
	$result = db_select('os2dagsorden_annotator_notes', 'notes')
	    ->fields('notes')
	    ->condition('uid', $user->uid,'=')
	    ->condition('meeting_id', $nid,'=')
	    ->execute();
    
    
	//looping through notes, adding them to array
	while($record = $result->fetchAssoc()) {
	  $note_arr = json_decode($record['note_info']);
    
	  //adding missing fields
	  $note_arr->id = $record['id'];
	  $note_arr->bilag_id = $record['bilag_id'];
	  $note_arr->bullet_point_id = $record['bullet_point_id'];
	  $note_arr->meeting_id = $meeting_id;//$record['meeting_id'];
    
	  $note_arr->user = $user->name;
	  $note_arr->permissions = array();
    
	  $notes[] = $note_arr;
	}
    }

    return $notes;
}

/**
 * Function that updates the reference of meeting nid
 *
 * @param $old_meeting_nid
 * @param $new_meeting_nid
 */
function os2dagsorden_annotator_update_notes_meeting($old_meeting_nid, $new_meeting_nid){
  db_update('os2dagsorden_annotator_notes')
    ->fields(array(
      'meeting_id' => $new_meeting_nid
    ))
    ->condition('meeting_id', $old_meeting_nid,'=')
    ->execute();
}

/**
 * Function that updates the reference of bilag nid
 *
 * @param $old_attachment_nid
 * @param $new_attachment_nid
 */
function os2dagsorden_annotator_update_notes_attachment($old_attachment_nid, $new_attachment_nid){
  $old_attachment = node_load($old_attachment_nid);
  $new_attachment = node_load($new_attachment_nid);
  
  //bullet point attachment body changed 
  //needs notes update
  if (strcasecmp($old_attachment->field_os2web_meetings_bpa_body[['und']][0]['value'], 
        $new_attachment->field_os2web_meetings_bpa_body['und'][0]['value']) != 0){
    
    $result = db_select('os2dagsorden_annotator_notes', 'notes')
            ->fields('notes')     
            ->condition('bilag_id', $old_attachment_nid,'=')
            ->execute();
    while ($record = $result->fetchAssoc()) { 
      //add note to first word in the string
       $ranges=json_decode($record["note_info"]);
       $bpa_body=strip_tags($new_attachment->field_os2web_meetings_bpa_body['und'][0]['value']);
       $firstWord=strstr($bpa_body, ' ',true);  
       $ranges->quote=$word;
       $ranges->ranges[0]->startOffset=0;
       $ranges->ranges[0]->start = "\/div\/p";
       $ranges->ranges[0]->end = "\/div\/p";
       $ranges->ranges[0]->endOffset=strlen($firstWord)+1;
       db_update('os2dagsorden_annotator_notes')
       ->fields(array(
       'note_info' => json_encode($ranges),
       'bilag_id' => $new_attachment_nid
      ))
    ->condition('id', $record['id'],'=')
    ->execute();      
    }
    
  }
  else {  
  db_update('os2dagsorden_annotator_notes')
    ->fields(array(
      'bilag_id' => $new_attachment_nid
    ))
    ->condition('bilag_id', $old_attachment_nid,'=')
    ->execute();
  } 
}