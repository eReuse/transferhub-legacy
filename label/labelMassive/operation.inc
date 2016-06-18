<?php
/**
 * Created by PhpStorm.
 * User: Xavier
 * Date: 04/03/2015
 * Time: 17:28
 */

/**
 * Implements hook_node_operations().
 */
function labelMassive_node_operations(){
    return Array(
        'labelMassive_nodes' => Array(
            'label' => t('Let\'s the user select multiple nodes to label them in one page.'),
            'configurable' => true,
            'callback' => 'labelMassive_label_op'
        )
    );
}

function labelMassive_label_op_form(){
    global $user;
    if(module_exists('labelPresets')){
        return Array('preset' => labelPresets_get_form_selector($user->uid));
    }
    return Array();
}

function labelMassive_label_op_submit($form,$form_state){
    return Array(
        'preset' => $form_state['values']['preset']
    );
}

function labelMassive_label_op($nids, $preset){
    drupal_goto(LABEL_MASSIVE_URL,Array('nids' => $nids, 'preset' => $preset),null,303);
}