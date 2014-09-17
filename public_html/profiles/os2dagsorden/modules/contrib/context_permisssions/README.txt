
Context Permissions for Drupal 7.x
----------------------------------
This module provides additional permissions for Context module.

With this module you can assign individual permissions to a 
role to create, edit, delete, clone, import, export, reverse,
activate and deactivate contexts.

In this way will not need assign the permission "administer site
configuration" to a role for you to manage contexts.

NOTE: In order for a role has access to import a context, you 
must also assign permission "use PHP for settings" to that role.


Installation
------------
Context Permissions can be installed like any other Drupal module -- 
place it in the modules directory for your site and enable it (and its 
requirement, Context, CTools and PHP Filter) on the `admin/modules` page.


Usage
-----
Activate the module and go to Permissions Administration Page
(admin/people/permissions). Assign permissions to desired roles.


Maintainers
-----------

- morgothz (David Langarica)
