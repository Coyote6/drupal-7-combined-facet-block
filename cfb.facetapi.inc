<?php
  
  
function cfb_facetapi_realm_info() {
 
  $realms = [];
  $realms['combo'] = [
    'label' => t('Combined Facets'),
    'weight' => -8,
    'default widget' => 'facetapi_links',
    'element type' => 'links',
    'description' => t ('The <em>Combined Facets</em> realm displays facets in a combined <a href="/admin/structure/block?destination=admin/config/development/performance">block</a>. Users are able to refine their searches in a drill-down fashion.'),
    'sortable' => false,
    'soft_limit' => 10
  ];
  return $realms;
  
}


function cfb_facetapi_searcher_info_alter (array &$searcher_info) {
  foreach ($searcher_info as &$info) {
    // Activate pretty paths optionally per searcher, as configured.
    $id = 'facetapi_pretty_paths_searcher_' . $info['name'];
    $info['url processor'] = variable_get($id) ? 'cfb' : 'standard';
    $info['facetapi pretty paths coder'] = 'default';
  }
}


function cfb_facetapi_widgets() {
  $info = [
    'cfb_select' => [
      'handler' => [
        'label' => t('Select (CFB Field)'),
        'class' => 'CfbSelectWidget',
        'query types' => ['term', 'date'],
      ],
    ],
  ];
  return $info;
}


function cfb_facetapi_url_processors() {  
  $info = [
    'cfb' => [
      'handler' => [
        'label' => t('Combined Facet URL Processors'),
        'class' => 'FacetapiUrlProcessorCfb',
      ],
    ],
  ];
  return $info;
}


