(function ($) {
  Drupal.behaviors.confirm = {
    attach: function(context, settings) {
      var events =  $('.form-submit-delete').clone(true).data('events');// Get the jQuery events.
      $('.form-submit-delete').unbind('mousedown'); // Remove the click events.
      $('.form-submit-delete').mousedown(function () {
	if (confirm('Are you sure you want to delete that?')) {
	  $.each(events.mousedown, function() {
	    this.handler(); // Invoke the mousedown handlers that was removed.
	  });
	}
	// Prevent default action.
	return false;
      });
    }
  }
})(jQuery);