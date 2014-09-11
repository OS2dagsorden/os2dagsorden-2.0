<?php
/**
 * os2dagsorden_theme
 *
 * PHP version 5
 *
 * @category Themes
 * @package  Themes_os2dagsorden_theme
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
function os2dagsorden_theme_preprocess_page(&$variables) 
{    
    drupal_add_js(drupal_get_path('theme', 'os2dagsorden_theme') . '/js/os2dagsorden_theme.js');
    drupal_add_js('add_show_hide_menu_behaviour(' . variable_get('os2dagsorden_collapse_menu', true) . ');', 'inline');
    drupal_add_js('add_tablet_orientation_listener();', 'inline');
    drupal_add_js('add_indicator_help_text();', 'inline');
    drupal_add_js('hide_print_buttons();', 'inline');
    if (variable_get('os2dagsorden_collapse_menu', true)=="false")
		  drupal_add_js('resize_listener();', 'inline');
    if (variable_get('os2dagsorden_show_search_block_title', 'true')==='false')
        drupal_add_js('hide_search_block_title()', 'inline');
		
    $view = views_get_page_view();
    if (!empty($view)) {
	global $base_path;	
        if ($view->name == 'meeting_details') {
            //adding expand/collapse behaviour to meeting details view
            $os2dagsorden_expand_all_bullets= variable_get('os2dagsorden_expand_all_bullets', false)?true:'false';
            drupal_add_js('bullet_point_add_expand_behaviour("'. $base_path .'?q=", ' . variable_get('os2dagsorden_expand_attachment', true) . ',  ' . $os2dagsorden_expand_all_bullets . ', ' . variable_get('os2dagsorden_expand_attachment_onload', 'false') .' )', 'inline');
            $variables['views'] = '';
            
            //adding pagescroll
		    drupal_add_css(drupal_get_path('theme', 'os2dagsorden_theme') . '/css/pagescroller.skins.css');	    
		    drupal_add_js(drupal_get_path('theme', 'os2dagsorden_theme') . '/js/jquery.pagescroller.js');
		    drupal_add_js('addPagescroller();', 'inline');
        }
        if ($view->name == 'meeting_details' || $view->name == 'speaking_paper') {
	    //adding has notes indicator to attachment
            $annotations = os2dagsorden_annotator_get_notes_by_meeting_id(arg(1));
	    
            $attachment_ids = array();
            foreach ($annotations as $note) {
               $attachment_ids[] = $note->bilag_id;
            }
            $attachment_ids = array_unique($attachment_ids);
            $attachment_ids = implode(",", $attachment_ids);

            drupal_add_js('ids = [' . $attachment_ids . ']; bullet_point_attachment_add_notes_indicator(ids)', 'inline');
            //reforcing the help text to be added
            drupal_add_js('add_indicator_help_text();', 'inline');
            
            //adding annotation 
		    drupal_add_js(drupal_get_path('module', 'os2dagsorden_annotator') . '/lib/annotator-full.min.js');	    
		    //drupal_add_js(drupal_get_path('module', 'os2dagsorden_annotator') . '/lib/touch-plugin/annotator.touch-no-add.min.js');
		    //drupal_add_js(drupal_get_path('module', 'os2dagsorden_annotator') . '/lib/touch-plugin/annotator.touch.min.js');
		    drupal_add_js(drupal_get_path('module', 'os2dagsorden_annotator') . '/lib/touch-plugin/annotator.touch-syddjurs.min.js');
		    drupal_add_js(drupal_get_path('module', 'os2dagsorden_annotator') . '/lib/json2.js');
		    drupal_add_js(drupal_get_path('module', 'os2dagsorden_annotator') . '/lib/XPath.js');
		    drupal_add_css(drupal_get_path('module', 'os2dagsorden_annotator') . '/lib/annotator-full.min.css');
		    drupal_add_css(drupal_get_path('module', 'os2dagsorden_annotator') . '/lib/touch-plugin/annotator.touch.css');
		    drupal_add_js(drupal_get_path('module', 'os2dagsorden_annotator') . '/js/os2dagsorden_annotator_secure.js');
        }
        if ($view->name == 'speaking_paper') {
            //adding expand/collapse behaviour bullet point details view
            drupal_add_js('bullet_point_details_init("'. $base_path .'?q=", ' . variable_get('os2dagsorden_expand_bilag', true) . ', ' . variable_get('os2dagsorden_expand_attachment_onload', false) . ')', 'inline');
        }
        if (variable_get('os2dagsorden_show_massive_expand_collapse_button', 'true')==='false' && ($view->name == 'speaking_paper' || $view->name == 'meeting_details'))
         drupal_add_js('hide_massive_expand_collapse_button();', 'inline');  
    } else if ($variables['page']['content']['content']['content']['system_main']['content']['#attributes']['class'][1] == 'node-speaker_paper-form'){ 
      //in "creating speaker paper"
      //hide extra fields
      drupal_add_js("jQuery(document).ready(function(){jQuery('.form-item-field-ref-bullet-point-und-0-target-id').hide();});","inline");
      
      //setting breadcrumb
      $destination = $_GET['destination'];
      $destination = explode('/', $destination);
      
      $breadcrumb[] = l('Hjem', $base_url);
      $breadcrumb[] .= l('Mødedetaljer', 'meeting/' . $destination[1]);
      
      if (isset($destination[3]))//bullet point
	  	$breadcrumb[] .= l('Dagsordenspunkt', 'meeting/' . $destination[1] . '/bullet-point/' . $destination[3]);
	
      $breadcrumb[] .= '<span class="breadcrumb-active">Opret talepapir</span>';
      drupal_set_breadcrumb($breadcrumb);
    }
}

/**
 * Implementation of theming the calendar title. 
 * Change the format of navigation title in calendar day view to be [weekday], [day]. [month] [year]
 *
 * @param mixed $params params
 *
 * @return reformatted title
 */
