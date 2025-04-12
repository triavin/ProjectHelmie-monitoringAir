<?php
$servername = "localost";
$username = "root";
$password = "";
$dbname = "db_monitoring_suhu_ph";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}
echo "Connected successfully";
?>
