<?php

/**
 * Implementation of hook_features_export_options. [component_hook]
 *
 * This hook will alert features of which specific items of this component may
 * be exported. For instances, in this case, we want to make available all the
 * existing items.  If there are no items to be exported, this component will
 * not be made available in the features export page.
 *
 * @return array
 *   A keyed array of items, suitable for use with a FormAPI select or
 *   checkboxes element.
 */
function views_restful_client_config_features_export_options() {
  $options = array();
  $result = views_restful_client_load_all();
  foreach ($result as $record) {
    $options[$record->nid] = $record->name;
  }
  return $options;
}

/**
 * Implementation of hook_features_export [component hook]
 *
 * This is a component hook, rather then a module hook, therefore this is the
 * callback from hook_features_api which relates to the specific component we
 * are looking to export. When a specific instance of the component we are
 * looking to export is selected, this will include the necessariy item, plus
 * any dependencies into our export array.
 *
 * @param array $data
 * this is the machine name for the component in question
 * @param array &$export
 * array of all components to be exported
 * @param string $module_name
 * The name of the feature module to be generated.
 * @return array
 * The pipe array of further processors that should be called
 */
function views_restful_client_config_features_export($data, &$export, $module_name) {
//we have module dependencies in order for this module to function properly
//so we'll add them here
  $export['dependencies']['views_restful_client'] = 'views_restful_client';

// The following is the simplest implementation of a straight object export
// with no further export processors called.
  foreach ($data as $component) {
    $export['features']['views_restful_client_config'][$component] = $component;
  }
  return array();
}


/**
 * Implementation of hook_features_export_render. [component hook]
 *
 * This hook will be invoked in order to export
 * Component hook. The hook should be implemented using the name ot the
 * component, not the module, eg. [component]_features_export() rather than
 * [module]_features_export().
 *
 * Render one or more component objects to code.
 *
 * @param string $module_name
 *   The name of the feature module to be exported.
 * @param array $data
 *   An array of machine name identifiers for the objects to be rendered.
 * @param array $export
 *   The full export array of the current feature being exported. This is only
 *   passed when hook_features_export_render() is invoked for an actual feature
 *   update or recreate, not during state checks or other operations.
 * @return array
 *   An associative array of rendered PHP code where the key is the name of the
 *   hook that should wrap the PHP code. The hook should not include the name
 *   of the module, e.g. the key for `hook_example` should simply be `example`.
 */
function views_restful_client_config_features_export_render($module_name, $data, $export = NULL) {
  $code = array();
  $code[] = '$mycomponents = array();';
  foreach ($data as $clientId) {
    $code[] = "  \$mycomponents['{$clientId}'] = " . features_var_export((array)views_restful_client_load_record($clientId)) .";";
  }
  $code[] = "return \$mycomponents;";
  $code = implode("\n", $code);
  return array('views_restful_client_config_features_default_settings' => $code);
}



/**
* Implementation of hook_features_rebuild(). [component_hook]
*/
function views_restful_client_config_features_rebuild($module) {
  $mycomponents = module_invoke($module, 'views_restful_client_config_features_default_settings');
  //loop over the items we need to recreate
  if (!empty($mycomponents)) {
    foreach ($mycomponents as $mycomponent) {
      views_restful_client_save_record(json_decode(json_encode($mycomponent)));
    }
  }
}


/**
 * Implementation of hook_features_revert(). [component_hook]
 */
function views_restful_client_config_features_revert($module) {
  views_restful_client_config_features_rebuild($module);
}