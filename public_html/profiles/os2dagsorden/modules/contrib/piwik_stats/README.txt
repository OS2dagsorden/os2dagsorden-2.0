-- SUMMARY --

This module pulls statistics from piwik and stores them to fields of any entity
(eg. nodes, users, ..).


-- FEATURES --

 - Statistical information is stored in fields you can attach to any
   fieldable entity
 - Dynamic formatters to show statistical information on entities
 - Configurable 'period' parameter for each field
 - Full Views integration to build things like "Top5 Viewed Nodes"
 - Statistics summary tab on nodes and users
 - Refresh statistics on cron (queued) run or on demand (batch)
 - Currently tested with latest Version of Piwik (1.8)


-- REQUESTED DATA --

 - Unique node page views.
 - Node page views.
 - Number of visits that started on a node.
 - Number of page views for visits that started on that node.
 - Time spend, in seconds, by visits that started on this node.
 - Number of visits that started on this node and bounced
   (viewed only one page).
 - Number of visits that finished on this node.
 - Total time spend on this node, in seconds.
 - Ratio of visitors leaving the website after landing on this node
   (in percent).
 - Ratio of visitors that do not view any other page after this node
   (in percent).


-- USAGE --

 - Install as usual (http://drupal.org/node/895232)
 - Go to admin/config/system/piwik and paste in your API authentication
   token (you'll find it on your piwik site at 'API').
 - (At advanced settings you can decide whether the fields should be filled
   on cron-run)
 - Attach the piwik field to an entity of your choice (content type, user
   fields, ...)
 - Now you can fill the fields for the first time by clicking on Fill
   statistical Piwik fields on the piwik settings page


-- REQUIREMENTS --

 - A working piwik installation with API access
   http://piwik.org/
 - Installed and configured piwik module
   http://drupal.org/project/piwik
