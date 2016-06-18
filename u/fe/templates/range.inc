<?php
/**
 * Created by PhpStorm.
 * User: Xavier
 * Date: 06/03/2015
 * Time: 12:02
 */

function theme_fe_range($element){
    $min = is_null($element['#min'])? '' : "min='{$element['#min']}'";
    $max = is_null($element['#max'])? '' : "max='{$element['#max']}'";
    $step = is_null($element['#step'])? '' : "step='{$element['#step']}'";
    _form_set_class($element,Array('form-fe_range'));
    $element['attributes'] = (is_array($element['attributes'])? $element['attributes'] : Array()) + Array('name' => $element['#name'], 'id' => $element['#id'], 'type' => 'range', 'value' => $element['#value']);
    $attributes = drupal_attributes($element['attributes']);
    return theme('form_element', $element, "<input $attributes $min $max $step/>");
}