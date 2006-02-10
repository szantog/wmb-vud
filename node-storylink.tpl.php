
<!-- start node -->
<div class="node storylink<?php print ($sticky) ? " sticky" : ""; ?>">
<?php print $picture ?>
<h2><a href="<?php print $node->vote_storylink_url ?>"><?php print $title ?></a></h2>
<?php print theme('vote_storylink_via', $node->vote_storylink_url); ?>
<?php print theme('vote_up_down_widget', $node->nid, 'node'); ?>
<div class="content">
<?php print $content ?>
</div>
<div class="info"><?php print $submitted ?>
<?php if ($terms): ?>
<span class="terms"> | <?php print t('Category') ?>: <?php print $terms ?></span>
<?php endif; ?>
</div>
<?php if ($links): ?>
<div class="links"><?php print $links ?></div>
<?php endif; ?>
<br class='clear' />
</div>
