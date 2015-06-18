<?php

/**
 * @file
 * Provides the Views' restful calls
 * 
 */
class RestfulTemplate {

  /**
   * The Restful  server's URL.
   *
   * @var string
   */
  private $base_url;

  /**
   * HTTP Basic Authentication header to set for requests to the Restful server.
   *
   * @var string
   */
  private $http_auth;

  /**
   *  Context path
   * 
   * @var string
   */
  private $context_path;

  /**
   * Filter the results 
   * @var array
   */
  private $filters;

  /**
   * Sort the results 
   * @var array
   */
  private $sorters;
  private $debug = FALSE;

  /**
   * This is the keys for retrieving infotmation
   * @var stdClass 
   */
  private $definition;
  private $datapath;

  public function __construct($options) {
    if (is_object($options)) {
      $this->initialize($options);
    }
  }
  
  private function initialize(stdClass $options){
    try {
        $this->definition = json_decode($options->configuration);
        $this->datapath = $this->definition->datapath;
        $this->base_url = $this->definition->url;
        // Set HTTP Basic Authentication parameter, if login data was set.
        if (strlen($this->definition->user) && strlen($this->definition->pass)) {
          $this->http_auth = 'Basic ' . base64_encode($this->definition->user . ':' . $this->definition->pass);
        }
      }
      catch (Exception $exc) {
        if ($this->debug) {
          drupal_set_message($exc->getTraceAsString(), 'error');
        }
        watchdog('views_restful_client', "Error occur on file %filename %line \n%error", array("%filename" => __FILE__, "%line" => __LINE__, "%error" => $exc->getTraceAsString()), WATCHDOG_ERROR);
      }
  }

  /**
   * Define ops for using in filter.
   */
  private function operations($operator, $l, $r) {
    $content = str_replace("%", "(\w+)?", $r);
    $startsWith = "/^" . $content . "/i";
    $endsWith = "/" . $content . "$/i";
    $match = "/" . $content . "/i";
    $key = trim(strtolower($operator));
    $table = array(
        '<' => create_function('$l,$r', 'return $l < $r;'),
        '<=' => create_function('$l,$r', 'return $l <= $r;'),
        '=' => create_function('$l,$r', 'return $l == $r;'),
        '===' => create_function('$l,$r', 'return $l === $r;'),
        '!=' => create_function('$l,$r', 'return $l != $r;'),
        '!==' => create_function('$l,$r', 'return $l !== $r;'),
        '>=' => create_function('$l,$r', 'return $l >= $r;'),
        '>' => create_function('$l,$r', 'return $l > $r;'),
        'between' => create_function('$l,$r', 'return ($l >= $r[0] && $l <= $r[1]);'),
        'not_between' => create_function('$l,$r', 'return !($l >= $r[0] && $l <= $r[1]);'),
        'equal' => create_function('$l, $r', 'return strcmp($l, $r) === 0;'),
        'not_equal' => create_function('$l, $r', 'return strcmp($l, $r) !== 0;'),
        'contains' => create_function('$l, $r', 'return preg_match($r, $l) === 1;'),
        'starts' => create_function('$l, $r', 'return preg_match($r, $l) === 1;'),
        'not_starts' => create_function('$l, $r', 'return preg_match($r, $l) !== 1;'),
        'ends' => create_function('$l, $r', 'return preg_match($r, $l) === 1;'),
        'not_ends' => create_function('$l, $r', 'return preg_match($r, $l) !== 1;'),
        'not_contains' => create_function('$l, $r', 'return preg_match($r, $l) !== 1;'),
        'regex' => create_function('$l, $r', 'return preg_match($r, $l) === 1;'),
        'empty' => create_function('$l, $r', 'return empty($l);'),
        'not_empty' => create_function('$l, $r', 'return !empty($l);')
    );

    if ((strcmp($key, 'starts') == 0) || (strcmp($key, 'not_starts') == 0)) {
      $arguments = array($l, $startsWith);
    }
    elseif ((strcmp($key, 'ends') == 0) || (strcmp($key, 'not_ends') == 0)) {
      $arguments = array($l, $endsWith);
    }
    elseif ((strcmp($key, 'regex') == 0) || (strcmp($key, 'contains') == 0) ||
            (strcmp($key, 'not_contains') == 0)) {
      $arguments = array($l, $match);
    }
    else {
      $arguments = array($l, $r);
    }

    return call_user_func_array($table[$key], $arguments);
  }

