<?php

/**
 * @file
 * Contains a Views field handler to take care of displaying delete links
 * as fields.
 */

class roomify_rate_handler_delete_link_field extends views_handler_field {

  function construct() {
    parent::construct();

    $this->additional_fields['rate_id'] = 'rate_id';
  }

  function option_definition() {
    $options = parent::option_definition();

    $options['text'] = array('default' => '', 'translatable' => TRUE);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['text'] = array(
      '#type' => 'textfield',
      '#title' => t('Text to display'),
      '#default_value' => $this->options['text'],
    );
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {
    $text = !empty($this->options['text']) ? $this->options['text'] : t('delete');
    $rate_id = $values->{$this->aliases['rate_id']};

    return l($text, 'admin/bat/config/rate/manage/' . $rate_id . '/delete');
  }

}
