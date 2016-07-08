function add_annotator(meeting_id, bullet_point_id, bilag_id, element_to_annotate, url, filter) {
  jQuery(document).ready(function() {
          	//"use strict";
		jQuery(element_to_annotate).annotator().annotator('addPlugin', 'Touch', {
			//force: location.search.indexOf('force') > -1,
			force: 1,
			useHighlighter: location.search.indexOf('highlighter') > -1
		});
		if (filter){
		  jQuery(element_to_annotate).annotator().annotator('addPlugin', 'Filter');
		}
		
		jQuery(element_to_annotate).annotator().annotator('addPlugin', 'Store', {
			// The endpoint of the store on your server.
			prefix: url,
			annotationData: {
				'bilag_id': bilag_id,
				'bullet_point_id': bullet_point_id,
				'meeting_id': meeting_id,
			},
			loadFromSearch: {
				'bilag_id': bilag_id,
				'bullet_point_id': bullet_point_id,
				'meeting_id': meeting_id,
			},
			urls: {
			  create:  'annotator/create',
			  read:    'annotator/read/:id',
			  update:  'annotator/update/:id',
			  destroy: 'annotator/delete/:id',
			  search:  'annotator/search'
			}
		});

        if (!jQuery("body .annotator-touch-controls.dummy-controls").length ) {
            jQuery('body').append(
                '<div class="annotator-touch-widget annotator-touch-controls dummy-controls">' +
                    '<div class="annotator-touch-widget-inner">' +
                        '<a class="annotator-button annotator-add annotator-focus">Lav note</a>' +
                    '</div>' +
                '</div>'
            );
            jQuery('body .annotator-touch-controls.dummy-controls').click(function(e) {
                //console.log('clicked');
                e.preventDefault();
                if (jQuery("#ToolTipDiv2").css('display') != 'block') {
                  jQuery("#ToolTipDiv2").html("Marker tekst og klik herefter på Lav note").fadeIn(400);
                  setTimeout(function(){
                      jQuery("#ToolTipDiv2").fadeOut("slow");
                  },5000)
                }
                else {
                  jQuery("#ToolTipDiv2").css({'display': 'none'});
                }
            })
        }

	});
}

function annotator_hide_menu(){
	jQuery(document).ready(function(){
		jQuery(".region-sidebar-second-inner").hide(); 
		jQuery("#show_hide_menu_button").val("⇒");
		jQuery("#region-content").removeClass("grid-18");
		jQuery("#region-content").addClass("grid-24");
	});
}

function annotator_add_floatinscrollbar(){
	jQuery(document).ready(function(){
		jQuery("#pdf-main").floatingScrollbar();
	});
}

function highlight_wrapper(element, searchParam){
    jQuery(document).ready(function() {
        jQuery(element).highlight(searchParam);
    });
}
