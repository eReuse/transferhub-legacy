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
function template_preprocess_sbutton(&$vars){
    $vars['attributes']['class'] .= ' sbutton  '.$vars['type'];
    if(!is_null($vars['identity'])) $vars['attributes']['id'] = $vars['identity'];
    $vars['image_html'] = is_null($vars['image'])? '' : theme('image',$vars['title'],$vars['title']);
    $vars['text_html'] = is_null($vars['text'])? '' : $vars['text'];
    $vars['tag'] = 'button';
    $vars['attributes']['type'] = 'button'; //Disables default behaviour of submit in a form.
    uiu_get_behaviour($vars);
    $vars['attributes_html'] = drupal_attributes($vars['attributes']);
}