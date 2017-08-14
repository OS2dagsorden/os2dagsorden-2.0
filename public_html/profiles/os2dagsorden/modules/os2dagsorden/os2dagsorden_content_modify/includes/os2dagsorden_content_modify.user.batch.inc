<?php

/**
 * Generates multiple users edit form, limited to committees manipulating only.
 *
 * @param $form       mixed the form
 * @param $form_state mixed the state of the form
 * @param $uids       array the array of uid of users to modify
 *
 * @return form
 */
function os2dagsorden_content_modify_user_batch_edit_form($form, $form_state, $uids) {
  $form['uids'] = array(
    '#type' => 'value',
    '#value' => $uids,
  );

  $form[] = array(
    '#markup' => '<div class="node clearfix">',
  );

  $form[] = array(
    '#markup' => '<div class="form-item"><b>' . t('Batch editing users') . '</b>',
  );
  foreach (explode(',', $uids) as $uid) {
    $batchEditUser = user_load($uid);
    if ($batchEditUser) {
      $form[] = array(
        '#markup' => '<li>' . $batchEditUser->name,
      );
    }
  }
  $form[] = array(
    '#markup' => '</div>',
  );
   $form[] = array(
    '#markup' => '<div class="form-item"><b>' . t('Træk udvalg fra kassen under Mulige udvalg til Følger-kassen.') . '</b></div>',
  );
  if (!os2dagsorden_access_helper_is_touch()) {

    _os2dagsorden_content_modify_render_drag_and_drop_remove_committees_controls($form);
    
   //render drag and drop functionality
    _os2dagsorden_content_modify_render_drag_and_drop_controls($form, explode(',', $uids));
    
    

  } else {
    //fallback to default controls
    _os2dagsorden_content_modify_render_default_controls($form, explode(',', $uids));
  }

  $form['save_user'] = array(
    '#type' => 'submit',
    '#attributes' => array(
      'class' => array('form-save-submit'),
    ),
    '#value' => t('Save User'),
    '#submit' => array('os2dagsorden_content_modify_user_batch_submit'),
  );

  $form[] = array(
    '#markup' => '</div>',
  );

  return $form;
}

/**
 * Renders the drag and drop controls for add/remove committee functionality
 * @param $form
 */
function _os2dagsorden_content_modify_render_drag_and_drop_remove_committees_controls(&$form) {
  $form[] = array(
    '#markup' => '<div class="remove-committee">',
  );

  $form['remove_com_div'] = array(
    '#access' => user_access('administer users'),
    '#type' => 'item',
    '#prefix' => '<label>' . t('Remove committees:') . '</label>',
    '#markup' => '<ul id="remove_com" class="droptrue"></ul>',
  );
  $form['remove_com_hidden'] = array(
    '#type' => 'hidden',
    '#attributes' => array(
      'id' => 'remove_com_hidden',
    )
  );

  $form[] = array(
    '#markup' => "</div>", //<div class="select-committee">
  );

  $form[] = array(
    '#markup' => '<div style="clear:both"></div>',
  );
}

/**
 * Submit for user bach form. Updates user profiles.
 *
 * @param $form       mixed the form
 * @param $form_state mixed state of the form
 *
 * @return none
 */
