<?php
/**
 * @file
 * Code for the OS2Web Meeting Views - meeting details view.
 */
 
/////////////////////////////////////////header START /////////////////////////////////////////
function os2dagsorden_meeting_views_meeting_details_breadcrumb(){
  global $base_url;
  $breadcrumb[] = l('Hjem', $base_url);
  $breadcrumb[] .= '<span class="breadcrumb-active">Mødedetaljer</span>';
  drupal_set_breadcrumb($breadcrumb);
}

function os2dagsorden_meeting_views_meeting_details_agenda_and_edit_button(){
  global $base_url;
  $q = explode('/',$_GET['q']);
  $meeting_id = $q[1];
  if (module_exists('os2dagsorden_create_agenda') && user_access('administer os2web')){
    print '<div class="controls-right">';
    print '<a href="' . $base_url . '/agenda/meeting/' . $meeting_id . '" class="form-submit">Edit</a>';
    print '<a href="' . $base_url . '/agenda/meeting/' . $meeting_id . '?simple=1" class="form-submit">Simple Edit</a>';
    print '</div>';
    print '<div class="clearfix"></div>';
  }
}

function os2dagsorden_meeting_views_meeting_details_description_download(){
  global $base_url;
  $q = explode('/',$_GET['q']);
  $meeting_id = $q[1];

  //user has no access to agenda
  if (!os2dagsorden_access_helper_check_user_can_see_meeting_agenda($meeting_id))
    return;

  //meeting all notes
  echo '<div class="controls-left">';
  echo '<a target="_blank" href="' . $base_url . '?q=meeting/' . $meeting_id . '/notes" class="form-submit">Mødenoter</a>';
  echo '</div>';

  ///////////////////////descriptions (not additional)
  echo '<div class="controls-right">';
  //closed version - if not empty
  $meeting = node_load($meeting_id);
  $user_can_see_closed_agendas = os2dagsorden_access_helper_check_user_can_see_closed_agenda($meeting->nid);

  if ($user_can_see_closed_agendas){
    if (!empty($meeting->field_os2web_meetings_full_doc_c['und'][0]['uri'])){
      echo '<a target="_blank" href="' . file_create_url($meeting->field_os2web_meetings_full_doc_c['und'][0]['uri']) . 
      '" class="form-submit">' . variable_get('os2dagsorden_meeting_description_download_title', 'Hent samlet dokument i PDF') . ' (lukket)</a>';
    }
  }

  //opened version - if not empty
  if (!empty($meeting->field_os2web_meetings_full_doc['und'][0]['uri'])){
      echo '<a target="_blank" href="' . file_create_url($meeting->field_os2web_meetings_full_doc['und'][0]['uri']) . 
      '" class="form-submit">' . variable_get('os2dagsorden_meeting_description_download_title', 'Hent samlet dokument i PDF') . '</a>';
  }
  echo '</div>';
  echo '<div class="clearfix"></div>';

  ///////////////////////descriptions (additional)
  $additional_descriptions = array();
  if (!empty($meeting->field_os2web_meetings_add_doc_c['und'])){
    foreach ($meeting->field_os2web_meetings_add_doc_c['und'] as $file){
	$additional_descriptions[$file['description']]['closed'] = $file;
    }
  }
  if (!empty($meeting->field_os2web_meetings_add_doc['und'])){
    foreach ($meeting->field_os2web_meetings_add_doc['und'] as $file){
	$additional_descriptions[$file['description']]['opened'] = $file;
    }
  }

  ksort($additional_descriptions);

  foreach ($additional_descriptions as $add_desc){
    echo '<div class="controls-right">';  
    //closed version additional - if not empty
    if ($user_can_see_closed_agendas){
      if (!empty($add_desc['closed'])){
	echo '<a target="_blank" href="' . file_create_url($add_desc['closed']['uri']) .
	'" class="form-submit">' . variable_get('os2dagsorden_meeting_description_download_title_additional', 'Hent tillægsdokument i PDF') . ' (lukket)</a>';
      }
    }
    //opened version additional - if not empty
    if (!empty($add_desc['opened'])){
	echo '<a target="_blank" href="' . file_create_url($add_desc['opened']['uri']) . 
	'" class="form-submit">' . variable_get('os2dagsorden_meeting_description_download_title_additional', 'Hent tillægsdokument i PDF') .  '</a>';
    }
    echo '</div>';
    echo '<div class="clearfix"></div>';
  }
}

