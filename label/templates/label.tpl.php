<?php
/**
 * Created by PhpStorm.
 * User: Xavier
 * Date: 03/03/2015
 * Time: 19:13
 */

?><article <?php print $attributes_html; ?>>
    <div>
        <figure class="logo">
            <?php print $logo_html; ?>
        </figure>
    </div>
    <div>
        <figure class="qr">
            <?php print $qr_html; ?>
        </figure>
        <div class="label_text">
            <?php foreach($lines as $element): ?>
                <?php if($element['visible']): ?>
                    <div class="line">
                        <span class="title"><?php print $element['title']; ?></span>
                        <span class="text"><?php print $element['value']; ?></span>
                    </div>
                <?php endif ?>
            <?php endforeach ?>
        </div>
    </div>
</article>