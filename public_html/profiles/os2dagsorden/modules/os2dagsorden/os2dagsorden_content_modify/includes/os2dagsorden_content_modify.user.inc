<?php

/**
 * Generates user edit form and (if uid is not null) loads and sets the parameters.
 * Depending on the user rights form is either limited (with no right) of full (with administer os2web right).
 *
 * @param $form       mixed the form
 * @param $form_state mixed the state of the form
 * @param $uid        int   the id of the user to be modified
 *
 * @return form
 */
function os2dagsorden_content_modify_user_edit_form($form, $form_state, $uid) {

  $form[] = array(
    '#markup' => '<div class="node clearfix">',
  );

  $form['full_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Full name:'),
    '#size' => 60,
    '#maxlength' => 128,
    '#description' => t('Is displayed in the top right corner.'),
  );

  $form['organization'] = array(
    '#type' => 'textfield',
    '#title' => t('Organization:'),
    '#size' => 60,
    '#maxlength' => 128,

  );

  $form['calendar_pref'] = array(
    //'#access' => user_access('administer os2web', $full_user),
    '#type' => 'checkboxes',
    '#field_prefix' => t('Which types of meetings should user see in the calendar'),
    '#options' => array(
      'pol' => t('Political'),
      'org' => t('Organizational')
    ),
    '#title' =>"<b>" . t('Calendar preferences:') . "</b>",
  );

  $form['forbidden_cat'] = array(
    '#access' => user_access('administer users'),
    '#type' => 'checkboxes',
    '#options' => array(
      'pol' => t('Political'),
      'org' => t('Organizational')
    ),
    '#title' =>"<b>" . t('Forbidden categories:') . "</b>",
    '#description' => t('Which categories the user is FORBIDDEN to have access to'),
  );

  $form['user_can_send_closed_bp'] = array(
    '#access' => user_access('administer users'),
    '#type' => 'radios',
    '#title' => "<b>" .t('User can send to friend closed bullet points') . "</b>" ,
    '#default_value' => false,
    '#options' => array(
      true => t('Yes'),
      false => t('No')
    ),
  );

  $form['user_roles'] = array(
    '#access' => (user_access('administer users')),
    '#type' => 'checkboxes',
    '#options' => array(
      'os2dagsorden limited' => t('OS2Dagsorden limited') .'<i>' . t(' (Kan kun tilgå udvalg man er medlem af)') .'</i>',
      'administrator+' => t('Administrator+')  . '<i>' . t(' (adgang til redigering af udvalg og brugere)').'</i>',
      'administrator++' => t('Administrator++') . '<i>' . t(' (rettigheder til al konfiguration og alle settings)').'</i>',
    ),
    '#title' => '<b>' . t('Brugerroller') . '</b>',
    '#description' => t('Hvilke roller tilsættes til brugeren'),
  );

  if (!user_access('administer os2web')) {
    $form['user_roles']['administrator++']['#disabled']  = TRUE;
  }

  //DAGS-349 - enabling drag and drop for touch devices
  _os2dagsorden_content_modify_render_drag_and_drop_controls($form, array($uid));

  //loading common user fields
  if ($uid) {
    _os2dagsorden_conten_modify_load_user_fields($form, $uid);
  }

  $form['save_user'] = array(
    '#type' => 'submit',
    '#attributes' => array(
      'class' => array('form-save-submit'),
    ),
    '#value' => t('Save'),
    '#submit' => array('os2dagsorden_content_modify_user_submit'),
  );
  $form[] = array(
    '#markup' => '</div>',//<div class="node clearfix">
  );

  return $form;
}

/**
 * Fills forms with drag and drop controls for manipulating users committees (member of/follows/follows+/follows++ and all committees).
 *
 * If uids is not null, the drag and drops controls will be prefilled with right values.
 * In case uids contains more than one id (batch edit), then only the committees shared amount all users will be prefilled into the boxes.
 *
 *
 * @param $form mixed the form
 * @param $uids array array of uid
 */