function os2dagsorden_meeting_views_meeting_details_admin_controls(){
  if (user_access('administer os2web')){
    global $base_url;
    $q = explode('/',$_GET['q']);
    $meeting_id = $q[1];
  
    //edit button
    echo '<div class="controls-left">';
    echo '<a href="' . $base_url . '?q=node/' . $meeting_id . '/edit" class="form-submit">Afpublicer møde</a>';
    echo '</div>';
  
    //import form
    echo '<div class="controls-left">';
    echo '<a href="' . $base_url . '?q=admin/config/os2web/esdh_provider" class="form-submit">Import form</a>';
    echo '</div>';
  }
}

function os2dagsorden_meeting_views_meeting_description_download(){
 global $base_url;
  $q = explode('/',$_GET['q']);
  $meeting_id = $q[1];
     $meeting = node_load($meeting_id);
    
  //opened version - if not empty
  if (!empty($meeting->field_meeting_description['und'][0]['uri'])){
      echo '<a target="_blank" href="' . file_create_url($meeting->field_meeting_description['und'][0]['uri']) . 
      '" ><span class="print-meeting-link">Samlet dokument</span> </a>';
  }
	else 
      echo '<a target="_blank" href="/printpdf/meeting/'.$meeting_id.'/print" ><span class="print-meeting-link">Samlet dokument</span> </a>';
}
/////////////////////////////////////////header END /////////////////////////////////////////

/////////////////////////////////////////PAGE fields start /////////////////////////////////////////
function os2dagsorden_meeting_views_meeting_details_fields_indicator_meeting_has_sp($meeting_id){
  os2dagsorden_meeting_views_common_meeting_has_sp($meeting_id);
}

function os2dagsorden_meeting_views_meeting_details_fields_indicator_meeting_has_notes($meeting_id){
  os2dagsorden_meeting_views_common_meeting_has_notes($meeting_id);
}
function os2dagsorden_meeting_views_meeting_details_fields_enddate($meeting_id){  
    if (variable_get('os2dagsorden_show_meeting_enddate', true)) {
        $meeting = node_load($meeting_id);
        $date = field_get_items('node', $meeting, 'field_os2web_meetings_date');
        $reset = date_default_timezone_get();
        date_default_timezone_set("UTC");
        strtotime($date[0]["value2"]);
        print format_date(strtotime($date[0]["value2"]), $type = 'short', '', $date[0]['timezone']);
        date_default_timezone_set($reset);
    } 
 }
 function os2dagsorden_meeting_views_meeting_details_fields_committee($meeting_id){ 
   if (variable_get('os2dagsorden_show_meeting_committee', true)) 
      os2dagsorden_meeting_views_common_meeting_committee($meeting_id);
 }
  function os2dagsorden_meeting_views_meeting_details_fields_type($meeting_id){ 
   if (variable_get('os2dagsorden_show_meeting_type', true)){ 
      $meeting = node_load($meeting_id);
      $meeting_type=field_get_items('node', $meeting, 'field_os2web_meetings_type');
      print $meeting_type[0]['value'];
 }
}
 function os2dagsorden_meeting_views_meeting_details_samlet_dokument_link(){
   if (variable_get('os2dagsorden_show_samlet_dokument_link', true)) 
       os2dagsorden_meeting_views_meeting_description_download();
 }
//////////////////////////////////////////PAGE fields end //////////////////////////////////////////// 

 /////////////////////////////////////////COMMENTS fields START /////////////////////////////////////////
