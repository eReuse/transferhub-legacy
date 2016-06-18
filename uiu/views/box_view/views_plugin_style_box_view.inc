<?php
class views_plugin_style_box_view extends views_plugin_style_default{
    function option_definition() {
        $options = parent::option_definition();
        $options['box_width'] = array('default'  => 25);
        $options['link_box'] = array('default'  => 0);
        return $options;
    }

    function options_form(&$form, &$form_state) {
        parent::options_form($form, $form_state);
        $form['box_width'] = array(
            '#type' => 'xsr_number',
            '#title' => 'Width of the box',
            '#default_value' => $this->options['box_width'],
        );
        $form['link_box'] = array(
            '#type' => 'checkbox',
            '#title' => 'Link box to it\'s node',
            '#default_value' => $this->options['link_box'],
        );
    }



}
?>