<?php
    session_start();
    include('verifica_login.php');
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>
<body>
    <h2>Bem vindo <?php echo $_SESSION['username']?>!</h2>
    <h2><a href="logout.php">Sair</a></h2>
    <h2><a href="delet_user.php">Deletar</a></h2>
</body>
</html>


