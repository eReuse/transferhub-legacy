<?php
/**
 * Created by PhpStorm.
 * User: Xavier
 * Date: 04/03/2015
 * Time: 20:12
 */

/**
 * REST CRUD methods for working with one unique preset.
 * @param $user
 * @param $preset
 */
function labelPresets_user_presets_specific($user,$preset){
    if(u_is_requested_media_type('json')){
        switch(u_get_request_method()){
            case U_GET:
                u_correct_json($preset); break;
            case U_PUT:
                u_send_empty_error(405);
                //labelPresets_set($_POST['preset_name'], $user->uid, $_POST['logo'], $_POST['attributes'], $_POST['lines']);
                break;
            case U_DELETE:
                u_send_empty_error(405);
                //labelPresets_delete($_POST['preset_name'],$user->uid); break;
            default: u_send_empty_error(405);
        }
    } else u_send_empty_error(406);
}