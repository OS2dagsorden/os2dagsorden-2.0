(function($) {
	Drupal.behaviors.poshy_tip = {
    attach: function (context, settings) {
      
      var selectors = Drupal.settings.poshy_tip.selectors;
      var theme = Drupal.settings.poshy_tip.theme;
      var properties = {};
      
      switch(theme) {
        case 'tip-darkgray':
          properties = {
            bgImageFrameSize: 11,
            offsetX: -25
          }
        break;
        case 'tip-green':
          properties = {
            className: 'tip-green',
            offsetX: -7,
            offsetY: 16,
            allowTipHover: false
          }
        break;
        case 'tip-skyblue':
          properties = {
            bgImageFrameSize: 9,
            offsetX: 0,
            offsetY: 20
          }
        break;
        case 'tip-twitter':
          properties = {
            showTimeout: 1,
            alignTo: 'target',
            alignX: 'center',
            offsetY: 5,
            allowTipHover: false,
            fade: false,
            slide: false
          }
        break;
        case 'tip-violet':
          properties = {
            bgImageFrameSize: 9
          }
        break;
        case 'tip-yellowsimple':
          properties = {
            showTimeout: 1,
            alignTo: 'target',
            alignX: 'center',
            offsetY: 5,
            allowTipHover: false
          }
        break;
      }
      
      properties.className = theme;
      
      if(selectors) {
        $(selectors).each(function(index) {
          if($(this).attr('title') != "") {
            $(this).poshytip(properties);
          }
        });
      }
    }
  } 
}(jQuery));