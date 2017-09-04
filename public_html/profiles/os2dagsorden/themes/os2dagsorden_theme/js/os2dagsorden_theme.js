(function($) {
if (!Array.prototype.indexOf) {
  Array.prototype.indexOf = function (searchElement  ) {
    'use strict';
    if (this == null) {
      throw new TypeError();
    }
    var n, k, t = Object(this),
        len = t.length >>> 0;

    if (len === 0) {
      return -1;
    }
    n = 0;
    if (arguments.length > 1) {
      n = Number(arguments[1]);
      if (n != n) { // shortcut for verifying if it's NaN
        n = 0;
      } else if (n != 0 && n != Infinity && n != -Infinity) {
        n = (n > 0 || -1) * Math.floor(Math.abs(n));
      }
    }
    if (n >= len) {
      return -1;
    }
    for (k = n >= 0 ? n : Math.max(len - Math.abs(n), 0); k < len; k++) {
      if (k in t && t[k] === searchElement) {
        return k;
      }
    }
    return -1;
  };
}

})(jQuery);

/**
 * Hides print buttons for the iPad
 */
function hide_print_buttons(){
  jQuery(document).ready(function() {
     if (isTouchDevice()){
	jQuery(".print-button").hide();
     }
  });
}

/*
 * Adds the subscribe/unsubscribe behavior for elements in the follows committees section
 */
function follows_subscribe_click(event) {
    var subscribed_elements = [];
    if (jQuery('#follows_subscribed_hidden').val() != '') {
        subscribed_elements = jQuery('#follows_subscribed_hidden').val().split(',');
    }

    var id_toggle = jQuery(event.target).attr('id').replace("checkbox_", "");
    if (subscribed_elements.indexOf(id_toggle) > -1) {
        //removing element 1 element
        subscribed_elements.splice(subscribed_elements.indexOf(id_toggle), 1);
    } else {
        //adding this element
        subscribed_elements.push(id_toggle);
    }

    jQuery(event.target).toggleClass('subscribed');
    jQuery('#follows_subscribed_hidden').val(subscribed_elements.join(','));
    //console.log(event.target);
}

jQuery(document).ready(function() {
    jQuery("ul.droptrue").sortable({
        connectWith: 'ul',
    });
    jQuery("ul.droptrue").bind("sortreceive", function(event, ui) {
        var arr_receiver = [];
        var arr_sender = [];
        jQuery(jQuery(this).children('li')).each(function(){
            arr_receiver.push(jQuery(this).attr('id'));
        });
        jQuery(jQuery(ui.sender[0]).children('li')).each(function(){
            arr_sender.push(jQuery(this).attr('id'));
        });
        jQuery('#' + jQuery(this).attr('id') + '_hidden').val(arr_receiver.join(','));
        jQuery('#' + jQuery(ui.sender[0]).attr('id') + '_hidden').val(arr_sender.join(','));
    });

    //add click behaviour to existing items

    jQuery(".select-committee #edit-follows-div ul.droptrue li input[type=checkbox]").click(follows_subscribe_click);
    //add behaviour to item that is added to the follow section
    jQuery(".select-committee #edit-follows-div ul.droptrue").bind("sortreceive", function(event, ui){
        jQuery(ui.item).addClass('can-subscribe');
        jQuery('#checkbox_' + ui.item.context.id).addClass('follows');
        //console.log(ui.item);
        setTimeout(function(){ jQuery(ui.item).find(["input[type=checkbox]"]).bind('click', follows_subscribe_click); }, 1);
    });

    //remove behaviour from item that is removed from the follow section
    jQuery(".select-committee.single #edit-follows-div ul.droptrue").bind("sortremove", function(event, ui){
        jQuery(ui.item).removeClass('can-subscribe subscribed');
        jQuery('#checkbox_' + ui.item.context.id ).removeClass('follows subscribed');
        jQuery('#checkbox_' + ui.item.context.id ).removeClass('checkbox_follows');
        jQuery('#checkbox_' + ui.item.context.id).addClass('checkbox');
        jQuery(ui.item).find("input[type=checkbox]").removeAttr("checked");
        jQuery('#checkbox_' + ui.item.context.id).unbind('click');

        //removing this element from subscribed
        var subscribed_elements = [];
        if (jQuery('#follows_subscribed_hidden').val() != '') {
            subscribed_elements = jQuery('#follows_subscribed_hidden').val().trim().split(',');
        }
        var id_toggle = jQuery(ui.item).attr('id');

        if (subscribed_elements.indexOf(id_toggle) > -1) {
            //removing element 1 element
            subscribed_elements.splice(subscribed_elements.indexOf(id_toggle), 1);
        }
        jQuery('#follows_subscribed_hidden').val(subscribed_elements.join(','));
    });

    
    jQuery("#edit-available-committee").css('height',jQuery(".select-committee").height()+"px");
    jQuery(".remove-committee").css('width',jQuery(".select-committee").width()+"px");
    //updatePostOrder();
});
 

