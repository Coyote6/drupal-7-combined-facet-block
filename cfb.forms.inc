<?php
  
  
function cbf_form ($form, &$form_state) {
  
  // Get our build info.
  $args = [];
  $builds = [];
  if (isset ($form_state['build_info']['args'])) {
    $args = $form_state['build_info']['args'];
    if (isset ($args[0])) {
      $builds = $args[0];
    }
  }

  foreach ($builds as $k => $v) {
    $form[$k] = $v['item'];
  }
  
  $form['submit'] = [
    '#type' => 'submit',
    '#value' => 'Filter',
  ];
  
  return $form;
  
}

function cbf_form_submit ($form, &$form_state) {
  
  // Get our build info.
  $args = [];
  $builds = [];
  if (isset ($form_state['build_info']['args'])) {
    $args = $form_state['build_info']['args'];
    if (isset ($args[0])) {
      $builds = $args[0];
    }
  }
  
  $segments = [];
  $cbf_widgets = [];
  $url_processor = null;
  
  // Remove all the select element's #options from the current list of facets,
  // and add back only the ones that were submitted with the form.
  //
  foreach ($builds as $k => $v) {
    if (isset ($v['item']) && isset ($v['item']['#type']) && $v['item']['#type'] == 'select' && isset ($v['item']['#paths']) && isset ($v['item']['#alias']) && isset ($v['item']['#url_processor'])) {
      $cbf_widgets[] = $v['item']['#alias'];
      $item_paths = $v['item']['#paths'];
      $url_processor = $v['item']['#url_processor'];
      if (isset ($form_state['values'][$k])) {
        $select_vals = $form_state['values'][$k];
        foreach ($select_vals as $sk => $sv) {
          if ($sk == $sv && isset ($item_paths[$sk])) {
            $item_path = $item_paths[$sk];
            $processor_values = FacetapiUrlProcessorCfb::getFacetValues ($item_path);
            if (is_object ($processor_values) && $processor_values instanceof FacetapiUrlProcessorCfbPath) {

              $url_processor = $processor_values->urlProcessor;
              $facet = $processor_values->facet;
              $values = $processor_values->values;
              $active = $processor_values->active;
              
              // Adds to segments if inactive, removes if active.
              foreach ($values as $value) {
                $segments[] = $url_processor->getPathSegmentAlias($facet, $value);
              }
                              
            }
          }
        }
      }
     
       
    }
  }
    
  // Redirect to the new URL if the processor is set.
  if (!is_null ($url_processor)) {
    
    // Allow for other facets to function.
    //
    // Get the original segments.
    // Remove any that are a combo widget.
    // Add them to the current segments.
    //
    $orig = $url_processor->getPathSegments();
    foreach ($orig as $k => $v) {
      if (in_array ($v['alias'], $cbf_widgets)) {
        unset ($orig[$k]);
      }
    }
    $segments += $orig;
    
    // Construct the path and redirect.
    $path = $url_processor->constructPath($segments);
    $form_state['redirect'] = $path;
    
  }

}

