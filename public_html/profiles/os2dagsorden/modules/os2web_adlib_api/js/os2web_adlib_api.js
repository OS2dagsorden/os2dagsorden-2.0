/**
 * @file
 * Javascript for ajax updates of job status
 */

jQuery(document).ready(function($) {
  "use strict";
  setInterval(function(){
    $('td.status').each(function() {
      update(this);
    });
  },3000);
  $('td.status').click(function() {
    $(this).html('Looking up..');
    update(this);
  });

  function update(e) {
    $.ajax({
      url:"/os2web/adlib/ajax/status/" + e.id,
      context:e,
      success:function(data) {
        $(this).html(data);
      }
    });
  }

});
