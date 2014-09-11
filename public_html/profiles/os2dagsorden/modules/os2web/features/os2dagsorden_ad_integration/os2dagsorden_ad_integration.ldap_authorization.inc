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
  $consumer_type->sid = 'balk.dk';
  $consumer_type->consumer_type = 'drupal_role';
  $consumer_type->consumer_module = 'ldap_authorization_drupal_role';
  $consumer_type->status = TRUE;
  $consumer_type->only_ldap_authenticated = TRUE;
  $consumer_type->derive_from_dn = FALSE;
  $consumer_type->derive_from_dn_attr = 'ou';
  $consumer_type->derive_from_attr = TRUE;
  $consumer_type->derive_from_attr_attr = 'memberOf';
  $consumer_type->derive_from_attr_use_first_attr = TRUE;
  $consumer_type->derive_from_attr_nested = TRUE;
  $consumer_type->derive_from_entry = FALSE;
  $consumer_type->derive_from_entry_nested = FALSE;
  $consumer_type->derive_from_entry_entries = '';
  $consumer_type->derive_from_entry_entries_attr = '';
  $consumer_type->derive_from_entry_attr = '';
  $consumer_type->derive_from_entry_search_all = FALSE;
  $consumer_type->derive_from_entry_use_first_attr = FALSE;
  $consumer_type->derive_from_entry_user_ldap_attr = 'dn';
  $consumer_type->mappings = 'Domain PowerUser|godkendt bruger
eDoc Chefgruppen|chefgruppen
eDoc Teknik- og Miljøudvalget|teknik- og miljøudvalget
eDoc Beredskabskommissionen|Beredskabskommissionen
eDoc Det politiske SSP-udvalg|det politiske ssp-udvalg
eDoc Direktionen|direktionen
eDoc Eliteidrætsrådet|eliteidrætsrådet
eDoc Frivillighedsrådet|frivillighedsrådet
eDoc Grønt Råd|grønt råd
eDoc Handicaprådet|handicaprådet
eDoc Innovationsudvalget|innovationsudvalget
eDoc Integrationsrådet|integrationsrådet
eDoc Internationalt Udvalg|internationalt udvalg
eDoc KMB IT-udvalget|kmb it-udvalget
eDoc Kommunalbestyrelsen|kommunalbestyrelsen
eDoc Konstituerende møde|konstituerende møde
eDoc Kultur- og Fritidsudvalget|kultur- og fritidsudvalget
eDoc Kunstrådet|kunstrådet
eDoc Seniorrådet|seniorrådet
eDoc Skole- og Uddannelsesudvalget|skole- og uddannelsesudvalget
eDoc Socialudvalget|socialudvalget
eDoc Studierejseudvalget|studierejseudvalget
eDoc Sundheds- og Forebyggelsesudvalget|sundheds- og forebyggelsesudvalget
eDoc Økonomiudvalget|økonomiudvalget
Grupper|os2dagsorden
pro-os2-dagsorden-admin|os2dagsorden admin
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
