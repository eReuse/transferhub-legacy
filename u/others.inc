<?php
/**
 * Created by PhpStorm.
 * User: Xavier
 * Date: 07/01/2015
 * Time: 20:18
 */

/**
 * Prints a custom access denial <i>and stops executing more code</i>.
 * Is based of the code of drupal_access_denied()
 * @version 6
 * @see drupal_access_denied()
 */
function u_accesDenial($element, $http_error_code = 403, $http_error_message = 'Forbidden', $custom_message = 'Access denied') {
drupal_set_header($_SERVER['SERVER_PROTOCOL'] . $http_error_code . $http_error_message);

watchdog('access denied', check_plain($_GET['q']), NULL, WATCHDOG_WARNING);

// Keep old path for reference, and to allow forms to redirect to it.
if (!isset($_REQUEST['destination'])) {
    $_REQUEST['destination'] = $_GET['q'];
}
drupal_set_title(t($custom_message));
print theme('page', $element);
module_invoke_all('exit');
exit();
}



/**
 * Adds a path to the theme discovery.
 *
 * Use this method as a workaround to modules to provide .tpl.php files for themes. The system will look for them in
 * path before looking in any other place or theme. Invoke this method in hook_theme_registry_alter
 *
 * - See https://www.drupal.org/node/715160
 *
 * @param $theme_registry Array Theme registry as hook_theme_registry_alter
 * @param $hooks String[] Template names to override
 * @param $path String path to look for templates
 */
function u_add_theme_path(&$theme_registry,$hooks,$path){
    foreach($hooks as $h)
        array_unshift($theme_registry[$h]['theme paths'], $path);
}


function u_get_internal_error_message($code){
    $array = Array(
        /*User derived errors*/
        4001 => Array(
                'devMessage' => 'Logged in user used another Facebook id to vote before',
                'userMessage' => t('You voted or shared before with another Facebook account. To vote with this Facebook account, log out first.'),
        ),
        4002 => Array(
            'devMessage' => 'User has already performed this social action',
            'userMessage' => t('You have already performed this social action.'),
        ),
        4003 => Array(
            'devMessage' => 'User needs to vote first',
        ),
        4004 => Array(
            'devMessage' => 'It already exists.',
        ),
        /*Programming client errors*/
        /*Data that should be validated by the client, but here is done it again for checking purposes*/
        6001 => Array(
            'devMessage' => 'The passed in value is not correct',
        ),
        7001 => Array(
            'devMessage' => 'Form error',
        ),
        /*Internal server errors*/
        5000 => Array(
            'devMessage' => 'Undefined internal Error. Needs to provide details.',
            'userMessage' => t('There has been an error. Please, contact the site administrator'),
        ),

    );
    return $array[$code];
}


