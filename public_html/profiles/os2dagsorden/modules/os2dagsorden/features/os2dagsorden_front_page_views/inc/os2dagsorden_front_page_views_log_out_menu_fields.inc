<?php
/**
 * @file
 * Code for the OS2Web front page views feature - Log out menu.
 */
 
/////////////////////////////////////////BLOCK START/////////////////////////////////////////
function os2dagsorden_front_page_views_log_out_menu_fields_user_position(){
  $full_user = os2dagsorden_access_helper_get_user();  
  if (isset($full_user->field_os2web_user_pos['und'])){
      $user_role_items = field_get_items('user', $full_user, 'field_os2web_user_pos');
       foreach ($user_role_items  as $itme_index => $item) 
          $positions_full[]= field_collection_field_get_entity($item);
          $min=$positions_full[0];
           foreach ($positions_full as $pos_index=>$pos){
              if ($pos->field_os2web_user_pos_priority['und'][0]['value'] < $min->field_os2web_user_pos_priority['und'][0]['value']) 
                $min=$pos;                  
           }
  print $min->field_os2web_user_pos_name['und'][0]['value'];
  }
}
/////////////////////////////////////////BLOCK END/////////////////////////////////////////