<?php
    session_start();
    include("conexao.php");
    if(empty($_POST['login']) || empty($_POST['senha'])){
        header('Location: ../HTML/index.html');
        exit();
    }
    $login = mysqli_real_escape_string($mysqli , $_POST['login']);
    $senha = mysqli_real_escape_string($mysqli , $_POST['senha']);

    $consulta = "SELECT * FROM `usuarios` WHERE username = '$login' and senha=md5('$senha')";
    $result = mysqli_query($mysqli,$consulta);
    $row = mysqli_num_rows($result);
    
    if($row == 1){
        $_SESSION['username'] = $login;
        header('Location: painel.php');
        exit();
    }else{
        header('Location: ../HTML/index.html');
        exit;
    }
?>