function os2dagsorden_meeting_views_meeting_details_comments_access(){
  if (variable_get('os2dagsorden_show_comments', false)) {
    $q = $_GET['q'];
    $q = explode('/', $q);
    $meeting_id = $q[1];
    $meeting = node_load($meeting_id);
    if (!empty($meeting->field_os2web_meetings_comments['und'][0]['value']))
       return TRUE;
    }
    return FALSE;
}

/////////////////////////////////////////COMMENTS fields END /////////////////////////////////////////
function os2dagsorden_meeting_views_meeting_details_special_conditions_access(){
  if (variable_get('os2dagsorden_show_comments', false)) {
    $q = $_GET['q'];
    $q = explode('/', $q);
    $meeting_id = $q[1];
    $meeting = node_load($meeting_id);
    if (!empty($meeting->field_os2web_meetings_conditions['und'][0]['value']))
       return TRUE;
    }
    return FALSE;
}

/////////////////////////////////////////DELTOG fields start /////////////////////////////////////////
function os2dagsorden_meeting_views_meeting_details_fields_participants_deltog($meeting_id){
  $meeting = node_load($meeting_id);
  print($meeting->field_os2web_meetings_partic['und'][0]['value']);
  
}
/////////////////////////////////////////DELTOG fields end /////////////////////////////////////////

/////////////////////////////////////////Afbud / Fraværende fields start /////////////////////////////////////////
function os2dagsorden_meeting_views_meeting_details_fields_participants_afbud_access(){
    return variable_get('os2dagsorden_show_participants_afbud', false);
}
function os2dagsorden_meeting_views_meeting_details_fields_participants_afbud($meeting_id){
   $meeting = node_load($meeting_id);
    if (isset($meeting->field_os2web_meetings_particcanl['und'])) 
        print($meeting->field_os2web_meetings_particcanl['und'][0]['value']);
  
}
/////////////////////////////////////////Afbud / Fraværende fields end /////////////////////////////////////////
/////////////////////////////////////////PRINT ALL SPEAKER PAPER fields start /////////////////////////////////////////
function os2dagsorden_meeting_views_meeting_details_fields_print_all_speaker_papers($nid){
  if (os2dagsorden_access_helper_meeting_has_speaker_paper($nid)){
    global $base_url;
    print "<div class='speaker-paper-all-print'>";
    print '<input class="form-submit print-button" type="button" onclick="window.open(';
    print(" ' " . $base_url . '/print/meeting/' . $nid . '/speaker-papers/print' . " ' ");
    print ')" value="Print Alle Talepapirer">';

    print "</div>";
  }
}
/////////////////////////////////////////PRINT ALL SPEAKER PAPER fields end /////////////////////////////////////////

/////////////////////////////////////////DAGSORDEN fields start /////////////////////////////////////////
function os2dagsorden_meeting_views_meeting_details_dagsorden_access(){
  $q = $_GET['q'];
  $q = explode('/', $q);
  $meeting_id = $q[1];

  return os2dagsorden_access_helper_check_user_can_see_meeting_agenda($meeting_id);
}

function os2dagsorden_meeting_views_meeting_details_fields_indicator_bullet_point_has_sp($bp_id){
  os2dagsorden_meeting_views_common_bullet_point_has_sp($bp_id);
}

function os2dagsorden_meeting_views_meeting_details_fields_indicator_bullet_point_has_notes($nid, $is_closed, $is_personal){
  $annotations = os2dagsorden_annotator_get_notes_by_bullet_point_id($nid);
  if (!empty($annotations))
    print '<div class="indicator-has-notes"></div>';
  else if(!os2dagsorden_access_helper_bullet_point_has_speaker_paper($nid) && !$is_closed && !$is_personal)
    print '<div class="indicator-empty"></div>';
}

