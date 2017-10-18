
README file for the Production check & Production monitor Drupal modules.


Introduction
============

When bringing a site live, you should double check a lot of settings, like the
error logging, site e-mail, disabling the Devel module and so on.
Next to that, you should ensure that all SEO modules are installed and properly
configured (like Google Analytics, Page Title, XML Sitemap etc.). The Production
check module will do all of this checking for you and present the results in a
convenient status page accessible through /admin/reports/prod-check. Through
this status page, you can easily navigate to all the settings pages or the
project pages of the missing modules to rectify all you need to.

It would of course also be nice that these settings remain as you set them up.
In some cases, when multiple developers make updates to a live site or with the
odd client having somehow gotten superadmin access, stuff can get changed,
usually unintended. That's where the Production monitor comes in the picture.
You can open up the Production check's XMLRPC interface through its settings
page and have the Production monitor module connect to it from a 'local'
monitoring site in your development environment. This will allow you to monitor
all your sites from a central server and keep an eye on them. When adding a site
using Production monitor, you can indicate what exactly needs to be monitored
for this site. Updates can be requested manually and are fetched automatically
each cron run.

    "But I like Nagios to monitor my sites!"

If you prefer Nagios monitoring, you can open up Production check's Nagios
integration from its settings page. You can specify what exactly you want to
monitor there. You will obviousely need to install the Nagios module to make
this functionality work.


Remote module update status monitoring
======================================
Since Production check recommends to turn of the Update module, we have
integrated its functionality in both Production check and Production monitor.
Production check can be configured to allow to transfer its module list with
versioning information once a week at a given time.
Production monitor can be configured to download this data along with all the
rest. It will then, upon your request (still need to add this on cron, but it's
a heavy operation, thinking about the best way to do this: the boost crawler
code makes a good candidate), check for module updates locally for the remote
site. Production check and Production monitor have the necessary code embedded
so you will never need to activate the Update module, not even on the monitor
site!


Performance monitoring
======================

If you install the performance module on a production site, you can use
Production monitor to remotely monitor the collected performance data. A new
subtab will be available displaying the module data in some nice Google charts.
Be sure to activate the fetching of performance data in the site's config!


Dependencies
============

- Nagios   http://drupal.org/project/nagios

There are no true dependencies defined in the .info file, but naturally you need
to install the Nagios module if you would like to integrate Production check
with your Nagios monitoring setup.

- Performance logging   http://drupal.org/project/performance

Again, no true dependencies defined, but if you want remote performance logging,
this module can provide it for you! Install it on the remote site and enable the
fetching of it's data when adding a site to Production monitor.


Development
===========
See prod_check.api.php


Installation
============

Production check
----------------
1. Extract the prod_check module and place it in /sites/all/modules/contrib

2. Remove the 'prod_monitor' folder and all it's contents

3. Upload the prod_check folder to the websites you wish to check / monitor,
 enable the module and adjust it's settings using /admin/config/system/prod-check.

4. You can check the /admin/reports/status page to verify if the Production
 check setup described above was executed correctly and no errors / warnings are
 reported.

5. You can find the result of the Production check module on
 /admin/reports/prod-check

Production monitor
------------------
1. Grab the prod_monitor folder from the package and upload it to your
 'monitoring site' and activate the module.
2. Make sure that the site you wish to monitor is running the prod_check module
3. Navigate to the prod_check settings page and activate XMLRPC and add an API
 key to 'secure' the connection. The key is limited to 128 characters.
4. Add the site to the Production monitor overview page on
 /admin/reports/prod-monitor
5. Enter the url and the API key and hit 'Get settings'. All available checks
 are now retrieved from the remote site. You can uncheck those that you do not
 wish to monitor.
6. If you wish to fetch the data immediately, check the appropriate box and save
 the settings. Good to go!

Cron setup
----------
To automatically check the site status and/or module updates on cron, you will
need to install drush and configure the following tasks in the crontab:

# Check ALL sites for updates, once a day starting at 0100H at night.
0 1 * * *    /path/to/drush -r /path/to/docroot prod-monitor-updates -y --quiet
# Fetch ALL site data every five minutes (or whatever you please obviously).
0/5 * * * *    /path/to/drush -r /path/to/docroot  prod-monitor-fetch -y --quiet

Obviously, the time and frequency of these cron jobs is at your discretion.
Do note that, depending on the number of sites you have configured, the crons
may be running for quite some time, especially the module update checking job!

Upgrading
---------
When upgrading Production monitor to a newer version, always run update.php to
verify if there are database or other updates that need to be applied!
When ignoring this step, you might get errors and/or strange behavior!

Nagios
------
1. Download and install the Nagios module from http://drupal.org/project/nagios
 as per its readme instructions
2. Enable Nagios support in the prod_check module on /admin/config/system/prod-check
 by ticking the appropriate box.
