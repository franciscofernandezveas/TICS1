<?php

require_once('conexion.php');

/*$id = $_GET['id'];
$nombre = $_GET['nombre'];
$edad = $_GET['edad'];
$peso = $_GET['peso'];
$ph = $_GET['ph'];
*/
$temperatura = $_GET['temp'];

$conn = new conexion();

$insertar = "INSERT INTO prueba1(temperatura) VALUES('$temperatura')";
$resultado =  mysqli_query($conn->conectarbd(),$insertar);

//$insertar = "INSERT INTO gatos(id,nombre,edad,peso,ph) VALUES('$id', '$nombre' ,'$edad' ,'$peso','$ph')";
//$resultado =  mysqli_query($conn->conectarbd(),$insertar);


?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@4.0.0/dist/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@4.0.0/dist/js/bootstrap.min.js" integrity="sha384-JZR6Spejh4U02d8jOt6vLEHfe/JQGiRRSQQxSfFWpi1MquVdAyjUar5+76PVCmYl" crossorigin="anonymous"></script>


    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Tics</title>
</head>
<body>
    

<h1>Dispensador de agua para gatos</h1>
<?php

if($resultado){
  echo "datos añadidos a base de datos";  
  header("Location: PortalGatitos.php");
exit();
}
else{
    echo "ta malo";  
}

?>





</body>
</html>