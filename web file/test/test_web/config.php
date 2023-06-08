<?php
$hostname = "localhost";
$username = "root";
$pass = "";
$db = "db_monitoring_suhu_ph";

// Koneksi dengan database
$koneksi = mysqli_connect($hostname, $username, $pass, $db);
// periksa koneksi database

if (!$koneksi) {
 echo "Gagal Terhubung pada MySQL: " . $mysql_connect_error();
 exit();
}
else{
    // echo "Berhasil Terhubung";
}

?>