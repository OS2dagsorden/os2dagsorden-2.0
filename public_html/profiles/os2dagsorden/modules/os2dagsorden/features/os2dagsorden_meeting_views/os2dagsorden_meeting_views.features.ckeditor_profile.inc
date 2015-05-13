<?php
/**
 * @file
 * os2dagsorden_meeting_views.features.ckeditor_profile.inc
 */

/**
 * Implements hook_ckeditor_profile_defaults().
 */
function os2dagsorden_meeting_views_ckeditor_profile_defaults() {
  $data = array(
    'CKEditor Global Profile' => array(
      'name' => 'CKEditor Global Profile',
      'settings' => array(
        'ckeditor_path' => '%m/../../../libraries/ckeditor',
        'ckeditor_local_path' => '',
        'ckeditor_plugins_path' => '%m/plugins',
        'ckeditor_plugins_local_path' => '',
        'ckfinder_path' => '%m/ckfinder',
        'ckeditor_allow_download_private_files' => 0,
        'private_dir' => '',
        'toolbar_wizard' => 't',
        'loadPlugins' => array(),
      ),
      'input_formats' => array(),
    ),
    'OS2dagsorden_filtered' => array(
      'name' => 'OS2dagsorden_filtered',
      'settings' => array(
        'ss' => 2,
        'default' => 't',
        'show_toggle' => 't',
        'skin' => 'kama',
        'uicolor' => 'default',
        'uicolor_textarea' => '<p>
	Click the <strong>UI Color Picker</strong> button to set your color preferences.</p>
',
        'uicolor_user' => 'default',
        'toolbar' => '[
    [\'Bold\',\'Italic\',\'Underline\',\'NumberedList\',\'BulletedList\',\'TextColor\',\'Image\']
]',
        'expand' => 't',
        'width' => '100%',
        'lang' => 'en',
        'auto_lang' => 't',
        'language_direction' => 'default',
        'enter_mode' => 'p',
        'shift_enter_mode' => 'br',
        'font_format' => 'p;div;pre;address;h1;h2;h3;h4;h5;h6',
        'custom_formatting' => 'f',
        'formatting' => array(
          'custom_formatting_options' => array(
            'indent' => 'indent',
            'breakBeforeOpen' => 'breakBeforeOpen',
            'breakAfterOpen' => 'breakAfterOpen',
            'breakAfterClose' => 'breakAfterClose',
            'breakBeforeClose' => 0,
            'pre_indent' => 0,
          ),
        ),
        'css_mode' => 'theme',
        'css_path' => '',
        'css_style' => 'theme',
        'styles_path' => '',
        'filebrowser' => 'none',
        'filebrowser_image' => '',
        'filebrowser_flash' => '',
        'ckeditor_load_method' => 'ckeditor.js',
        'ckeditor_load_time_out' => 0,
        'forcePasteAsPlainText' => 'f',
        'html_entities' => 't',
        'scayt_autoStartup' => 'f',
        'theme_config_js' => 'f',
        'js_conf' => '',
        'loadPlugins' => array(
          'drupalbreaks' => array(
            'name' => 'drupalbreaks',
            'desc' => 'Plugin for inserting Drupal teaser and page breaks.',
            'path' => '%base_path%%plugin_dir%drupalbreaks/',
            'buttons' => array(
              'DrupalBreak' => array(
                'label' => 'DrupalBreak',
                'icon' => 'images/drupalbreak.png',
              ),
            ),
            'default' => 't',
          ),
          'tableresize' => array(
            'name' => 'tableresize',
            'desc' => 'Table Resize plugin',
            'path' => '%base_path%%editor_path%plugins/tableresize/',
            'buttons' => FALSE,
            'default' => 't',
          ),
        ),
      ),
      'input_formats' => array(
        'filtered_html' => 'Filtered HTML',
      ),
    ),
    'Os2dagsorden_full' => array(
      'name' => 'Os2dagsorden_full',
      'settings' => array(
        'ss' => 2,
        'default' => 't',
        'show_toggle' => 'f',
        'skin' => 'kama',
        'uicolor' => 'default',
        'uicolor_textarea' => '<p>
	Click the <strong>UI Color Picker</strong> button to set your color preferences.</p>
',
        'uicolor_user' => 'default',
        'toolbar' => '[
    [\'Source\'],
    [\'Cut\',\'Copy\',\'Paste\',\'PasteText\',\'PasteFromWord\',\'-\',\'SpellChecker\',\'Scayt\'],
    [\'Undo\',\'Redo\',\'Find\',\'Replace\',\'-\',\'SelectAll\',\'RemoveFormat\'],
    [\'Image\',\'Flash\',\'Table\',\'HorizontalRule\',\'Smiley\',\'SpecialChar\',\'Iframe\'],
    \'/\',
    [\'Bold\',\'Italic\',\'Underline\',\'Strike\',\'-\',\'Subscript\',\'Superscript\'],
    [\'NumberedList\',\'BulletedList\',\'-\',\'Outdent\',\'Indent\',\'Blockquote\',\'CreateDiv\'],
    [\'JustifyLeft\',\'JustifyCenter\',\'JustifyRight\',\'JustifyBlock\',\'-\',\'BidiRtl\',\'BidiLtr\'],
    [\'Link\',\'Unlink\',\'Anchor\',\'Linkit\',\'LinkToNode\',\'LinkToMenu\'],
    \'/\',
    [\'Format\',\'Font\',\'FontSize\'],
    [\'TextColor\',\'BGColor\'],
    [\'Maximize\',\'ShowBlocks\'],
    [\'DrupalBreak\',\'DrupalPageBreak\']
]',
        'expand' => 't',
        'width' => '100%',
        'lang' => 'da',
        'auto_lang' => 't',
        'language_direction' => 'default',
        'enter_mode' => 'p',
        'shift_enter_mode' => 'br',
        'font_format' => 'p;div;pre;address;h1;h2;h3;h4;h5;h6',
        'custom_formatting' => 't',
        'formatting' => array(
          'custom_formatting_options' => array(
            'indent' => 0,
            'breakBeforeOpen' => 0,
            'breakAfterOpen' => 0,
            'breakBeforeClose' => 0,
            'breakAfterClose' => 0,
            'pre_indent' => 0,
          ),
        ),
        'css_mode' => 'none',
        'css_path' => '',
        'css_style' => 'theme',
        'styles_path' => '',
        'filebrowser' => 'none',
        'filebrowser_image' => '',
        'filebrowser_flash' => '',
        'ckeditor_load_method' => 'ckeditor.js',
        'ckeditor_load_time_out' => 0,
        'forcePasteAsPlainText' => 'f',
        'html_entities' => 't',
        'scayt_autoStartup' => 'f',
        'theme_config_js' => 'f',
        'js_conf' => 'config.removePlugins = \'elementspath\';',
        'loadPlugins' => array(
          'drupalbreaks' => array(
            'name' => 'drupalbreaks',
            'desc' => 'Plugin for inserting Drupal teaser and page breaks.',
            'path' => '%base_path%%plugin_dir%drupalbreaks/',
            'buttons' => array(
              'DrupalBreak' => array(
                'label' => 'DrupalBreak',
                'icon' => 'images/drupalbreak.png',
              ),
            ),
            'default' => 't',
          ),
        ),
      ),
      'input_formats' => array(
        'full_html' => 'Full HTML',
      ),
    ),
  );
  return $data;
}
