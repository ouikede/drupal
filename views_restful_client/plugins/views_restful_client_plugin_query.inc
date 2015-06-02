<?php

/**
 * @file
 * Provides the Views' query
 */
function errorHandler($errno, $errstr, $errfile, $errline) {
  // watchdog('views_restful_client', "Error occur on file %filename %line \n%error", array("%filename" =>$errfile, "%line" => $errline, "%error" => $errline), WATCHDOG_ERROR);
  return TRUE;
}

/**
 * Query plugin for views_restful_client_plugin
 */
class views_restful_client_plugin_query extends views_plugin_query {

  /**
   * An array of fields.
   */
  var $fields = array();

  /**
   * An array of path components.
   */
  var $pathcomponents = array();

  /**
   * An array of sections of the filters
   */
  var $filters = array();

  /**
   * A simple array of order by clauses.
   */
  var $orderby = array();

  /**
   *
   * @var RestfulTemplate
   */
  private $restTemplate;
  private static $ALLOWED_CMD = array("time", "date", "abs");

  /**
   *
   * @var array
   * 
   */
  private $placeholders = array();

  /**
   * Constructor; Create the basic query object and fill with default values.
   */
  function init($base_table, $base_field, $options) {

    try {

      $table_name = "views_restful_client_";
      $length = strlen($table_name);
      if (substr($base_table, 0, $length) == $table_name) {
        $restclientId = substr($base_table, $length);

        $this->restTemplate = views_restful_client_template_load($restclientId);
      }
      parent::init($base_table, $base_field, $options);
    }
    catch (Exception $e) {
      watchdog_exception('view_restful_client', $e);
    }
  }

  /**
   * Add a field to the query table, possibly with an alias. This will
   * automatically call ensure_table to make sure the required table
   * exists, *unless* $table is unset.
   *
   * @param $table
   *   The table this field is attached to. If NULL, it is assumed this will
   *   be a formula; otherwise, ensure_table is used to make sure the
   *   table exists.
   * @param $field
   *   The name of the field to add. This may be a real field or a formula.
   * @param $alias
   *   The alias to create. If not specified, the alias will be $table_$field
   *   unless $table is NULL. When adding formulae, it is recommended that an
   *   alias be used.
   * @param $params
   *   An array of parameters additional to the field that will control items
   *   such as aggregation functions and DISTINCT.
   *
   * @return $name
   *   The name that this field can be referred to as. Usually this is the alias.
   */
  function add_field($table, $field, $alias = '', $params = array()) {
    $alias = $field;

    // Add field info array.
    if (empty($this->fields[$field])) {
      $this->fields[$field] = array(
          'field' => $field,
          'table' => $table,
          'alias' => $alias,
              ) + $params;
    }

    return $field;
  }

  /**
   * Add an ORDER BY clause to the query.
   *
   * @param $table
   *   The table this field is part of. If a formula, enter NULL.
   *   If you want to orderby random use "rand" as table and nothing else.
   * @param $field
   *   The field or formula to sort on. If already a field, enter NULL
   *   and put in the alias.
   * @param $order
   *   Either ASC or DESC.
   * @param $alias
   *   The alias to add the field as. In SQL, all fields in the order by
   *   must also be in the SELECT portion. If an $alias isn't specified
   *   one will be generated for from the $field; however, if the
   *   $field is a formula, this alias will likely fail.
   * @param $params
   *   Any params that should be passed through to the add_field.
   */
  function add_orderby($table, $field = NULL, $order = 'ASC', $alias = '', $params = array()) {
    $sorter = new stdClass;
    $sorter->field = isset($field)? trim(str_replace(".", "",$field)) : "";
    $sorter->order = $order;
    $sorter->type = (isset($params['type'])) ? $params['type'] : 'string';
    $this->orderby[] = $sorter;
  }

  /**
   * Add a simple WHERE clause to the query. The caller is responsible for
   * ensuring that all fields are fully qualified (TABLE.FIELD) and that
   * the table already exists in the query.
   *
   * @param $group
   *   The WHERE group to add these to; groups are used to create AND/OR
   *   sections. Groups cannot be nested. Use 0 as the default group.
   *   If the group does not yet exist it will be created as an AND group.
   * @param $field
   *   The name of the field to check.
   * @param $value
   *   The value to test the field against. In most cases, this is a scalar. For more
   *   complex options, it is an array. The meaning of each element in the array is
   *   dependent on the $operator.
   * @param $operator
   *   The comparison operator, such as =, <, or >=. It also accepts more complex
   *   options such as IN, LIKE, or BETWEEN. Defaults to IN if $value is an array
   *   = otherwise. If $field is a string you have to use 'formula' here.
   *
   * The $field, $value and $operator arguments can also be passed in with a
   * single DatabaseCondition object, like this:
   * @code
   *   $this->query->add_where(
   *     $this->options['group'],
   *     db_or()
   *       ->condition($field, $value, 'NOT IN')
   *       ->condition($field, $value, 'IS NULL')
   *   );
   * @endcode
   *
   * @see QueryConditionInterface::condition()
   * @see DatabaseCondition
   */
  function add_where($group, $field, $value = NULL, $operator = NULL) {
    $filter = new stdClass;
    $filter->field = isset($field)? trim(str_replace(".", "",$field)) : "";
    $filter->value = $value;
    $filter->operator = $this->getOperator($operator);
    $this->filters[] = $filter;
  }

