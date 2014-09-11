<?php
/**
 * @file
 * os2dagsorden_rules_and_permissions.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function os2dagsorden_rules_and_permissions_default_rules_configuration() {
  $items = array();
  $items['rules_disable_direct_content_view_for_non_admins'] = entity_import('rules_config', '{ "rules_disable_direct_content_view_for_non_admins" : {
      "LABEL" : "Disable direct content view for non-admins",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules" ],
      "ON" : [ "node_view" ],
      "IF" : [
        { "node_is_of_type" : {
            "node" : [ "node" ],
            "type" : { "value" : {
                "bullet_point" : "bullet_point",
                "bullet_point_attachment" : "bullet_point_attachment",
                "speaker_paper" : "speaker_paper"
              }
            }
          }
        }
      ],
      "DO" : [ { "redirect" : { "url" : "\\u003Cfront\\u003E" } } ]
    }
  }');
  return $items;
}