function _os2dagsorden_content_modify_render_drag_and_drop_controls(&$form, $uids) {
  $single_or_batch_class = (sizeof($uids) == 1)? 'single' : 'batch';

  $form[] = array(
    '#markup' => "
        <div class=\"select-committee {$single_or_batch_class}\">",
  );

  $form['member_of_div'] = array(
    '#access' => user_access('administer users'),
    '#type' => 'item' ,
    '#prefix' => '<label>' . t('Member of:') . '</label>',
    '#markup' => '',
  );
  $form['member_of_hidden'] = array(
    '#type' => 'hidden',
    '#attributes' => array(
      'id' => 'member_of_hidden',
    )
  );
  $form['follows_div'] = array(
    '#type' => 'item' ,
    '#prefix' => '<label class="label_follows">' . t('Follows:') . '</label><div class="note">Notifikationer på mail:</div>',
    '#markup' => '',
  );
  $form['follows_hidden'] = array(
    '#type' => 'hidden',
    '#attributes' => array(
      'id' => 'follows_hidden',
    )
  );
  //if (sizeof($uids) == 1) {
    $form['follows_subscribed_hidden'] = array(
      '#type' => 'hidden',
      '#attributes' => array(
        'id' => 'follows_subscribed_hidden',
      )
    );
  //}

  $form['follows_plus_div'] = array(
    '#access' => user_access('administer users'),
    '#type' => 'item' ,
    '#prefix' => '<label>' . t('Follows+:') . '</label>',
    '#markup' => '',

  );
  $form['follows_plus_hidden'] = array(
    '#type' => 'hidden',
    '#attributes' => array(
      'id' => 'follows_plus_hidden',
    )
  );

  $form['follows_plus_plus_div'] = array(
    '#access' => user_access('administer users'),
    '#type' => 'item' ,
    '#prefix' => '<label>' . t('Follows++:') . '</label>',
    '#markup' => '',

  );
  $form['follows_plus_plus_hidden'] = array(
    '#type' => 'hidden',
    '#attributes' => array(
      'id' => 'follows_plus_plus_hidden',
    )
  );
  $form[] = array(
    '#markup' => '</div >',//<div class="select-committee">
  );

  $shared_all_user_committee = array();

  if ($uids) {
    $com_terms = os2dagsorden_settings_get_active_committees();
    $com_select = array();
    foreach ($com_terms as $com_term) {
      // Display term short name if possible.
      if ($short_name = field_get_items('taxonomy_term', $com_term, 'field_os2web_meetings_com_shname')) {
        $term_name = $short_name[0]['value'];
      }
      else {
        $term_name = $com_term->name;
      }
      $com_select[$com_term->tid] = $term_name;
    }
    $shared_member_of = array();
    $shared_follows = array();
    $shared_follows_subscribed = array();
    $shared_follows_plus = array();
    $shared_follows_plus_plus = array();
    foreach ($uids as $uid) {
      $user = user_load($uid);

      //member of
      if (field_get_items('user', $user, 'field_user_committee')) {
        $user_member_of_field = field_get_items('user', $user, 'field_user_committee');
        $user_member_of_field = os2dagsorden_content_modify_asort($user_member_of_field);
        foreach ($user_member_of_field as $member_of) {
          if (isset($com_select[$member_of['tid']])) {
            $shared_member_of[$member_of['tid']]++;
            $shared_all_user_committee[$member_of['tid']]++;
          }
        }
      }
      //follows
      if (field_get_items('user', $user, 'field_follows_committee')) {
        $user_follows_field = field_get_items('user', $user, 'field_follows_committee');
        $user_follows_field = os2dagsorden_content_modify_asort($user_follows_field);
        foreach ($user_follows_field as $follows) {
          if (isset($com_select[$follows['tid']])) {
            $shared_follows[$follows['tid']]++;
            $shared_all_user_committee[$follows['tid']]++;
          }
        }
      }


      //follows subscribed, only for single user edit
      if (field_get_items('user', $user, 'field_follows_committee_subsc')) {
        $user_follows_subscribed_field = field_get_items('user', $user, 'field_follows_committee_subsc');
        foreach ($user_follows_subscribed_field as $follows_subs) {
          if (isset($com_select[$follows_subs['tid']])) {
            $shared_follows_subscribed[$follows_subs['tid']]++;
          }
        }
      }
      //follows plus
      if (field_get_items('user', $user, 'field_follows_committee_plus')) {
        $user_follows_plus_field = field_get_items('user', $user, 'field_follows_committee_plus');
        $user_follows_plus_field = os2dagsorden_content_modify_asort($user_follows_plus_field);

        foreach ($user_follows_plus_field as $follows_plus) {
          if (isset($com_select[$follows_plus['tid']])) {
            $shared_follows_plus[$follows_plus['tid']]++;
            $shared_all_user_committee[$follows_plus['tid']]++;
          }
        }
      }

      //follows plus plus
      if (field_get_items('user', $user, 'field_follows_committee_pp')) {
        $user_follows_plus_plus_field = field_get_items('user', $user, 'field_follows_committee_pp');
        $user_follows_plus_plus_field = os2dagsorden_content_modify_asort($user_follows_plus_plus_field);
        foreach ($user_follows_plus_plus_field as $follows_plus_plus) {
          if (isset($com_select[$follows_plus_plus['tid']])) {
            $shared_follows_plus_plus[$follows_plus_plus['tid']]++;
            $shared_all_user_committee[$follows_plus_plus['tid']]++;
          }
        }
      }
    }

    //printing member of
    $content = "<ul id='member_of' class='droptrue'>";
    foreach ($shared_member_of as $tid => $count) {
      if ($count == count($uids)) {
        $form['member_of_hidden']['#value'] .= $tid . ',';
        $content .= "<li id='{$tid}' class='ui-state-default'><span>{$com_select[$tid]}</span><input id='checkbox_$tid' type='checkbox' class='checkbox'></li>";
      }
    }
    $content .= '</ul>';
    $form['member_of_div']['#markup'] = $content;

    //printing follows
    $content = "<ul id='follows' class='droptrue'>";
    foreach ($shared_follows as $tid => $count) {
      if ($count == count($uids)) {
        $form['follows_hidden']['#value'] .= $tid . ',';

        //setting correct follows subscribed marker
        //if (sizeof($uids) == 1) {
          $subscribed_class = 'can-subscribe';
          if (count($uids) == $shared_follows_subscribed[$tid]) {
            $subscribed_class .= ' subscribed';
            $form['follows_subscribed_hidden']['#value'] .= $tid . ',';
            $check_id = $tid;
          }
        //}
        if ($check_id == $tid){
          $content .= "<li id='{$tid}' class='ui-state-default {$subscribed_class}'><span>{$com_select[$tid]}</span><input id='checkbox_$tid' type='checkbox' class='checkbox_follows' checked='checked' ></li>";
        }else{
          $content .= "<li id='{$tid}' class='ui-state-default {$subscribed_class}'><span>{$com_select[$tid]}</span><input id='checkbox_$tid' type='checkbox' class='checkbox_follows'></li>";
        }
      }
    }
    $content .= '</ul>';
    $form['follows_div']['#markup'] = $content;

    //printing follows plus
    $content = "<ul id='follows_plus' class='droptrue'>";
    foreach ($shared_follows_plus as $tid => $count) {
      if ($count == count($uids)) {
        $form['follows_plus_hidden']['#value'] .= $tid . ',';
        $content .= "<li id='{$tid}' class='ui-state-default'><span>{$com_select[$tid]}</span><input id='checkbox_$tid' type='checkbox' class='checkbox'></li>";
      }
    }
    $content .= '</ul>';
    $form['follows_plus_div']['#markup'] = $content;

    //printing follows plus plus
    $content = "<ul id='follows_plus_plus' class='droptrue'>";
    foreach ($shared_follows_plus_plus as $tid => $count) {
      if ($count == count($uids)) {
        $form['follows_plus_plus_hidden']['#value'] .= $tid . ',';
        $content .= "<li id='{$tid}' class='ui-state-default'><span>{$com_select[$tid]}</span><input id='checkbox_$tid' type='checkbox' class='checkbox'></li>";
      }
    }
    $content .= '</ul>';
    $form['follows_plus_plus_div']['#markup'] = $content;

    //printing arrows reverse
    $form[]['#markup'] =
      '<div class="arrows-reverse">
      <img src = "' . base_path() . drupal_get_path('theme', 'os2dagsorden_theme') . '/img/img_arrows_reverse.png">
      </div>';

    //printing available committees
    $com_list = "<ul id='available_committee' class='droptrue'>";
    asort($com_select);
    foreach ($com_select as $tid=>$com_term) {
      //if the committee actually available?
      if ($shared_all_user_committee[$tid] < count($uids)) {
        $com_list  .= "<li id='{$tid}' class='ui-state-default'><span>{$com_term}</span><input id='checkbox_$tid'  type='checkbox' class='checkbox'></li>";
      }
    }
    $com_list .= "</ul>";
    $form['available_committee'] = array(
      '#type' => 'item' ,
      '#prefix' => "<div class='available_committee'><label>" . t('Available committee') . ":</label>",
      '#markup' => $com_list,
      '#suffix' => '</div>'
    );
    $form[] = array(
      '#markup' => '<div style="clear:both"></div>',
    );
  }
}

