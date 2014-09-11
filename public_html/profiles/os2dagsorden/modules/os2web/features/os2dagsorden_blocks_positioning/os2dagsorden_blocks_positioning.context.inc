<?php
/**
 * @file
 * os2dagsorden_blocks_positioning.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function os2dagsorden_blocks_positioning_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'os2dagsorden_annotator_light';
  $context->description = 'The light version of annotator page';
  $context->tag = '';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'meeting/*/bullet-point/*/bullet-point-attachment-light/*' => 'meeting/*/bullet-point/*/bullet-point-attachment-light/*',
      ),
    ),
  );
  $context->reactions = array(
    'region' => array(
      'bartik' => array(
        'disable' => array(
          'header' => 0,
          'help' => 0,
          'page_top' => 0,
          'page_bottom' => 0,
          'highlighted' => 0,
          'featured' => 0,
          'content' => 0,
          'sidebar_first' => 0,
          'sidebar_second' => 0,
          'triptych_first' => 0,
          'triptych_middle' => 0,
          'triptych_last' => 0,
          'footer_firstcolumn' => 0,
          'footer_secondcolumn' => 0,
          'footer_thirdcolumn' => 0,
          'footer_fourthcolumn' => 0,
          'footer' => 0,
          'dashboard_main' => 0,
          'dashboard_sidebar' => 0,
          'dashboard_inactive' => 0,
        ),
      ),
      'seven' => array(
        'disable' => array(
          'content' => 0,
          'help' => 0,
          'page_top' => 0,
          'page_bottom' => 0,
          'sidebar_first' => 0,
          'dashboard_main' => 0,
          'dashboard_sidebar' => 0,
          'dashboard_inactive' => 0,
        ),
      ),
      'os2dagsorden_theme' => array(
        'disable' => array(
          'page_top' => 'page_top',
          'page_bottom' => 'page_bottom',
          'user_first' => 'user_first',
          'user_second' => 'user_second',
          'branding' => 'branding',
          'menu' => 'menu',
          'sidebar_first' => 'sidebar_first',
          'sidebar_second' => 'sidebar_second',
          'header_first' => 'header_first',
          'header_second' => 'header_second',
          'preface_first' => 'preface_first',
          'preface_second' => 'preface_second',
          'preface_third' => 'preface_third',
          'postscript_first' => 'postscript_first',
          'postscript_second' => 'postscript_second',
          'postscript_third' => 'postscript_third',
          'postscript_fourth' => 'postscript_fourth',
          'footer_first' => 'footer_first',
          'footer_second' => 'footer_second',
          'dashboard_main' => 'dashboard_main',
          'dashboard_sidebar' => 'dashboard_sidebar',
          'dashboard_inactive' => 'dashboard_inactive',
          'content' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('The light version of annotator page');
  $export['os2dagsorden_annotator_light'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'os2dagsorden_content';
  $context->description = 'content is shown everywhere';
  $context->tag = '';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        '~<front>' => '~<front>',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'system-main' => array(
          'module' => 'system',
          'delta' => 'main',
          'region' => 'content',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('content is shown everywhere');
  $export['os2dagsorden_content'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'os2dagsorden_front_page';
  $context->description = 'Front page blocks positioning';
  $context->tag = '';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        '<front>' => '<front>',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-c8c6c91b397acf23018fcefd40a1fa29' => array(
          'module' => 'views',
          'delta' => 'c8c6c91b397acf23018fcefd40a1fa29',
          'region' => 'content',
          'weight' => '-10',
        ),
        'views-0293ca2a3a9d3ff12dd399cf7b0b4333' => array(
          'module' => 'views',
          'delta' => '0293ca2a3a9d3ff12dd399cf7b0b4333',
          'region' => 'content',
          'weight' => '-11',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Front page blocks positioning');
  $export['os2dagsorden_front_page'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'os2dagsorden_login_block';
  $context->description = 'shown only to the unauthorized users';
  $context->tag = '';
  $context->conditions = array(
    'user' => array(
      'values' => array(
        'anonymous user' => 'anonymous user',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'user-login' => array(
          'module' => 'user',
          'delta' => 'login',
          'region' => 'content',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('shown only to the unauthorized users');
  $export['os2dagsorden_login_block'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'os2dagsorden_show_hide_menu';
  $context->description = 'show or hides the side pane';
  $context->tag = '';
  $context->conditions = array(
    'sitewide' => array(
      'values' => array(
        1 => 1,
      ),
    ),
    'user' => array(
      'values' => array(
        'administrator' => 'administrator',
        'authenticated user' => 'authenticated user',
        'os2dagsorden' => 'os2dagsorden',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'block-1' => array(
          'module' => 'block',
          'delta' => 1,
          'region' => 'menu',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('show or hides the side pane');
  $export['os2dagsorden_show_hide_menu'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'os2dagsorden_user_logout';
  $context->description = 'Modified log out menu';
  $context->tag = '';
  $context->conditions = array(
    'sitewide' => array(
      'values' => array(
        1 => 1,
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-user_logout_menu-block' => array(
          'module' => 'views',
          'delta' => 'user_logout_menu-block',
          'region' => 'menu',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Modified log out menu');
  $export['os2dagsorden_user_logout'] = $context;

  return $export;
}
