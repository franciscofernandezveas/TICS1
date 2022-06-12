<?php

require_once('conexion.php');

 /*  $id = $_GET['id'];
$nombre = $_GET['nombre'];
$edad = $_GET['edad'];
$peso = $_GET['peso'];
$ph = $_GET['ph'];
*/
$temperatura = $_GET['temp'];

$conn = new conexion();


//$query = "SELECT * FROM gatos WHERE id = 'gato3'";
$select = mysqli_query($conn->conectarbd(),$query);
if($select->num_rows){

//para agregar a la base de datos
$query = "INSERT INTO gatos(id,nombre,edad,peso,ph) VALUES('gato3','fcococo','1','1','1') ";
$insert = mysqli_query($conn->conectarbd(),$query);
$query = "UPDATE gatos SET nombre = $nombre,edad = $edad,peso = $peso,ph = $ph WHERE id = $id ";
$update = mysqli_query($conn->conectarbd(),$query);
echo "DATOS RECIBIDOS<br>";
echo "{ideee:" .$id.", NOM:".$nombre."}"; 
}
else{
    echo "error<br>";
}


?>