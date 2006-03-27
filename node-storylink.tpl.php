
<!-- start node -->
<div class="node storylink<?php print ($sticky) ? ' sticky' : ''; ?>">
<?php print $picture ?>
<h2><a href="<?php print $storylink_url ?>"><?php print ($seqid) ? $seqid .'. ' : '' ?><?php print $title ?></a></h2>
<?php print $vote_storylink_via ?>
<?php print $vote_up_down_widget ?>
<div class="content">
<?php print $content ?>
</div>
<div class="info"><?php print $submitted ?>
<?php if ($terms): ?>
<span class="terms"> | <?php print t('Category') ?>: <?php print $terms ?></span>
<?php endif; ?>
</div>
<?php if ($links): ?>
<div class="links">&raquo; <?php print $links ?></div>
<?php endif; ?>
<br class="clear" />
</div>