  function add_where_expression($group, $snippet, $args = array()) {

    $mainTokens = explode(")", $snippet);
    if (count($mainTokens) == 2) {
      $token = $mainTokens[1];
      $tokens = explode(":", $token);
      $operator = trim($tokens[0]);
    }
    $operator = $this->getOperator($operator);


    $token = $mainTokens[0];
    $tokens = explode("(", $token);
    if (count($tokens) >= 2) {
      $token = str_replace("'", "", $tokens[1]);
      $tokens = explode(",", $token);
      foreach ($tokens as $token) {
        if (!empty(trim($token)) && !empty($args)) {
          foreach ($args as $key => $value) {
            $filter = new stdClass;
            $filter->field = isset($token)? trim(str_replace(".", "",$token)) : "";
            $filter->value = trim($value);
            $filter->operator = $this->getOperator($operator);
            $this->filters[] = $filter;
          }
        }
      }
    }
  }

  function getOperator($operator) {
    $operator = !isset($operator) ? 'equal' : trim($operator);
    $operator = (strcmp($operator, 'LIKE') == 0) ? 'regex' : $operator;
    $operator = (strcmp($operator, 'IN') == 0) ? 'equal' : $operator;

    return $operator;
  }

  /**
   * 
   * @param type $field
   * @param type $value
   */
  function add_path_component($field, $value = NULL) {
    $path = new stdClass;
    $path->field = isset($field)? trim(str_replace(".", "",$field)) : "";
    $path->value = $value;
    $this->pathcomponents[] = $path;
  }

  function allowed_commmand($command) {
    ///I need to figure out a better way to stop system calls
    $allowed = self::$ALLOWED_CMD;
    $cmdList = explode(";", $command);
    $execute = FALSE;

    if (count($cmdList) == 1) {
      foreach ($allowed as $token) {
        $execute = (strpos($cmdList[0], $token) !== FALSE && strpos($cmdList[0], $token) == 0) ? TRUE : FALSE;
        if ($execute) BREAK;
      }
    }
    return $execute;
  }

  function run_eval($command) {
    if ($this->allowed_commmand(trim($command))) {
      set_error_handler("errorHandler"); // This is needed to catch eval exceptions      
      $value = eval('return ' . $command . ';');
      restore_error_handler();
    }
    else {
      $value = $command;
    }
    return $value;
  }

  function compute_path() {
    $paths = $this->options['path_component'];
    if (!empty($paths) && !empty($this->pathcomponents)) {
      $isEvalEnabled = $this->options['enable_php_eval'];
      foreach ($this->pathcomponents as $path) {
        $value = trim($path->value);
        if ($isEvalEnabled && !empty($value)) {
          $value = $this->run_eval($value);
        }
        $paths = str_replace("[" . $path->field . "]", $value, $paths);
      }
    }
    return $paths;
  }

  function compute_url() {
    $paths = $this->options['application_url'];
    return $paths;
  }

  /**
   * Generates a unique placeholder used in the db query.
   */
  function placeholder($base = 'views') {

    $holder = "";
    if (!isset($this->placeholders[$base])) {
      $this->placeholders[$base] = 0;
      $holder = ':' . $base;
    }
    else {
      $holder = ':' . $base . ++$this->placeholders[$base];
    }

    return $holder;
  }

  /**
   * Executes the query and fills the associated view object with according
   * values.
   *
   * Values to set: $view->result, $view->total_rows, $view->execute_time,
   * $view->pager['current_page'].
   *
   * $view->result should contain an array of objects. The array must use a
   * numeric index starting at 0.
   *
   * @param view $view
   *   The view which is executed.
   */
  function execute(&$view) {
    $start = microtime(TRUE);
    try {


      $this->restTemplate->setFilter($this->filters);
      $this->restTemplate->setSorter($this->orderby);
      $this->restTemplate->setDebug($this->options['enable_debug']);
      $this->restTemplate->setBaseURL($this->compute_url());
      $this->restTemplate->setContextPath($this->compute_path());
      $this->restTemplate->setDataPath($this->options['data_root_path']);
      $response = $this->restTemplate->sendRequest($this->query());

      if ($this->pager->use_count_query() || !empty($view->get_total_rows)) {
        // Hackish execute_count_query implementation.
        $this->pager->total_items = count($response->result);
        if (!empty($this->pager->options['offset'])) {
          $this->pager->total_items -= $this->pager->options['offset'];
        }

        $this->pager->update_page_info();
      }

      // Deal with offset & limit.
      $offset = !empty($this->offset) ? intval($this->offset) : 0;
      $limit = !empty($this->limit) ? intval($this->limit) : 0;
      $contents = $limit ? array_slice($response->result, $offset, $limit) : array_slice($response->result, $offset);


      $keys = array_keys($view->field);
      if (!empty($keys) && !empty($contents)) {
        foreach ($keys as $id) {
          $label = $view->field[$id]->options['label'];
          if (!empty($label)) {
            $values = $contents[0];
            $tokens = explode("]", $label);
            foreach ($tokens as $token) {
              $token = substr(trim($token), 1);
              if (isset($values->{$token})) {
                $label = str_replace("[" . $token . "]", $values->{$token}, $label);
              }
            }
            $view->field[$id]->options['label'] = $label;
          }
        }
      }
      $view->result = $contents;
      $view->total_rows = count($contents);

      $this->pager->post_execute($view->result);
    }
    catch (Exception $ex) {
      watchdog('views_restful_client', "Error occur on file %filename %line \n%error", array("%filename" => __FILE__, "%line" => __LINE__, "%error" => $ex->getTraceAsString()), WATCHDOG_ERROR);
    }
    $view->execute_time = microtime(TRUE) - $start;

    return TRUE;
  }

