<?php
/*
 * hook preprocess page
 */
function kldagsorden_preprocess_page(&$variables) {
  // Color
  if (module_exists('color')) {
    _color_page_alter($variables);
  }
}
/*
 * hook process html
 */
function kldagsorden_process_html(&$variables) {
  // Hook into color.module.
  if (module_exists('color')) {
    _color_html_alter($variables);
  }
}  