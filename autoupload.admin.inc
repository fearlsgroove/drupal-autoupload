<?php

/**
 * @file
 * Contains the administrative functions of the autoupload module.
 *
 * This file is included by the autoupload module, and includes the
 * settings form.
 */

function autoupload_admin_form() {
  $autoupload_predefined = variable_get('autoupload_predefined');

  $form['predefined'] = array(
    '#type'  => 'fieldset',
    '#title' => t('File Types'),
  );
  $form['predefined']['desc'] = array(
    '#markup' => t('Choose the type(s) of file fields where you would like to use Auto Upload.'),
  );
  $form['predefined']['managed_file'] = array(
    '#type' => 'checkbox',
    '#title' => t('Managed'),
    '#description' => t('Drupal core managed file fields.'),
    '#default_value' => $autoupload_predefined['managed_file'],
  );

  $media_disabled = module_exists('media') ? FALSE : TRUE;
  $form['predefined']['media'] = array(
    '#type' => 'checkbox',
    '#title' => t('Media'),
    '#description' => t('Auto upload files using the Media module\'s media file selector.'),
    '#disabled' => $media_disabled,
    '#default_value' => $media_disabled ? 0 : $autoupload_predefined['media'],
  );
  $form['predefined']['media_library'] = array(
    '#type' => 'checkbox',
    '#title' => t('Media Library'),
    '#description' => t('Auto select media files from the media library.'),
    '#disabled' => $media_disabled,
    '#default_value' => $media_disabled ? 0 : $autoupload_predefined['media_library'],
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );
  return $form;
}

function autoupload_admin_form_submit($form, &$form_state) {
  $selectors = $predefined = array();
  $values = $form_state['values'];

  $predefined_types = _autoupload_get_predefined();
  foreach ($predefined_types as $type => $type_data) {
    $predefined[$type] = $values[$type];
    if ($values[$type]) {
      $selectors[$type] = $type_data;
    }
  }

  variable_set('autoupload_selectors', $selectors);
  variable_set('autoupload_predefined', $predefined);
  drupal_set_message(t('The configuration options have been saved.'));
}

/*
 * Admin helper function to return the predefined file field types
 *
 * The $types array data is passed to the autoUpload JavaScript var selectors
 *   index : type of file handled
 *   value : Array containing selectors for file input and submit button
 *     context  - context of the file select elements
 *     file_input - file input selector
 *     file_event - file input event
 *     submit_input - submit input selector
 *     submit_event - event type on submit input to trigger upload/selection
 *     error  - error element selector
 *     error_remove - indicates how to handle error removal.
 *       empty - error removal is not needed, already handled
 *       'id' - selector is an id. remove the id from the element
 *       'class' - selector is a class. remove the class from the element
 *       'element' - remove the entire error element
 */
function _autoupload_get_predefined($type = NULL) {
  $types = array(
    'managed_file' => array(
      'context' => 'div.form-managed-file',
      'file_input' => 'input.form-file',
      'file_event' => 'change',
      'submit_input' => 'input.form-submit[value=Upload]',
      'submit_event' => 'mousedown',
      'error' => 'div.error',
      'error_remove' => '',
    ),
    'media' => array(
      'context' => '#media-add-upload',
      'file_input' => '#edit-upload',
      'file_event' => 'change',
      'submit_input' => '#edit-submit',
      'submit_event' => 'click',
      'error' => 'input.error',
      'error_remove' => 'class',
    ),
    'media_library' => array(
      'context' => '#media-tab-library',
      'file_input' => 'li',
      'file_event' => 'mouseup',
      'submit_input' => 'a.button-yes',
      'submit_event' => 'click',
      'error' => '',
      'error_remove' => '',
    ),
  );
  return $type ? (isset($types[$type]) ? $types[$type] : NULL) : $types;
}
