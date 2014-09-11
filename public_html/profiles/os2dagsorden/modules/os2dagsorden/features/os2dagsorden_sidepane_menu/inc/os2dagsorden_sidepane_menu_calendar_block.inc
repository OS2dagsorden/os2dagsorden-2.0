<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

function os2dagsorden_sidepane_menu_show_calendar_block(){
  $q = explode('/',$_GET['q']);
if ($q[0]=='calendar-field-date')
    return FALSE;
return TRUE;
}