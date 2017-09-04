/**
 * Makes the side menu sticky, so that it is always present on the right
 */
function stick_side_menu(){  
  jQuery(document).ready(function () {
    var menuHeight = jQuery('#region-sidebar-second').height();
    var documentHeight = jQuery(document).height();
    
    if (!isTouchDevice() && menuHeight < documentHeight-150){//only add when the width of the document is enough to fit the whole menu + buffer
      jQuery('#region-sidebar-second .region-sidebar-second-inner').append('<div class="side-menu-go-top"><a href="#">^ TIL TOPPEN ^</a></div>');
      var top = jQuery('#region-sidebar-second .region-sidebar-second-inner').offset().top - parseFloat(jQuery('#region-sidebar-second .region-sidebar-second-inner').css('marginTop').replace(/auto/, 0));
      jQuery(window).scroll(function (event) {
    var y = jQuery(this).scrollTop();
    if (y >= (top-50)) {
      jQuery('#region-sidebar-second .region-sidebar-second-inner').addClass('fixed');
    } else {
      jQuery('#region-sidebar-second .region-sidebar-second-inner').removeClass('fixed');
    }
      });
      jQuery('.side-menu-go-top').click(function (event){
    jQuery('html, body').animate({ scrollTop: 0 }, 'fast');
      });
    }
  });
}

function hide_search_block_title_ballerup(){
 jQuery(document).ready(function() {   
     jQuery("#block-views-exp-meetings-search-page .help-button").hide();
     jQuery("#block-views-exp-meetings-search-page .views-exposed-form").css("padding-left","0px");
   });
}