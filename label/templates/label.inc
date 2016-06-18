<?php
/**
 * Created by PhpStorm.
 * User: Xavier
 * Date: 03/03/2015
 * Time: 19:05
 */

function template_preprocess_label(&$vars){
    $vars['qr_html'] = theme('qr',$vars['nid']);
    $vars['logo_html'] = theme('image',$vars['logo'],'QR logo','QR logo',null,false);
    $data = Array();
    uasort($vars['lines'],'label_sort');        //We sort the lines by the position
    foreach($vars['lines'] as $field_name => $line)
        if($line['set_in_attr']) $data['data-'.$field_name] = $line['value'];
    $vars['attributes_html'] = drupal_attributes($data + Array(
        'class' => 'label',
        'id' => 'label_'.$vars['nid'],
        'style' =>  "margin-top:{$vars['space']['vertical']}mm; margin-right:{$vars['space']['horizontal']}mm;".
                    "width:{$vars['size']['width']}mm; height:{$vars['size']['height']}mm;".$vars['style']
    ));
}

function label_sort($a,$b){
    if($a['position'] == $b['position']) return 0;
    else return ($a['position'] < $b['position'])? -1 : 1;
}