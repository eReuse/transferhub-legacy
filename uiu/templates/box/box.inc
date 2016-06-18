<?php
/**
 * Created by PhpStorm.
 * User: Xavier
 * Date: 27/12/2014
 * Time: 14:10
 */
/**
 * Preprocessor that generates a box.
 *
 * A box is a basic HTML container that <b>visually</b> encapsulates an element. Use it when you just want to differentiate
 * the element from others of the page.
 *
 * It is extended and used by Cards, menus, popups, in views...
 * The variables sent to theme('...') are:
 * - element: string. The HTML output of the element.
 * - type: UI_THEME_TYPE.
 * - link_box: true|false if you want the box to act as an <a> tag or not. Specify the href in attributes.
 * - tag: string. HTML tag to show. Not used when link_box is true.
 * - attributes: Array of attributes to send to drupal_attributes()
 * @see drupal_attributes
 * @param $vars Array
 *
 * Using this theme returns the HTML output of the box.
 */
function template_preprocess_box(&$vars){
    //dpm($vars,'box');
    /*Search uses old-unusued D6 box. We need to change arguments to match it with our box. */
    if($vars['element'] == t('Search results') || $vars['element'] == t('Your search yielded no results')){
        $aux = $vars['element'];
        $vars['element'] = $vars['type'];
        $vars['type'] = $aux;
    }
    $vars['attributes']['class'] = 'box '.$vars['attributes']['class'].' '.$vars['type'];
    if($vars['link_box']){
        $vars['tag'] = 'a';
        $vars['attributes']['class'] .= ' box_link';
    }
    $vars['attributes_html'] = drupal_attributes($vars['attributes']);
}
