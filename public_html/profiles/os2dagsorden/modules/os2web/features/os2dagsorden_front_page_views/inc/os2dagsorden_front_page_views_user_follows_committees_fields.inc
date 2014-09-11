<?php
/**
 * @file
 * Code for the OS2Web front page views feature - User follows committees.
 */
 
/////////////////////////////////////////header START /////////////////////////////////////////
function os2dagsorden_front_page_views_user_follows_committees_help_text(){
  print '<div class="help-button" title="Her kan du se de udvalg du er sat op til at følge. 
  Følger betyder at du kun kan se åbne punkter og Følger+ betyder at du også kan se lukkede punkter. 
  Ret henvendelse til Direktionssekretariatet hvis du mener det skal ændres."></div>';
}
/////////////////////////////////////////header END /////////////////////////////////////////

/////////////////////////////////////////BLOCK START/////////////////////////////////////////
function os2dagsorden_front_page_views_user_follows_committees_fields_print_committees(){
  $full_user = os2dagsorden_access_helper_get_user();
  if (isset($full_user->field_follows_committee_plus['und'])){
    foreach ($full_user->field_follows_committee_plus['und'] as $com){
      $com_term = taxonomy_term_load($com['tid']);
      if (isset($com_term->field_name_short['und']))
	print($com_term->field_name_short['und'][0]['value']);
      else
	print($com_term->name);
      
      print('<b>+</b><br/>');
    }
  }

  if (isset($full_user->field_follows_committee['und'])){
    foreach ($full_user->field_follows_committee['und'] as $com){
      $com_term = taxonomy_term_load($com['tid']);
      if (isset($com_term->field_name_short['und']))
	print($com_term->field_name_short['und'][0]['value']);
      else
	print($com_term->name);

      print('<br/>');
    }
  }
}
/////////////////////////////////////////BLOCK END /////////////////////////////////////////
