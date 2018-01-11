<?php
/*
 * hook preprocess page
 */
function os2dagsorden_theme_preprocess_page(&$variables) {
  // Color
  if (module_exists('color')) {
    _color_page_alter($variables);
  }
}
/*
 * hook process html
 */
function os2dagsorden_theme_process_html(&$variables) {
  // Hook into color.module.
  if (module_exists('color')) {
    _color_html_alter($variables);
  }
}  