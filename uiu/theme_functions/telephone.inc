<?php
/**
 * Created by PhpStorm.
 * User: Xavier
 * Date: 06/02/2015
 * Time: 12:30
 */

/**
 * Inserts a telephone number where user can call just pressing on it (HTML 5 compliant)
 *
 * @param $prefix String Set the worldwide prefix
 * @param $number int|String set the number
 * @param bool $show_prefix Set is show the prefix or not
 * @return string
 */
function theme_telephone($prefix,$number,$show_prefix = false){
    $show = $show_prefix? $prefix : '';
    return "<a href='tel:$prefix$number'>$show$number</a>";
}