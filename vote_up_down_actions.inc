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
function vote_up_down_actions_theme() {
  return array(
  );
} */

/**
 * @file
 * Contains Drupal actions and actions sets for use with vote_up_down.module and the Voting API..
 */

/**
 * Implementation of hook_votingapi_action_sets().
 */
/* function vote_up_down_votingapi_action_sets() { */
/*   $sets = array( */
/*     'vote_up_down_promotion' => array( */
/*       'description' => 'Promotes a node to the front page if enough users vote for it.', */
/*       'content_type' => 'node', */
/*       'condition_mask' => 'AND', */
/*       'enabled' => 1, */
/*       'source' => 'vote_up_down', */
/*  */
/*       'conditions' => array( */
/*         'is_promoted' => array( */
/*           'description' => 'Node is not promoted', */
/*           'handler' => 'votingapi_node_properties_handler', */
/*           'data' => array( */
/*             'property' => 'promote', */
/*             'comparison' => '!=', */
/*             'value' => 1, */
/*           ), */
/*         ), */
/*         'min_vote' => array( */
/*           'description' => 'Sum higher than 5', */
/*           'handler' => 'votingapi_vote_result_handler', */
/*           'data' => array( */
/*             'tag' => 'vote', */
/*             'function' => 'sum', */
/*             'comparison' => '>', */
/*             'value' => 5, */
/*           ), */
/*         ), */
/*       ), */
/*       'actions' => array( */
/*         'action_node_promote', */
/*         'action_vote_up_down_userpoints_add', */
/*       ), */
/*     ), */
/*  */
/*     'vote_up_down_demotion' => array( */
/*       'description' => 'Demote a node from the front page if enough users vote against it.', */
/*       'content_type' => 'node', */
/*       'condition_mask' => 'AND', */
/*       'enabled' => 1, */
/*       'source' => 'vote_up_down', */
/*  */
/*       'conditions' => array( */
/*         'is_promoted' => array( */
/*           'description' => 'Node is promoted', */
/*           'handler' => 'votingapi_node_properties_handler', */
/*           'data' => array( */
/*             'property' => 'promote', */
/*             'comparison' => '=', */
/*             'value' => 1, */
/*           ), */
/*         ), */
/*         'min_vote' => array( */
/*           'description' => 'Sum lower than 0', */
/*           'handler' => 'votingapi_vote_result_handler', */
/*           'data' => array( */
/*             'tag' => 'vote', */
/*             'function' => 'sum', */
/*             'comparison' => '<', */
/*             'value' => 0, */
/*           ), */
/*         ), */
/*       ), */
/*       'actions' => array( */
/*         'action_node_unpromote', */
/*         'action_vote_up_down_userpoints_remove', */
/*       ), */
/*     ), */
/*  */
/*   ); */
/*  */
/*  */
/*   return $sets; */
/* } */

/**
 * Implementation of a Drupal action.
 * Award userpoint to node author.
 */
function action_vote_up_down_userpoints_add($op, $edit = array(), &$node) {
  switch ($op) {
    case 'metadata':
      return array(
        'description' => t('Award userpoint to node author (Vote up/down)'),
        'type' => t('Node'),
        'batchable' => FALSE,
        'configurable' => FALSE,
      );

    case 'do':
      userpoints_userpointsapi('points', variable_get('userpoints_actions', 0), $node->uid);
      watchdog('action', 'Awarded userpoint to author of node id %id', array('%id' => intval($node->nid)));
      break;

    // return an HTML config form for the action
    case 'form':
      return '';

    // validate the HTML form
    case 'validate':
      return TRUE;

    // process the HTML form to store configuration
    case 'submit':
      return '';
  }
}

/**
 * Implementation of a Drupal action.
 * Deduct userpoint from node author.
 */
function action_vote_up_down_userpoints_remove($op, $edit = array(), &$node) {
  switch ($op) {
    case 'metadata':
      return array(
        'description' => t('Deduct userpoint from node author (Vote up/down)'),
        'type' => t('Node'),
        'batchable' => FALSE,
        'configurable' => FALSE,
      );

    case 'do':
      userpoints_userpointsapi('points', -variable_get('userpoints_actions', 0), $node->uid);
      watchdog('action', 'Deducted userpoint from author of node id %id', array('%id' => intval($node->nid)));
      break;

    // return an HTML config form for the action
    case 'form':
      return '';

    // validate the HTML form
    case 'validate':
      return TRUE;

    // process the HTML form to store configuration
    case 'submit':
      return '';
  }
}

/**
 * Touches the creation date of a node. Useful for moderated nodes that should appear
 * 'fresh' as soon as they're promoted.
 */
function action_vote_up_down_node_touch_created($op, $edit = array(), &$node) {
  switch ($op) {
    case 'metadata':
      return array(
        'description' => t('Touch node creation date (Vote up/down)'),
        'type' => t('Node'),
        'batchable' => TRUE,
        'configurable' => FALSE,
      );

    case 'do':
      $node->created = time();
      if (!$edit['defer']) {
        node_save($node);
      }
      watchdog('action', 'Touched creation date of node id %id', array('%id' => intval($node->nid)));
      break;

    // return an HTML config form for the action
    case 'form':
      return '';

    // validate the HTML form
    case 'validate':
      return TRUE;

    // process the HTML form to store configuration
    case 'submit':
      return '';
  }
}

/**
 * Touches the change date of a node. Useful for moderated nodes that should appear
 * 'fresh' as soon as they're promoted.
 */
function action_vote_up_down_node_touch_changed($op, $edit = array(), &$node) {
  switch ($op) {
    case 'metadata':
      return array(
        'description' => t('Touch node change date (Vote up/down)'),
        'type' => t('Node'),
        'batchable' => TRUE,
        'configurable' => FALSE,
      );

    case 'do':
      $node->changed = time();
      if (!$edit['defer']) {
        node_save($node);
      }
      watchdog('action', 'Touched change date of node id %id', array('%id' => intval($node->nid)));
      break;

    // return an HTML config form for the action
    case 'form':
      return '';

    // validate the HTML form
    case 'validate':
      return TRUE;

    // process the HTML form to store configuration
    case 'submit':
      return '';
  }
}
