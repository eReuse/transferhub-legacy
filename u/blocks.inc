<?php
/**
 * Created by PhpStorm.
 * User: Xavier
 * Date: 29/12/2014
 * Time: 13:10
 */


/**
 * Gets a themed block.
 *
 * @see http://valerio.della-porta.com/node/20
 *
 * @param string $type
 * - If the block is generated by the user: use 'block'
 * - If the block is implemented by a module: Write the name of the module.
 * @param string|int $blockId
 * - If the block is generated by the user: Id of the block. To get it go to admin/build/block and then get the url of the configuration of the block. It's the number at the end.
 * - If the block is implemented by a module: delta of the block. See the block implementation for more info.
 * @param bool $subject Decide if print the title of the block or not.
 * @return string HTML output of the block.
 */
function u_get_themed_block($type,$blockId = 0,$subject = true){
    $block = (object) module_invoke($type, 'block', 'view', $blockId);
    $block->module = $type;
    $block->delta = $blockId;
    if(!$subject) unset($block->subject);
    return theme('block', $block);
}