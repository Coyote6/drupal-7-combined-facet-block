<?php

module_load_include ('inc', 'facetapi', 'plugins/facetapi/widget');

/**
 * Widget that renders facets as a multiselect element.
 */
class CfbSelectWidget extends FacetapiWidget {
  
  protected $defaults = [];
  protected $paths = [];
  protected $alias = '';
  protected $urlProcessor;

  public function execute() {
    $element = &$this->build[$this->facet['field alias']];
    $this->setup( $element);
    $element = [
      '#type' => 'select',
      '#title' => $this->settings->settings['title'],
      '#multiple' => TRUE,
      '#options' => $this->buildOptions ($element),
      '#attributes' => $this->build['#attributes'],
      '#default_value' => $this->defaults,
      '#paths' => $this->paths,
      '#alias' => $this->alias,
      '#url_processor' => $this->urlProcessor
    ];
  }
  
  function setup ($build) {
    $path = null;
    foreach ($build as $value => $item) {
      $key = $this->getOptionKey($item);
      if (isset ($item['#active']) && $item['#active'] == 1) {
        $this->defaults[] = $key;
      }
      $path = $this->paths[$key] = $item['#path'];
    }
    $this->alias = FacetapiUrlProcessorCfb::getAliasValue ($path);
    $processor_values = FacetapiUrlProcessorCfb::getFacetValues ($path);
    if (is_object ($processor_values) && $processor_values instanceof FacetapiUrlProcessorCfbPath) {
      $this->urlProcessor = $processor_values->urlProcessor;
    }
  }

  
  function buildOptions ($build, $options = [], $depth = 0) {
    $options = [];
    $settings = $this->settings->settings;
    foreach ($build as $value => $item) {
      if (empty($item['#item_children']) || !$settings['optgroups']) {

        $key = $this->getOptionKey($item);
        $markup = $item['#markup'];
  
        if ($settings['add_count']) {
          if (!$settings['remove_count_on_active'] || ($settings['remove_count_on_active'] && !$item['#active'])) {
            $markup .= ' (' . $item['#count'] . ')';
          }
        }
        
        $options[$key] = $markup;
        
        // Prepend the text with a depth indicator.
        if ($depth > 0) {
          $options[$key] = str_repeat('-', $depth) . ' ' . $options[$key];
        }
        // If the current item is active, but if we have selected the "Remove
        // selected" option, remove this items from our array, since we want to
        // hide it.
        if ($item['#active'] && $settings['remove_selected']) {
          unset($options[$key]);
        }

      }
      if ($item['#item_children']) {
        if ($settings['optgroups']) {
          // Recursively add any children of the item to the #options array (this
          // will result in them being placed inside optgroups).
          $options[$item['#markup']] = $this->buildOptions ($item['#item_children']);
        }
        else {
          // Not using optgroups, so put all items at the root level.
          $options = $options + $this->buildOptions($item['#item_children'], $options, $depth + 1);
        }
      }
      
    }
    return $options;
  }
  
  /**
   * Gets the key to use for an item in the select element #options array.
   */
  protected function getOptionKey($item) {
    $settings = $this->settings->settings;
    if ($settings['act_single'] && isset($item['#query']['f'])) {
      return implode('&', $item['#query']['f']);
    }
    // Set the key to the filter that will appear in the URL if this item is
    // selected. We need to do it this way (rather than using $item['#query'])
    // so that multiple selections can be combined together in the form's
    $facet_url = drupal_encode_path($this->facet['field alias']) . ':' . $item['#indexed_value'];
    if (isset($settings['disable_empty']) && $settings['disable_empty'] == 1 && $item['#count'] == 0) {
      // Submit handler. ":disabled" is added for facets with 0 items.
      $facet_url .= ':disabled';
    }
    return $facet_url;
  }
  
  
  /**
   * Overrides FacetapiWidget::settingsForm().
   */
  function settingsForm(&$form, &$form_state) {

    $form['widget']['widget_settings']['cfb'][$this->id]['title'] = [
      '#type' => 'textfield',
      '#title' => t('Display Title'),
      '#default_value' => $this->settings->settings['title'],
      '#description' => t('The title to display over this particular facet in the block form.'),
      '#states' => [
        'visible' => [
          'select[name="widget"]' => ['value' => $this->id],
        ],
      ],
    ];
  }

  /**
   * Overrides FacetapiWidget::getDefaultSettings().
   */
  function getDefaultSettings() {
    $settings = [
      'title' => $this->facet['field alias'],
    ];
    return $settings;
  }
  
}


