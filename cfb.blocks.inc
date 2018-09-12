<?php

function cfb_block_info() {

	$info = [
  	'combo-facet' => [
    	'info' => 'Combined Facet',
  		'cache' => DRUPAL_NO_CACHE
  	]
	];
  return $info;
	
}


function cfb_block_view ($delta = '') {
  $searcher = 'search_api@candidate_search';
  $realm = 'combo';  
  $build_realm = facetapi_build_realm ($searcher, $realm); 
  $builds = [];
  $order = _cfb_get_var ('cfb_order');
  
  foreach ($order as $k => $o) {
    if (isset ($build_realm[$k])) {
      $v = $build_realm[$k];
      if (isset ($v[$k])) {
        $f = $v[$k];
        if (isset ($f['submit'])) {
          unset ($f['submit']);
        }
        $v[$k] = $f;
      }
      
      $item = '';
      if (isset ($v[$k])) {
        $item = $v[$k];
      }
      $builds[$k] = [
        'title' => $v['#title'],
        'item' => $item
      ];
    }
    
  }
  
  $form = drupal_get_form('cbf_form', $builds);
  $html = drupal_render ($form);
  
  
  // Returns the subject and content of the block.
  $block = [
   'subject' => 'Filters',
   'content' => $html
  ];
    
  return $block;
}