<?php

/**
 * Class PDFConverter.
 *
 * Converts a file to PDF using the soffice shell command.
 * Be sure to have some office install like LibreOffice.
 */
class PDFConverter {

  const FAMILY_TEXT           = "Text";
  const FAMILY_SPREADSHEET    = "Spreadsheet";
  const FAMILY_PRESENTATION   = "Presentation";
  const FAMILY_DRAWING        = "Drawing";
  const FAMILY_MULTIPAGETIFF  = "Multipage";
  const FAMILY_MSG            = "Outlook";

  /**
   * Array of families' extensions.
   * @var array
   */
  public static $familyExtensions = array(
    self::FAMILY_TEXT => array('txt', 'doc', 'docx', 'odt', 'html'),
    self::FAMILY_SPREADSHEET => array('ods','ots','rdf','xls','xlsx','xlsb'),
    self::FAMILY_PRESENTATION => array('ppt', 'pptx', 'odp'),
    self::FAMILY_DRAWING => array('odg'),
    self::FAMILY_MULTIPAGETIFF => array('tiff', 'tif'),
    self::FAMILY_MSG => array('msg', 'eml'),
  );

  /**
   * Array which defines the correct filter format to be used in the conversion.
   * @var array
   */
  public static $exportFilterMap = array(
    "pdf" => array(
      self::FAMILY_TEXT => array('unoconv' => 'document'),
      self::FAMILY_SPREADSHEET => array('unoconv' => 'spreadsheet'),
      self::FAMILY_PRESENTATION => array('unoconv' => 'presentation'),
      self::FAMILY_DRAWING => array('unoconv' => 'graphics'),
      self::FAMILY_MULTIPAGETIFF => array('ImageMagick' => 'ImageMagick'),
      self::FAMILY_MSG => array('Outlook-msg' => 'Outlook-msg'),
    ),
  );

  public $file;
  public $fileExtension;
  public $fileFamily;
  public $fileName;
  public $pdf;

  /**
   * Contructor.
   *
   * @param string $file
   *   Path of file
   */
  public function __construct($file) {
    if (file_exists($file)) {
      $this->file = $file;
      $this->pdf = preg_replace('/\.(' . implode('|', self::getAllowedExtenstions()) . ')$/i', '.pdf', $file);
      $this->fileExtension = strtolower(pathinfo($this->file, PATHINFO_EXTENSION));
      $this->fileName=strtolower(pathinfo($this->file, PATHINFO_FILENAME));

      $this->fileFamily = $this->getFamily();
    }
    else {
      throw new Exception($file . ' does not exists.');
    }
  }

  /**
   * Get the family of the file. Text, Drawing etc.
   *
   * @return string
   *   The family
   */
  protected function getFamily() {
    if (!$this->fileFamily) {
      // Find which 'Family' the file is in.
      foreach (self::$familyExtensions as $family => $extensions) {
        if (in_array($this->fileExtension, $extensions)) {
          $this->fileFamily = $family;
          break;
        }
      }
    }
    return $this->fileFamily;
  }

