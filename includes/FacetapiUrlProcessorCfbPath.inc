<?php
  
  
class FacetapiUrlProcessorCfbPath {
  
  public $urlProcessor;
  public $facet;
  public $values;
  public $active;
  
  public function __construct ($urlProcessor, $facet, $values, $active) {
    $this->urlProcessor = $urlProcessor;
    $this->facet = $facet;
    $this->values = $values;
    $this->active = $active;
  }
  
}