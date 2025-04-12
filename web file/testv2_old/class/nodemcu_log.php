<?php
class Nodemcu_log {
    private $conn;

    public function __construct($db) {
        $this->conn = $db;
    }

    public function createLogData($idDevice, $suhu, $ph) {
        $query = "INSERT INTO dt_sensor (idDevice, suhu, ph) VALUES (?, ?, ?)";

        if ($stmt = $this->conn->prepare($query)) {
            $stmt->bind_param("sdd", $idDevice, $suhu, $ph); // "idd" means integer, double, double

            if ($stmt->execute()) {
                return true;
            } else {
                echo "Execute failed: (" . $stmt->errno . ") " . $stmt->error;
                return false;
            }

            $stmt->close();
        } else {
            echo "Prepare failed: (" . $this->conn->errno . ") " . $this->conn->error;
            return false;
        }
    }
}
?>
