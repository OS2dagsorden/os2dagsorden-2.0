<?php
/**
 * @file
 * os2dagsorden_ad_integration.ldap_authorization.inc
 */

/**
 * Implements hook_default_ldap_authorization().
 */
function os2dagsorden_ad_integration_default_ldap_authorization() {
  $export = array();

  $consumer_type = new stdClass();
  $consumer_type->disabled = FALSE; /* Edit this to true to make a default consumer_type disabled initially */
  $consumer_type->api_version = 1;
  $consumer_type->sid = 'ldap_syddjursnet';
  $consumer_type->consumer_type = 'drupal_role';
  $consumer_type->consumer_module = 'ldap_authorization_drupal_role';
  $consumer_type->status = TRUE;
  $consumer_type->only_ldap_authenticated = TRUE;
  $consumer_type->derive_from_dn = TRUE;
  $consumer_type->derive_from_dn_attr = 'ou';
  $consumer_type->derive_from_attr = FALSE;
  $consumer_type->derive_from_attr_attr = 'memberOf';
  $consumer_type->derive_from_attr_use_first_attr = TRUE;
  $consumer_type->derive_from_attr_nested = FALSE;
  $consumer_type->derive_from_entry = FALSE;
  $consumer_type->derive_from_entry_nested = FALSE;
  $consumer_type->derive_from_entry_entries = '';
  $consumer_type->derive_from_entry_entries_attr = '';
  $consumer_type->derive_from_entry_attr = '';
  $consumer_type->derive_from_entry_search_all = FALSE;
  $consumer_type->derive_from_entry_use_first_attr = FALSE;
  $consumer_type->derive_from_entry_user_ldap_attr = 'dn';
  $consumer_type->mappings = 'syddjurs|os2dagsorden
Ekstern Plus|os2dagsorden
';
  $consumer_type->use_filter = TRUE;
  $consumer_type->synch_to_ldap = FALSE;
  $consumer_type->synch_on_logon = TRUE;
  $consumer_type->revoke_ldap_provisioned = TRUE;
  $consumer_type->create_consumers = TRUE;
  $consumer_type->regrant_ldap_provisioned = TRUE;
  $export['drupal_role'] = $consumer_type;

  return $export;
}
