<?php

/**
 * @file
 * @todo.
 */
/**
 * @defgroup views_sort_handlers Views sort handlers
 * @{
 * Handlers to tell Views how to sort queries.
 */

/**
 * Base sort handler that has no options and performs a simple sort.
 *
 * @ingroup views_sort_handlers
 */
class views_restful_client_handler_sort_string extends views_handler_sort {

  /**
   * Called to add the sort to a query.
   */
  function query() {
    $params = array('type' => 'string');
    $this->query->add_orderby($this->table_alias, $this->real_field, $this->options['order'], NULL, $params);
  }

  function ui_name($short = FALSE) {
    return $this->get_field(parent::ui_name($short));
  }

}
