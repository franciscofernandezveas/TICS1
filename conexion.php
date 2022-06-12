<?php

class conexion{
    const user='root';
    const pass='12345';
    const db="tics1";
    const servidor="localhost";

    public function conectarbd(){
        $conectar = new mysqli(self::servidor, self::user,self::pass,self::db);
        if($conectar->connect_error){
            die("error en la conexion".$conectar->connect_error);
        }
        return $conectar;
    }

}

?>