jQuery(document).ready(function() {
    jQuery('.form-item-from-date-value-date input.form-text').change(function(){
          jQuery(this).val(prepareDate(jQuery(this).val()));
    })
    jQuery('.form-item-to-date-value-date input.form-text').change(function(){
          jQuery(this).val(prepareDate(jQuery(this).val()));
    })
    // Set body font size.
    jQuery('body').css({'font-size' : Drupal.settings.os2dagsorden_settings.body_font_size+'px'});

    // Set title font size.
    jQuery('table.views-table tr td a').css({'font-size' : Drupal.settings.os2dagsorden_settings.title_font_size+'px'});
    jQuery('.view-user-committee .views-row').css({'font-size' : Drupal.settings.os2dagsorden_settings.title_font_size+'px'});
    jQuery('.view-user-follow-committees .views-row').css({'font-size' : Drupal.settings.os2dagsorden_settings.title_font_size+'px'});
    jQuery('.view-user-follow-committees .view-empty').css({'font-size' : Drupal.settings.os2dagsorden_settings.title_font_size+'px'});


    // Sidepane arrow position.
    set_up_button_position('.front #block-block-1', '.front #region-sidebar-second', 'front', jQuery(window).width());
    set_up_button_position('.not-front #block-block-1', '.not-front #region-sidebar-second', 'not-front', jQuery(window).width());
    resize_listener();
});
function set_up_button_position(button_id, region_sidebar_second, frontpage, width) {
  // Sidepane arrow position.
  if (Drupal.settings.os2dagsorden_settings.sidepane_arrow_position != 'classic' && width > 740) {
    if (frontpage == 'front') {
      jQuery(button_id).css({'top' : '73px'});
      jQuery(region_sidebar_second).css({'margin-top':'42px'});
    }
    else {
      jQuery(button_id).css({'top' : '66px'});
      jQuery(region_sidebar_second).css({'margin-top':'0px'});
      jQuery('#breadcrumb').css({'width': '80%'});
    }
  }
  else if (width < 740) {
    if (frontpage == 'front') {
      jQuery(button_id).css({'top' : '28px'});
      jQuery(region_sidebar_second).removeAttr("style");
    }

  }
}
/* Changed ddmmyy and ddmmyyyy date formats to dd-mm-yyyy  */
function prepareDate(dateValue) {
   fromDateArray=dateValue.match( /^([0-9]{2})([0-9]{2})([0-9]{2,4})$/);
   if (fromDateArray){
    if (fromDateArray[3].length<4)
      fromDateArray[3]=2000 + parseInt(fromDateArray[3]);
       return fromDateArray[1]+'-'+fromDateArray[2]+'-'+fromDateArray[3];
   }
   else{
     return dateValue;
  }
 }
/**
 * Fixes the bug when two click are needed to follow link on iPad
 */
