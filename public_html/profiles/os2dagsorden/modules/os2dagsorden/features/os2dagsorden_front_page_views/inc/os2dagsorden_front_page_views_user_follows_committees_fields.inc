<?php
/**
 * @file
 * Code for the OS2Web front page views feature - User follows committees.
 */
 
/////////////////////////////////////////header START /////////////////////////////////////////
function os2dagsorden_front_page_views_user_follows_committees_help_text(){
  print '<div class="help-button" id="os2dagsorden_front_page_views_user_follows_committees_help" aria-label="' . variable_get('os2dagsorden_user_follows_help_text', 'Her kan du se de udvalg du er sat op til at følge. Følger betyder at du kun kan se åbne punkter og Følger+ betyder at du også kan se lukkede punkter. Ret henvendelse til Direktionssekretariatet hvis du mener det skal ændres.') . '"></div>';
}
/////////////////////////////////////////header END /////////////////////////////////////////

/////////////////////////////////////////BLOCK START/////////////////////////////////////////
function os2dagsorden_front_page_views_user_follows_committees_fields_print_committees(){
  $full_user = os2dagsorden_access_helper_get_user();
  $output_list = array();
  if (isset($full_user->field_follows_committee_pp['und'])){
    $term_list = $full_user->field_follows_committee_pp['und'];
    foreach ($term_list as $com) {
      $output_list[$com['tid']] = array(
        'tid' => $com['tid'],
        'fleld' => 'c_pp',
      );
    }
  }
  
  if (isset($full_user->field_follows_committee_plus['und'])){
    $term_list = $full_user->field_follows_committee_plus['und'];
    foreach ($term_list as $com) {
      $output_list[$com['tid']] = array(
        'tid' => $com['tid'],
        'fleld' => 'c_plus',
      );
    }
  }

  if (isset($full_user->field_follows_committee['und'])){
    $term_list = $full_user->field_follows_committee['und'];
    foreach ($term_list as $com) {
      $output_list[$com['tid']] = array(
        'tid' => (int)$com['tid'],
        'fleld' => 'cc',
      );
    }
  }
  $order_list = os2dagsorden_content_modify_asort($output_list);
  foreach ($order_list as $key => $term) {
    if ($term['tid'] == $output_list[$term['tid']]['tid']) {
      $term['field'] = $output_list[$term['tid']]['fleld'];
      $order_list[$key] = $term ;
    }
  }
  foreach ($order_list as $com){
    $com_term = taxonomy_term_load($com['tid']);
    if (isset($com_term->field_os2web_meetings_com_shname['und'])){
     $link = $com_term->field_os2web_meetings_com_shname['und'][0]['value'];
    }
    else {
     $link = $com_term->name;
    }
    if ($com['field'] == 'c_plus') {
      $link .= '<b>++</b>';
    }
    elseif ($com['field'] == 'c_pp') {
      $link .= '<b>++</b>';
    }
    print '<a href="/meetings-search?field_os2web_meetings_committee_tid=' .$com['tid'] . '&from_date=&to_date">' . $link . '</a></br>';
  }
}
/////////////////////////////////////////BLOCK END /////////////////////////////////////////
