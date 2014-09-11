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

function bullet_point_add_expand_behaviour_ringsted(url, massive_bilag_expand, bullet_points_expand){
  var pathname = window.location.pathname;
  jQuery(document).ready(function() {
    jQuery(".bullet-point-attachments .view-content .item-list .ul-item-list-dagsordenspunkt").each(function(index) {
      jQuery(this).children("li.bilags_cases").children(".bilags_cases_container").attr("id","bilags_cases_container_"+index);
      jQuery(this).children("li.bilags_cases").children(".bilags_cases_container").hide();

      bilag_cases_add_expand_behaviour(this,index, url, massive_bilag_expand);
    });
  });
}

function bilag_cases_add_expand_behaviour(bulletPoint, bulletPointIndex, url, massive_bilag_expand){
  var pathname = window.location.pathname;
  jQuery(bulletPoint).children("li").children(".bilags_cases_container").each(function(index_attachment){
    jQuery(this).attr("id","bilags_cases_container_"+bulletPointIndex+"_"+index_attachment);
    jQuery(this).hide();

    jQuery(this).parent().prepend("<input type='button' class='button hide_show_bilags_cases' id='btn_hide_bilags_cases_"+bulletPointIndex+"_"+index_attachment+"' value='⇓'>");
    jQuery("#btn_hide_bilags_cases_"+bulletPointIndex+"_"+index_attachment).click(function(){
      //hide or show the content container
      jQuery("#bilags_cases_container_"+bulletPointIndex+"_"+index_attachment).toggle();

      //change the arrow button icon
      if (jQuery("#btn_hide_bilags_cases_"+bulletPointIndex+"_"+index_attachment).val() == "⇓"){//closed
	jQuery("#btn_hide_bilags_cases_"+bulletPointIndex+"_"+index_attachment).val("⇑");
	//saving in local storage
	window.localStorage.setItem(pathname + "-bilags_cases_container_"+bulletPointIndex+"_"+index_attachment, "true");
      }
      else {//opened
	jQuery("#btn_hide_bilags_cases_"+bulletPointIndex+"_"+index_attachment).val("⇓");
	//saving in local storage
	window.localStorage.setItem(pathname + "-bilags_cases_container_"+bulletPointIndex+"_"+index_attachment, "false");
      }

    });

    //reading from local storage
    if (JSON.parse(window.localStorage.getItem(pathname + "-bilags_cases_container_"+bulletPointIndex+"_"+index_attachment)) === true){
      jQuery("#btn_hide_bilags_cases_"+bulletPointIndex+"_"+index_attachment).click();
    }
  });
}

function bullet_point_details_init_ringsted(url, massive_bilag_expand){
  jQuery(document).ready(function() {   
  jQuery(".item-list-dagsordenspunkt .ul-item-list-dagsordenspunkt").each(function(index) {
	bilag_cases_add_expand_behaviour(this, index, url, massive_bilag_expand);
    });
  });
}

function open_all_bilag_case_bullet_points(expand_bilags, expand_cases) {
  jQuery(document).ready(function() {
   if (expand_bilags)  { 
     jQuery("li.bilags").children(".hide_show_bilags_cases").each(function(index) {
         if (jQuery(this).val() == '⇓') {          
	jQuery(this).click();
      }
    }); 
  }
  if(expand_cases)  { 
     
    jQuery("li.cases").children(".hide_show_bilags_cases").each(function(index) {
      if (jQuery(this).val() == '⇓') {
	jQuery(this).click();
      }
    }); 
  }

  });
  
}

function hide_search_block_title_ringsted(){
  jQuery(document).ready(function() {   
     jQuery("#block-views-exp-meetings-search-page .help-button").hide();
     jQuery("#block-views-exp-meetings-search-page .views-exposed-form").css("padding-left","0px");
   });
}