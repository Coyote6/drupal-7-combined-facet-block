<?php

// Configs
define ('CFB_PATH', drupal_get_path ('module', 'cfb'));


// Get additional includes.
module_load_include ('inc', 'cfb', 'includes/FacetapiUrlProcessorCfbPath');
module_load_include ('inc', 'cfb', 'plugins/facetapi/widget');
module_load_include ('inc', 'cfb', 'plugins/facetapi/url_processor');
module_load_include ('inc', 'cfb', 'cfb.forms.admin');
module_load_include ('inc', 'cfb', 'cfb.forms');
module_load_include ('inc', 'cfb', 'cfb.facetapi');
module_load_include ('inc', 'cfb', 'cfb.blocks');


function _cfb_variables () {
	
	$vars = [
		'cfb_order' => []
	];
	return $vars;
	
}

function _cfb_get_var ($name) {

	$vars = _cfb_variables();
	$def = null;
	if (isset ($vars[$name])) {
		$def = $vars[$name];
	}	
	return variable_get ($name, $def);
	
}
