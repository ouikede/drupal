<?php

/**
 * Implements hook_views_data().
 */
function views_restful_client_views_data() {
  $data = array();

  $table_name = "views_restful_client";


  $query = db_select($table_name, 'vrc')
          ->fields('vrc', array('nid', 'name', 'description', 'configuration'));
  $result = $query->execute()->fetchAll();
  foreach ($result as $record) {


    $key = $table_name . "_" . $record->nid;
    $table = &$data[$key];
    // Define the group this table and its fields should appear under
    // in the Views administrative interface.
    $table['table']['group'] = t($record->name);

    // Advertise this table as a possible base table. This makes it possible
    // to create a standalone view of "Databasics" entries.
    $table['table']['base'] = array(
        'title' => t($record->name),
        'help' => t($record->description),
        'query class' => 'views_restful_client'
    );


    $config = json_decode($record->configuration);

    $numeric_in_filter = array('handler' => 'views_restful_client_handler_filter_in_numeric');
    $string_in_filter = array('handler' => 'views_restful_client_handler_filter_in_string');
    $numeric_filter = array('handler' => 'views_restful_client_handler_filter_numeric');
    $string_filter = array('handler' => 'views_restful_client_handler_filter_string');
    $date_filter = array('handler' => 'views_restful_client_handler_filter_date');
   
    $numeric_sort = array('handler' => 'views_restful_client_handler_sort_numeric');
    $string_sort = array('handler' => 'views_restful_client_handler_sort_string');
    $date_sort = array('handler' => 'views_restful_client_handler_sort_date');
    
    $simple_field = array('handler' => 'views_restful_client_handler_field', 'click sortable' => TRUE);
    $numeric_field = array('handler' => 'views_restful_client_handler_field_numeric', 'click sortable' => TRUE);
    $date_field = array('handler' => 'views_restful_client_handler_field_date', 'click sortable' => TRUE);
    
    $simple_argument = array('handler' => 'views_restful_client_argument', 'restful_client_id' => $record->nid);
    $date_argument = array('handler' => 'views_restful_client_argument', 'restful_client_id' => $record->nid);

    $hasOptions = FALSE;
    $seperator = (strcmp($config->contenttype, "json") == 0) ? "." : " ";
    foreach ($config->fields as $fieldItem) {   
      $hasOptions = (isset($fieldItem->options) && is_array($fieldItem->options));
      if (isset($fieldItem->type) && (strcmp($fieldItem->type, "numeric") == 0 )) {
        $filter = ($hasOptions) ? $numeric_in_filter : $numeric_filter;
        $sort = $numeric_sort;
        $field_handler = $numeric_field;
        $argument_handler = $simple_argument;
      }
      elseif (isset($fieldItem->type) && (strcmp($fieldItem->type, "date") == 0 )) {
        $filter = $date_filter;
        $sort = $date_sort;
        $field_handler = $date_field;
        $argument_handler = $date_argument;
      }
      else {
        $filter = ($hasOptions) ? $string_in_filter : $string_filter;
        $sort = $string_sort;
        $field_handler = $simple_field;
        $argument_handler = $simple_argument;
      }


      if ($hasOptions) {
        $table[$fieldItem->identifier] = array(
            'title' => t($fieldItem->name),
            'help' => t('Appears in the restful call request : ' . $config->datapath . $seperator . $fieldItem->query),
            'restful_client_id' => $record->nid,
            'options callback' => 'views_restful_client_options',
            'callback arguments' => $fieldItem->options,
            'field' => $field_handler,
            'argument' => $argument_handler,
            'filter' => $filter,
            'sort' => $sort,
        );
      }
      else {
        $table[$fieldItem->identifier] = array(
            'title' => t($fieldItem->name),
            'help' => t('Appears in the restful call request : ' . $config->datapath . $seperator . $fieldItem->query),
            'restful_client_id' => $record->nid,
            'field' => $field_handler,
            'argument' => $argument_handler,
            'filter' => $filter,
            'sort' => $sort,
        );
      }
    }
  }

  return $data;
}

/**
 * Implements hook_views_plugins().
 */
function views_restful_client_views_plugins() {
  return array(
      'query' => array(
          'views_restful_client' => array(
              'title' => t('Restful Request'),
              'help' => t('Query will be generated and run using the Restful Client API.'),
              'handler' => 'views_restful_client_plugin_query',
              'path' => drupal_get_path('module', 'views_restful_client') . '/plugins',
          ),
      )
  );
}

