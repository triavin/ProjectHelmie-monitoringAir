<?php
include_once '../config/database.php';
include_once '../class/nodemcu_log_detail.php';

// Create a database connection
$database = new Database();
$db = $database->getConnection();

// Create an instance of Nodemcu_log
$nodemcu_log = new Nodemcu_log_detail($db);

// Get the parameters from the URL
$idDevice = isset($_GET['idD']) ? strval($_GET['idD']) : null;
$suhu = isset($_GET['suhu']) ? floatval($_GET['suhu']) : null;
$ph = isset($_GET['ph']) ? floatval($_GET['ph']) : null;
$outputSuhuUp = isset($_GET['osu']) ? floatval($_GET['osu']) : null;
$outputSuhuDown = isset($_GET['osd']) ? floatval($_GET['osd']) : null;
$outputPhStabilizer = isset($_GET['op']) ? floatval($_GET['op']) : null;


// Validate the parameters
if ($idDevice !== null && $suhu !== null && $ph !== null) {
    if ($nodemcu_log->createLogData($idDevice, $suhu, $ph)) {
        echo $idDevice;
        echo " Log data created successfully";
    } else {
        echo "Failed to create log data";
    }
} else {
    echo "Invalid parameters";
}

// Validate the parameters
if ($idDevice !== null && $suhu !== null && $ph !== null && $outputSuhuDown !== null && $outputSuhuUp !== null && $outputPhStabilizer !== null) {
    if ($nodemcu_log->createLogDataDetail($idDevice, $suhu, $ph, $outputSuhuDown, $outputSuhuUp, $outputPhStabilizer)) {
        echo $idDevice;
        echo "Log data created successfully";
    } else {
        echo "Failed to create log data";
    }
} else {
    echo "Invalid parameters";
}
?>
