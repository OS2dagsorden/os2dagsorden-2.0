The OS2dagsorden was programmed by Bellcom Udvikling ApS (http://bellcom.dk)
for OS2 - Offentligt digitaliseringsfællesskab (http://os2.eu).

Copyright (c) 2015, OS2 - Offentligt digitaliseringsfællesskab.

The OS2dagsorden is free software; you may use, study, modify and
distribute it under the terms of version 2.0 of the Mozilla Public
License. See the LICENSE file for details. If a copy of the MPL was not
distributed with this file, You can obtain one at
http://mozilla.org/MPL/2.0/.

All source code in this and the underlying directories is subject to
the terms of the Mozilla Public License, v. 2.0. 

For installtion please use Setup installation guide: https://github.com/OS2dagsorden/os2dagsorden-2.0/wiki/Setup-installation

# OS2Dagsorden project

The project is based on [Bellcom OS2Dagsorden solution](https://github.com/bellcom/os2dagsorden_profile)
and using it as main codebase source for:
- Contrib modules
- OS2Dagsorden/OS2Web common mofules and feature.

Bellcom OS2Dagsorden included to project as [git submodule](https://git-scm.com/book/en/v2/Git-Tools-Submodules).


## Project setup

To clone project repo with submodules and define project folder
structure please following command:
```
curl -o- https://raw.githubusercontent.com/bellcom/os2dagsorden-2.0/master/init.sh | sh
```

After successful script finishing you should get all required files and
folder to setup project locally.

Setup db credentials `setting.php`.
Load existing db or install drupal from profile.