function os2dagsorden_theme_date_nav_title($params) 
{
    $granularity = $params['granularity'];
    $view = $params['view'];
    $date_info = $view->date_info;
    $link = !empty($params['link']) ? $params['link'] : FALSE;
    $format = !empty($params['format']) ? $params['format'] : NULL;
    switch ($granularity) {
        case 'year':
            $title = $date_info->year;
            $date_arg = $date_info->year;
            break;
        case 'month':
            $format = !empty($format) ? $format : (empty($date_info->mini) ? 'F Y' : 'F');
            $title = date_format_date($date_info->min_date, 'custom', $format);
            $date_arg = $date_info->year . '-' . date_pad($date_info->month);
            break;
        case 'day':
            $format = !empty($format) ? $format : (empty($date_info->mini) ? 'l, j. F Y' : 'l, F j');
            $title = date_format_date($date_info->min_date, 'custom', $format);
            $date_arg = $date_info->year . '-' . date_pad($date_info->month) . '-' . date_pad($date_info->day);
            break;
        case 'week':
            $format = !empty($format) ? $format : (empty($date_info->mini) ? 'F j, Y' : 'F j');
            $title = t('Week of @date', array('@date' => date_format_date($date_info->min_date, 'custom', $format)));
            $date_arg = $date_info->year . '-W' . date_pad($date_info->week);
            break;
    }
    if (!empty($date_info->mini) || $link) {
        // Month navigation titles are used as links in the mini view.
        $attributes = array('title' => t('View full page month'));
        $url = date_pager_url($view, $granularity, $date_arg, TRUE);
        return l($title, $url, array('attributes' => $attributes));
    }
    else {
        return $title;
    }
}

/**
 * Format the time row headings in the week and day view.
 * Change the time format to be [hour].[minutes]
 *
 * @param mixed $vars vars
 *
 * @return reformatted title
 */
function os2dagsorden_theme_calendar_time_row_heading($vars) 
{
    $start_time = $vars['start_time'];
    $next_start_time = $vars['next_start_time'];
    $curday_date = $vars['curday_date'];
    static $format_hour, $format_ampm;
    if (empty($format_hour)) {
        $format = variable_get('date_format_short', 'm/d/Y - H:i');
        $limit = array('hour', 'minute');
        $format_hour = str_replace(array('a', 'A'), '', date_limit_format($format, $limit));
        $format_ampm = strstr($format, 'a') ? 'a' : (strstr($format, 'A') ? 'A' : '');
    }
    if ($start_time == '00:00:00' && $next_start_time == '23:59:59') {
        $hour = t('All times');
    }
    elseif ($start_time == '00:00:00') {
        $date = date_create($curday_date . ' ' . $next_start_time);
        $hour = t('Before @time', array('@time' => date_format($date, $format_hour)));
    }
    else {
        $date = date_create($curday_date . ' ' . $start_time);
        $hour = date_format($date, $format_hour);
    }
    if (!empty($date)) {
        $ampm = date_format($date, $format_ampm);
    }
    else {
        $ampm = '';
    }
    return array('hour' => $hour, 'ampm' => $ampm);
}

