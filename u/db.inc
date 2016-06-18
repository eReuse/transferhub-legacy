<?php
/**
 * Created by PhpStorm.
 * User: Xavier
 * Date: 17/02/2015
 * Time: 16:47
 */

/**
 * Returns the complete array of the result of a db_query().
 * @param $db_result Object db_query() result.
 * @return array Results. If there is an error the array will be empty.
 */
function u_fetch_all_array($db_result){
    $result = Array();
    while($aux = db_fetch_array($db_result)) $result[] = $aux;
    return $result;
}

/**
 * Gets the first result of applying the query
 * @param $db_query String Query. Extra parameters are passed to db_query()
 * @return object The element
 * @throws OutOfBoundsException If the element has not been found
 * @throws PDOException if it has been any error in the db
 */
function u_db_get_one_object($db_query){
    $res = db_fetch_object(call_user_func_array('db_query',array_merge(Array($db_query),func_get_args())));
    if($res === false){
        $error = db_error();
        if(!$error) throw new OutOfBoundsException('',0);
        else throw new PDOException('',db_error());
    }
    return $res;
}