/**
 * Prefills the form with the user information, loads everything except the committees preferences
 *
 * @param $form mixed the form
 * @param $uid  int   single uid
 */
function _os2dagsorden_conten_modify_load_user_fields(&$form, $uid) {
  //saving for usage in the submit function
  $form['uid'] = array(
    '#type' => 'value',
    '#value' => $uid,
  );
  $user = user_load($uid);

  //filling the fields
  if (field_get_items('user', $user, 'field_user_full_name') ){
    $full_name_field = array_pop(field_get_items('user', $user, 'field_user_full_name'));
    $form['full_name']['#default_value'] = $full_name_field['value'];
  }
  if (field_get_items('user', $user, 'field_user_organization') ){
    $organization_field = array_pop(field_get_items('user', $user, 'field_user_organization'));
    $form['organization']['#default_value'] = $organization_field['value'];
  }


  if (field_get_items('user', $user, 'field_user_can_send_closed_bp')){
    $user_can_send_closed_bp = array_pop(field_get_items('user', $user, 'field_user_can_send_closed_bp'));
    $form['user_can_send_closed_bp']['#default_value'] = $user_can_send_closed_bp['value'];
  }

  if (field_get_items('user', $user, 'field_user_forrbidden_categories')) {
    $forrbidden_cats_field = field_get_items('user', $user, 'field_user_forrbidden_categories');
    $selection = array();

    foreach ($forrbidden_cats_field as $forrbidden_cat) {
      $selection[] = $forrbidden_cat['value'];
    };
    $form['forbidden_cat']['#default_value'] = $selection;
    $options = $form['calendar_pref']['#options'];
    foreach ($selection as $forbidden_cat){
      unset($options[$forbidden_cat]);
    }
    $form['calendar_pref']['#options'] = $options;
  }

  if (field_get_items('user', $user, 'field_user_meetings_category')) {
    $calendar_prefs_field = field_get_items('user', $user, 'field_user_meetings_category');
    $selection = array();
    foreach ($calendar_prefs_field as $cal_pref) {
      $selection[]=$cal_pref['value'];
    }

    $form['calendar_pref']['#default_value'] = $selection;
  }

  $form['user_roles']['#default_value'] = $user->roles;
}

