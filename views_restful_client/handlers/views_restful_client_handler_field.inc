<?php

/**
 * @file
 * Base field handler for views_restful_client.
 */
class views_restful_client_handler_field extends views_handler_field {

  /**
   * Called to determine what to tell the clicksorter.
   */
  function click_sort($order) {
    if (isset($this->real_field)) {
      // Since fields should always have themselves already added, just
      // add a sort on the field.
      $params = array('type' => 'string');
      $this->query->add_orderby($this->table_alias, $this->real_field, $order, $this->field_alias, $params);
    }
  }

  /**
   * Render.
   */
  function render($values) {
    $value = $this->get_value($values);
    return $this->sanitize_value($value);
  }

}
