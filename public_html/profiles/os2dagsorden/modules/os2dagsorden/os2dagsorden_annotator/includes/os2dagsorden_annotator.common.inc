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
    
    $result = db_select('os2dagsorden_annotator_notes', 'notes')
	->fields('notes')
	->condition('uid', $user->uid,'=')
	->condition('meeting_id', $meeting_id,'=')
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