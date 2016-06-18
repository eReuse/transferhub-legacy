<?php
/**
 * Created by PhpStorm.
 * User: Xavier
 * Date: 27/12/2014
 * Time: 19:54
 */

/**
 * Generates a popup.
 *
 * Popups are floating elements that can appear and disappear when some triggers are fired.
 *
 * There are 2 ways to show the popup to the user. For both you generate the HTML accordingly using this theme(...)
 * implementation and then:
 * - Print the HTML whenever template you want to and set the javascript using Popup.prototype.createPopupFromDom(id) being
 * the id the same variable you use here as $identity
 * - Send the HTML to some kind of Drupal.settings javascript variable and setting it to the website using
 * Popup.prototype.createPopup(html,father) where html is this HTML and father a CSS selector to prepend the html to.
 *
 * You can extend and override Popup JS class to change the behaviour or add new triggers to custom buttons, for example.
 * see Popup.js
 *
 * @see Popup
 *
 * @param string $identity Unique identifier across the html page generated, exactly the 'id' HTML attribute.
 * @param string $element HTML output of the element the popup has.
 * @param string $type Type of style accordingly as UI_THEME_TYPE.
 * @param string $title Optional. Some title to add to the beginning popup.
 * @param array $options Special options to modify behaviour of popup:
 * ['buttons']['defaults']['cross'|'accept'|'cancel'] = true. Define true to one of the three default buttons to make them
 * appear in the popup. If false or value not present they won't appear in the popup.
 * @param array $attributes Array of attributes to send to theme('floating'). See the spec there.
 * @return string HTML output.
 */
function theme_popup($identity, $element = '', $type = UI_THEME_TYPE::NORMAL, $title = '', $options = Array(), $attributes = Array(), $arrow = UI_FLOATING_ARROW::NONE){
    $cross = $buttons = null;
    if($options['buttons']['defaults']['cross'])
        $cross = theme('xbutton', $identity.'_cross', null, Array('class' => 'cross'));
    $buttons = _uiu_popup_generate_buttons($identity, $options['buttons']);
    $header = strlen($title)? "<header class='header'><h4>$title</h4></header>" : '';
    $element = "<div class='popup-element'>$element</div>";
    $attributes['class'] .= ' popup no_display';        //Animation 2 will add the other classes at the beginning
    $var = theme('floating',$identity,$cross.$header.$element.$buttons,$type,$attributes, $arrow);
    return $var;
}

function _uiu_popup_generate_buttons($identity, $buttons){
    $output = '<div class="buttons">';
    if($buttons['defaults']['accept'])
        $output .= theme('sbutton', $identity.'_accept', t('Accept'), null, Array(), UI_THEME_TYPE::BOLD, Array('class' => 'accept'));
    if($buttons['defaults']['cancel'])
        $output .= theme('sbutton', $identity.'_cancel', t('Cancel'), null, Array(), UI_THEME_TYPE::NORMAL, Array('class' => 'cancel'));
    return $output."</div>";
}