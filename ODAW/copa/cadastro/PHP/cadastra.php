<?php

    $username = trim($_POST['username']);
    $email = trim(($_POST['email']));
    $cpf= trim($_POST['cpf']);
    $pass = trim(md5($_POST['password']));
    print($pass);
    include("conexao.php");
    
    $result = $mysqli->query("SELECT COUNT(*) FROM usuarios WHERE email = '{$email}'");
    $row = $result->fetch_row();
    if ($row[0] > 0) {
        header('Location: ../HTML/index.html');
    } else {
        $consult ="INSERT INTO usuarios(`username`, `email`, `cpf`, `senha`) VALUES ('$username','$email','$cpf','$pass')";
        $cone = $mysqli->query($consult) or die($mysqli->error);
    }
  
?>