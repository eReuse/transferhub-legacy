<?php
/**
 * Created by PhpStorm.
 * User: Xavier
 * Date: 27/12/2014
 * Time: 14:14
 */

/**
 * Preprocess function to create the box from the view.
 * @param $vars
 */
function template_preprocess_box_view(&$vars){
    $vars['rows_html'] = Array();
    foreach($vars['rows'] as $id => $row)
        $vars['rows_html'][$id] = theme('box', $row, UI_THEME_TYPE::NORMAL, true, 'article',
            Array(
                'class' =>' box_view',
                'href' => url('node/'.$vars['view']->result[$id]->nid),
                'style' => "width:{$vars['options']['box_width']}%;",
            ));
/*
    $vars['rows_html'] = Array();
    foreach($vars['rows'] as $id => &$row){
        $vars['rows_html'][$id] = '<a class="box normal box_view" href="'.url('node/'.$vars['view']->result[$id]->nid).'" style="width:'.$vars['options']['box_width'].'%;">'.$row.'</a>';
    }*/
}