  /**
   * Converts a document to PDF.
   *
   * @param string $output_dir
   *   The path to put the converted file. If not provided they are saved in
   *   same directory.
   */
  public function convert($output_dir = NULL) {
    if (!$output_dir) {
      $output_dir = pathinfo($this->file, PATHINFO_DIRNAME);
    }

    // Switch on what type of conversion.
    switch (key(self::$exportFilterMap['pdf'][$this->fileFamily])) {

      //
      // Convert by using soffice command.
      //
      case 'soffice':
        // Get the correct filter name. If couldnt be found it uses regular
        // writer as filter.
        $filter_name = isset(self::$exportFilterMap['pdf'][$this->fileFamily]['soffice']) ? self::$exportFilterMap['pdf'][$this->fileFamily]['soffice'] : self::$exportFilterMap['pdf'][self::FAMILY_TEXT]['soffice'];
        shell_exec('soffice --headless --invisible -convert-to pdf:' . $filter_name . ' -outdir "' . $output_dir . '" "' . $this->file . '" &>/dev/null');

        return TRUE;

      break;

      //
      // Convert by using unoconv command.
      //
      case 'unoconv':
        // Get the correct filter name. If couldnt be found it uses regular
        // writer as filter.
        if ($this->fileExtension=='html'){
          // change HTML encoding to UTF 8
           $this->improveHTML($output_dir, FALSE); 
           $tmp_filename=$output_dir . '/' .  $this->fileName.'_tmp.'.$this->fileExtension;
           $encoding= str_replace("\n", '', array_pop(explode(':', shell_exec('file --mime-encoding ' . $this->file))));         //
           if (strpos($encoding,'unknown')) 
                $encoding = 'iso-8859-1' ;  
           shell_exec('iconv -f ' . $encoding . ' -t utf8 ' . $this->file . ' > ' . $tmp_filename);
           shell_exec('mv ' .  $tmp_filename . ' ' . $this->file);
          
         } 
        $filter_name = isset(self::$exportFilterMap['pdf'][$this->fileFamily]['unoconv']) ? self::$exportFilterMap['pdf'][$this->fileFamily]['unoconv'] : self::$exportFilterMap['pdf'][self::FAMILY_TEXT]['unoconv'];
        shell_exec('unoconv -f pdf -eSelectPdfVersion=1 --doctype=' . $filter_name . ' "' . $this->file . '" &>/dev/null');
        $this->improveHTML($output_dir, TRUE);
        return TRUE;

      break;

      //
      // Convert using th ImageMagick php extension. This is good to convert any
      // multipage .tiff files to pdf.
      //
      case 'ImageMagick':
        shell_exec('convert -quiet "' . $this->file . '" -density 300x300 -compress jpeg "' . $this->pdf . '"');

        return TRUE;

      break;

      //
      // Convert all Outlook .msg files. These are a bit difficult. First we
      // need to convert the .msg file to an .eml file. An .eml file are easier
      // to unpack. Next unpack the .eml for its attached files. Recursivly?
      // Nooo, unpacked .msg files will be treated by their own file conversion.
      //
      case 'Outlook-msg':
        $eml_file = preg_replace('/\.msg$/i', '.eml', $this->file);
        $sub_dir = $this->file . '_attachments';
        if (!file_exists($sub_dir) && !is_dir($sub_dir)) {
          mkdir($sub_dir);
        }

        // http://blog.spiralofhope.com/667-importing-eml-into-msg-or-mbox.html
        // Convert .msg file to .eml
        if (!file_exists($eml_file) && preg_match('/\.msg$/i', $this->file)) {
          shell_exec('mapitool -i --no-verbose "' . $this->file . '" &>/dev/null');
        }

        // http://manpages.ubuntu.com/manpages/intrepid/man1/munpack.1.html
        // Unpack .eml file. This will put all attached documents into same
        // directory.
        if (file_exists($eml_file) && !file_exists($sub_dir . '/' . basename($eml_file) . '.part1.html')) {
          shell_exec('munpack -t -C "' . $sub_dir . '" "' . $eml_file . '"');

          // Munpack unpacks the content of the email in .msg as a part1(txt)
          // and part2(html). Lets rename them and make it a correct filetype.
          // These new files are handled and converted at their own run. eg.
          // next cron.
          if (file_exists($sub_dir . '/part1')) {
            rename($sub_dir . '/part1', $sub_dir . '/' . basename($eml_file) . '.part1.html');
          }
          if (file_exists($sub_dir . '/part2')) {
            rename($sub_dir . '/part2', $sub_dir . '/' . basename($eml_file) . '.part2.html');
          }
        }

        return TRUE;

      break;

      default:
        return FALSE;

      break;
    }

  }

  /**
   * Get all allowed extensions.
   * @return array
   *   All allowed extensions
   */
  public static function getAllowedExtenstions() {
    $allowed_extensions = array();
    foreach (self::$familyExtensions as $extensions_array) {
      $allowed_extensions = array_merge($allowed_extensions, $extensions_array);
    }
    return $allowed_extensions;
  }
 private function improveHTML($output_dir, $inline_img=TRUE) {
   $html = file_get_contents($this->file);

   $doc = new DOMDocument();
   @$doc->loadHTML($html);
   $tags = $doc->getElementsByTagName('img');
   if ($tags->length==0) return FALSE;
   foreach ($tags as $tag) {
    if ($tag->getAttribute('src')!="") {
     preg_match("#\w*?.(jpg|png|gif)#is", $tag->getAttribute('src'), $filename);     
     if (file_exists($output_dir . '/' . $filename[0])){
        if ($inline_img)  {
        $imgData = base64_encode(file_get_contents($output_dir . '/' . $filename[0]));
        $src = 'data: '.mime_content_type($output_dir . '/' . $filename[0]).';base64,'.$imgData;
    }   
    else 
      $src=$filename[0];
        
   $tag->setAttribute('src',$src);     
  }
 }
 }
  $doc->saveHTMLFile($this->file);
 } 
}
 