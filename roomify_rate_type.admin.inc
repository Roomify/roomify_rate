<?php

/**
 * @file
 * RoomifyRateType editing UI.
 */

/**
 * UI controller.
 */
class RoomifyRateTypeUIController extends EntityDefaultUIController {
  /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {
    $items = parent::hook_menu();

    foreach ($items as &$item) {
      unset($item['access callback']);
      $item['access arguments'] = array('administer roomify_rate_type entities');
    }

    return $items;
  }
}

/**
 * Generates the rate type editing form.
 */
function roomify_rate_type_form($form, &$form_state, $rate_type, $op = 'edit') {
  if ($op == 'clone') {
    $rate_type->label .= ' (cloned)';
    $rate_type->type = '';
  }

  $form['label'] = array(
    '#title' => t('rate type name'),
    '#type' => 'textfield',
    '#default_value' => $rate_type->label,
    '#description' => t('The human-readable name of this rate type.'),
    '#required' => TRUE,
    '#size' => 30,
    '#weight' => -100,
  );

  // Machine-readable type name.
  $form['type'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($rate_type->type) ? $rate_type->type : '',
    '#maxlength' => 32,
    '#machine_name' => array(
      'exists' => 'roomify_rate_get_types',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for this rate type. It must only contain lowercase letters, numbers, and underscores.'),
    '#weight' => -99,
  );

  if ($op == 'edit') {
    $form['type']['#disabled'] = TRUE;
  }

  // Add the field related form elements.
  $form_state['roomify_rate_type'] = $rate_type;
  field_attach_form('roomify_rate_type', $rate_type, $form, $form_state);

  $form['additional_settings'] = array(
    '#type' => 'vertical_tabs',
    '#weight' => 99,
  );

  $form['actions'] = array(
    '#type' => 'actions',
    '#tree' => FALSE,
  );

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save rate type'),
    '#weight' => 100,
    '#submit' => array('roomify_rate_type_form_submit'),
  );

  return $form;
}

/**
 * Form API submit callback for the rate type form.
 */
function roomify_rate_type_form_submit(&$form, &$form_state) {
 $rate_type = entity_ui_controller('roomify_rate_type')->entityFormSubmitBuildEntity($form, $form_state);
  // Save and go back.
  $rate_type->save();

  $form_state['rate_type'] = $rate_type;

  $form_state['redirect'] = 'admin/bat/config/rate-types';
}