function add_indicator_help_text(){
  jQuery(document).ready(function() {
      jQuery('.indicator-has-notes').each(function() {
	  jQuery(this).attr('title', 'Ikonet er ikke klikbart, men angiver at du har lavet en eller flere noter.');
      });
      jQuery('.indicator-has-speaker-paper').each(function() {
	  jQuery(this).attr('title', 'Ikonet er ikke klikbart, men angiver at du har oprettet et talepapir.');
      });
  });
}


/**
 *Add the listener to the tabler orientation property. On device rotation side menu is either forces to be closed, or shown
 */
function add_tablet_orientation_listener(){
  jQuery(document).ready(function() {
      jQuery(window).bind('orientationchange', function(e) {
          switch (window.orientation) {
              case -90:
              case 90:
                  if (JSON.parse(window.localStorage.getItem('hide_side_menu')) === true) {
                      hide_side_menu(false);
                  } else {
                      show_side_menu(false);
                  }
                  break;
              default:
                  hide_side_menu(false);
                  break;
          }
     });
  });
}

/**
 * Adds the behaviour of showing/hidng the right side panel with menu.
 */

function add_show_hide_menu_behaviour(menu_collapse){
   jQuery(document).ready(function() {
      jQuery("#region-content").removeAttr("style");
       if (menu_collapse && (window.localStorage.getItem('hide_side_menu') === null || window.localStorage.getItem('hide_side_menu').length === 0)) {
          hide_side_menu(false);
       } else if (JSON.parse(window.localStorage.getItem('hide_side_menu')) === true) {
           hide_side_menu(false);
       }
       //forcing to be closed on portrain orientation
       if (window.orientation == 0 || window.orientation == 180) {
           hide_side_menu(false);
       }
       jQuery("#show_hide_menu_button").click(function(){
          //saving for landscape orientation only, portrait does not affect the saved value
          var saveForLandscapeOnly = (window.orientation != 0 && window.orientation != 180);
          if (jQuery("#show_hide_menu_button").val() == "⇒") {
              hide_side_menu(saveForLandscapeOnly);
          }
          else {
              show_side_menu(saveForLandscapeOnly);
          }
       });
   });
}

function resize_listener(){
  function decide_menu_visible() {
    var width = (window.innerWidth > 0) ? window.innerWidth : screen.width;
    // Sidepane arrow position.
    if (width < 740 || width > 740) {
      set_up_button_position('.front #block-block-1', '.front #region-sidebar-second', 'front', width);
      set_up_button_position('.not-front #block-block-1', '.not-front #region-sidebar-second', 'not-front', width);
    }
//    if (width > 768) {
//       if (JSON.parse(window.localStorage.getItem('hide_side_menu')) != true) {
//         show_side_menu(false);
//       }
//    }

  };

  var resizeTimer;
  jQuery(window).resize(function() {
    clearTimeout(resizeTimer);
    resizeTimer = setTimeout(decide_menu_visible, 100);
  });
}

/**
 * A funtion to hide the menu
 */
function hide_side_menu(user_defined){
  jQuery(document).ready(function() {
	jQuery(".region-sidebar-second-inner").hide();
	jQuery("#show_hide_menu_button").val("⇐");
	jQuery("#region-content").removeClass("grid-18");
	jQuery("#region-content").addClass("grid-24");
    if (Drupal.settings.os2dagsorden_settings.sidepane_arrow_position != 'classic') {
      if (jQuery(window).width() > 980 ) {
        jQuery("#region-content").css({'width': '93%'});
      }
      else if (jQuery(window).width() > 740 && jQuery(window).width() < 980 ) {
        jQuery("#region-content").css({'width': '91%'});
      }
      else {
        jQuery("#region-content").removeAttr("style");
      }
    }
    if (user_defined === true) {
      window.localStorage.setItem("hide_side_menu", "true");
    }
  });
}

/**
 * A funtion show hide the menu
 */