  private function filterResults($object) {
    $isValid = TRUE;
    $isFilterEnable = !empty($this->filters);
    if ($isFilterEnable) {
      $isValid = FALSE;
      foreach ($this->filters as $pattern) {
        $operator = $pattern->operator;
        if (isset($object->{$pattern->field}) && isset($pattern->value)) {
          $left = $object->{$pattern->field};
          $right = $pattern->value;
          $isValid = $this->operations($operator, trim($left), trim($right));
          if ($isValid) {
            break;
          }
        }
      }
    }
    return $isValid;
  }

  private function sortResults(&$result) {

    if (!empty($this->sorters)) {
      foreach ($this->sorters as $pattern) {
        $order = strtolower($pattern->order);
        $type = strtolower($pattern->type);
        if (strcmp($order, 'asc') == 0) {
          $function = (strcmp($type, 'numeric') == 0) ? 'isort_asc' : ((strcmp($type, 'date') == 0) ? 'dsort_asc' : 'ssort_asc');
        }
        else {
          $function = (strcmp($type, 'numeric') == 0) ? 'isort_desc' : ((strcmp($type, 'date') == 0) ? 'dsort_desc' : 'ssort_desc');
        }
        usort($result, array(new rest_template_comparable($pattern->field), $function));
      }
    }
  }

  private function processJSON($content) {
    $data = json_decode($content);
    $itemsList = (isset($data->{$this->datapath})) ? $data->{$this->datapath} : NULL;
    $result = array();
    if (is_array($itemsList)) {
      foreach ($itemsList as $item) {
        $object = new stdClass;
        foreach ($this->definition->fields as $field) {
          if ((strcmp($field->type, "date") === 0) && isset($item->{$field->query})) {
            $object->{$field->identifier} = rest_template_comparable::getTime($item->{$field->query});
          }
          else {
            $object->{$field->identifier} = isset($item->{$field->query}) ? $item->{$field->query} : '';
          }
        }
        if ($this->filterResults($object)) {
          $result[] = $object;
        }
      }
    }
    else {
      $object = new stdClass;
      $item = $itemsList;
      foreach ($this->definition->fields as $field) {
        if ((strcmp($field->type, "date") === 0) && isset($item->{$field->query})) {
          $object->{$field->identifier} = rest_template_comparable::getTime($item->{$field->query});
        }
        else {
          $object->{$field->identifier} = isset($item->{$field->query}) ? $item->{$field->query} : '';
        }
      }
      if ($this->filterResults($object)) {
        $result[] = $object;
      }
    }
    $this->sortResults($result);
    return $result;
  }

  private function processXML($content) {
    $result = array();
    try {
      libxml_use_internal_errors(true);
      $xmldoc = simplexml_load_string($content);
      if ($xmldoc !== false && !empty($this->datapath)) {
        $elementList = $xmldoc->xpath($this->datapath);
        if (!is_null($elementList)) {
          foreach ($elementList as $element) {
            $object = new stdClass;
            $row = simplexml_load_string($element->asXML());
            foreach ($this->definition->fields as $field) {
              if (!empty($field->query)) {
                $item = $row->xpath($field->query);
                if (strcmp($field->type, "raw") === 0) {
                  $object->{$field->identifier} = (!empty($item)) ? json_encode($item) : '';
                }
                elseif ((strcmp($field->type, "date") === 0) && isset($item[0])) {

                  $object->{$field->identifier} = rest_template_comparable::getTime($item[0]->__toString());
                }
                else {
                  $object->{$field->identifier} = (!empty($item)) ? $item[0]->__toString() : '';
                }
              }
            }
            if ($this->filterResults($object)) $result[] = $object;
          }
        }
      }
      $this->sortResults($result);
    }
    catch (Exception $exc) {
      if ($this->debug) {
        drupal_set_message($exc->getTraceAsString(), 'error');
      }
      watchdog('views_restful_client', "Error occur on file %filename %line \n%error", array("%filename" => __FILE__, "%line" => __LINE__, "%error" => $exc->getTraceAsString()), WATCHDOG_ERROR);
    }
    catch (ErrorException $exc) {
      if ($this->debug) {
        drupal_set_message($exc->getTraceAsString(), 'error');
      }
      watchdog('views_restful_client', "Error occur on file %filename %line \n%error", array("%filename" => __FILE__, "%line" => __LINE__, "%error" => $exc->getTraceAsString()), WATCHDOG_ERROR);
    }


    return $result;
  }