/**
 * Submit for user edit form. Updates user profile.
 *
 * @param $form       mixed the form
 * @param $form_state mixed state of the form
 *
 * @return none
 */
function os2dagsorden_content_modify_user_submit($form, $form_state) {
  $input = $form_state['input'];

  //input extraction
  extract($input);

  $follows = explode(',', $follows_hidden);
  $follows_subscribed = explode(',', $follows_subscribed_hidden);
  $member_of = explode(',', $member_of_hidden);
  $follows_plus = explode(',', $follows_plus_hidden);
  $follows_plus_plus = explode(',', $follows_plus_plus_hidden);

  $user = user_load($form_state['values']['uid']);
  $user->field_user_full_name['und'][0]['value'] = $full_name;
  $user->field_user_organization['und'][0]['value'] = $organization;
  $user->field_user_can_send_closed_bp['und'][0]['value'] = $user_can_send_closed_bp;

  //unsetting follows committees
  $user->field_follows_committee['und'] = array();
  if ($follows) {
    foreach ($follows as $tid) {
      if (!empty($tid))
        $user->field_follows_committee['und'][]['tid'] = $tid;
    }
  }

  //unsetting follows subscribed committees only on desktop devices
  $user->field_follows_committee_subsc['und'] = array();
  if ($follows_subscribed) {
    foreach ($follows_subscribed as $tid) {
      if (!empty($tid))
        $user->field_follows_committee_subsc['und'][]['tid'] = $tid;
    }
  }

  //unsetting calendar preferences
  $user->field_user_meetings_category['und'] = array();
  if (isset($calendar_pref)) {
    foreach ($calendar_pref as $cal_pref) {
      if (isset($forbidden_cat)){
        if (!in_array($cal_pref, $forbidden_cat))
          $user->field_user_meetings_category['und'][]['value'] = $cal_pref;
      }
      else
        $user->field_user_meetings_category['und'][]['value'] = $cal_pref;
    }
  }

  if (user_access('administer users')){//only for the full form submit
    //unsetting positions
    $user->field_user_positions['und'] = array();
    if ($user_pos) {
      foreach ($user_pos as $tid) {
        $user->field_user_positions['und'][]['tid'] = $tid;
      }
    }

    //unsetting calendar preferences
    $user->field_user_forrbidden_categories['und'] = array();
    foreach ($forbidden_cat as $f_cat){
      $user->field_user_forrbidden_categories['und'][]['value'] = $f_cat;
    }
    //unsetting committees
    $user->field_user_committee['und'] = array();
    if ($member_of) {
      foreach ($member_of as $tid) {
        if (!empty($tid))
          $user->field_user_committee['und'][]['tid'] = $tid;
      }
    }

    //unsetting follows plus committees
    $user->field_follows_committee_plus['und'] = array();
    if ($follows_plus) {
      foreach ($follows_plus as $tid) {
        if (!empty($tid))
          $user->field_follows_committee_plus['und'][]['tid'] = $tid;
      }
    }

    //unsetting follows ++ committees
    $user->field_follows_committee_pp['und'] = array();
    if ($follows_plus_plus) {
      foreach ($follows_plus_plus as $tid) {
        if (!empty($tid))
          $user->field_follows_committee_pp['und'][]['tid'] = $tid;
      }
    }

    //os2dagsorden limited role
    $user_roles_saved = $user->roles;

    //os2dagsorden admin role
    if(user_access('administer os2web')){
      if (!$user_roles['administrator++']){
        if (($key = array_search('administrator++', $user_roles_saved)) !== false) {
          unset($user_roles_saved[$key]);
        }
      } else {
        if ((array_search('administrator++', $user_roles_saved)) === false) {
          $rid = user_role_load_by_name('administrator++')->rid;
          $user_roles_saved[$rid] = 'administrator++';
        }
      }
    }
    if (!$user_roles['os2dagsorden limited']){
      if (($key = array_search('os2dagsorden limited', $user_roles_saved)) !== false) {
        unset($user_roles_saved[$key]);
      }
    } else {
      if ((array_search('os2dagsorden limited', $user_roles_saved)) === false) {
        $rid = user_role_load_by_name('os2dagsorden limited')->rid;
        $user_roles_saved[$rid] = 'os2dagsorden limited';
      }
    }

    if (!$user_roles['administrator+']){
      if (($key = array_search('administrator+', $user_roles_saved)) !== false) {
        unset($user_roles_saved[$key]);
      }
    } else {
      if ((array_search('administrator+', $user_roles_saved)) === false) {
        $rid = user_role_load_by_name('administrator+')->rid;
        $user_roles_saved[$rid] = 'administrator+';
      }
    }
    $user->roles = $user_roles_saved;
  }

  user_save($user);
  drupal_set_message(t('Dine ændringer er blevet gemt'));
}

/**
 * Sorting terms alphabetically based on field_os2web_meetings_com_shname
 *
 * @param array $term_list
 * @return array
 */
function os2dagsorden_content_modify_asort($term_list = array()) {
  $new_array = array();
  $return_array = array();
  if ($term_list) {
    foreach ($term_list as $tid) {
      if ($term = taxonomy_term_load($tid['tid'])) {
        if ($short_name = field_get_items('taxonomy_term', $term, 'field_os2web_meetings_com_shname')) {
          $term_name = $short_name[0]['value'];
        }
        else {
          $term_name = $term->name;
        }
        $new_array[$tid['tid']] = $term_name;
      }
    }
    asort($new_array);

    foreach ($new_array as $tid => $name) {
      $return_array[] = array('tid' => $tid);
    }
  }
  return $return_array;
}
