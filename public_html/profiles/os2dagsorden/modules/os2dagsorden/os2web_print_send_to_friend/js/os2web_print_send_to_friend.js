jQuery(document).ready(function($) {
  $(".throbber").hide();
  $("#send_to_friend_form").submit(function(e){
    e.preventDefault;
    var $form = $("#send_to_friend_form");
    serializedData = $form.serialize();

    var email = $("#field_send_to_friend_email").val();
    var meeting_id = $("#field_meeting_id").val();
    var bp_id = $("#field_bullet_point_id").val();
    var base_url = $("#field_base_url").val();
    
    if (!checkEmail(email)){
     $("#field_send_to_friend_email").focus();
     $("#field_send_to_friend_email").addClass("error");
     return false;
    } else {
      $(".throbber").show();
      $("#field_send_to_friend_email").removeClass("error");

      $.post(base_url + "/meeting/" + meeting_id + "/bullet-point/" + bp_id + "/send_to_friend_service", serializedData, function(response){
	$(".throbber").hide();
	parent.Lightbox.end();
      });
      return false;
    }
  });

  function checkEmail(email) {
    var regex = /^([a-zA-Z0-9_\.\-\+])+\@(([a-zA-Z0-9\-])+\.)+([a-zA-Z0-9]{2,4})+$/;
    return regex.test(email);
  }

});