  /**
   * Sends an HTTP request to Solr.
   *
   * This is just a wrapper around drupal_http_request().
   */
  private function makeHttpRequest($url, $options = array()) {
    if (empty($options['method']) || $options['method'] == 'GET' || $options['method'] == 'HEAD') {
      // Make sure we are not sending a request body.
      $options['data'] = NULL;
    }
    if ($this->http_auth) {
      $options['headers']['Authorization'] = $this->http_auth;
    }
    if ($this->debug) {
      drupal_set_message($url, 'status');
    }

    $response = drupal_http_request($url, $options);
    if (!isset($response->code) || $response->code < 0) {
      $response->code = 0;
      $response->status_message = 'Request failed';
    }
    // Additional information may be in the error property.
    if (isset($response->error)) {
      $response->status_message .= ': ' . check_plain($response->error);
    }

    if (!isset($response->data)) {
      $response->result = array();
      $response->response = NULL;
    }
    else {
      if (strcmp($this->definition->contenttype, 'json') == 0) {
        $response->result = $this->processJSON($response->data);
      }
      else if (strcmp($this->definition->contenttype, 'xml') == 0) {
        $response->result = $this->processXML($response->data);
      }
    }

    return $response;
  }

  public function setDebug($debug) {
    $this->debug = $debug;
  }

  public function getDefinition() {
    return $this->definition;
  }

  public function setFilter($filter) {
    if (is_array($filter) && !empty($filter)) {
      $this->filters = $filter;
    }
  }

  public function setDataPath($datapath) {
    if (!empty($datapath)) {
      $this->datapath = $datapath;
    }
  }

  public function getDataPath() {
    return $this->datapath;
  }

  public function getBaseURL() {
    return $this->base_url;
  }

  public function setBaseURL($url) {
    if (!empty($url)) {
      $this->base_url = $url;
    }
  }

  public function setContextPath($path) {
    if (!empty($path)) {
      $this->context_path = (strpos($path, "/") === 0) ? $path : "/" . $path;
    }
  }

  public function setSorter($sorter) {
    if (is_array($sorter) && !empty($sorter)) {
      $this->sorters = $sorter;
    }
  }

  public function sendRequest(array $params = array(), array $options = array()) {
    $query = empty($params) ? "" : "?" . http_build_query($params);
    $url = $this->base_url;
    if (!empty($this->context_path)) {
      $url = $url . $this->context_path;
    }
    $url = $url . $query;
    return $this->makeHttpRequest($url, $options);
  }

}

class rest_template_comparable {

  var $sortFilter;

  function __construct($sortFilter) {
    $this->sortFilter = $sortFilter;
  }

  public static function getTime($datetime) {
    $unixtime = 0;
    if (isset($datetime) && is_numeric($datetime)) {
      $unixtime = (strlen(trim($datetime)) != 10) ? intval($datetime) / 1000 : intval($datetime);
    }
    else {
      $unixtime = strtotime($datetime);
    }
    return $unixtime;
  }

  /**
   * Sort Ascending.
   */
  public function ssort_asc($a, $b) {
    $field = $this->sortFilter;
    $a_value = isset($a->{$field}) ? $a->{$field} : '';
    $b_value = isset($b->{$field}) ? $b->{$field} : '';
    return strcasecmp($a_value, $b_value);
  }

  /**
   * Sort Descending.
   */
  public function ssort_desc($a, $b) {
    return -$this->ssort_asc($a, $b);
  }

  /**
   * Sort Ascending.
   */
  public function isort_asc($a, $b) {
    $field = $this->sortFilter;
    $a_value = isset($a->{$field}) ? $a->{$field} : 0;
    $b_value = isset($b->{$field}) ? $b->{$field} : 0;
    return ($a_value < $b_value) ? -1 : (($a_value === $b_value) ? 0 : 1);
  }

  /**
   * Sort Descending.
   */
  public function isort_desc($a, $b) {
    return -$this->isort_asc($a, $b);
  }

  /**
   * Sort Ascending.
   */
  public function dsort_asc($a, $b) {
    $field = $this->sortFilter;
    $a_value = isset($a->{$field}) ? self::getTime($a->{$field}) : 0;
    $b_value = isset($b->{$field}) ? self::getTime($b->{$field}) : 0;
    return ($a_value < $b_value) ? -1 : (($a_value === $b_value) ? 0 : 1);
  }

  /**
   * Sort Descending.
   */
  public function dsort_desc($a, $b) {
    return -$this->dsort_asc($a, $b);
  }

}
