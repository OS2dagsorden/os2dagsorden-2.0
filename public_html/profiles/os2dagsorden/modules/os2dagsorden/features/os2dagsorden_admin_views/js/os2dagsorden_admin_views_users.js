(function($) {

    Drupal.behaviors.os2dagsorden_admin_views = {
        attach: function(context, settings) {
            if ($('#views-exposed-form-os2dagsorden-users-view-system-1 .views-exposed-form .views-exposed-widgets #show-more').length == 0) {
                if (show_hide_commitee_fields()) {
                    $("#views-exposed-form-os2dagsorden-users-view-system-1 .views-exposed-form .views-exposed-widgets #edit-commitee-wrapper").after('<div class="views-exposed-widget views-show-more-button"><input type="button" id="show-more" name="" value="Show more" class="form-submit" >    </div>');
                    $("#views-exposed-form-os2dagsorden-users-view-system-1 .views-exposed-form .views-exposed-widgets #edit-field-follows-committee-pp-tid-wrapper").hide();
                    $("#views-exposed-form-os2dagsorden-users-view-system-1 .views-exposed-form .views-exposed-widgets #edit-field-follows-committee-plus-tid-wrapper").hide();
                    $("#views-exposed-form-os2dagsorden-users-view-system-1 .views-exposed-form .views-exposed-widgets #edit-field-follows-committee-tid-wrapper").hide();
                    $("#views-exposed-form-os2dagsorden-users-view-system-1 .views-exposed-form .views-exposed-widgets #edit-field-user-committee-tid-wrapper").hide();
                }
                else
                    $("#views-exposed-form-os2dagsorden-users-view-system-1 .views-exposed-form .views-exposed-widgets #edit-field-follows-committee-pp-tid-wrapper").after('<div class="views-exposed-widget views-show-more-button"><input type="button" id="show-more" name="" value="Hide" class="form-submit">    </div>');
                $("#views-exposed-form-os2dagsorden-users-view-system-1 .views-exposed-form .views-exposed-widgets  .views-submit-button").insertAfter($('#views-exposed-form-os2dagsorden-users-view-system-1 .views-exposed-form .views-exposed-widgets .views-show-more-button'));
                $("#views-exposed-form-os2dagsorden-users-view-system-1 .views-exposed-form .views-exposed-widgets  .views-reset-button").insertAfter($("#views-exposed-form-os2dagsorden-users-view-system-1 .views-exposed-form .views-exposed-widgets  .views-submit-button"));
               $("#views-exposed-form-os2dagsorden-users-view-system-1 .views-exposed-form .views-exposed-widgets #edit-field-user-committee-tid-wrapper").css({"clear":"both"});
                    
                $('#views-exposed-form-os2dagsorden-users-view-system-1 .views-exposed-form .views-exposed-widgets #show-more').click(function() {
                    $("#views-exposed-form-os2dagsorden-users-view-system-1 .views-exposed-form .views-exposed-widgets #edit-field-follows-committee-pp-tid-wrapper").toggle();
                    $("#views-exposed-form-os2dagsorden-users-view-system-1 .views-exposed-form .views-exposed-widgets #edit-field-follows-committee-plus-tid-wrapper").toggle();
                    $("#views-exposed-form-os2dagsorden-users-view-system-1 .views-exposed-form .views-exposed-widgets #edit-field-follows-committee-tid-wrapper").toggle();
                    $("#views-exposed-form-os2dagsorden-users-view-system-1 .views-exposed-form .views-exposed-widgets #edit-field-user-committee-tid-wrapper").toggle();
                    if ($('#views-exposed-form-os2dagsorden-users-view-system-1 .views-exposed-form .views-exposed-widgets #show-more').attr('value') == 'Show more')
                        $('#views-exposed-form-os2dagsorden-users-view-system-1 .views-exposed-form .views-exposed-widgets #show-more').attr('value', 'Hide');
                    else
                        $('#views-exposed-form-os2dagsorden-users-view-system-1 .views-exposed-form .views-exposed-widgets #show-more').attr('value', 'Show more');
                    return false;
                });
            }
            function show_hide_commitee_fields() {
                if ($("#views-exposed-form-os2dagsorden-users-view-system-1 .views-exposed-form .views-exposed-widgets #edit-field-follows-committee-pp-tid-wrapper #edit-field-follows-committee-pp-tid").val() != 'All')
                    return false
                if ($("#views-exposed-form-os2dagsorden-users-view-system-1 .views-exposed-form .views-exposed-widgets #edit-field-follows-committee-plus-tid-wrapper #edit-field-follows-committee-plus-tid").val() != 'All')
                    return false
                if ($("#views-exposed-form-os2dagsorden-users-view-system-1 .views-exposed-form .views-exposed-widgets #edit-field-follows-committee-tid-wrapper #edit-field-follows-committee-tid").val() != 'All')
                    return false
                if ($("#views-exposed-form-os2dagsorden-users-view-system-1 .views-exposed-form .views-exposed-widgets #edit-field-user-committee-tid-wrapper #edit-field-user-committee-tid").val() != 'All')
                    return false
                return true;
            }

        }
    };
}(jQuery));