function os2dagsorden_meeting_views_meeting_details_fields_bullet_point_title($title, $meeting_id, $bp_id){
  global $base_url;

  //logic for touch devices
  if (os2dagsorden_access_helper_is_touch()){
    if (mb_strlen($title) > 70)
      $title = mb_substr($title, 0, 67) . '...';
  } else {//desktop device
    if (mb_strlen($title) > 95) {
      $tooltip = ' title="' . $title . '"';
      $title = mb_substr($title, 0, 92) . '...';
    }
  }

  if (os2dagsorden_access_helper_check_user_can_see_bullet_point($meeting_id, $bp_id))
    print '<a href="' . $base_url . '/meeting/' . $meeting_id . '/bullet-point/' . $bp_id . '" class="first-child poshy_tip"' . $tooltip . '>' . $title . '</a>';
  else 
    print '<a class="first-child">' . $title . '</a>';
}

function os2dagsorden_meeting_views_meeting_details_fields_bullet_point_attachments_with_text($meeting_id, $bp_id){
  global $user, $base_url;
  $bullet_point = node_load($bp_id);
  if (isset($bullet_point->field_os2web_meetings_attach['und'])){
    print '<div class="item-list">';
    print '<ul class="ul-item-list-dagsordenspunkt">';
    if ($bullet_point->field_os2web_meetings_bul_closed['und'][0]['value'] == 1 && !os2dagsorden_meeting_views_meeting_details_show_closed_bullet_point_content($meeting_id, $bp_id)){
      print "<i>Dagsordenpunktets indhold er skjult fordi dagsordenspunktet er lukket. 
      Klik på dagsordenspunktets overskrift for at få indeholdet frem.</i>";
    } else if ($bullet_point->field_os2web_meetings_bul_pers['und'][0]['value'] == 1 && !os2dagsorden_meeting_views_meeting_details_show_closed_bullet_point_content($meeting_id, $bp_id)) {
      print "<i>Dagsordenpunktets indhold er skjult fordi dagsordenspunktet er et personpunkt. 
      Klik på dagsordenspunktets overskrift for at få indeholdet frem.</i>";
    }
    else {
      $bilags = array();
      $cases = array();
      $all_attachments = array();
      foreach($bullet_point->field_os2web_meetings_attach['und'] as $attachment_id){
	$hash = $attachment_id['target_id'];
	$all_attachments[$hash] = $attachment_id;
      }

      foreach($all_attachments as $attachment_id){
	$attachment = node_load($attachment_id['target_id']);

	if (!empty($attachment->field_os2web_meetings_bpa_file['und'])){// if is bilag
	  //saving bilags to the end
	 //if (stripos($attachment->title, "Bilag") === 0)
	if ($attachment->field_os2web_meetings_bpa_type['und'][0]['value']=='Sager')
           $cases[] = $attachment;
        else
           $bilags[] = $attachment; 
	 
	} else {//not bilag
	  print '<li class="non-bilag">';
	  
	  //logic for touch devices
	  if (os2dagsorden_access_helper_is_touch()){
	  if (mb_strlen($attachment->title) > 52)
	    $title = mb_substr($attachment->title, 0, 49) . '...';
	  else
	    $title = $attachment->title;
	  } else {//desktop device
	    if (mb_strlen($attachment->title) > 70)
	      $title = mb_substr($attachment->title, 0, 67) . '...';
	    else
	      $title = $attachment->title;
	  }
	  
	  $link = $base_url . '/meeting/' . $meeting_id . '/bullet-point/' . $bp_id . '/bullet-point-attachment/' . $attachment->nid;
	  print '<div id="' . $attachment->nid . '" class="indicator-has-no-notes"></div><a href="' . $link . '" class="first-child last-child">' . $title . '</a>';

	  //attachment text - if any
	  if (!empty($attachment->field_os2web_meetings_bpa_body['und'][0]['safe_value'])){	
	    print '<div class="attachment_text_container">';

	    print '<div class="attachment_text_full_container ajax-progress bpa-' . $meeting_id . '-' . $bp_id . '-' . $attachment->nid . '">';
	    print 'Vent venligst...<div class="throbber"></div>';
	    print '</div>';

	    print '</div>';
	  }
	  print '</li>';
	}
      }

    if ($bullet_point->title !== 'Bilag' && $bullet_point->title !== 'Sager'){
      if (!empty($cases) && !(variable_get('os2dagsorden_show_case_bullet_point', FALSE))&& variable_get('os2dagsorden_show_bilag_bullet_point', FALSE)){
         _os2dagsorden_meeting_views_meeting_details_bilag_cases($cases, $meeting_id, $bp_id);  
         if (!empty($bilags))
           _os2dagsorden_meeting_views_meeting_details_bilag_cases_bullet_point('Bilag', $bilags, $meeting_id, $bp_id);
      }            
      else{
      if (!empty($bilags)){
           if (variable_get('os2dagsorden_show_bilag_bullet_point', FALSE))
              _os2dagsorden_meeting_views_meeting_details_bilag_cases_bullet_point('Bilag', $bilags, $meeting_id, $bp_id, 'bilags');
           else
              _os2dagsorden_meeting_views_meeting_details_bilag_cases($bilags, $meeting_id, $bp_id);
      }
   	if (!empty($cases)){
            if (variable_get('os2dagsorden_show_case_bullet_point', FALSE))              
           _os2dagsorden_meeting_views_meeting_details_bilag_cases_bullet_point(variable_get('os2dagsorden_sager_group_title', 'Sager'), $cases, $meeting_id, $bp_id, 'cases');
            else
            _os2dagsorden_meeting_views_meeting_details_bilag_cases($cases, $meeting_id, $bp_id);  
                               
	  }
       } 
    }
    else {
	_os2dasorden_meeting_views_meeting_details_bilag_cases_with_content($bilags, $meeting_id, $bp_id);
	_os2dasorden_meeting_views_meeting_details_bilag_cases_with_content($cases, $meeting_id, $bp_id);
      }  
      
       print '</div>';
    }
    print '</ul>';
    print '</div>';
  }
}

