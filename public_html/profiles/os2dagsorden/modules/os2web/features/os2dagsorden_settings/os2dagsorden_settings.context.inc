<?php
/**
 * @file
 * os2dagsorden_settings.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function os2dagsorden_settings_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'os2dagsorden_sidepane';
  $context->description = 'Will be shown on calendar month view only. Other time os2web_calendar (sidepane included will be shown))';
  $context->tag = '';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        '~admin*' => '~admin*',
      ),
    ),
    'user' => array(
      'values' => array(
        'authenticated user' => 'authenticated user',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views--exp-meetings_search-page' => array(
          'module' => 'views',
          'delta' => '-exp-meetings_search-page',
          'region' => 'content',
          'weight' => '-11',
        ),
        'menu-menu-sidepane-menu' => array(
          'module' => 'menu',
          'delta' => 'menu-sidepane-menu',
          'region' => 'sidebar_second',
          'weight' => '-23',
        ),
        'views-events-block_1' => array(
          'module' => 'views',
          'delta' => 'events-block_1',
          'region' => 'sidebar_second',
          'weight' => '-22',
        ),
        'views-user_committee-block_1' => array(
          'module' => 'views',
          'delta' => 'user_committee-block_1',
          'region' => 'sidebar_second',
          'weight' => '-21',
        ),
        'views-user_follow_committees-block_1' => array(
          'module' => 'views',
          'delta' => 'user_follow_committees-block_1',
          'region' => 'sidebar_second',
          'weight' => '-20',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('Will be shown on calendar month view only. Other time os2web_calendar (sidepane included will be shown))');
  $export['os2dagsorden_sidepane'] = $context;

  return $export;
}
