<?php
/**
 * @file
 * ldap_rk.ldap_servers.inc
 */

/**
 * Implements hook_default_ldap_servers().
 */
function ldap_rk_default_ldap_servers() {
  $export = array();

  $ldap_servers_conf = new stdClass();
  $ldap_servers_conf->disabled = FALSE; /* Edit this to true to make a default ldap_servers_conf disabled initially */
  $ldap_servers_conf->api_version = 1;
  $ldap_servers_conf->sid = 'rkdc01';
  $ldap_servers_conf->name = 'rkdc01';
  $ldap_servers_conf->status = TRUE;
  $ldap_servers_conf->ldap_type = 'ad';
  $ldap_servers_conf->address = 'rkdc01.ringsted.int';
  $ldap_servers_conf->port = 389;
  $ldap_servers_conf->tls = FALSE;
  $ldap_servers_conf->followrefs = FALSE;
  $ldap_servers_conf->bind_method = 1;
  $ldap_servers_conf->binddn = 'CN=Serviceman OS2 Test,OU=ServiceUsers,OU=SikkerhedsGrupper,DC=ringsted,DC=int';
  $ldap_servers_conf->bindpw = 'VaDreguch3';
  $ldap_servers_conf->basedn = array(
    0 => 'OU=Org,DC=ringsted,DC=int',
    1 => 'OU=Eksterne_konsulenter,OU=SikkerhedsGrupper,DC=ringsted,DC=int',
    2 => 'OU=Brugergrupper,OU=SikkerhedsGrupper,DC=ringsted,DC=int',
  );
  $ldap_servers_conf->user_attr = 'samaccountname';
  $ldap_servers_conf->account_name_attr = '';
  $ldap_servers_conf->mail_attr = 'mail';
  $ldap_servers_conf->mail_template = '';
  $ldap_servers_conf->picture_attr = 'thumbnailphoto';
  $ldap_servers_conf->unique_persistent_attr = '';
  $ldap_servers_conf->unique_persistent_attr_binary = FALSE;
  $ldap_servers_conf->user_dn_expression = '';
  $ldap_servers_conf->ldap_to_drupal_user = '';
  $ldap_servers_conf->testing_drupal_username = '';
  $ldap_servers_conf->testing_drupal_user_dn = '';
  $ldap_servers_conf->grp_unused = FALSE;
  $ldap_servers_conf->grp_object_cat = 'group';
  $ldap_servers_conf->grp_nested = TRUE;
  $ldap_servers_conf->grp_user_memb_attr_exists = TRUE;
  $ldap_servers_conf->grp_user_memb_attr = 'memberof';
  $ldap_servers_conf->grp_memb_attr = 'member';
  $ldap_servers_conf->grp_memb_attr_match_user_attr = 'dn';
  $ldap_servers_conf->grp_derive_from_dn = FALSE;
  $ldap_servers_conf->grp_derive_from_dn_attr = '';
  $ldap_servers_conf->grp_test_grp_dn = '';
  $ldap_servers_conf->grp_test_grp_dn_writeable = '';
  $ldap_servers_conf->search_pagination = TRUE;
  $ldap_servers_conf->search_page_size = 1000;
  $ldap_servers_conf->weight = 0;
  $export['rkdc01'] = $ldap_servers_conf;

  $ldap_servers_conf = new stdClass();
  $ldap_servers_conf->disabled = FALSE; /* Edit this to true to make a default ldap_servers_conf disabled initially */
  $ldap_servers_conf->api_version = 1;
  $ldap_servers_conf->sid = 'rkdc02';
  $ldap_servers_conf->name = 'rkdc02';
  $ldap_servers_conf->status = TRUE;
  $ldap_servers_conf->ldap_type = 'ad';
  $ldap_servers_conf->address = 'rkdc02.ringsted.int';
  $ldap_servers_conf->port = 389;
  $ldap_servers_conf->tls = FALSE;
  $ldap_servers_conf->followrefs = FALSE;
  $ldap_servers_conf->bind_method = 1;
  $ldap_servers_conf->binddn = 'CN=Serviceman OS2 Test,OU=ServiceUsers,OU=SikkerhedsGrupper,DC=ringsted,DC=int';
  $ldap_servers_conf->bindpw = 'VaDreguch3';
  $ldap_servers_conf->basedn = array(
    0 => 'OU=Org,DC=ringsted,DC=int',
    1 => 'OU=Eksterne_konsulenter,OU=SikkerhedsGrupper,DC=ringsted,DC=int',
    2 => 'OU=Brugergrupper,OU=SikkerhedsGrupper,DC=ringsted,DC=int',
  );
  $ldap_servers_conf->user_attr = 'samaccountname';
  $ldap_servers_conf->account_name_attr = '';
  $ldap_servers_conf->mail_attr = 'mail';
  $ldap_servers_conf->mail_template = '';
  $ldap_servers_conf->picture_attr = 'thumbnailphoto';
  $ldap_servers_conf->unique_persistent_attr = '';
  $ldap_servers_conf->unique_persistent_attr_binary = FALSE;
  $ldap_servers_conf->user_dn_expression = '';
  $ldap_servers_conf->ldap_to_drupal_user = '';
  $ldap_servers_conf->testing_drupal_username = '';
  $ldap_servers_conf->testing_drupal_user_dn = '';
  $ldap_servers_conf->grp_unused = FALSE;
  $ldap_servers_conf->grp_object_cat = 'group';
  $ldap_servers_conf->grp_nested = TRUE;
  $ldap_servers_conf->grp_user_memb_attr_exists = TRUE;
  $ldap_servers_conf->grp_user_memb_attr = 'memberof';
  $ldap_servers_conf->grp_memb_attr = 'member';
  $ldap_servers_conf->grp_memb_attr_match_user_attr = 'dn';
  $ldap_servers_conf->grp_derive_from_dn = FALSE;
  $ldap_servers_conf->grp_derive_from_dn_attr = '';
  $ldap_servers_conf->grp_test_grp_dn = '';
  $ldap_servers_conf->grp_test_grp_dn_writeable = '';
  $ldap_servers_conf->search_pagination = TRUE;
  $ldap_servers_conf->search_page_size = 1000;
  $ldap_servers_conf->weight = 0;
  $export['rkdc02'] = $ldap_servers_conf;

  $ldap_servers_conf = new stdClass();
  $ldap_servers_conf->disabled = FALSE; /* Edit this to true to make a default ldap_servers_conf disabled initially */
  $ldap_servers_conf->api_version = 1;
  $ldap_servers_conf->sid = 'rkdc03';
  $ldap_servers_conf->name = 'rkdc03';
  $ldap_servers_conf->status = TRUE;
  $ldap_servers_conf->ldap_type = 'ad';
  $ldap_servers_conf->address = 'rkdc03.ringsted.int';
  $ldap_servers_conf->port = 389;
  $ldap_servers_conf->tls = FALSE;
  $ldap_servers_conf->followrefs = FALSE;
  $ldap_servers_conf->bind_method = 1;
  $ldap_servers_conf->binddn = 'CN=Serviceman OS2 Test,OU=ServiceUsers,OU=SikkerhedsGrupper,DC=ringsted,DC=int';
  $ldap_servers_conf->bindpw = 'VaDreguch3';
  $ldap_servers_conf->basedn = array(
    0 => 'OU=Org,DC=ringsted,DC=int',
    1 => 'OU=Eksterne_konsulenter,OU=SikkerhedsGrupper,DC=ringsted,DC=int',
    2 => 'OU=Brugergrupper,OU=SikkerhedsGrupper,DC=ringsted,DC=int',
  );
  $ldap_servers_conf->user_attr = 'samaccountname';
  $ldap_servers_conf->account_name_attr = '';
  $ldap_servers_conf->mail_attr = 'mail';
  $ldap_servers_conf->mail_template = '';
  $ldap_servers_conf->picture_attr = 'thumbnailphoto';
  $ldap_servers_conf->unique_persistent_attr = '';
  $ldap_servers_conf->unique_persistent_attr_binary = FALSE;
  $ldap_servers_conf->user_dn_expression = '';
  $ldap_servers_conf->ldap_to_drupal_user = '';
  $ldap_servers_conf->testing_drupal_username = '';
  $ldap_servers_conf->testing_drupal_user_dn = '';
  $ldap_servers_conf->grp_unused = FALSE;
  $ldap_servers_conf->grp_object_cat = 'group';
  $ldap_servers_conf->grp_nested = TRUE;
  $ldap_servers_conf->grp_user_memb_attr_exists = TRUE;
  $ldap_servers_conf->grp_user_memb_attr = 'memberof';
  $ldap_servers_conf->grp_memb_attr = 'member';
  $ldap_servers_conf->grp_memb_attr_match_user_attr = 'dn';
  $ldap_servers_conf->grp_derive_from_dn = FALSE;
  $ldap_servers_conf->grp_derive_from_dn_attr = '';
  $ldap_servers_conf->grp_test_grp_dn = '';
  $ldap_servers_conf->grp_test_grp_dn_writeable = '';
  $ldap_servers_conf->search_pagination = TRUE;
  $ldap_servers_conf->search_page_size = 1000;
  $ldap_servers_conf->weight = 0;
  $export['rkdc03'] = $ldap_servers_conf;

  return $export;
}