function show_side_menu(user_defined){
	jQuery(".region-sidebar-second-inner").show();
	jQuery("#show_hide_menu_button").val("⇒");
	jQuery("#region-content").removeClass("grid-24");
	jQuery("#region-content").addClass("grid-18");
    if (Drupal.settings.os2dagsorden_settings.sidepane_arrow_position != 'classic') {
      jQuery("#region-content").removeAttr("style");
    }
    if (user_defined === true) {
        window.localStorage.setItem("hide_side_menu", "false");
    }
}

/**
 * Adds the expand behaviour to bullet point on meeting or bullet-point view
 *
 * @url is base url, used to send the parameted to attachment_add_expand_behaviour()
 */
function bullet_point_add_expand_behaviour(url, massive_bilag_expand, bullet_points_expand, attachments_expand){
  var pathname = window.location.pathname;
   jQuery(document).ready(function() {
        jQuery(".bullet-point-attachments .view-content .item-list .ul-item-list-dagsordenspunkt").each(function(index) {
          jQuery(this).attr("id","attachments_container_"+index);
          jQuery(this).hide();

          jQuery(this).parent().parent().parent().children(".hide_show_button_container").append("<input type='button' class='button' id='btn_hide_show_attachments_"+index+"' value='⇓'></a>");

         jQuery("#btn_hide_show_attachments_"+index).click(function(){
             jQuery("#attachments_container_"+index).toggle();
             if (jQuery("#btn_hide_show_attachments_"+index).val() == "⇓"){//closed
                jQuery("#btn_hide_show_attachments_"+index).val("⇑");
                if (attachments_expand)
                    bullet_points_expand_all(this, index, url, massive_bilag_expand, attachments_expand);
                //saving in local storage
                window.localStorage.setItem(pathname + "-attachments_container_"+index, "true");
            }
            else {//opened
                jQuery("#btn_hide_show_attachments_"+index).val("⇓");
                //saving in local storage
                window.localStorage.setItem(pathname + "-attachments_container_"+index, "false");
            }
           });

          attachment_add_expand_all_behaviour(this, index, url, massive_bilag_expand);
          attachment_add_expand_behaviour(this,index,url, massive_bilag_expand, attachments_expand);

         if (bullet_points_expand && (window.localStorage.getItem(pathname + "-attachments_container_"+index)===null||window.localStorage.getItem(pathname + "-attachments_container_"+index)===true)){
                  bullet_points_expand_all(this, index, url, massive_bilag_expand, attachments_expand);
          }
          else{     //reading from local storage
          if (JSON.parse(window.localStorage.getItem(pathname + "-attachments_container_"+index)) === true){
            jQuery("#btn_hide_show_attachments_"+index).click();
                        }
                }
        });
 });
}

/**
 * Initiator function to add expand behaviour for bullet point, is used on bullet-point view
 *
 * @url is base url, used to send the parameted to attachment_add_expand_behaviour()
 */
function bullet_point_details_init(url, massive_bilag_expand, attachments_expand){
  jQuery(document).ready(function() {
    jQuery(".item-list-dagsordenspunkt .ul-item-list-dagsordenspunkt").each(function(index) {
	attachment_add_expand_all_behaviour(this, index, url, massive_bilag_expand);
	attachment_add_expand_behaviour(this, index, url, massive_bilag_expand);
        bilag_cases_add_expand_behaviour(this, index, url, massive_bilag_expand);
       if (attachments_expand)
            bullet_points_expand_all(this, index, url, massive_bilag_expand, attachments_expand);
    });
  });
}

function bullet_points_expand_all(bulletPoint, bulletPointIndex, url, massive_bilag_expand, attachments_expand){
  var pathname = window.location.pathname;
        jQuery("#attachments_container_"+bulletPointIndex).show();
        jQuery("#btn_hide_show_attachments_"+bulletPointIndex).val("⇑");
        if (attachments_expand){
          jQuery("[id^=attachment_text_container_"+bulletPointIndex+"_]").each(function(index_attachment){
            attachment_load_content(bulletPointIndex, index_attachment, url);
                jQuery("#btn_hide_show_attachment_text_"+bulletPointIndex+"_"+index_attachment).val("⇑");
                jQuery(this).show();

          });
      }
    jQuery(".btn_hide_show_all_attachments_text_"+bulletPointIndex).val('⇈');
}
/**
 * Add expand all behavious for bullet point - opens all of its children.
 *
 * Also loads the comment of the attachment via Ajax and adds the annotator to it, if these actions has not been done before
 *
 */
