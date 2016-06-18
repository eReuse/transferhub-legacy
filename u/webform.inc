<?php
/**
 * Created by PhpStorm.
 * User: Xavier
 * Date: 18/01/2015
 * Time: 23:58
 */

/**
 * Implementation of hook_nodeapi.
 *
 * -Brings translation to webform's title.
 * @param $node
 * @param $op
 */
function u_nodeapi(&$node, $op){
    if($node->type == 'webform' && $op == 'view'){
        $node->title = t($node->title);
    }

}

/**
 * Implementation of hook_alter.
 *
 * - Brings translation to webform form labels and markup, integrating it with 18n.
 * @param $form
 * @param $form_state
 * @param $form_id
 */
function u_form_alter(&$form, &$form_state, $form_id){
  //  dpm($form,'form');
  //  dpm($form_state,'form_state');
   // dpm($form_id,'fid');
    if(strpos($form_id,'webform_client_form')!==false){
        foreach($form['submitted'] as &$elem) {
            if (is_string($elem['#title']))
                $elem['#title'] = t($elem['#title']);
            if(is_string($elem['#markup']))
                $elem['#markup'] = t($elem['#markup']);
        }
    }
}