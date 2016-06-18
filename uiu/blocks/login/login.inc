<?php
/**
 * Created by PhpStorm.
 * User: Xavier
 * Date: 09/01/2015
 * Time: 13:12
 */


function uiu_login(){
    $path = drupal_get_path('module','uiu').'/blocks/login';
    global $base_url;
    $text = t('Logo of !sitename',Array('!sitename' => $base_url));
    if(variable_get('theme_default', NULL) == 'reutilitza') $logo = theme('image',$path.'/logo.png',$text,$text);
    $form_html = drupal_get_form('user_login_block');
    $new_pass = l(t('Request new password'), 'user/password', array('attributes' => array('title' => t('Request new password via e-mail.'))));
    $new_user = theme('sbutton','uiu_login_new_user',t('Create new account'),null,Array('type' => 'link', 'link' => url('user/register')),UI_THEME_TYPE::EMPHASIS);
    return '<div id="uiu_login">'.$logo.'<div id="uiu_login_form">'.$form_html."</div><div id='uiu_login_buttons'>$new_pass$new_user</div></div>";
}


/**
 * Implements hook_form_alter().
 */
function uiu_form_user_login_block_alter(&$form, &$form_state){
    $form['name']['#attributes']['placeholder'] = $form['name']['#title'];
    $form['pass']['#attributes']['placeholder'] = $form['pass']['#title'];
    unset($form['links']);
}