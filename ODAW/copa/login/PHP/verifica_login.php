<?php
if(!$_SESSION['username']){
    header('Location: ../HTML/index.html');
    exit();
}
?>