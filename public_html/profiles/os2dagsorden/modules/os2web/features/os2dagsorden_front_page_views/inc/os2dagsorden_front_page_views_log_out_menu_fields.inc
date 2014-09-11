<?php
/**
 * @file
 * Code for the OS2Web front page views feature - Log out menu.
 */
 
/////////////////////////////////////////BLOCK START/////////////////////////////////////////
function os2dagsorden_front_page_views_log_out_menu_fields_user_position(){
  $full_user = os2dagsorden_access_helper_get_user();

  if (isset($full_user->field_user_positions['und'])){
    $tids = array();
    foreach ($full_user->field_user_positions['und'] as $item){
      $tids[] = $item['tid'];
    }
    $terms = entity_load('taxonomy_term', $tids, array());
    $min = $terms[$tids[0]];

    foreach ($terms as $term){
      if ($term->field_priority['und'][0]['value'] <  $min->field_priority['und'][0]['value'])
	$min = $term;
    }
    print $min->name;
  }
}
/////////////////////////////////////////BLOCK END/////////////////////////////////////////