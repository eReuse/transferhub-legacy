<?php
/**
 * Created by PhpStorm.
 * User: Xavier
 * Date: 04/03/2015
 * Time: 19:02
 */

/**
 * REST CRUD methods for working with presets
 * @param $user
 */
function labelPresets_user_presets($user){
    if(u_is_requested_media_type('json')){
        switch(u_get_request_method()){
            case U_GET:
                u_correct_json(labelPresets_getPresets($user->uid));
                break;
            case U_POST:
                try {
                    labelPresets_create($_POST['preset_name'], $user->uid, $_POST['logo'], $_POST['attributes'], $_POST['lines']);
                }
                catch(Exception $err){
                    u_set_status_code(400);
                    u_correct_json(u_add_rest_error(4004, $err->getMessage()));
                }
                break;
            default: u_send_empty_error(405);
        }
    }
    else u_send_empty_error(406);
}