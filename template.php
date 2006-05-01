<?php
function _phptemplate_variables($hook, $vars) {
  switch($hook) {
    case 'node':
      $vars['storylink_url'] = check_url($vars['node']->vote_storylink_url);
      if (arg(1) != 'add' && arg(1) != 'edit') {
        $vars['vote_up_down_widget'] = theme('vote_up_down_widget', $vars['node']->nid, 'node');
      }
      $vars['vote_storylink_via'] = theme('vote_storylink_via', $vars['node']->vote_storylink_url);
      if (arg(1) == 'top') {
        static $count;
        $count = is_array($count) ? $count : array();
        $count[$hook] = is_int($count[$hook]) ? $count[$hook] : 1;
        $vars['seqid'] = $count[$hook]++;
      }
      break;
  }
  return $vars;
}
?>
