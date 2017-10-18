(function ($) {

  // Prod monitor settings page styling.
  Drupal.behaviors.prod_monitor = {
    attach: function(context, settings) {
      $('#prod-check-settings', context).equalHeights('px');
      $('#prod-check-settings', context).equalWidths('px');
    }
  };

})(jQuery);

