<?php
/**
 * @file
 * Code for the OS2Web front page views feature - Log out menu.
 */
function os2dagsorden_front_page_views_fields_text_log_off(){
    print '<a href="' . $GLOBALS['base_url'] . '/logout" class="user-logout-btn button">' . variable_get('os2dagsorden_title_general_log_off', 'Log af') . '</a>';
}

function os2dagsorden_front_page_views_fields_settings(){
    print '<a href="' . $GLOBALS['base_url'] . '/user/simple_edit" class="settings-btn button">' . variable_get('os2dagsorden_title_general_mine_indstillinger', 'Mine indstillinger') . '</a>';
}