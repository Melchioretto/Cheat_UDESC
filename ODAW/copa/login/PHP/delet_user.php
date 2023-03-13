<?php
session_start();
include("conexao.php");
$user=$_SESSION['username'];
$deleta = "DELETE FROM `usuarios` WHERE username = '$user'";
$conx = $mysqli->query($deleta) or die($mysqli->error);
session_destroy();
header('Location: ../HTML/index.html');
exit();
?>