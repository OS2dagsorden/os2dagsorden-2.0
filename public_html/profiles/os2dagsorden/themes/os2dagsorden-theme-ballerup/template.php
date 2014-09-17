<?php
/**
 * os2dagsorden_theme_ballerup
 *
 * PHP version 5
 *
 * @category Themes
 * @package  Themes_os2dagsorden_theme_ballerup
 * @author   Stanislav Kutasevits <stan@bellcom.dk>
 * @license  http://www.gnu.org/copyleft/gpl.html GNU General Public License
 * @file
 * This file is empty by default because the base theme chain (Alpha & Omega) provides
 * all the basic functionality. However, in case you wish to customize the output that Drupal
 * generates through Alpha & Omega this file is a good place to do so.
 *
 * Alpha comes with a neat solution for keeping this file as clean as possible while the code
 * for your subtheme grows. Please read the README.txt in the /preprocess and /process subfolders
 * for more information on this topic.
 */

/**
 * Implementation of hook_preprocess_page.
 * Adds needed JS behaviour, loads the notes/speaker paper indicators, makes the security log entries.
 *
 * @param mixed &$variables variables
 * @return none
 */
function os2dagsorden_theme_ballerup_preprocess_page(&$variables)
{
	drupal_add_js(drupal_get_path('theme', 'os2dagsorden_theme_ballerup') . '/js/os2dagsorden_theme_ballerup.js');
	drupal_add_js('stick_side_menu();', 'inline');
	drupal_add_css(drupal_get_path('theme', 'os2dagsorden_theme_ballerup') . '/css/ie.css', array('group' => CSS_THEME, 'browsers' => array('IE' => 'lt IE 9', '!IE' => FALSE), 'preprocess' => FALSE));
       if (variable_get('os2dagsorden_show_search_block_title', 'true')==='false')
            drupal_add_js('hide_search_block_title_ballerup()', 'inline');
        
}
