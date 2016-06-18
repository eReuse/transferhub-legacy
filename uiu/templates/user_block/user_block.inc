<?php
/**
 * Created by PhpStorm.
 * User: Xavier
 * Date: 11/01/2015
 * Time: 19:37
 */

function template_preprocess_user_block(&$vars){
    global $user;
    profile_load_profile($user);
    $vars['profile_name'] = $user->profile_name;
    $vars['profile_surname'] = $user->profile_surname;
    $vars['name'] = $user->name;
    $vars['account_title'] = t('Account');
    $vars['view_account'] = l(t('View my account'),"user/$user->uid");
    $vars['edit_account'] = l(t('Edit my account'),"user/$user->uid/edit");
    $vars['edit_personal_info'] = l(t('Edit personal information'),"user/$user->uid/edit/Informaci%C3%B3%20personal");
    $vars['newsletter_title'] = t('Newsletter');
    $vars['manage_subscriptions'] = l(t('Manage my subscriptions'),"user/$user->uid/edit/newsletter");
    $vars['logout'] = theme('sbutton','user_block_logout',t('Logout'),null,
        Array('type'=>'link','link'=>url('logout')),UI_THEME_TYPE::EMPHASIS);
    $vars['picture'] = uiu_get_user_picture_small();
}