function _os2dagsorden_meeting_views_meeting_details_bilag_cases( $elements, $meeting_id, $bp_id){
    foreach ($elements as $attachment){
    print '<li class="bilag">';
	
	//logic for touch devices
	if (os2dagsorden_access_helper_is_touch()){
	  if (mb_strlen($attachment->title) > 60)
	    $title = mb_substr($attachment->title, 0, 57) . '...';
	  else
	    $title = $attachment->title;
	} else {//desktop device
	  if (mb_strlen($attachment->title) > 95)
	    $title = mb_substr($attachment->title, 0, 92) . '...';
	  else
	    $title = $attachment->title;
	}
	if ($attachment->field_os2web_meetings_bpa_closed['und'][0]['value'] == 1)
	  print '<div class="indicator-unlocked"></div>';
	else
	  print '<div class="indicator-empty"></div>';
	  
	//$link = $base_url . '/meeting/' . $meeting_id . '/bullet-point/' . $bp_id . '/bullet-point-attachment/' . $attachment->nid;
	      if (!empty($attachment->field_os2web_meetings_bpa_html['und'][0]))
            $link = $base_url . '/meeting/' . $meeting_id . '/bullet-point/' . $bp_id . '/bullet-point-attachment/' . $attachment->nid;
        else
            $link = file_create_url($attachment->field_os2web_meetings_bpa_file['und'][0]['uri']);
        
	print '<div id="' . $attachment->nid . '" class="indicator-has-no-notes"></div>';
        if (os2dagsorden_access_helper_check_user_can_see_bullet_point_attachment($meeting_id, $bp_id, $attachment->nid)){
	  print '<a href="' . $link . '" target="_blank" class="first-child last-child">' . $title . '</a>';

           
	  //attachment text - if any
	  /*if (!empty($attachment->field_os2web_meetings_bpa_html['und'][0])){	  
	    print '<div class="attachment_text_container">';

	    print '<div class="attachment_text_trimmed_container ajax-progress bpa-' . $meeting_id . '-' . $bp_id . '-' . $attachment->nid . '">';

	    print 'Vent venligst...<div class="throbber"></div>';
	    print '</div>';
	    print('<a class="first-child last-child" href="' . $link . '" target="_blank">Læs mere...</a>');

	    print '</div>';
	  }*/
	} else {
	  print '<a class="first-child last-child">' . $title . '</a>';
	}
	print '</li>';
      }
    }

