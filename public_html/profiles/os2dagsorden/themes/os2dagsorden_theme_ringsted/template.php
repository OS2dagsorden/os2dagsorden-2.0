<?php
/**
 * os2dagsorden_theme_ringsted
 *
 * PHP version 5
 *
 * @category Themes
 * @package  Themes_os2dagsorden_theme_ringsted
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
function os2dagsorden_theme_ringsted_preprocess_page(&$variables) {
	drupal_add_js(drupal_get_path('theme', 'os2dagsorden_theme_ringsted') . '/js/os2dagsorden_theme_ringsted.js');
	drupal_add_js('stick_side_menu();', 'inline');
	drupal_add_css(drupal_get_path('theme', 'os2dagsorden_theme_ringsted') . '/css/ie.css', array('group' => CSS_THEME, 'browsers' => array('IE' => 'lt IE 9', '!IE' => FALSE), 'preprocess' => FALSE));
        if (variable_get('os2dagsorden_show_search_block_title', 'true')==='false')
            drupal_add_js('hide_search_block_title_ringsted()', 'inline');
        
	$view = views_get_page_view();
	if (!empty($view)) {
	global $base_path;	
	if ($view->name == 'meeting_details') {
	    //adding expand/collapse behaviour to meeting details view
	    drupal_add_js('bullet_point_add_expand_behaviour_ringsted("'. $base_path .'?q=", ' . variable_get('os2dagsorden_expand_bilag', true) . ',  ' . variable_get('os2dagsorden_expand_all_bullets', false) . ')', 'inline');
            drupal_add_js('open_all_bilag_case_bullet_points(' . variable_get('os2dagsorden_expand_bilags', "true") . ','. variable_get('os2dagsorden_expand_cases', "false") .')', 'inline');
              
	    
	}
	if ($view->name == 'speaking_paper') {
            //adding expand/collapse behaviour bullet point details view
            drupal_add_js('bullet_point_details_init_ringsted("'. $base_path .'?q=", ' . variable_get('os2dagsorden_expand_bilag', true) . ')', 'inline');
	    drupal_add_js('open_all_bilag_case_bullet_points(' . variable_get('os2dagsorden_expand_bilags', "true") . ','. variable_get('os2dagsorden_expand_cases', "false") .')', 'inline');
              
        }
}
}