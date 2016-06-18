<?php
/**
 * Created by PhpStorm.
 * User: Xavier
 * Date: 27/12/2014
 * Time: 14:05
 */

/**
 * Generates a button that is not a form submit button.
 *
 * Use this tho have a standard way of generating buttons.
 *
 * @param $vars
 */
function template_preprocess_xbutton(&$vars){
    $vars['attributes']['class'] .= ' xbutton '.$vars['type'];
    $vars['attributes']['id'] = $vars['identity'];
    $vars['tag'] = 'button';
    uiu_get_behaviour($vars);
    $vars['attributes']['type'] = 'button'; //Disables default behaviour of submit in a form.
    $vars['attributes_html'] = drupal_attributes($vars['attributes']);
}