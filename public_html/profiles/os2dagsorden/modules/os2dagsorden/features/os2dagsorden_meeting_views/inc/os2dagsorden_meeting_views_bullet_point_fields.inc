<?php
/**
 * @file
 * Code for the OS2Web Meeting Views - speaker paper (bullet point) view.
 */

/////////////////////////////////////////header START /////////////////////////////////////////
function os2dagsorden_meeting_views_bullet_point_breadcrumb(){
  global $base_url;
  $q = explode('/',$_GET['q']);
  $breadcrumb[] = l('Hjem', $base_url);
  $breadcrumb[] .= l('Mødedetaljer', 'meeting/'.$q[1]);
  $breadcrumb[] .= '<span class="breadcrumb-active">Dagsordenspunkt</span>';
  drupal_set_breadcrumb($breadcrumb);
}

function os2dagsorden_meeting_views_bullet_point_print_send_to_friend(){
  if (module_exists('os2web_print_send_to_friend')){
    global $base_url;
    $q = explode('/',$_GET['q']);
    $meeting_id = $q[1];
    $bp_id = $q[3];
    print '<div class="controls-right">';
    print '<a href="' . $base_url . '?q=meeting/' . $meeting_id . '/bullet-point/' . $bp_id . '/send_to_friend_form" class="form-submit" rel="lightframe">Send til en ven</a>
    <a href="' . $base_url . '?q=/print/meeting/' . $meeting_id . '/bullet-point/' . $bp_id . '/print" class="form-submit print-button" target="_blank">Print</a>';
    print '</div>';
    print '<div class="clearfix"></div>';
  }
}

function os2dagsorden_meeting_views_bullet_point_print_to_pdf(){
  global $base_url;
  $q = explode('/',$_GET['q']);
  $meeting_id = $q[1];
  $bp_id = $q[3];
  print '<div class="controls-right">';
  print '<a href="' . $base_url . '?q=/printpdf/meeting/' . $meeting_id . '/bullet-point/' . $bp_id . '/print" class="form-submit" target="_blank">PDF</a>';
  print '</div>';
}
/////////////////////////////////////////header END /////////////////////////////////////////

/////////////////////////////////////////PAGE START /////////////////////////////////////////
function os2dagsorden_meeting_views_bullet_point_page_access(){
  $q = explode("/", $_GET['q']);

  $meeting_id =  $q[1];
  $bullet_point_id = $q[3];

  return os2dagsorden_access_helper_check_user_can_see_bullet_point($meeting_id, $bullet_point_id);
}

function os2dagsorden_meeting_views_bullet_point_fields_indicator_bullet_point_has_notes($bp_id){
  os2dagsorden_meeting_views_common_bullet_point_has_notes($bp_id);
}

function os2dagsorden_meeting_views_bullet_point_fields_title_navigation_buttons($bp_id){
  $q = explode("/", $_GET['q']);

  $meeting_id =  $q[1];
  $meeting = node_load($meeting_id);
  
  $bullet_point = node_load($bp_id);
  
  $previous_bullet_point = null;
  $next_bullet_point = null;
  foreach ($meeting->field_os2web_meetings_bullets['und'] as $new_bp) {
    if (intval($bp_id) != intval($new_bp['target_id'])) {
      $new_bullet_point = node_load($new_bp['target_id']);
      //checking if the ordinal number of new bullet point is BELOW the current bulet point ordinal number
      //at the same time, checking if user has an access to that bullet point
      if ($new_bullet_point->field_os2web_meetings_bul_number['und'][0]['value'] < $bullet_point->field_os2web_meetings_bul_number['und'][0]['value'] && os2dagsorden_access_helper_check_user_can_see_bullet_point($meeting_id,$new_bp['target_id'])){
	  //checking if there is no pointer to previous bullet point
	  //or the ordinal number of the new bullet point is higher than the ordinal number of current previous bullet point
	  if (!$previous_bullet_point || $new_bullet_point->field_os2web_meetings_bul_number['und'][0]['value'] > $previous_bullet_point->field_bul_point_number['und'][0]['value']){
	    $previous_bullet_point = $new_bullet_point;
	  }
      }
      //checking if the ordinal number of new bullet point is ABOVE the current bulet point ordinal number
      //at the same time, checking if user has an access to that bullet point
      else if ($new_bullet_point->field_os2web_meetings_bul_number['und'][0]['value'] > $bullet_point->field_os2web_meetings_bul_number['und'][0]['value'] && os2dagsorden_access_helper_check_user_can_see_bullet_point($meeting_id,$new_bp['target_id'])) {
	  //checking if there is no pointer to next bullet point
	  //or the ordinal number of the new bullet point is higher than the ordinal number of current next bullet point
	  if (!$next_bullet_point || $new_bullet_point->field_os2web_meetings_bul_number['und'][0]['value'] < $next_bullet_point->field_bul_point_number['und'][0]['value']){
	      $next_bullet_point = $new_bullet_point;
	  }
      }
      
      //check if everything is set already, then break the loop
      if ($previous_bullet_point && $next_bullet_point &&
	  $previous_bullet_point->field_os2web_meetings_bul_number['und'][0]['value']+1 ==
	  $bullet_point->field_os2web_meetings_bul_number['und'][0]['value']
	  &&
	  $next_bullet_point->field_os2web_meetings_bul_number['und'][0]['value']-1 ==
	  $bullet_point->field_os2web_meetings_bul_number['und'][0]['value']
	  )
	  break;
    }
  }
  
  global $base_url;
  
  if ($previous_bullet_point)
    print '<a href="' . $base_url . '/meeting/' . $meeting_id . '/bullet-point/' . $previous_bullet_point->nid . '" class="form-submit nav-button left"><</a>';
  if ($next_bullet_point)
    print '<a href="' . $base_url . '/meeting/' . $meeting_id . '/bullet-point/' . $next_bullet_point->nid . '" class="form-submit nav-button right">></a>';
  
  if ($bullet_point->field_os2web_meetings_bul_closed['und'][0][value] == 1)
    print '<div class="indicator-unlocked"></div>';
  if ($bullet_point->field_os2web_meetings_bul_pers['und'][0][value] == 1)
    print '<div class="indicator-personal"></div>';
    
  print $bullet_point->title;
}