function os2dagsorden_content_modify_user_batch_submit($form, $form_state) {
  $input = $form_state['input'];

  //input extraction
  extract($input);

  if (!$member_of) {
    $member_of = array();
  }
  if (!$follows) {
    $follows = array();
  }
  if (!$follows_plus) {
    $follows_plus = array();
  }
  if (!$follows_plus_plus) {
    $follows_plus_plus = array();
  }
  if (!$remove_committees) {
    $remove_committees = array();
  }
  if (!$follows_subscribed) {
    $follows_subscribed = array();
  }

  if (!os2dagsorden_access_helper_is_touch()) {
    $follows = explode(',', $follows_hidden);
    $member_of = explode(',', $member_of_hidden);
    $follows_plus = explode(',', $follows_plus_hidden);
    $follows_plus_plus = explode(',', $follows_plus_plus_hidden);
    $remove_committees = explode(',', $remove_com_hidden);
    $follows_subscribed = explode(',', $follows_subscribed_hidden);
  }

  $uids = explode(',', $form_state['values']['uids']);
  foreach ($uids as $uid) {
    $user = user_load($uid);

    //user committees
    if (is_array($member_of)) {
      $existing_tids = os2dagsorden_access_helper_get_user_member_of_committees($uid);

      $user->field_user_committee['und'] = array();
      //readding existing tids, if not removed, and not added to any other box
      foreach ($existing_tids as $tid) {

        if (!in_array($tid, $remove_committees) && !in_array($tid, array_merge($follows, $follows_plus, $follows_plus_plus))) {
          $user->field_user_committee['und'][]['tid'] = $tid;
        }
      }

      //newly added committes
      foreach ($member_of as $tid) {
        if (!empty($tid) && !in_array($tid, $existing_tids) && !in_array($tid, $remove_committees)) {
          $user->field_user_committee['und'][]['tid'] = $tid;
        }
      }
    }

    //user follows committees
    if (is_array($follows)) {
      $existing_tids = os2dagsorden_access_helper_get_user_follow_committees($uid);
      $existing_follow_subscribed_tids = os2dagsorden_access_helper_get_user_follow_subscribed_committees($uid);

      $user->field_follows_committee['und'] = array();
      $user->field_follows_committee_subsc['und'] = array();
      //readding existing tids, if not removed, and not added to any other box
      foreach ($existing_tids as $tid) {
        if (!in_array($tid, $remove_committees) && !in_array($tid, array_merge($member_of, $follows_plus, $follows_plus_plus))) {
          $user->field_follows_committee['und'][]['tid'] = $tid;

          if (!empty($follows_subscribed) && in_array($tid, $follows_subscribed)) {
            $user->field_follows_committee_subsc['und'][]['tid'] = $tid;
          }
        }
      }

      //newly added committes
      foreach ($follows as $tid) {
        if (!empty($tid) && !in_array($tid, $existing_tids) && !in_array($tid, $remove_committees)) {
          $user->field_follows_committee['und'][]['tid'] = $tid;
          if (!empty($follows_subscribed) && in_array($tid, $follows_subscribed)) {
            $user->field_follows_committee_subsc['und'][]['tid'] = $tid;
          }
        }
      }
    }

    //user follows plus committees
    if (is_array($follows_plus)) {
      $existing_tids = os2dagsorden_access_helper_get_user_follow_plus_committees($uid);

      $user->field_follows_committee_plus['und'] = array();
      //readding existing tids, if not removed, and not added to any other box
      foreach ($existing_tids as $tid) {
        if (!in_array($tid, $remove_committees) && !in_array($tid, array_merge($member_of, $follows, $follows_plus_plus))) {
          $user->field_follows_committee_plus['und'][]['tid'] = $tid;
        }
      }

      //newly added committes
      foreach ($follows_plus as $tid) {
        if (!empty($tid) && !in_array($tid, $existing_tids) && !in_array($tid, $remove_committees)) {
          $user->field_follows_committee_plus['und'][]['tid'] = $tid;
        }
      }
    }

    //user follows ++ committees
    if (is_array($follows_plus_plus)) {
      $existing_tids = os2dagsorden_access_helper_get_user_follow_pp_committees($uid);

      $user->field_follows_committee_pp['und'] = array();
      //readding existing tids, if not removed, and not added to any other box
      foreach ($existing_tids as $tid) {
        if (!in_array($tid, $remove_committees) && !in_array($tid, array_merge($member_of, $follows, $follows_plus))) {
          $user->field_follows_committee_pp['und'][]['tid'] = $tid;
        }
      }

      //newly added committes
      foreach ($follows_plus_plus as $tid) {
        if (!empty($tid) && !in_array($tid, $existing_tids) && !in_array($tid, $remove_committees)) {
          $user->field_follows_committee_pp['und'][]['tid'] = $tid;
        }
      }
    }

    user_save($user);
  }

  drupal_set_message(t('Dine ændringer er blevet gemt til @count bruger', array('@count' => count($uids))));
}