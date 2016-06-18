<?php
/**
 * Created by PhpStorm.
 * User: Xavier
 * Date: 05/04/2015
 * Time: 23:26
 */

/**
 * Gets the total of social actions performed to a node divided per type of social action.
 * @param $nid int
 * @param int|null $uuid Optional. Reduces the results taking just the uuid.
 * @return array [type of social action] = times actioned
 */
function socialActions_get($nid, $uuid = null){
    $uuid_query = is_null($uuid)? '' : ' AND uuid = %d';
    $array =
        u_fetch_all_array(
            db_query("SELECT COUNT(*) AS votes FROM social_actions WHERE nid=%d $uuid_query GROUP BY type",$nid,$uuid
            )
        );    //MyISAM should save rows in index = ++fast
    if (sizeof($array) == 0) $array[0]['votes'] = 0;
    return $array;
}

function socialActions_has_user_voted($uuid, $nid){
    //u_correct_json(Array('u'=>$uuid, 'n'=>$nid));
    return db_result(db_query('SELECT 1 FROM social_actions WHERE uuid =%d AND nid=%d',$uuid, $nid));
}

/**
 * Sets a social action.
 *
 * @param $nid int Node id
 * @param $uid int User id
 * @param $facebook_id int Facebook id
 * @param $type String Defined as xsr_social_actions_get_type_of_actions
 * @return bool True or false depending if has been or not an error.
 *
 */
function socialActions_set($nid,$uid,$facebook_id,$type){
    //u_correct_json(Array('uuid'=>$facebook_id, 'nid'=>$nid, 'uid'=>$uid, 'ip'=> ip_address()));
    $uuid = _socialActions_get_or_generate_uuid($uid, $facebook_id);
     return db_query("INSERT INTO social_actions (uuid,nid,type,ip) VALUES(%d,%d,%d,'%s')",$uuid,$nid,$type,ip_address());
}

/**
 * Both parameters can't be null.
 * @param $uid
 * @param $facebook_id
 * @return int uuid
 */
function _socialActions_get_or_generate_uuid($uid = null, $facebook_id = null){
    $uuid = socialActions_get_uuid($uid, $facebook_id);
    #u_correct_json(Array('uuid'=>$uuid, 'b'=>$facebook_id, 'uid'=>$uid));
    if($uuid === false)
        $uuid = _socialActions_generate_uuid($uid, $facebook_id);
    return $uuid;
}

function _socialActions_generate_uuid($uid, $facebook_id){
    if(!is_null($uid) && !is_null($facebook_id)){
        //We know the combination uid and facebook id does not exist
        //We detect if facebook and user matches
        $count = db_result(db_query('SELECT COUNT(*) FROM social_actions_uuid WHERE (facebook_id=%d AND uid IS NOT NULL) OR (uid=%d AND facebook_id IS NOT NULL)', $facebook_id, $uid));
        if($count > 0) throw new DrupalAndFacebookMismatch();
        //Now we detect if facebook voted without drupal once, and/or drupal voted without facebook once
        $result = db_query('SELECT * FROM social_actions_uuid WHERE facebook_id=%d OR uid=%d', $facebook_id, $uid);
        $array = u_fetch_all_array($result);
        if(sizeof($array) == 0) _socialActions_insert_uuid($facebook_id, $uid); //Adds new with both fb_id and uid
        elseif(sizeof($array) == 1) _socialActions_update_uuid($array[0]['uuid'], $facebook_id, $uid); //Updates existing fb_id or uid with the other's value
        elseif(sizeof($array) == 2) _socialActions_merge_uuid($array[0]['uuid'], $array[1]['uuid'], $facebook_id, $uid);
    }
    else _socialActions_insert_uuid($facebook_id, $uid);
    return socialActions_get_uuid($uid, $facebook_id);
}

function _socialActions_insert_uuid($facebook_id, $uid){
    $fb_placeholder = $uid_placeholder = '%d';
    if(is_null($uid)){
        $uid1 = 'NULL';
        $uid_placeholder = '%s';
    } else $uid1 = $uid;
    if(is_null($facebook_id)){
        $facebook_id1 = 'NULL';
        $fb_placeholder = '%s';
    } else $facebook_id1 = $facebook_id;
    db_query("INSERT INTO social_actions_uuid (uid, facebook_id) VALUES($uid_placeholder, $fb_placeholder)", $uid1, $facebook_id1); //'%s' for the nulls
}

/**
 * @param $uuid not null
 * @param $facebook_id . not null
 * @param $uid . not null
 */
function _socialActions_update_uuid($uuid, $facebook_id, $uid){
    db_query('UPDATE social_actions_uuid SET facebook_id=%d, uid=%d WHERE uuid=%d', $facebook_id, $uid, $uuid);
}

function _socialActions_merge_uuid($uuid_to_delete, $uuid2, $facebook_id, $uid){
    $params = Array();
    $result = u_fetch_all_array(db_query('SELECT nid FROM social_actions WHERE type=0 AND uuid=%d', $uuid2));
    foreach($result as $val) $params[] = intval($val['nid']);
    $placeholders = db_placeholders($params);
    array_unshift($params, $uuid_to_delete);
    db_query("DELETE FROM social_actions WHERE uuid=%d AND type=0 AND nid IN ($placeholders)", $params);
    db_query('DELETE FROM social_actions_uuid WHERE uuid=%d', $uuid_to_delete);
    _socialActions_update_uuid($uuid2, $facebook_id, $uid);
}

/**
 * Gets all the uuid table or false, if it doesn't exists.
 * <b>Both parameters can't be null.</b>
 *
 * @param $uid int|null
 * @param $facebook_id int|null
 * @return int|false uuid or false if doesn't exist
 */
function socialActions_get_uuid($uid = null, $facebook_id = null){
    if(is_null($uid))
        return db_result(db_query('SELECT uuid FROM social_actions_uuid WHERE facebook_id=%d',$facebook_id));
    elseif(is_null($facebook_id))
        return db_result(db_query('SELECT uuid FROM social_actions_uuid WHERE uid=%d',$uid));
    else
        return db_result(db_query('SELECT uuid FROM social_actions_uuid WHERE uid=%d AND facebook_id=%d',$uid,$facebook_id));
}

/**
 * Checks if the facebook id is from the same user id
 * @param $uid int
 * @param $facebook_id int
 * @return bool
 */
function socialActions_check_fb_id_uid($uid, $facebook_id){
    $sql = "SELECT COUNT(*) FROM social_actions_uuid WHERE (uid=%d AND facebook_id IS NULL) AND (facebook_id=%d OR facebook_id IS NULL)";
    return db_result(db_query($sql, $uid, $facebook_id)) == 1; //If there is more than 1, fb_id is from another drupal account
}

/**
 * Sets the user type
 * @param $nid int
 * @param $uuid int
 * @param $user_type string
 * @return bool False indicating that has been a problem with de db or no vote has found to update the type of user.
 */
function socialActions_set_user_type($nid,$uuid,$user_type){
    $result = db_query("UPDATE social_actions SET user_type=%d WHERE nid=%d AND uuid=%d AND type=%d",$user_type,$nid,$uuid,SOCIALACTIONS_VOTE);
    return $result && db_affected_rows();
}

class DrupalAndFacebookMismatch extends Exception{

}