function os2dagsorden_meeting_views_bullet_point_fields_attachments_and_content($meeting_id, $bp_id){
  global $base_url;
  $bullet_point = node_load($bp_id);
  if (isset($bullet_point->field_os2web_meetings_attach['und'])){
    print '<table><tr><td>';
    print '<div class="item-list item-list-dagsordenspunkt">';
    print '<ul class="ul-item-list-dagsordenspunkt">';

    $bilags = array();

    $all_attachments = array();
    foreach($bullet_point->field_os2web_meetings_attach['und'] as $attachment_id){
      $hash = $attachment_id['target_id'];
      $all_attachments[$hash] = $attachment_id;
    }

    foreach($all_attachments as $attachment_id){
      $attachment = node_load($attachment_id['target_id']);

      if (!empty($attachment->field_os2web_meetings_bpa_file['und'])){// if is bilag
	//saving bilags to the end
	if ($attachment->field_os2web_meetings_bpa_type['und'][0]['value']=='Sager')
           $cases[] = $attachment;
        else
           $bilags[] = $attachment; 
	 
      } else {//not bilag
	print '<li class="non-bilag">';      
	      
	//logic for touch devices
	if (os2dagsorden_access_helper_is_touch()){
	  if (mb_strlen($attachment->title) > 55)
	    $title = mb_substr($attachment->title, 0, 52) . '...';
	  else
	    $title = $attachment->title;
	} else {//desktop device
	  if (mb_strlen($attachment->title) > 85)
	    $title = mb_substr($attachment->title, 0, 82) . '...';
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
       _os2dagsorden_meeting_views_bullet_point_bilag_cases($cases, $meeting_id, $bp_id);  
       if (!empty($bilags))
        _os2dagsorden_meeting_views_bullet_point_bilag_cases_bullet_point('Bilag', $bilags, $meeting_id, $bp_id, 'bilags');
      }            
      else{
      if (!empty($bilags)){
       if (variable_get('os2dagsorden_show_bilag_bullet_point', FALSE))
        _os2dagsorden_meeting_views_bullet_point_bilag_cases_bullet_point('Bilag', $bilags, $meeting_id, $bp_id, 'bilags');
       else
        _os2dagsorden_meeting_views_bullet_point_bilag_cases($bilags, $meeting_id, $bp_id);
      }
      if (!empty($cases)){
       if (variable_get('os2dagsorden_show_case_bullet_point', FALSE))              
         _os2dagsorden_meeting_views_bullet_point_bilag_cases_bullet_point(variable_get('os2dagsorden_sager_group_title', 'Sager'), $cases, $meeting_id, $bp_id, 'cases');
       else
         _os2dagsorden_meeting_views_bullet_point_bilag_cases($cases, $meeting_id, $bp_id);  
                               
      }
     } 
    }
    else {
      _os2dagsorden_meeting_views_bullet_point_bilag_cases_with_content($bilags, $meeting_id, $bp_id); 
      _os2dagsorden_meeting_views_bullet_point_bilag_cases_with_content($cases, $meeting_id, $bp_id);
      }
    print '</ul>';
    print '</div>';
    print '</td></tr></table>';
  }
}
function _os2dagsorden_meeting_views_bullet_point_bilag_cases( $elements, $meeting_id, $bp_id){
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
	  
	//$link = $base_url . '/meeting/' . $meeting_id . '/bullet-point/' . $bp_id . '/bullet-point-attachment/' . $attachment->nid;
	      if (!empty($attachment->field_os2web_meetings_bpa_html['und'][0]))
            $link = $base_url . '/meeting/' . $meeting_id . '/bullet-point/' . $bp_id . '/bullet-point-attachment/' . $attachment->nid;
        else
            $link = file_create_url($attachment->field_os2web_meetings_bpa_file['und'][0]['uri']);
        
        if (os2dagsorden_access_helper_check_user_can_see_bullet_point_attachment($meeting_id, $bp_id, $attachment->nid)){
	  print '<div id="' . $attachment->nid . '" class="indicator-has-no-notes"></div><a href="' . $link . '" target="_blank" class="first-child last-child">' . $title . '</a>';

           
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
function _os2dagsorden_meeting_views_bullet_point_bilag_cases_bullet_point($bp_title, $elements, $meeting_id, $bp_id, $attachment_type){
  print '<li class="bilags_cases ' . $attachment_type . '">';
  print '<div class="indicator-has-no-notes"></div>';
  print '<a class="first-child last-child">' . $bp_title . '</a>';
  print '<div class="bilags_cases_container">';

  //going through all bilags
  foreach ($elements as $attachment){
    print '<div class="bilag">';
    
    //logic for touch devices
    if (os2dagsorden_access_helper_is_touch()){
      if (mb_strlen($attachment->title) > 70)
	$title = mb_substr($attachment->title, 0, 67) . '...';
      else
	$title = $attachment->title;
    } else {//desktop device
      if (mb_strlen($attachment->title) > 105)
	$title = mb_substr($attachment->title, 0, 102) . '...';
      else
	$title = $attachment->title;
    }
    if ($attachment->field_os2web_meetings_bpa_closed['und'][0]['value'] == 1)
	print '<div class="indicator-unlocked"></div>';

    if (!empty($attachment->field_os2web_meetings_bpa_html['und'][0]))
	$link = $base_url . '/meeting/' . $meeting_id . '/bullet-point/' . $bp_id . '/bullet-point-attachment/' . $attachment->nid;
    else
	$link = file_create_url($attachment->field_os2web_meetings_bpa_file['und'][0]['uri']);
	
    if (os2dagsorden_access_helper_check_user_can_see_bullet_point_attachment($meeting_id, $bp_id, $attachment->nid)){
      print '<div id="' . $attachment->nid . '" class="indicator-has-no-notes"></div><a href="' . $link . '" target="_blank" class="first-child last-child">' . $title . '</a>';
    } else {
      print '<a class="first-child last-child">' . $title . '</a>';
    }
    print '</div>';
  }
  print '</div>';
  print '</li>';
}

function _os2dagsorden_meeting_views_bullet_point_bilag_cases_with_content($elements, $meeting_id, $bp_id){
  //going through all bilags
  foreach ($elements as $attachment){
    print '<li class="bilag">';
    
    //logic for touch devices
    if (os2dagsorden_access_helper_is_touch()){
      if (mb_strlen($attachment->title) > 70)
	$title = mb_substr($attachment->title, 0, 67) . '...';
      else
	$title = $attachment->title;
    } else {//desktop device
      if (mb_strlen($attachment->title) > 105)
	$title = mb_substr($attachment->title, 0, 102) . '...';
      else
	$title = $attachment->title;
    }
    if ($attachment->field_os2web_meetings_bpa_closed['und'][0]['value'] == 1)
	print '<div class="indicator-unlocked"></div>';

    if (!empty($attachment->field_os2web_meetings_bpa_html['und'][0]))
	$link = $base_url . '/meeting/' . $meeting_id . '/bullet-point/' . $bp_id . '/bullet-point-attachment/' . $attachment->nid;
    else
	$link = file_create_url($attachment->field_os2web_meetings_bpa_file['und'][0]['uri']);
	
    if (os2dagsorden_access_helper_check_user_can_see_bullet_point_attachment($meeting_id, $bp_id, $attachment->nid)){
      print '<div id="' . $attachment->nid . '" class="indicator-has-no-notes"></div><a href="' . $link . '" target="_blank" class="first-child last-child">' . $title . '</a>';
      
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
/////////////////////////////////////////PAGE END /////////////////////////////////////////

/////////////////////////////////////////SPEAKER PAPER START /////////////////////////////////////////
function os2dagsorden_meeting_views_bullet_point_fields_print_link($bp_id, $sp_id){
  global $base_url;
  print "<div class='speaker-paper-print'>";
  print '<input class="form-submit print-button" type="button" onclick="window.open(';
  print(" ' " . $base_url . '/print/bullet-point/' . $bp_id . '/speaker-paper/' . $sp_id . '/print' . " ' ");
  print ')" value="Print Talepapir">';
  print "</div>";
}
/////////////////////////////////////////SPEAKER PAPER END /////////////////////////////////////////