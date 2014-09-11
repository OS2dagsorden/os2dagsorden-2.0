os2web_pdf_converter
====================

Script to be used in crontab. Converts files in giving dir to PDF format.

Can convert following file formats to PDF:

    txt doc docx odt html
    ods ots rdf xls xlsx
    ppt pptx odp
    odg tiff msg eml


Requirements
------------
Be sure to have the technologies installed on the server where you use this
script.

 - mapitool (Convert .msg to .eml)
   `sudo apt-get install rubygems`
   `gem install ruby-msg`

 - munpack (Unpack .eml files)
   `sudo apt-get install mpack`

 - soffice (Use libre or oo to convert any type to PDF)
   `sudo apt-get install libreoffice`

 - ImageMagick (Convert multipaged .tiff files to PDF)
   `sudo apt-get install imagemagick`

 - UnoConv (Convert documents from OpenOffice to PDF)
   `sudo apt-get install unoconv`

Usage
-----

  `php os2web_pdf_converter.php /path/to/files [/path/to/Drupal]`

Arguments:

1: Path to files which should be converted. This should either be an
   relative path or an absolute.

2: Path to your Drupal instance. When providing a valid Drupal path, it
   tries to update the corrosponding file entity in Drupal with the new
   .pdf URI. Providing the Drupal path bootstraps Drupal with database access.
