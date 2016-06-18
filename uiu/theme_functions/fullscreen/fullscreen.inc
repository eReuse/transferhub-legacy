<?php
/**
 * Created by PhpStorm.
 * User: Xavier
 * Date: 27/12/2014
 * Time: 19:54
 */

/**
 * Generates a Fullscreen popup.
 *
 * It's exactly the same popup but appears above everything and makes all the screen darker, so impacts on user.
 * User cannot touch anything else except the popup or the dark screen, in the latter case it will cause the popup to close.
 *
 * There is just one fullscreen popup at screen at time.
 *
 * You can override the behaviour, for example, not closing the popup when user touches the gray area and forcing him
 * to touch a button, by extending and overriding Fullscreen.js
 *
 * See theme('popup') to get more info.
 *
 * @see theme_popup
 *
 * @param string $identity See popup parameters.
 * @param string $element See popup parameters.
 * @param string $type See popup parameters.
 * @param string $title See popup parameters.
 * @param array $options See popup parameters.
 * @param array $attributes See popup parameters.
 * @return string HTML output.
 */
function theme_fullscreen($identity, $element = '', $type = UI_THEME_TYPE::NORMAL, $title = '', $options = Array(), $attributes = Array()){
    $attributes['class'] .= ' fullscreen';
    return theme('popup',$identity,$element,$type,$title,$options,$attributes);
}