/**
 * Changes the format of the exposed form - meetings search.
 * Also removes the unneeded links on log in page.
 *
 * @param mixed &$form       form
 * @param mixed &$form_state form state
 *
 * @return none
 */
function os2dagsorden_theme_form_alter(&$form, &$form_state) {
    if ($form['#id'] == 'views-exposed-form-meetings-search-page') {	
	$form['from_date']['value']['#date_format'] = 'd-m-Y';
        $form['to_date']['value']['#date_format'] = 'd-m-Y';
        
        if (!is_array($_SESSION['views']['meetings_search']['page']['from_date']['value'])){
	  if (!empty($_SESSION['views']['meetings_search']['page']['from_date']['value'])){
	    $old_value = $_SESSION['views']['meetings_search']['page']['from_date']['value'];
	    $_SESSION['views']['meetings_search']['page']['from_date']['value'] = array();
	    $old_value = date_create_from_format("Y-m-d", $old_value);
	    $old_value = $old_value->format('d-m-Y');
	    $_SESSION['views']['meetings_search']['page']['from_date']['value']['date'] = $old_value;
	  }
	}
	
	if (!is_array($_SESSION['views']['meetings_search']['page']['to_date']['value'])){
	  if (!empty($_SESSION['views']['meetings_search']['page']['to_date']['value'])){
	    $old_value = $_SESSION['views']['meetings_search']['page']['to_date']['value'];
	    $_SESSION['views']['meetings_search']['page']['to_date']['value'] = array();
	    $old_value = date_create_from_format("Y-m-d", $old_value);
	    $old_value = $old_value->format('d-m-Y');
	    $_SESSION['views']['meetings_search']['page']['to_date']['value']['date'] = $old_value;
	  }
	}
    } else if ($form['#id'] == 'user-login-form') {
	$form['name']['#description'] = "";
	$form['pass']['#description'] = "";
	$form['links']['#markup'] = "";
    }
}

/**
 * Preprocess HTML hook.
 * Fixes the IE compatibility problem.
 *
 * @param mixed &$form       form
 * @param mixed &$form_state form state
 *
 * @return none
 */
function os2dagsorden_theme_preprocess_html(&$vars) {
    // Setup IE meta tag to force IE rendering mode
    $meta_ie_render_engine = array(
      '#type' => 'html_tag',
      '#tag' => 'meta',
      '#attributes' => array(
	'http-equiv' => 'X-UA-Compatible',
	'content' =>  'IE=8,IE=Edge,chrome=1',
      ),
      '#weight' => '-99999',
    );
    
     $format_detection = array(
      '#type' => 'html_tag',
      '#tag' => 'meta',
      '#attributes' => array(
	'name' => 'format-detection',
	'content' =>  'telephone=no',
      ),
      '#weight' => '-99999',
    );
    
    //<meta name="format-detection" content="telephone=no">
  
    // Add header meta tag for IE to head
    drupal_add_html_head($meta_ie_render_engine, 'meta_ie_render_engine');
    drupal_add_html_head($format_detection, 'format-detection');
}

function os2dagsorden_theme_menu_local_task($variables) {
  $link = $variables['element']['#link'];
  $href = explode('/', $link['href']);
  $node = node_load($href[1]);
  
  if ($link['path'] === 'node/%/edit' && $node->type !== 'page')//disabling edit tab, if only node type is not page
    return '';
  else if ($link['path'] === 'node/%/view')//disabling view tab
    return '';
  else if ($link['path'] === 'user/%/edit' || $link['path'] === 'user/%/view' || $link['path'] === 'user/%/simple_edit')
    return '';
  else 
    return theme_menu_local_task($variables);
}