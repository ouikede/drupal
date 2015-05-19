<?php

/**
 * @file
 * 
 */
function views_restful_client_admin_content() {
  $result = views_restful_client_load_all();
  $header = array(
      t('Name'),
      t('Description'),
      t('URL'),
      t('Operation')
  );

  $rows = array();

  foreach ($result as $record) {
    $config = json_decode($record->configuration);
    $rows[] = array(
        $record->name,
        $record->description,
        $config->url,
        l(t('edit'), "admin/config/search/restfulclient/restfulclient/{$record->nid}/edit"),
    );
  }



  return array(
      '#theme' => 'table',
      '#header' => $header,
      '#rows' => $rows,
      '#empty' => t('There are no search servers or indexes defined yet.'),
  );
}

function views_restful_client_admin_setting($form, &$form_state, $clientId = -1) {

  if (!empty($clientId) && is_numeric($clientId)) {
    $result = views_restful_client_load_record($clientId);
    if (!empty($result)) {
      $config = json_decode($result->configuration);
    }
  }

  
 
  if (empty($config)) {
    $result = new stdClass;
    $result->nid = time();
    $result->name = '';
    $result->description = '';
    $config = new stdClass;
    $config->url = '';
    $config->user = '';
    $config->pass = '';
    $config->datapath = '';
    $config->contenttype = 'json';
    $showDeleteButton = FALSE;
  }
  else{ 
    $showDeleteButton = TRUE;
  }


  $form = array();
  //$form['#tree'] = TRUE;
  $form['client_id'] = array(
      '#type' => 'hidden',
      '#title' => t('Client ID'),
      '#value' => $result->nid
  );
  $form['name'] = array(
      '#type' => 'textfield',
      '#title' => t('Name'),
      '#value' => $result->name,
      '#maxlength' => 20,
  );
  $form['description'] = array(
      '#type' => 'textfield',
      '#title' => t('Description'),
      '#value' => $result->description,
      '#maxlength' => 255,
  );
  $form['url'] = array(
      '#type' => 'textfield',
      '#title' => t('Feed URL'),
      '#value' => $config->url
  );
  $form['user'] = array(
      '#type' => 'textfield',
      '#title' => t('Username'),
      '#value' => $config->user
  );
  $form['pass'] = array(
      '#type' => 'textfield',
      '#title' => t('Password'),
      '#value' => $config->pass
  );

  $form['datapath'] = array(
      '#type' => 'textfield',
      '#title' => t('Data Root Path'),
      '#value' => $config->datapath
  );

  $optionscontenttype = array(
      'json' => t('JSON Content'),
      'xml' => t('XML Content')
  );

  $form['contenttype'] = array(
      '#type' => 'select',
      '#title' => t('Content Type'),
      '#value' => $config->contenttype,
      '#options' => $optionscontenttype
  );

  $header = array(t('Field Label'), t('Drupal Machine Name'), t('Data Path Query'), t('Field Type'));
  $rows = array();
  $count = 1;
  $optionsdatatype = array(
      'string' => t('String'),
      'numeric' => t('Number'),
      'raw' => t('Raw'),
      'date' => t('Date')
  );


  if (!empty($config->fields)) {

    foreach ($config->fields as $column) {
      $form['client_field_id_overview'][$column->query] = array();
      $form['client_field_id_overview'][$column->query]['name'] = array('#name' => 'field_name_' . $count, '#type' => 'textfield', '#value' => $column->name);
      $form['client_field_id_overview'][$column->query]['identifier'] = array('#name' => 'field_identifier_' . $count, '#type' => 'textfield', '#value' => $column->identifier);
      $form['client_field_id_overview'][$column->query]['query'] = array('#name' => 'field_query_' . $count, '#type' => 'textfield', '#value' => $column->query);
      $form['client_field_id_overview'][$column->query]['type'] = array('#name' => 'field_type_' . $count, '#type' => 'select', '#value' => $column->type, '#options' => $optionsdatatype);

      $row = array();
      $row[] = drupal_render($form['client_field_id_overview'][$column->query]['name']);
      $row[] = drupal_render($form['client_field_id_overview'][$column->query]['identifier']);
      $row[] = drupal_render($form['client_field_id_overview'][$column->query]['query']);
      $row[] = drupal_render($form['client_field_id_overview'][$column->query]['type']);
      $rows[] = $row;

      $count = $count + 1;
    }
  }


  ///Empty field to add a new parameter  
  $form['client_field_id_overview']["new"] = array();
  $form['client_field_id_overview']["new"]['name'] = array('#name' => 'field_name_' . $count, '#type' => 'textfield');
  $form['client_field_id_overview']["new"]['identifier'] = array('#name' => 'field_identifier_' . $count, '#type' => 'textfield');
  $form['client_field_id_overview']["new"]['query'] = array('#name' => 'field_query_' . $count, '#type' => 'textfield');
  $form['client_field_id_overview']["new"]['type'] = array('#name' => 'field_type_' . $count, '#type' => 'select', '#options' => $optionsdatatype);

  $row = array();
  $row[] = drupal_render($form['client_field_id_overview']["new"]['name']);
  $row[] = drupal_render($form['client_field_id_overview']["new"]['identifier']);
  $row[] = drupal_render($form['client_field_id_overview']["new"]['query']);
  $row[] = drupal_render($form['client_field_id_overview']["new"]['type']);
  $rows[] = $row;



   $form['client_field_id_overview']['table_title'] = array(
      '#markup' => t('Mapping Data Content to View Field Label'),
  );

  $form['client_field_id_overview']['table'] = array(
      '#theme' => 'table', '#header' => $header, '#rows' => $rows,
      '#tree' => TRUE
  );


  // Submit button.
  $form['buttons']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
      '#submit' => array('views_restful_client_submit'),
  );

  $form['buttons']['cancel'] = array(
      '#type' => 'submit',
      '#value' => t('Cancel'),
      '#submit' => array('views_restful_client_cancel'),
      '#validate' => array(),
  );

  if ($showDeleteButton) {
    $form['buttons']['delete'] = array(
        '#type' => 'submit',
        '#value' => t('Delete'),
        '#submit' => array('views_restful_client_delete'),
        '#validate' => array(),
    );
  }

  return $form;
}

