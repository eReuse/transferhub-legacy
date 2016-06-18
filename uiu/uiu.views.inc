<?php
/**
 * Implementation of hook_view_plugins()
 * - Registers xsr_box view plug-in
 * @return array
 */
function uiu_views_plugins() {
    $views_path = drupal_get_path('module', 'uiu').'/views';
    return array(
        'module' => 'uiu',
        'style' => array(
            'box_view' => array( //Name of plugin
                'path' => $views_path .'/box_view',
                'parent' => 'default',
                'title' => t('VBox'),
                'theme' => 'box_view',
                'theme path' => $views_path.'/box_view',
                'help' => t('Styles rows as boxes.'),
                'handler' => 'views_plugin_style_box_view',
                'uses row plugin' => true,
                'uses fields' => TRUE,
                'uses options' => true,
                'type' => 'normal',
            ),
        ),
    );
}
