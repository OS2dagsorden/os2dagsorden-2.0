<script type="text/x-nemid" id="nemid_parameters"><?php echo $params;?></script>
<script>
 function onNemIDMessage(e) {
     var event = e || event;

     var win = document.getElementById("nemid_iframe").contentWindow, postMessage = {}, message;
     message = JSON.parse(event.data);

     if (message.command === "SendParameters") {
         var htmlParameters = document.getElementById("nemid_parameters").innerHTML;

         postMessage.command = "parameters";
         postMessage.content = htmlParameters;
         win.postMessage(JSON.stringify(postMessage), "<?php echo $settings['danid_baseurl'];?>");
     }

     if (message.command === "changeResponseAndSubmit") {
          document.postBackForm.response.value = message.content;
          document.postBackForm.submit();
     }
 }

 if (window.addEventListener) {
     window.addEventListener("message", onNemIDMessage);
 } else if (window.attachEvent) {
     window.attachEvent("onmessage", onNemIDMessage);
 }
</script>

<?php

if (!isset($_SESSION['nemid_login']['errors'])) {
  if (arg(0) == 'node' && is_numeric(arg(1))) {
    $nid = arg(1);
  }

?>

<iframe id="nemid_iframe" title="NemID" allowfullscreen="true" scrolling="no" frameborder="0" style="width:300px;height:450px;border:0; display:inline-block" src="<?php echo $settings['iframe_url']; ?>"></iframe>
<div style="display:inline-block; vertical-align: top; width: 500px"><?php echo ($help)? $help['value'] : '' ?></div>
<form name="postBackForm" action="<?php

  if (isset($nid) && is_numeric($nid)) {
    $node = node_load($nid);
    if ($node->type == 'webform') {
      echo url('node/'.$nid);
    }
  }
  else {
    echo url('nemid/verify');
  }

  ?>" method="post">
  <input type="hidden" name="response" value=""/>
</form>

<?php
}
else
{
  echo t("There was a problem the NemID client");
}
?>
