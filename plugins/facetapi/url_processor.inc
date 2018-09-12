<?php
  
  
module_load_include ('inc', 'facetapi_pretty_paths', 'plugins/facetapi/url_processor_pretty_paths');
  
  
class FacetapiUrlProcessorCfb extends FacetapiUrlProcessorPrettyPaths {
   
  public function getFacetPath (array $facet, array $values, $active) {
    
    // Move all url processing to the form submit.
    //
    // @see FacetapitUrlProcessorCfbPath '/includes/FacetapiUrlProcessorCfbPath.inc'
    // @see cbf_form_submit
    //
    $facetValues = new FacetapiUrlProcessorCfbPath ($this, $facet, $values, $active);
    
    // Get the alias for the segment and store it by the path.
    $alias = $this->getFacetPrettyPathsAlias ($facet);    
    
    // Trick the url_is_external() function by actually returning the url,
    // set by the parent. This will be used as the k
    //
    $path = parent::getFacetPath ($facet, $values, $active);
    
    // Store the values in a static function to be retieved by the path.
    self::getFacetValues ($path, $facetValues);
    self::getAliasValue ($path, $alias);
    
    // Trick the url_is_external() function by actually returning the url,
    // set by the parent. This will be used as the key when reaccessing the
    // values from the cbf_form_submit() function.
    //
    // @see cbf_form_submit
    //
    return $path;
    
  }
 
  // Helper to store the values from the getFacetPath method to be accessed later. 
  public static function getFacetValues ($path, $set = false) {
    $vals = &drupal_static(__FUNCTION__);
    if (!isset ($vals)) {
      $vals = [];
    }
    
    if (!isset ($vals[$path]) && $set && is_object ($set) && $set instanceof FacetapiUrlProcessorCfbPath) {
      $vals[$path] = $set;
      return $set;
    }
    else if (isset ($vals[$path])) {
      return $vals[$path];
    }

    return null;
    
  }
  
  // Helper to store the value from the getFacetPrettyPathsAlias method to be accessed later. 
  public static function getAliasValue ($path, $set = false) {
    $vals = &drupal_static(__FUNCTION__);
    if (!isset ($vals)) {
      $vals = [];
    }
    
    if (!isset ($vals[$path]) && $set && is_string ($set)) {
      $vals[$path] = $set;
      return $set;
    }
    else if (isset ($vals[$path])) {
      return $vals[$path];
    }

    return null;
    
  }
  
  // Helper function to return the needed segment path.
  public function getPathSegmentAlias ($facet, $value) {
    return parent::getPathSegment($facet, $value);
  }
  
  // Helper function return the path segments.
  public function getPathSegments () {
    return $this->pathSegments;
  }
  
}


