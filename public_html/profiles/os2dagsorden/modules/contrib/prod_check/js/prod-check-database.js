(function ($) {

  // Show / hide detailed db info.

  Drupal.behaviors.prod_check = {
    attach: function(context, settings) {
      $('#content').find('a.show-more').unbind('click').bind('click', function(e) {
        e.preventDefault();

        var $this = $(this),
            details = $this.attr('data-details'),
            hide = Drupal.t('Hide details'),
            show = Drupal.t('Show details'),
            active = 'expanded';

        if ($this.hasClass(active)) {
          $('#content').find('pre.' + details).hide();
          $this.text(show);
          $this.removeClass(active);
        }
        else {
          $('#content').find('pre.' + details).show();
          $this.text(hide);
          $this.addClass(active);
        }
      });
    }
  };

})(jQuery);

