<?php

/**
 * https://os2web.atlassian.net/browse/DAGS-330
 * @author: Stanislav Kutasevits, stan@bellcom.dk
 * 
 * This script will loop through all of the committeers taxonomy terms and remove the duplicates in field: field_os2web_meetings_com_subid
 *
 * Example,
 *
 * term before running script:
 * Afsluttede Børnefagligt Forum, field_os2web_meetings_com_subid: [1,2,50,2,1]
 *
 * term after running script:
 * Afsluttede Børnefagligt Forum, field_os2web_meetings_com_subid: [1,2,50]
 **/
$time_start = microtime(true);
print('==========================' . PHP_EOL);
print('Started DAGS-330_clean_committee_duplicate_sub_id.php' . PHP_EOL);
print('==========================' . PHP_EOL);

$vocabulary = taxonomy_vocabulary_machine_name_load('os2web_meetings_tax_committee');
$terms = entity_load('taxonomy_term', FALSE, array('vid' => $vocabulary->vid));
foreach ($terms as $term) {
  if (isset($term->field_os2web_meetings_com_subid['und'])) {
    //putting all subid into one array with subid being the key - ensuring there is no duplicates added
    $new_field_os2web_meetings_com_subid = array();
    foreach ($term->field_os2web_meetings_com_subid['und'] as $sub_id) {
      $new_field_os2web_meetings_com_subid[$sub_id['value']] = array(
        'value' => $sub_id['value']
      );
    }

    //checking if the sizes of list are diffent. If they are different, field had some duplicates before
    if (sizeof($new_field_os2web_meetings_com_subid) < sizeof($term->field_os2web_meetings_com_subid['und'])) {
      print('Found term with duplicates: ' . $term->name . ' [tid: ' . $term->tid . ']' . PHP_EOL);
      print('Current subid list: ' . print_r($term->field_os2web_meetings_com_subid['und'],1));
      $new_field_os2web_meetings_com_subid = array_values($new_field_os2web_meetings_com_subid);
      print('New subid list: ' . print_r($new_field_os2web_meetings_com_subid,1));
      $term->field_os2web_meetings_com_subid['und'] = $new_field_os2web_meetings_com_subid;

      taxonomy_term_save($term);
      print('Term saved: ' . $term->name . ' [tid: ' . $term->tid . ']' . PHP_EOL);
      print('==========================' . PHP_EOL);
    }

  }
}

print('Finished DAGS-330_clean_committee_duplicate_sub_id.php' . PHP_EOL);
print('Total execution time: ' . (microtime(true) - $time_start) . ' seconds' . PHP_EOL);
print('==========================' . PHP_EOL);