<?php

/**
 * @file
 * Definition of views_handler_sort_numeric.
 */

/**
 * Handler for GROUP BY on simple numeric fields.
 *
 * @ingroup views_sort_handlers
 */
class views_restful_client_handler_sort_numeric extends views_handler_sort {
  /**
   * Called to add the field to a query.
   */
  function query() {
    $this->ensure_my_table();
    $params = array('type' => 'numeric');
    $this->query->add_orderby($this->table_alias, $this->real_field, $this->options['order'], NULL, $params);
  }

  function ui_name($short = FALSE) {
    return $this->get_field(parent::ui_name($short));
  }
}