function attachment_add_expand_all_behaviour(bulletPoint, bulletPointIndex, url, massive_bilag_expand){
  var pathname = window.location.pathname;

  if (jQuery('li', bulletPoint).size() > 1) {
      jQuery(bulletPoint).prepend("<input type='button' class='button hide_show_all_attachments_text btn_hide_show_all_attachments_text_"+bulletPointIndex+" top' value='⇊'></a>");
      jQuery(bulletPoint).append("<input type='button' class='button hide_show_all_attachments_text btn_hide_show_all_attachments_text_"+bulletPointIndex+" bottom' value='⇊'></a>");

      jQuery(".btn_hide_show_all_attachments_text_"+bulletPointIndex).click(function(){
        if (jQuery(".btn_hide_show_all_attachments_text_"+bulletPointIndex).val() == "⇊"){
        jQuery("[id^=attachment_text_container_"+bulletPointIndex+"_]").each(function(index_attachment){
          if (massive_bilag_expand || !jQuery(this).children().first().hasClass("attachment_text_trimmed_container")){//skip bilags
            //saving in the local storage
            window.localStorage.setItem(pathname + "-attachment_text_container_"+bulletPointIndex+"_"+index_attachment, "true");
            jQuery(this).show();

            //handle single expand button
            jQuery("#btn_hide_show_attachment_text_"+bulletPointIndex+"_"+index_attachment).val("⇑");
          }

          attachment_load_content(bulletPointIndex, index_attachment, url);
        });

        jQuery(".btn_hide_show_all_attachments_text_"+bulletPointIndex).val("⇈");
        } else {
            jQuery("[id^=attachment_text_container_"+bulletPointIndex+"_]").each(function(index_attachment){
          //saving in the local storage
          window.localStorage.setItem(pathname + "-attachment_text_container_"+bulletPointIndex+"_"+index_attachment, "false");
          jQuery(this).hide();

          //handle single expand button
          jQuery("#btn_hide_show_attachment_text_"+bulletPointIndex+"_"+index_attachment).val("⇓");
        });

        jQuery(".btn_hide_show_all_attachments_text_"+bulletPointIndex).val("⇊");
        }
      });
  }
}

/**
 * Adds expand behaviour on a single attachment.
 *
 * Also calls attachment_load_content
 */
