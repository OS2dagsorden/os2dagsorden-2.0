<?php
/**
 * @file
 * os2dagsorden_ad_integration.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function os2dagsorden_ad_integration_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ldap_authentication_conf';
  $strongarm->value = array(
    'sids' => array(
      'balk.dk' => 'balk.dk',
    ),
    'authenticationMode' => 1,
    'loginConflictResolve' => 2,
    'acctCreation' => 4,
    'loginUIUsernameTxt' => 'Brugernavn',
    'loginUIPasswordTxt' => 'Kodeord',
    'ldapUserHelpLinkUrl' => NULL,
    'ldapUserHelpLinkText' => 'Hjælp til logon',
    'emailOption' => 3,
    'emailUpdate' => 1,
    'allowOnlyIfTextInDn' => array(),
    'excludeIfTextInDn' => array(),
    'allowTestPhp' => '',
    'excludeIfNoAuthorizations' => NULL,
    'ssoRemoteUserStripDomainName' => NULL,
    'seamlessLogin' => NULL,
    'ldapImplementation' => 'mod_auth_kerb',
    'cookieExpire' => NULL,
  );
  $export['ldap_authentication_conf'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ldap_profile_conf';
  $strongarm->value = array(
    'ldap_fields' => array(
      0 => 'samaccountname',
      1 => 'mail',
    ),
    'mapping' => array(
      'username' => 'samaccountname',
      'mail' => 'mail',
      'field_user_full_name' => 'displayname',
    ),
    'derivedMapping' => array(
      'field_navn_stilling' => array(
        'derive' => FALSE,
        'derive_value' => '',
      ),
      'field_user_id' => array(
        'derive' => FALSE,
        'derive_value' => '',
      ),
      'field_user_full_name' => array(
        'derive' => FALSE,
        'derive_value' => '',
      ),
    ),
  );
  $export['ldap_profile_conf'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ldap_servers_encryption';
  $strongarm->value = '6';
  $export['ldap_servers_encryption'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ldap_servers_encrypt_key';
  $strongarm->value = '8nATpSXoOJ';
  $export['ldap_servers_encrypt_key'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ldap_servers_require_ssl_for_credentails';
  $strongarm->value = 0;
  $export['ldap_servers_require_ssl_for_credentails'] = $strongarm;

  return $export;
}