function _os2dagsorden_meeting_views_meeting_details_bilag_cases_bullet_point($bp_title, $elements, $meeting_id, $bp_id, $attachment_type){
  print '<li class="bilags_cases ' . $attachment_type. '">';
  print '<div class="indicator-has-no-notes"></div>';
  print '<a class="first-child last-child">' . $bp_title. '</a>';
  print '<div class="bilags_cases_container">';

  //going through all bilags
  foreach ($elements as $attachment){
    print '<div class="bilag">';
    
    //logic for touch devices
    if (os2dagsorden_access_helper_is_touch()){
      if (mb_strlen($attachment->title) > 60)
	$title = mb_substr($attachment->title, 0, 57) . '...';
      else
	$title = $attachment->title;
    } else {//desktop device
      if (mb_strlen($attachment->title) > 80)
	$title = mb_substr($attachment->title, 0, 78) . '...';
      else
	$title = $attachment->title;
    }
    if ($attachment->field_os2web_meetings_bpa_closed['und'][0]['value'] == 1)
      print '<div class="indicator-unlocked"></div>';
    else
      print '<div class="indicator-empty"></div>';
      
    if (!empty($attachment->field_os2web_meetings_bpa_html['und'][0]))
      $link = $base_url . '/meeting/' . $meeting_id . '/bullet-point/' . $bp_id . '/bullet-point-attachment/' . $attachment->nid;
    else
      $link = file_create_url($attachment->field_os2web_meetings_bpa_file['und'][0]['uri']);
    
    print '<div id="' . $attachment->nid . '" class="indicator-has-no-notes"></div>';  
    if (os2dagsorden_access_helper_check_user_can_see_bullet_point_attachment($meeting_id, $bp_id, $attachment->nid)){
      print '<a href="' . $link . '" target="_blank" class="first-child last-child">' . $title . '</a>';
    } else {
      print '<a class="first-child last-child">' . $title . '</a>';
    }
    print '</div>';
  }

  print '</div>';
  print '</li>';
}

function _os2dasorden_meeting_views_meeting_details_bilag_cases_with_content($elements, $meeting_id, $bp_id){
  //going through all bilags
  foreach ($elements as $attachment){
    print '<li class="bilag">';
    
    //logic for touch devices
    if (os2dagsorden_access_helper_is_touch()){
      if (mb_strlen($attachment->title) > 60)
	$title = mb_substr($attachment->title, 0, 57) . '...';
      else
	$title = $attachment->title;
    } else {//desktop device
      if (mb_strlen($attachment->title) > 80)
	$title = mb_substr($attachment->title, 0, 78) . '...';
      else
	$title = $attachment->title;
    }
    if ($attachment->field_os2web_meetings_bpa_closed['und'][0]['value'] == 1)
      print '<div class="indicator-unlocked"></div>';
    else
      print '<div class="indicator-empty"></div>';
      
    if (!empty($attachment->field_os2web_meetings_bpa_html['und'][0]))
      $link = $base_url . '/meeting/' . $meeting_id . '/bullet-point/' . $bp_id . '/bullet-point-attachment/' . $attachment->nid;
    else
      $link = file_create_url($attachment->field_os2web_meetings_bpa_file['und'][0]['uri']);
    
    print '<div id="' . $attachment->nid . '" class="indicator-has-no-notes"></div>';
    if (os2dagsorden_access_helper_check_user_can_see_bullet_point_attachment($meeting_id, $bp_id, $attachment->nid)){
      print '<a href="' . $link . '" target="_blank" class="first-child last-child">' . $title . '</a>';
      
      //attachment text - if any
      if (!empty($attachment->field_os2web_meetings_bpa_html['und'][0])){
	//should bilag be visible
	if (variable_get('os2dagsorden_show_bilag', TRUE)){
	  print '<div class="attachment_text_container">';

	  print '<div class="attachment_text_trimmed_container ajax-progress bpa-' . $meeting_id . '-' . $bp_id . '-' . $attachment->nid . '">';

	  print 'Vent venligst...<div class="throbber"></div>';
	  print '</div>';
	  print('<a class="first-child last-child" href="' . $link . '" target="_blank">Læs mere...</a>');

	  print '</div>';
	}
      }
    } else {
      print '<a class="first-child last-child">' . $title . '</a>';
    }
    print '</li>';
  }
}

