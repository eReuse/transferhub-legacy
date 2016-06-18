<?php
/**
 * Created by PhpStorm.
 * User: Xavier
 * Date: 27/12/2014
 * Time: 19:54
 */

/**
 * Generates a floating box.
 *
 * @param integer $identity Unique identifier across the html page generated, exactly the 'id' HTML attribute.
 * @param string $element HTML output of the element the popup has.
 * @param string $type Type of style accordingly as UI_THEME_TYPE.
 * @param array $attributes Array of attributes to send to theme('Box'). See the spec there.
 * @return string HTML output.
 */
function theme_floating($identity, $element = '', $type = UI_THEME_TYPE::NORMAL, $attributes = Array(), $arrow = UI_FLOATING_ARROW::NONE){
    $attributes['class'] .= " floating arrow_$arrow";
    $attributes['id'] = $identity;
    return theme('box',$element,$type,false,'article',$attributes);
}