function attachment_add_expand_behaviour(bulletPoint, bulletPointIndex, url, massive_bilag_expand,  attachments_expand){
  var pathname = window.location.pathname;

  jQuery(bulletPoint).children("li").children(".attachment_text_container").each(function(index_attachment){
    jQuery(this).attr("id","attachment_text_container_"+bulletPointIndex+"_"+index_attachment);
    jQuery(this).hide();

    jQuery(this).parent().prepend("<input type='button' class='button hide_show_attachment_text' id='btn_hide_show_attachment_text_"+bulletPointIndex+"_"+index_attachment+"' value='⇓'></a>");
    jQuery("#btn_hide_show_attachment_text_"+bulletPointIndex+"_"+index_attachment).click(function(){
      //hide or show the content container
      jQuery("#attachment_text_container_"+bulletPointIndex+"_"+index_attachment).toggle();

      attachment_load_content(bulletPointIndex, index_attachment, url);

      //change the arrow button icon
      if (jQuery("#btn_hide_show_attachment_text_"+bulletPointIndex+"_"+index_attachment).val() == "⇓"){//closed
	jQuery("#btn_hide_show_attachment_text_"+bulletPointIndex+"_"+index_attachment).val("⇑");
	//saving in local storage
	window.localStorage.setItem(pathname + "-attachment_text_container_"+bulletPointIndex+"_"+index_attachment, "true");
      }
      else {//opened
	jQuery("#btn_hide_show_attachment_text_"+bulletPointIndex+"_"+index_attachment).val("⇓");
	//saving in local storage
	window.localStorage.setItem(pathname + "-attachment_text_container_"+bulletPointIndex+"_"+index_attachment, "false");
      }

      //handle expand all
      if (attachments_expand){
	if (jQuery("[id^=btn_hide_show_attachment_text_"+bulletPointIndex+"_][value='⇓']").length > 0)
      jQuery(".btn_hide_show_all_attachments_text_"+bulletPointIndex).val("⇊");
	else
      jQuery(".btn_hide_show_all_attachments_text_"+bulletPointIndex).val("⇈");
      } else {
	var new_val = "⇈";
	jQuery("[id^=btn_hide_show_attachment_text_"+bulletPointIndex+"_]").each(function(){
	  if (jQuery(this).parent().hasClass("non-bilag")){
	    if (jQuery(this).val() == '⇓'){
	      new_val = "⇊";
	    }
	  }
	});
    jQuery(".btn_hide_show_all_attachments_text_"+bulletPointIndex).val(new_val);
      }
    });

    //reading from local storage
    if (JSON.parse(window.localStorage.getItem(pathname + "-attachment_text_container_"+bulletPointIndex+"_"+index_attachment)) === true){
      jQuery("#btn_hide_show_attachment_text_"+bulletPointIndex+"_"+index_attachment).click();
    }
  });
  jQuery("#attachments_container_"+bulletPointIndex).each(function(index) {
      jQuery(this).children("li.bilags_cases").children(".bilags_cases_container").attr("id","bilags_cases_container_"+bulletPointIndex);
      jQuery(this).children("li.bilags_cases").children(".bilags_cases_container").hide();
      bilag_cases_add_expand_behaviour(this,bulletPointIndex, url, massive_bilag_expand);
    });
  }

/**
 * Loads the content of the attachment and places it into the container
 *
 * Also loads the comment of the attachment via Ajax and adds the annotator to it, if these actions has not been done before
 */