  function parseQuery(array $entries, $isEvalEnabled) {

    $entry = array();
    $entry[0] = trim($entries[0]);
    $entry[1] = isset($entries[1]) ? preg_replace('/\s+/', '', $entries[1]) : '';
    foreach ($this->pathcomponents as $path) {
      $value = $path->value;
      $field = "[" . $path->field . "]";
      $entry[1] = str_replace($field, $value, $entry[1]);
    }

    foreach ($this->filters as $path) {
      $value = $path->value;
      $field = "[" . $path->field . "]";
      $entry[1] = str_replace($field, $value, $entry[1]);
    }
    if ($isEvalEnabled && !empty(trim($entry[1]))) {
      $entryeval = $this->run_eval($entry[1]);
      $entry[1] = (!empty($entryeval)) ? $entryeval : $entry[1];
    }
    return $entry;
  }

  /**
   * Generate a query from all of the information supplied to the object.
   *
   * @param $get_count
   *   Provide a countquery if this is true, otherwise provide a normal query.
   */
  function query($get_count = FALSE) {
    $query_variables = $this->options['query_parameters'];
    $isEvalEnabled = $this->options['enable_php_eval'];
    $params = array();
    if (!empty($query_variables)) {
      $tokens = explode(PHP_EOL, $query_variables);
      foreach ($tokens as $token) {
        $entries = $this->parseQuery(explode('|', $token), $isEvalEnabled);
        $params[$entries[0]] = trim($entries[1]);
      }
    }
    return $params;
  }

  /**
   * Builds the necessary info to execute the query.
   */
  function build(&$view) {
    $view->init_pager();

// Let the pager modify the query to add limits.
    $this->pager->query();

    $view->build_info['query'] = $this->query();
  }

  /**
   * Option definition.
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['application_url'] = array('default' => '');
    $options['path_component'] = array('default' => '');
    $options['query_parameters'] = array('default' => '');
    $options['enable_debug'] = array('default' => FALSE);
    $options['data_root_path'] = array('default' => '');
    $options['enable_php_eval'] = array('default' => FALSE);



    return $options;
  }

  /**
   * Options form.
   */
  function options_form(&$form, &$form_state) {

    $definition = $this->restTemplate->getDefinition();
    $contentField = '';
    foreach ($definition->fields as $column) {
      $contentField .= $column->identifier . " => " . $column->name . "<br/>";
    }

    $path = empty($this->options['data_root_path']) ? array('default' => $this->restTemplate->getDataPath()) : $this->options['data_root_path'];
    $url = empty($this->options['application_url']) ? array('default' => $this->restTemplate->getBaseURL()) : $this->options['application_url'];


    $form['application_url'] = array(
        '#type' => 'textfield',
        '#title' => t('The Feed URL'),
        '#default_value' => $url,
        '#maxlength' => 5000,
    );

    $form['path_component'] = array(
        '#type' => 'textfield',
        '#title' => t('The URL Path Components'),
        '#default_value' => $this->options['path_component'],
        '#description' => t("The URL or path to the restful client.<br/>" . $contentField),
        '#maxlength' => 1024,
    );

    $form['data_root_path'] = array(
        '#type' => 'textfield',
        '#title' => t('Data Root Path'),
        '#default_value' => $path,
        '#description' => t("Data Root Path"),
        '#maxlength' => 1024,
    );

    $form['query_parameters'] = array(
        '#type' => 'textarea',
        '#title' => t('Query Parameters Send to Feed URL'),
        '#default_value' => $this->options['query_parameters'],
        '#description' => t("Query Parameters Send to Feed URL"),
        '#required' => FALSE,
    );
    $form['enable_php_eval'] = array(
        '#type' => 'checkbox',
        '#title' => t('Enable PHP evaluation of parameters'),
        '#default_value' => $this->options['enable_php_eval'],
        '#description' => t('Run eval on the argument on if it one of these functions : ' . implode(",", self::$ALLOWED_CMD)),
        '#required' => FALSE,
    );

    $form['enable_debug'] = array(
        '#type' => 'checkbox',
        '#title' => t('Enable Debugging'),
        '#default_value' => $this->options['enable_debug'],
        '#description' => t('This is use for debugging purpose only'),
        '#required' => FALSE,
    );
  }

}
