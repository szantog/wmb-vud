<?php
// $Id$

/* TODO FormAPI image buttons are now supported.
   FormAPI now offers the 'image_button' element type, allowing developers to
   use icons or other custom images in place of traditional HTML submit buttons.

$form['my_image_button'] = array(
  '#type'         => 'image_button',
  '#title'        => t('My button'),
  '#return_value' => 'my_data',
  '#src'          => 'my/image/path.jpg',
); */

/* TODO New user_mail_tokens() method may be useful.
   user.module now provides a user_mail_tokens() function to return an array
   of the tokens available for the email notification messages it sends when
   accounts are created, activated, blocked, etc. Contributed modules that
   wish to make use of the same tokens for their own needs are encouraged
   to use this function. */

/* TODO
   There is a new hook_watchdog in core. This means that contributed modules
   can implement hook_watchdog to log Drupal events to custom destinations.
   Two core modules are included, dblog.module (formerly known as watchdog.module),
   and syslog.module. Other modules in contrib include an emaillog.module,
   included in the logging_alerts module. See syslog or emaillog for an
   example on how to implement hook_watchdog.
function example_watchdog($log = array()) {
  if ($log['severity'] == WATCHDOG_ALERT) {
    mysms_send($log['user']->uid,
      $log['type'],
      $log['message'],
      $log['variables'],
      $log['severity'],
      $log['referer'],
      $log['ip'],
      format_date($log['timestamp']));
  }
} */

/* TODO Implement the hook_theme registry. Combine all theme registry entries
   into one hook_theme function in each corresponding module file.
function template_theme() {
  return array(
  );
} */

function _phptemplate_variables($hook, $vars) {
  switch($hook) {
    case 'node':
      $vars['storylink_url'] = check_url($vars['node']->vote_storylink_url);
      if (arg(1) != 'add' && arg(2) != 'edit') {
        $style = variable_get('vote_up_down_widget_style_node', 0) == 1 ? '_alt' : '';
        $vars['vote_up_down_widget'] = theme("vote_up_down_widget$style", $vars['node']->nid, 'node');
        $vars['vote_up_down_points'] = theme("vote_up_down_points$style", $vars['node']->nid, 'node');
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
