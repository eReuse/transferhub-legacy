<?php
/**
 * Created by PhpStorm.
 * User: Xavier
 * Date: 11/01/2015
 * Time: 19:37
 */

?>
<figure id="user_block_figure">
    <?php print $picture; ?>
    <figcaption>
        <?php print $name; ?>
    </figcaption>
</figure>
<div id="names"><?php print $profile_name.' '.$profile_username;?></div>
<div>
    <h4><?php print $account_title; ?></h4>
    <div><?php print $view_account; ?></div>
    <div><?php print $edit_account; ?></div>
    <div><?php print $edit_personal_info; ?></div>
</div>
<div>
    <h4><?php print $newsletter_title;?></h4>
    <div><?php print $manage_subscriptions;?></div>
</div>
<?php print $logout;?>