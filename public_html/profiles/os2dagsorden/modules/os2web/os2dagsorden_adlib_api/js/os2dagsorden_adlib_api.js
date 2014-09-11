/* 
 * 
 * @author Jesper Mathiassen <jm@bellcom.dk>
 * @copyright Bellcom Open Source aps.
 */

jQuery(document).ready(function($) {
  $('td.status').each(function() {
    update(this)
  });
  $('td.status').click(function() {
    $(this).html('Looking up..');
    update(this);
  });

  function update(e) {
    $.ajax({
      url:"/os2dagsorden/adlib/ajax/status/"+e.id,
      context:e,
      success:function(data) {
        $(this).html(data);
      }
    });
  }

});
