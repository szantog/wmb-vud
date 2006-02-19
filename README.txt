Drupal vote_up_down and vote_storylink module:
---------------------------------------------
Author - Fredrik Jonsson <fredrik at combonet dot se>
Requires - Drupal 4.7
License - GPL (see LICENSE)


Overview:
--------
These two modules is a attempt to build a digg.com/reddit.com clone
for Drupal. They build upon a number of other module, se below.

This is not a point and click solution. This project provide the
missing pieces but you need to put them all together.

Pages that are generated:
* storylink (same as storylink/new)
* storylink/new
* storylink/top

Feed that are generated:
* storylink/new/feed
* storylink/top/feed


Installation and configuration:
------------------------------
You first need to install the following modules:
* Links Package http://drupal.org/node/24719
* Voting API http://drupal.org/node/36041
  (cvs version after 2006-02-09 of Voting API)

To be able to automatically promote storylinks that have a specified
number of votes to the front page you also need to install: 
* Actions http://drupal.org/project/actions
* Voting Actions http://drupal.org/node/46895

Installation is as simple as creating a directory named 
'vote_up_down' in your 'modules' directory and
copying the module and the images into it, then 
enabling the modules at 'administer >> modules'.

For configuration options go to 'administer >> settings
>> vote_up_down.


Bookmarklet to submit story links:
---------------------------------
javascript:location.href='http://www.example.com/node/add/storylink?edit[url]='+encodeURIComponent(location.href)+'&edit[title]='+encodeURIComponent(document.title)

Replace "www.example.com" with your domain.


Theme story links:
-----------------
If you use a PHPTemplate theme you can theme storylinks nodes
with a "node-storylink.tpl.php" file. An example is included.