3. Untick the checkboxes for those items you do not whish to be monitored by
 Nagios.
4. Save the settings and you're good to go!

Performance logging
-------------------
1. Download and install the Nagios module from http://drupal.org/project/performance
 as per its readme instructions
2. Enable fetching of performance data on /admin/reports/prod-monitor when
 adding or editing a site.

Drush
-----
You can view the Production Check statuspage using Drush, simply by using this
command:

  $ drush prod-check

or its alias:

  $ drush pchk

A colour coded table will be printed. The information is limited to the name of
the check and the status. In the Drupal version of the status page, you have an
extra line explaining more about the curent status of a specific check.

You can easily make your site 'production ready' by using the following command:

  $ drush prod-check-prodmode

or its alias:

  $ drush pchk-pmode

This will fix most of the problems reported in the status page. You can have
some extra control on the process by adding the --config option:

  $ drush pchk-pmode --config

This will ask for some input before setting up the site.

For Production monitor, these commands are available:

  $ drush prod-monitor [id]
  $ drush prod-monitor-fetch [id]
  $ drush prod-monitor-flush [id]
  $ drush prod-monitor-delete [id]
  $ drush prod-monitor-updates [id] (--check, --security-only)

or their aliases:

  $ drush pmon [id]
  $ drush pmon-fe [id]
  $ drush pmon-fl [id]
  $ drush pmon-rm [id]
  $ drush pmon-up [id] (--check, --security-only)

The id parameter is optional for the prod-monitor command. The best usage is to
first get a list of sites:

  $ drush pmon

Now look up the id of a site, then use the other commands to act on that
specific site by passing it the id:

  $ drush pmon 3
  $ drush pmon-fl 3

You can pass multiple ID's by separating them with spaces:

  $ drush pmon 3 6 19
  $ drush pmon-fl 19 4 1

The prod-monitor-updates command acts on one id only!

APC/OPcache
-----------
Production Check complains about APC not being installed or misconfigured. What
is APC you wonder? Well, APC is an opcode caching mechanism that will pre-com-
pile PHP files and keep them stored in memory. The full manual can be found
here: http://php.net/manual/en/book.apc.php .
PHP version 5.5 comes bundled with an alternative to APC named OPcache. The full
manual can be found here: http://php.net/manual/en/book.opcache.php .

For Drupal sites, it is important to tune APC/OPcache in order to achieve
maximum performance there. Drupal uses a massive amount of files and therefore
you should assign a proper amount of RAM to APC/OPcache. For a dedicated setup
64Mb should be sufficient, in shared setups, you will need to multiply that!
To tune your setup, you can use the aforementioned hidden link provided by
Production check. You can see the memory usage there, verify your settings and
much more.
To help you out even further, an APC config file can be found in
docs/apc.ini.txt. You must obviousely rename this file and omit the .txt
extension (drupal.org CVS did not seem to accept files with .ini extension?).

Note: This 'hidden link' makes use of the APC supplied PHP code and is subject
to the PHP license: http://www.php.net/license/3_01.txt .
The OPcache variant is taken from https://github.com/rlerdorf/opcache-status .


Updates
=======
When new checks are added to the prod_check module, the prod_monitor module will
automatically fetch them from the remote server when you edit the settings. Upon
displaying the edit form, XMLRPC is ALWAYS used to build op the checkboxes array
so that you always have the latest options available.
Cron is NOT used to do this, since we want to keep the transfer to a minimum.


Hidden link
===========
Production check adds some 'hidden links' to the site where you can check the
APC/OPcache, Memcache and DB status of your site. These pages can be found on:
  /admin/reports/status/apc-opc
  /admin/reports/status/memcache
  /admin/reports/status/database

This is in analogy with the system module that adds this 'hidden page':
 /admin/reports/status/php

Truely unmissable when setting up your site on a production server to check if
all is well!


The detailed report page
========================

The page is divided into 4 sections:

 - Settings: checks various Drupal settings
 - Server: checks that are 'outside of Drupal' such as APC/OPcache and wether or
           not you have removed the release note files from the root.
 - Performance: checks relevant to the performance settings in Drupal such as
                page / block caching.
 - Modules: checks if certain modules are on / off
 - SEO: performs very basic SEO checks such as 'is Google Analytics activated
        and did you provide a GA account number.

The sections might shift over time (maybe some stuff should go under a
'Security' section etc.).

The checks itself should be self explanatory to Drupal developers, so they won't
be described in detail here.


Support
=======

For support requests, bug reports, and feature requests, please us the issue cue
of Menu Clone on http://drupal.org/project/issues/prod_check.


Thanks
======

kbahey (http://drupal.org/user/4063) for making the performance logging
integration possible!
bocaj (http://drupal.org/user/582042) for all the great contributions!
