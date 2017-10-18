(function ($) {

  // Prod check settings page styling.

  Drupal.behaviors.prod_check = {
    attach: function(context, settings) {
      $('#edit-prod-check-module-list-time', context).mask('99:99');
      $('#prod-check-settings', context).equalHeights('px');
      $('#prod-check-settings', context).equalWidths('px');

      $('#prod-check-nagios', context).change(function() {
        $('#prod-check-settings', context).equalHeights('px');
        $('#prod-check-settings', context).equalWidths('px');
      });
    }
  };

})(jQuery);

