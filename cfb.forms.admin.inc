<?php
  
  
function cfb_config_form ($form, &$form_state) {
 
  $order = _cfb_get_var ('cfb_order');
  
  $searcher = 'search_api@candidate_search';
  $realm = 'combo'; 
  
  // Get the facets.
  $adapter = facetapi_adapter_load ($searcher);
  $facets = $adapter->getEnabledFacets($realm);
  
  $weight = count ($order);
  
  // Add any new facets.
  foreach ($facets as $id => $f) {
    if (!isset ($order[$id])) {
      $weight++;
      $order[$id] = [
        'id' => $id,
        'name' => $f['label'],
        'weight' => $weight
      ];
    }
  }
  
  // Remove any old facets.
  foreach ($order as $id => $o) {
    if (!isset ($facets[$id])) {
      unset ($order[$id]);
    }
  } 
   
  $form_state['storage'] = [
    'cfb' => $order
  ];
  
  $form['#tree'] = TRUE;
  foreach ($order as $id => $o) {

    $form['order'][$o['id']]['id'] = [
      '#type' => 'hidden',
      '#default_value' => $o['id'],
    ];
    $form['order'][$o['id']]['name'] = [
      '#type' => 'markup',
      '#markup' => $o['name'],
    ];
    $form['order'][$o['id']]['weight'] = [
      '#type' => 'weight',
      '#title' => t('Weight'),
      '#title_display' => 'invisible',
      '#default_value' => $o['weight'],
    ];
    
  }
  
  $form['submit'] = [
    '#type' => 'submit', 
    '#value' => t('Save changes')
  ];
  
	return $form;

}


function cfb_config_form_submit ($form, &$form_state) {

  $orders = [];
  if (isset ($form_state['storage']) && isset ($form_state['storage']['cfb'])) {
    $orders = $form_state['storage']['cfb'];
  }
  
  $order = [];
  
  foreach ($form_state['values']['order'] as $o) {
    
    $name = $orders[$o['id']]['name'];
    $order[$o['id']] = [
      'id' => $o['id'],
      'name' => $name,
      'weight' => $o['weight']
    ];
    
  }
  
  if (!empty ($order)) {
    usort ($order, '_cfb_arraysort');
  }
  
  // Add the id back to the order.
  $new_order = [];
  foreach ($order as $o) {
    $new_order[$o['id']] = $o;
  }
  
  variable_set ('cfb_order', $new_order);
  drupal_set_message (t ('The order has been saved.'));
  
}


// Custom array sort function by weight.
function _cfb_arraysort ($a, $b) {
  if (isset($a['weight']) && isset($b['weight'])) {
    return $a['weight'] < $b['weight'] ? -1 : 1;
  }
  return 0;
}
