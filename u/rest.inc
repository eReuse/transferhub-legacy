<?php
/**
 * Created by PhpStorm.
 * User: Xavier
 * Date: 17/02/2015
 * Time: 16:44
 */

function u_get_input_values(){
    $return = Array();
    parse_str(file_get_contents("php://input"),$return);
    return $return;
}


/**
 * gets the requested method. This is, GET / POST / Put...
 * @return mixed
 */
define('U_POST','POST');
define('U_GET', 'GET');
define('U_PUT', 'PUT');
define('U_DELETE', 'DELETE');
function u_get_request_method(){
    return $_SERVER['REQUEST_METHOD'];
}

/**
 * Sets the answer's status code using a predefined HTTP status code.
 * @param $code int
 * @throws UnexpectedValueException when code is not a predefined HTTP status code
 */
function u_set_status_code($code){
    switch ($code) {
        case 100: $text = 'Continue'; break;
        case 101: $text = 'Switching Protocols'; break;
        case 200: $text = 'OK'; break;
        case 201: $text = 'Created'; break;
        case 202: $text = 'Accepted'; break;
        case 203: $text = 'Non-Authoritative Information'; break;
        case 204: $text = 'No Content'; break;
        case 205: $text = 'Reset Content'; break;
        case 206: $text = 'Partial Content'; break;
        case 300: $text = 'Multiple Choices'; break;
        case 301: $text = 'Moved Permanently'; break;
        case 302: $text = 'Moved Temporarily'; break;
        case 303: $text = 'See Other'; break;
        case 304: $text = 'Not Modified'; break;
        case 305: $text = 'Use Proxy'; break;
        case 400: $text = 'Bad Request'; break;
        case 401: $text = 'Unauthorized'; break;
        case 402: $text = 'Payment Required'; break;
        case 403: $text = 'Forbidden'; break;
        case 404: $text = 'Not Found'; break;
        case 405: $text = 'Method Not Allowed'; break;
        case 406: $text = 'Not Acceptable'; break;
        case 407: $text = 'Proxy Authentication Required'; break;
        case 408: $text = 'Request Time-out'; break;
        case 409: $text = 'Conflict'; break;
        case 410: $text = 'Gone'; break;
        case 411: $text = 'Length Required'; break;
        case 412: $text = 'Precondition Failed'; break;
        case 413: $text = 'Request Entity Too Large'; break;
        case 414: $text = 'Request-URI Too Large'; break;
        case 415: $text = 'Unsupported Media Type'; break;
        case 500: $text = 'Internal Server Error'; break;
        case 501: $text = 'Not Implemented'; break;
        case 502: $text = 'Bad Gateway'; break;
        case 503: $text = 'Service Unavailable'; break;
        case 504: $text = 'Gateway Time-out'; break;
        case 505: $text = 'HTTP Version not supported'; break;
        default: throw new UnexpectedValueException($code.' is not a predefined HTTP status code');
    }
    drupal_set_header($_SERVER['SERVER_PROTOCOL'] .' '.$code.' '.$text);
}

function u_correct_json($var){
    drupal_set_header('Content-Type: application/json');
    print json_encode($var);
    module_invoke_all('exit');
    exit;
}

/**
 * Generates an error response for a REST body-answer and appends it to the appropriate place in the response Array.
 *
 * You can send more than one error.
 * @param $code int Internal Error Code
 * @param null $details string Details that provide extra info for this concrete error
 * @param array $response Response array to append the error to
 * @return array The returned response
 */
function u_add_rest_error($code,$details = null,$response = Array('errors' => Array())){
    $error =  u_get_internal_error_message($code);
    $response['errors'][] = Array('code' => $code, 'devMessage' => $error['devMessage'], 'userMessage' => isset($error['userMessage'])? $error['userMessage'] : '', 'details' => $details);
    return $response;
}

function u_is_requested_media_type($media_type){
    return strpos($_SERVER['HTTP_ACCEPT'],$media_type) !== false;
}

function u_send_empty_error($error_code){
    u_set_status_code($error_code); module_invoke_all('exit'); exit;
}

function u_get_range(){
    //http://stackoverflow.com/questions/2209204/parsing-http-range-header-in-php
}

function u_set_status_code_and_exit($status_code){
    u_set_status_code($status_code); module_invoke_all('exit'); exit;
}
