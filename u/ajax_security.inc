<?php

/**
 * Gets an unique token to give back to an ajax request and saves it into the session.
 * @param $id int|string Unique id for the token. Not use in generating the ID.
 * @return string token
 * @see u_ajax_check_unique_token check it with that function
 */
function u_ajax_generate_unique_token($id){
    return ($_SESSION['u_ajax_token'][$id] = uniqid('',true));
}

/**
 * Checks the token with the one the server has.
 * @param $id int
 * @param $token string token generated with u_ajax_get_unique_token
 * @param bool $destroy_after true if want to destroy the saved cookie so it cannot be reused
 * @return bool
 * @see u_ajax_generate_unique_token
 */
function u_ajax_check_unique_token($id,$token,$destroy_after = true){
    $saved_cookie = $_SESSION['u_ajax_token'][$id];
    if($destroy_after) unset($_SESSION['u_ajax_token'][$id]);
    return $saved_cookie === $token;
}