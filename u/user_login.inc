<?php
/**
 * Created by PhpStorm.
 * User: Xavier
 * Date: 19/01/2015
 * Time: 9:51
 */

function u_form_user_register_alter(&$form, &$form_state){
    $form['#redirect'] = 'user/registered';
//    $form['redirect'] = 'user/registered';
}