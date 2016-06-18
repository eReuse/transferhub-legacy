<?php
/**
 * Created by PhpStorm.
 * User: Xavier
 * Date: 03/03/2015
 * Time: 20:24
 */



function theme_qr($nid){
    require_once(_label_get_qr_lib_uri());
    $saving_path = file_directory_path().'/'.LABEL_FILE_PATH.'/'.LABEL_QR_TEMP_PATH."/$nid.png";
    QRcode::png(_label_get_qr_url($nid),$saving_path,"H",4,2);
    $text = "QR for $nid";
    return theme('image',$saving_path,$text,$text);
}



/**
 * Gets a
 * @param $nid
 * @param $uid
 */
function _label_get_qr_url($nid){
    global $base_url;
    return $base_url.url('node/'.$nid);
}