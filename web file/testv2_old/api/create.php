<?php
include_once '../config/database.php';
include_once '../class/nodemcu_log.php';

// Create a database connection
$database = new Database();
$db = $database->getConnection();

// Create an instance of Nodemcu_log
$nodemcu_log = new Nodemcu_log($db);

// Get the parameters from the URL
$idDevice = isset($_GET['idDevice']) ? strval($_GET['idDevice']) : null;
$suhu = isset($_GET['suhu']) ? floatval($_GET['suhu']) : null;
$ph = isset($_GET['ph']) ? floatval($_GET['ph']) : null;

// Validate the parameters
if ($idDevice !== null && $suhu !== null && $ph !== null) {
    if ($nodemcu_log->createLogData($idDevice, $suhu, $ph)) {
        echo $idDevice;
        echo "Log data created successfully";
    } else {
        echo "Failed to create log data";
    }
} else {
    echo "Invalid parameters";
}
?>
