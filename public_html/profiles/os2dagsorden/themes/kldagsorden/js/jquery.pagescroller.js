/*
 *	Page Scroller PRO - jQuery Plugin
 *	A simple plugin to add smooth scroll interaction to your website
 *
 *	Support at: http://www.pagescroller.com
 *
 *	Copyright (c) 2012 Dairien Boyd. All Rights Reserved
 *
 *	Version: 1.0 (2/2/2012)
 *	Requires: jQuery v1.4+
 *
 *	Page Scroller is released under the GNU General Public License
 *	(http://www.gnu.org/licenses/). By using Page Scroller, you 
 *	acknowledge and agree to the Terms of Service found here:
 *	(http://www.pagescroller.com/tos/)
 *
 */


var pageScroller = {};

(function($){ 
    $.fn.extend({ 
         
        // pass the options to pageScroller
        pageScroller: function(options) {

            //Set the default values, use comma to separate the settings, example:
            var defaults = {
				currentSection: 0,
                sectionClass: 'section',
				linkClass: 'link',
				navigation: new Array(),
				navigationClass: 'standardNav light',
				navigationLabel: 'Navigation',
				animationSpeed: 500,
				animationType: 'swing',
				scrollOffset: 0,
				HTML5mode: false,
				deepLink: false,
				keyboardControl: true,
				animationBefore: function() {},
				animationComplete: function() {},
				onChange: function() {}
            }
                 
            var options =  $.extend(defaults, options);

			pageScroll = function(pageScroll, o){
				
				// update jquery default animation interval
				$.fx.interval = 5;
				
				// store global pageScroller variables
				pageScroller.scrollDocument = $(document);
				pageScroller.scrollWindow = $(window);
				pageScroller.scrollBody = $("body");
				pageScroller.scrollPosition = pageScroller.scrollWindow.scrollTop();
				pageScroller.currentSectionHeight = pageScroller.scrollWindow.height();
				pageScroller.options = o;
				pageScroller.options.scrollOffset = parseInt(pageScroller.options.scrollOffset);
				
				// use div element is selector, unless HTML5 mode is enabled - use nav tag
				var navWrapper = "div";
				if(o.HTML5mode) navWrapper = "nav";
				
				// create a nav object if an array is passed
				if(pageScroller.options.navigation instanceof Array){
					pageScroll.append('<'+navWrapper+' class="pageScrollerNav '+o.navigationClass+'"><ul></ul></'+navWrapper+'>');
					pageScroller.wrapper = $('.'+o.navigationClass.replace(/\s/g,'.'), pageScroll);
					pageScroller.navigation = $('ul', pageScroller.wrapper);
					pageScroller.wrapper.addClass('left');
					// ensure page scroller is positioned relative (for absolute position nav)
					pageScroll.css({ position: 'relative' });
				}
				
				// use section tag if HTML5 mode is enabled
				if(o.HTML5mode){
					pageScroller.sections = $('section', pageScroll);
				}else{
					pageScroller.sections = $('.'+o.sectionClass, pageScroll);
				}
								
				// set basic position for each section
				pageScroller.sections.each(function(index){
					
					var section = $(this);
					var sectionTitle = pageScroller.sections.eq(index).attr('title');
					var linkClass = o.linkClass+' '+o.linkClass+'_'+(index+1);
					
					// add unique class to last section
					if(index == pageScroller.sections.length-1) linkClass += ' '+o.linkClass+'_last';
					
					// set general section CSS rules
					section.css({
						display: 'block',
						position: 'relative',
						float: 'none'
					});
					
					// add unique section class
					section.addClass(pageScroller.options.sectionClass+'_'+(index+1));

					// create corresponding navigation links
					if(pageScroller.options.navigation instanceof Array){
						if(pageScroller.options.navigation.length){
							pageScroller.navigation.append('<li class="'+linkClass+'"><a href="#pageScroll'+index+'">'+pageScroller.options.navigation[index]+'</a></li>');
						}else if(sectionTitle && sectionTitle != ''){
							pageScroller.navigation.append('<li class="'+linkClass+'"><a href="#pageScroll'+index+'">'+sectionTitle+'</a></li>');
						}else{
							pageScroller.navigation.append('<li class="'+linkClass+'"><a href="#pageScroll'+index+'">Navigation '+(index+1)+'</a></li>');
						}
					}else{
						pageScroller.navigation = $(pageScroller.options.navigation);
					}
					
				});
				
				// set page link variable
				pageScroller.pageLinks = $('a', pageScroller.navigation);
				
				// set click events for page links
				pageScroller.pageLinks.each(function(index){
					$(this).bind('click', function(e){
						e.preventDefault();
						o.animationBefore();
						// instantly update active state if not already animating
						if(!pageScroller.scrollBody.is(':animated')){
							pageScroller.pageLinks.parent('li').removeClass('active');
							$(this).parent('li').addClass('active');
						}
						scrollPageTo(pageScroll, pageScroller.sections.eq(index), index);
					});
				});				
				
				// add next and previous functions
				pageScroller.next = function(){ next(pageScroll, pageScroller.options.currentSection); }
				pageScroller.prev = function(){ prev(pageScroll, pageScroller.options.currentSection); }
				pageScroller.goTo = function(index){ goTo(pageScroll, pageScroller.options.currentSection, index); }
				
				// add keyboard control
				if(pageScroller.options.keyboardControl){
					pageScroller.scrollDocument.bind('keydown', function(e){
						var key = e.which ? e.which : e.keyCode;
						if(key == 38 || key == 40){
							e.preventDefault();
							if(key == 38){
								if(!pageScroller.options.currentSection){
									pageScroller.goTo(pageScroller.options.currentSection+1);
								}else{
									pageScroller.goTo(pageScroller.options.currentSection);
								}
							}else if(key == 40){
								if(pageScroller.options.currentSection+1 == pageScroller.sections.length){
									pageScroller.goTo(pageScroller.options.currentSection+1);
								}else{
									pageScroller.goTo(pageScroller.options.currentSection+2);
								}
							}
						}
					});
				}
				
				// update navigation one page scroll
				pageScroller.scrollWindow.bind('scroll', function(e){
					findPosition();				
				});
				
				// find position on page load
				setTimeout(function(){ if(pageScroller.scrollPosition == 0) getHashTag(); findPosition(); }, 200);		
				
			}
			
			// determine current section from hash tag
			var getHashTag = function(){
				
				if(pageScroller.options.deepLink){
					var hashTag = window.location.hash;
					if(hashTag){
						pageScroller.pageLinks.each(function(index){
							var checkHash = pageScroller.pageLinks.eq(index).html();
							checkHash = checkHash.replace(/[^a-zA-Z 0-9]+/g,'').replace(/\s+/g, '-').toLowerCase();
							checkHash = '#section-'+checkHash;
							if(hashTag == checkHash){
								pageScroller.goTo(index+1);
								return false;
							}
						});
					}
				}
				
			}
			
			// updates current page scroller element
			var findPosition = function(){
				
				//updates scroll position and distance
				pageScroller.scrollPosition = pageScroller.scrollWindow.scrollTop();
				pageScroller.scrollDistance = pageScroller.scrollPosition + pageScroller.currentSectionHeight;
				
				for (i=0;i<pageScroller.sections.length;i++) {
				
					// defines current section and distance from top
					var section = pageScroller.sections.eq(i);
					var sectionTop = section.offset().top;
					
					//account for offset scroll targets
					if(pageScroller.options.scrollOffset && sectionTop){
						sectionTop += pageScroller.options.scrollOffset;
					}
					
					// reset next section value
					var nextSectionTop = 0;
					
					// only fires if there is a preceeding section
					if(i < pageScroller.sections.length-1){
						var nextSection = pageScroller.sections.eq(i+1);
						if(pageScroller.options.scrollOffset){
							nextSectionTop = nextSection.offset().top + pageScroller.options.scrollOffset;
						}else{
							nextSectionTop = nextSection.offset().top;
						}
						var currentLink = pageScroller.pageLinks.eq(i).parent('li');
						var lastLink = pageScroller.pageLinks.eq(pageScroller.sections.length-1).parent('li');
					}
					
					// update nav if page is animating
					if(!pageScroller.scrollBody.is(':animated')){
						// make last link active if end of page is reached and last section is not active
						if(pageScroller.scrollDocument.height() == pageScroller.scrollDistance) {
							if(!lastLink.hasClass('active')){
								updateTo = pageScroller.sections.length-1;
								updateNav(updateTo);
								return false;
							}
						// make link active if the scroll position is somewhere between
						// the current section and it's not already active
						}else if(nextSectionTop){
							if(pageScroller.scrollPosition >= sectionTop && pageScroller.scrollPosition < nextSectionTop){
								if(!currentLink.hasClass('active')){
									updateTo = i;
									updateNav(updateTo);
									return false;
								}
							}
						// make last link active active
						}else if(pageScroller.scrollPosition >= sectionTop && i == pageScroller.sections.length-1){
							if(!lastLink.hasClass('active')){
								updateTo = pageScroller.sections.length-1;
								updateNav(updateTo);
								return false;
							}
						}
					}else{
						return false;
					}
					
				}
				
			}
			
			// animate page to targeted section
			var scrollPageTo = function(pageScroll, targetSection, index){
				
				var page = $("html, body");
				var scrollWindow = $(window);
				var pageTop = scrollWindow.scrollTop();
				targetSection = targetSection.offset().top;
				
				//account for scrollOffset setting
				if(pageScroller.options.scrollOffset) targetSection += pageScroller.options.scrollOffset;	
				
				//do not scroll to distance beyond document top
				if(targetSection < 0) targetSection = 0;
				
				// scroll page if not currently animating
				if(targetSection != pageTop && !page.is(':animated')){
					page.animate({ 
						scrollTop: targetSection
					}, 
					pageScroller.options.animationSpeed,
					pageScroller.options.animationType).promise().done(function(){
						updateNav(index);
						pageScroller.options.animationComplete();
					});
				}
				
			}
			
			// create deeplinks if enabled
			var addHashTag = function(index){
				var myLink = pageScroller.pageLinks.eq(index).html();
				myLink = myLink.replace(/[^a-zA-Z 0-9]+/g,'').replace(/\s+/g, '-').toLowerCase();
				window.location.hash = 'section-'+myLink;
			}
			
			// update plugin and navigation to current section
			var updateNav = function(index){
				pageScroller.pageLinks.parent('li').removeClass('active');
				pageScroller.pageLinks.eq(index).parent('li').addClass('active');
				pageScroller.options.currentSection = index;
				if(pageScroller.options.deepLink){
					addHashTag(index);
				}
				pageScroller.options.onChange();
			}
			
			// built in next function
			var next = function(pageScroll, o){
				var index = o+1;
				if(index != pageScroller.sections.length){
					var targetSection = pageScroller.sections.eq(index);
					scrollPageTo(pageScroll, targetSection, index);
				}
			}
			
			// built in previous function
			var prev = function(pageScroll, o){
				var index = o-1;
				if(index <= 0) index = 0;
				var targetSection = pageScroller.sections.eq(index);
				scrollPageTo(pageScroll, targetSection, index);
			}
			
			// built in go to function
			var goTo = function(pageScroll, o, index){
					index = index-1;
					var targetSection = pageScroller.sections.eq(index);
					scrollPageTo(pageScroll, targetSection, index);
			}
			
			if(!pageScroller.options){
				return pageScroll(this, options);
			}

        }
    });
     
})(jQuery);