function views_restful_client_submit(&$form, &$form_state) {


  $inputs = $form_state['input'];
  $record = new stdClass();
  $record->nid = (!empty($inputs['client_id'])) ? $inputs['client_id'] : NULL;


  $record->name = $inputs['name'];
  $record->description = $inputs['description'];

  $config = new stdClass;
  $config->user = $inputs['user'];
  $config->pass = $inputs['pass'];
  $config->url = $inputs['url'];
  $config->datapath = $inputs['datapath'];
  $config->contenttype = $inputs['contenttype'];
  $config->fields = array();

  $loop = 1;
  while (!empty($inputs['field_name_' . $loop])) {
    $field = new stdClass;
    $field->name = trim($inputs['field_name_' . $loop]);
    $identifer = strtolower(preg_replace("/[^a-zA-Z0-9]/", "_", $inputs['field_identifier_' . $loop]));
    $field->identifier = trim($identifer);
    $field->query = $inputs['field_query_' . $loop];
    $field->type = $inputs['field_type_' . $loop];
    if (!empty($field->name) && !empty($field->identifier)) {
      $config->fields[] = $field;
    }

    $loop = $loop + 1;
  }

  $record->configuration = json_encode($config);

  views_restful_client_save_record($record);

 
   $form_state['redirect'] = "admin/config/search/restfulclient/restfulclient/{$record->nid}/edit";

  drupal_set_message(t('The configuration has been saved.'), 'status');
}

function views_restful_client_cancel(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/config/search/restfulclient';
}

function views_restful_client_delete(&$form, &$form_state) {
  $nid = $form_state['input']['client_id'];
  if (is_numeric($nid)) {
    views_restful_client_delete_record($nid);
    $form_state['redirect'] = 'admin/config/search/restfulclient';
  }
}
