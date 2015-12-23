<?php
const IMPORT_STATUS_SCHEDULED = "Scheduled";
const IMPORT_STATUS_IMPORTED = "Imported";
const IMPORT_STATUS_IGNORED = "Ignored";
const IMPORT_STATUS_DELETED = "Deleted";

/**
 * This function adds a meeting entry to the database
 *
 * @param $meeting
 */
function os2web_esdh_provider_index_meeting($nid, $manifest, $agenda){
  //drupal_set_message("MANIFEST: " . print_r($manifest,1));
  //drupal_set_message("AGENDA: " . print_r($agenda,1));

  $status = IMPORT_STATUS_SCHEDULED;
  if ($nid){
    $status = IMPORT_STATUS_IMPORTED;
  }
  if (empty($agenda['publish']) || $agenda['publish'] == 0) {
    $status = IMPORT_STATUS_IGNORED;
  }

  //trying to update existing entry
  if (os2web_esdh_provider_index_meeting_is_meeting_indexed($manifest['id'], $agenda['meeting_sub_id'])){
  db_update('os2web_esdh_provider_import')
    ->fields(array(
      'nid' => $nid? $nid : 0,
      'import_status' => $status,
      'meeting_xml' => $manifest['uri'],
      'meeting_name' => $agenda['title'],
      'meeting_xml_changed' => ($manifest['uri'])? filemtime(drupal_realpath($manifest['uri'])) : NULL,
      'agenda_xmlid' => $agenda['agenda_xmlid'],
      'agenda_access' => ($agenda['agenda_access'] == 'Lukket')? 0 : 1,
      'agenda_publish' => ($agenda['publish']) ? 1 : 0,
      'agenda_type' => $agenda['type'],
      'agenda_xml_changed' => ($agenda['path'])? filemtime(drupal_realpath($agenda['path'])) : NULL,
      'committeed_id' => $agenda['committee_id'],
    ))
    ->condition('meeting_xmlid', $manifest['id'], '=')
    ->condition('agenda_sysid', $agenda['meeting_sub_id'], '=')
    ->execute();
  } else {//no entry found - create a new entry
    db_insert('os2web_esdh_provider_import')
      ->fields(array(
        'nid' => $nid? $nid : 0,
        'import_status' => $status,
        'meeting_xml' => $manifest['uri'],
        'meeting_xmlid' => $manifest['id'],
        'meeting_name' => $agenda['title'],
        'meeting_sysid' => $agenda['meeting_id'],
        'meeting_xml_changed' => ($manifest['uri'])? filemtime(drupal_realpath($manifest['uri'])) : NULL,
        'agenda_sysid' => $agenda['meeting_sub_id'],
        'agenda_xmlid' => $agenda['agenda_xmlid'],
        'agenda_access' => ($agenda['agenda_access'] == 'Lukket')? 0 : 1,
        'agenda_publish' => ($agenda['publish']) ? 1 : 0,
        'agenda_type' => $agenda['type'],
        'agenda_xml_changed' => ($agenda['path'])? filemtime(drupal_realpath($agenda['path'])) : NULL,
        'committeed_id' => $agenda['committee_id'],
        'committeed_tid' => 0,
      ))
      ->execute();
  }
}

function os2web_esdh_provider_index_meeting_is_manifest_outdated($meeting_xmlid, $currentXmlChanged){
  if (!os2web_esdh_provider_index_meeting_is_meeting_indexed($meeting_xmlid)) //manifest is not indexed
    return TRUE;

  $rowCount = db_select('os2web_esdh_provider_import', 'o')
    ->fields('o')
    ->condition('meeting_xmlid', $meeting_xmlid, '=')
    ->condition('meeting_xml_changed', $currentXmlChanged, '<')
    ->execute()
    ->rowCount();

  return $rowCount > 0;
}

function os2web_esdh_provider_index_meeting_has_deleted_agendas($meeting_xmlid){
  $rowCount = db_select('os2web_esdh_provider_import', 'o')
    ->fields('o')
    ->condition('meeting_xmlid', $meeting_xmlid, '=')
    ->condition('import_status', IMPORT_STATUS_DELETED, '=')
    ->execute()
    ->rowCount();

  return $rowCount > 0;
}

function os2web_esdh_provider_index_meeting_is_meeting_indexed($meeting_xmlid, $agenda_sysid = FALSE){
  $query = db_select('os2web_esdh_provider_import', 'o')
    ->fields('o')
    ->condition('meeting_xmlid', $meeting_xmlid, '=');

  if ($agenda_sysid)
    $query->condition('agenda_sysid', $agenda_sysid, '=');

  $rowCount = $query->execute()
              ->rowCount();

  return $rowCount > 0;
}

function os2web_esdh_provider_index_meeting_update_status($meeting_xmlid, $agenda_sysid = null , $status){
  $query = db_update('os2web_esdh_provider_import')
    ->fields(array(
      'import_status' => $status,
    ))
    ->condition('meeting_xmlid', $meeting_xmlid, '=');
  
    if ($agenda_sysid)
      $query->condition('agenda_sysid', $agenda_sysid, '=');
    
    $query->execute();
}

function os2web_esdh_provider_index_meeting_update_nid($meeting_xmlid, $agenda_sysid = null, $nid){
  $query = db_update('os2web_esdh_provider_import')
    ->fields(array(
      'nid' => $nid,
    ))
    ->condition('meeting_xmlid', $meeting_xmlid, '=');
    
    if ($agenda_sysid)
      $query->condition('agenda_sysid', $agenda_sysid, '=');
    
    $query->execute();
}

function os2web_esdh_provider_index_meeting_get_nid($meeting_xmlid){
  $nid = db_select('os2web_esdh_provider_import', 'o')
    ->fields('o', array('nid'))
    ->condition('meeting_xmlid', $meeting_xmlid, '=')
    ->condition('import_status', IMPORT_STATUS_IMPORTED, '=')
    ->execute()
    ->fetchField();

  return $nid;
}

function os2web_esdh_provider_index_meeting_update_committee_tid($meeting_xmlid, $agenda_sysid, $tid){
  db_update('os2web_esdh_provider_import')
    ->fields(array(
      'committeed_tid' => $tid,
    ))
    ->condition('meeting_xmlid', $meeting_xmlid, '=')
    ->condition('agenda_sysid', $agenda_sysid, '=')
    ->execute();
}