function os2dagsorden_meeting_views_meeting_details_fields_speaker_paper_link($meeting_id, $bp_id, $bp_title){
  global $base_url;
  if (!os2dagsorden_access_helper_check_user_can_see_bullet_point($meeting_id, $bp_id)){
    print "<a>&nbsp;</a>";
  }
  else {
    if (os2dagsorden_access_helper_bullet_point_has_speaker_paper($bp_id)){
      $link = $base_url . '?q=meeting/' . $meeting_id . '/bullet-point/' . $bp_id;
      print '<a href="' . $link . '"><div class="indicator-has-speaker-paper"></div>Talepapir</a>';
    } else {
      $q = $_GET['q'];
      $link = $base_url . '?q=node/add/os2web-meetings-spaper&edit[field_os2web_meetings_sp_bullet][und][0][target_id]=' . $bp_title . ' (' . $bp_id . ')' . '&destination=' . $q;
      print '<a href="' . $link . '"><div class="indicator-create-speaker-paper"></div>Nyt talepapir</a>';
    }
  }
}
function os2dagsorden_meeting_views_meeting_details_fields_bullet_point_print_link($meeting_id, $bp_id){
  global $base_url;

  if (os2dagsorden_access_helper_check_user_can_see_bullet_point($meeting_id, $bp_id) && variable_get('os2dagsorden_show_print_icon', false)){
    print '<a href="' . $base_url . '/print/meeting/' . $meeting_id . '/bullet-point/' . $bp_id . '/print"><span class="bullet-point-print-link"></span>&nbsp;</a>';
  } else {
    print '<a href="' . $base_url . '/meeting/' . $meeting_id . '/bullet-point/' . $bp_id . '">&nbsp;</a>';
  }
}
/////////////////////////////////////////DAGSORDEN fields END /////////////////////////////////////////

/////////////////////////////////////////DAGSORDEN filter fields START /////////////////////////////////////////
function os2dagsorden_meeting_views_meeting_details_fields_filter_bullet_point($nid, $filter_opened){
   if (variable_get('os2dagsorden_group_closed_bullet_points', 'false') === 'false'){//put inline
    //accept every type
    return FALSE;
  } else {//put separately
    $bullet_point = node_load($nid);
    
    if ($filter_opened){//accept opened
      if ($bullet_point->field_os2web_meetings_bul_closed['und'][0]['value'] == 0)
	return FALSE;
      else
	return TRUE;
    } else {//accept closed
      if ($bullet_point->field_os2web_meetings_bul_closed['und'][0]['value'] == 1)
	return FALSE;
      else
	return TRUE;
    }
  }
}

function os2dagsorden_meeting_views_meeting_details_show_closed_bullet_point_content($meeting_id, $bp_id){
 if (variable_get('os2dagsorden_show_closed_bullet_point_content', FALSE) && os2dagsorden_access_helper_check_user_can_see_bullet_point($meeting_id, $bp_id))
   return TRUE;
 return FALSE;
}
/////////////////////////////////////////DAGSORDEN filter fields END /////////////////////////////////////////

/////////////////////////////////////////LUKKET DAGSORDEN fields START /////////////////////////////////////////
function os2dagsorden_meeting_views_meeting_details_lukket_dagsorden_access(){
  if (os2dagsorden_meeting_views_meeting_details_dagsorden_access()){ 
       return variable_get('os2dagsorden_group_closed_bullet_points', 'false') === 'true';
  }
}
/////////////////////////////////////////LUKKET DAGSORDEN fields END /////////////////////////////////////////