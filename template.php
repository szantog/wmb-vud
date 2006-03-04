<?php
function _phptemplate_variables($hook, $vars) {
  switch($hook) {
    case 'node' :
      if (arg(1) != 'add' && arg(1) != 'edit') {
        $vars['vote_up_down_widget'] = theme('vote_up_down_widget', $vars['node']->nid, 'node');
      }
      $vars['vote_storylink_via'] = theme('vote_storylink_via', $vars['node']->vote_storylink_url);
      break;
  }
  return $vars;
}
?>
