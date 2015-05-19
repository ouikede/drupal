<?php

/**
 * @file
 * Definition of views_restful_client_argument.
 */

/**
 * Argument handler to accept a user id.
 *
 * @ingroup views_argument_handlers
 */
class views_restful_client_argument extends views_handler_argument {

    function init(&$view, &$options) {
        parent::init($view, $options);
        $this->value = array();
    }

    function option_definition() {
        $options = parent::option_definition();
        return $options;
    }

    function options_form(&$form, &$form_state) {
        parent::options_form($form, $form_state);
    }

    /**
     * Build the summary query based on a string
     */
    function summary_query() {

        $this->ensure_my_table();
        $this->summary_name_field();
        return $this->summary_basics(FALSE);
    }

    /**
     * Get the formula for this argument.
     *
     * $this->ensure_my_table() MUST have been called prior to this.
     */
    function get_formula() {
        return "SUBSTRING($this->table_alias.$this->real_field, 1, " . intval($this->options['limit']) . ")";
    }

    /**
     * Build the query based upon the formula
     */
    function query($group_by = FALSE) {
        $argument = $this->argument;
        if (!empty($this->options['transform_dash'])) {
            $argument = strtr($argument, '-', ' ');
        }

        $this->value = array($argument);
        $this->operator = 'or';
        $this->ensure_my_table();


        $this->query->add_path_component($this->real_field, $argument);

    }

    /**
     * Provide the argument to use to link from the summary to the next level;
     * this will be called once per row of a summary, and used as part of
     * $view->get_url().
     *
     * @param $data
     *   The query results for the row.
     */
    function summary_argument($data) {
        return $data->{$this->base_alias};
    }

    function get_sort_name() {
        return t('Alphabetical', array(), array('context' => 'Sort order'));
    }

    /**
     * Get the title this argument will assign the view, given the argument.
     *
     * This usually needs to be overridden to provide a proper title.
     */
    function title() {
        return check_plain($this->argument);
    }

    /**
     * Called by the view object to get the title. This may be set by a
     * validator so we don't necessarily call through to title().
     */
    function get_title() {
        if (isset($this->validated_title)) {
            return $this->validated_title;
        } else {
            return $this->title();
        }
    }

     /**
   * Provides the name to use for the summary. By default this is just
   * the name field.
   *
   * @param $data
   *   The query results for the row.
   */
  function summary_name($data) {
    $value = $data->{$this->name_alias};
    if (empty($value) && !empty($this->definition['empty field name'])) {
      $value = $this->definition['empty field name'];
    }
    return check_plain($value);
  }
}
