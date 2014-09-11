The purpose of this module is to import the information from three views returing XML structure, located remotely.

The views are:
-user committees - user rights(is member of, follows, follows+), user roles(role title and weight)
-committees - list of currently functioning commitees
-meetings - list of scheduled meetings

Modules is designed to create/update/delete a particular entry based on the pulled information.

The module has specific configuration, which is the links, using which the particular view can be accesses: admin/config/os2web/settings
The module also has the support, of proxing the connection - configured in the same config page.