function attachment_load_content(bulletPointIndex, index_attachment, url){
    //load the content on first click and add the annotator
    if (jQuery("#attachment_text_container_"+bulletPointIndex+"_"+index_attachment).children().contents().first().text() == "Vent venligst..."){
      //get meeting id, bullet-point id and bilag id
      classes = jQuery("#attachment_text_container_"+bulletPointIndex+"_"+index_attachment).children().attr('class').split(' ');
      var cl = jQuery.grep(classes, function(string, i){
	return (string.indexOf("bpa-") == 0);
      });

      cl_arr = String(cl).split("-");
      var bilag_id = cl_arr[3];
      var bullet_point_id = cl_arr[2];
      var meeting_id = cl_arr[1];

      //add real content
      jQuery.get(url + "meeting/" + meeting_id + "/bullet-point/" + bullet_point_id + "/bullet-point-attachment-raw/" + bilag_id, function(html) {
	//remove dummy text
	jQuery("#attachment_text_container_"+bulletPointIndex+"_"+index_attachment).children().contents().first().remove();
	jQuery("#attachment_text_container_"+bulletPointIndex+"_"+index_attachment).children().contents().first().remove();

	jQuery("#attachment_text_container_"+bulletPointIndex+"_"+index_attachment).children().first().append(html);

	//add annotator to it
	add_annotator(meeting_id, bullet_point_id, bilag_id, ".bpa-" + meeting_id + "-" + bullet_point_id + "-" + bilag_id,url, false);

	//add preview stamp picture, if is actual bilag
	if (jQuery(".bpa-" + meeting_id + "-" + bullet_point_id + "-" + bilag_id).hasClass("attachment_text_trimmed_container"))
	  jQuery(".bpa-" + meeting_id + "-" + bullet_point_id + "-" + bilag_id).prepend('<div class="indicator-preview"></div>');
      });
    }
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

/**
 * Adds notes indicators, to bullet point attachment
 *
 */
function bullet_point_attachment_add_notes_indicator(ids){
  jQuery(document).ready(function() {
	jQuery(".indicator-has-no-notes").each(function(){
	  if (ids.indexOf(parseInt(this.id)) != -1){
	    jQuery(this).attr("class","indicator-has-notes");
	  }
	});
   });
}

/**
 * Checks if device is touchable
 *
 */
function isTouchDevice(){
  return "ontouchstart" in window || window.DocumentTouch && document instanceof DocumentTouch;
}

function addPagescroller(){
  if (isTouchDevice()){
    jQuery(document).ready(function() {

      var maxPages = jQuery('.views-field-php-4').size();

	    if (maxPages > 1){//meeting is not empty
        jQuery('<div class="section section-bottom"></div>').insertAfter(jQuery('#section-content'));

	      jQuery('#page').pageScroller({
		      navigation: '#arrow-controls',
		      sectionClass: 'section',
	      });

	      jQuery('.bullet-point-attachments').prepend('<div id="arrow-controls" class="light right">'
	      + '<a href="#" class="prev"></a><br/>'
	      + '<a href="#" class="next"></a>'
	      + '</div>');

	      // assigns 'next' API command to link
	      jQuery('#arrow-controls .next').bind('click', function(e){
		      e.preventDefault();
          //console.log(pageScroller.current);
		      //pageScroller.goTo(page);
		      pageScroller.next();
	      });

  	    // assigns 'previous' API command to link
  	    jQuery('#arrow-controls .prev').bind('click', function(e){
  		    e.preventDefault();

  		    //console.log(pageScroller.current);
  		    //pageScroller.goTo(page);
  		    pageScroller.prev();

  	    });
	    }
    });
  }
}

function hide_budget_menu(){
  jQuery(document).ready(function() {
      jQuery("#menu-budget").parent().hide();
  });
}

function hide_massive_expand_collapse_button(){
  jQuery(document).ready(function() {
    jQuery(".ul-item-list-dagsordenspunkt").each(function(index) {
          //jQuery("#btn_hide_show_all_attachments_text_"+index).hide();
          jQuery(".btn_hide_show_all_attachments_text_"+index).hide();
    });
  });
}

function hide_search_block_title(){
 jQuery(document).ready(function() {
   jQuery("#block-views-exp-meetings-search-page .block-title").hide();
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

// Help text clickable.

(function($) {
  $(document).ready(function() {
    $("body").append("<div id='ToolTipDiv' class='tip-darkgray'></div>");
    $("body").append("<div id='ToolTipDiv2' class='tip-darkgray'></div>");
    $(".help-button").each(function() {
      var offset = $(this).offset();

      $(this).click(function(e) {
        if ($("#ToolTipDiv").css('display') == 'block') {
          $("#ToolTipDiv").css({'position': 'absolute', 'bottom': '', 'right': ''});
          if ($("#ToolTipDiv").hasClass($(this).attr('id'))) {
            $("#ToolTipDiv").fadeOut(400);
            $("#ToolTipDiv").attr('class', 'tip-darkgray');
          }
          else {
            $("#ToolTipDiv").css({'top': offset.top + 30, 'left': offset.left - 300, 'max-width': '300px'});
            $("#ToolTipDiv").attr('class', 'tip-darkgray');
            $("#ToolTipDiv").addClass($(this).attr('id'));
            $("#ToolTipDiv").html($(this).attr('aria-label')).fadeIn(400)
          }
        }
        else {

          $("#ToolTipDiv").css({'top': offset.top + 30, 'left': offset.left - 300, 'max-width': '300px'});
          $("#ToolTipDiv").addClass($(this).attr('id'));
          $("#ToolTipDiv").html($(this).attr('aria-label')).fadeIn(400);

        }

      });
    });
  });
})( jQuery );
