(function ($) {

  // Trigger loading of the Google graphs.
  Drupal.behaviors.prod_monitor_init = {
    attach: function(context, settings) {
      var script = document.createElement('script');
      script.src = document.location.protocol + '//www.google.com/jsapi?callback=Drupal.behaviors.prod_monitor_performance.initGoogleDependencies';
      script.type = 'text/javascript';
      $('head').append(script);
    }
  }

  // All functions used to setup and render the graphs.
  Drupal.behaviors.prod_monitor_performance = {
    initGoogleDependencies: function() {
      google.load('visualization', '1', {
        'callback':Drupal.behaviors.prod_monitor_performance.initGraphs,
        'packages':['annotatedtimeline']
      })
    },

    initGraphs: function() {
      $('.performance-data').each(function() {
        var callback = $(this).attr('id').replace('-', '_');
        //console.log(Drupal.behaviors.prod_monitor_performance[callback]);
        Drupal.behaviors.prod_monitor_performance[callback]();
      });
    }
  }

})(jQuery);

