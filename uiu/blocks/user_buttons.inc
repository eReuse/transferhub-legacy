<?php
/**
 * Created by PhpStorm.
 * User: Xavier
 * Date: 12/01/2015
 * Time: 23:08
 */


function uiu_user_buttons(){
    $output = '';
    if(user_is_anonymous()){
        $options = Array('<a href="#" id="login_popup_button">'.t('Login').'</a>');
        if(variable_get('user_register',"0") == "1") $options[] = l(t('Register'),'user/register',Array('attributes'=>Array('id'=>'register_button')));
        $output = "<div class='user_buttons'>".implode($options,'<span class="separator">|</span>')."</div>";
    }
    else{
        $element = uiu_get_user_picture_small()
            .theme('image',drupal_get_path('module','uiu').'/arrow_down.png','Arrow down','Arrow down',
                Array('class' => 'user-arrow'));
        $output = "<a ".drupal_attributes(Array('class' => 'user-profile','href'=>'#', 'id' => 'user_popup_button')).">$element</a>";
    }
    return $output;
}