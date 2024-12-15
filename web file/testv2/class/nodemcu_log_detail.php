<?php
class Nodemcu_log_detail {
    private $conn;

    public function __construct($db) {
        $this->conn = $db;
    }

    public function createLogDataDetail($idDevice, $suhu, $ph, $outputSuhuDown, $outputSuhuUp, $outputPhStabilizer) {
        $query = "INSERT INTO dt_sensor_detail (
                idDevice
                , suhu
                , ph
                , nilaiOutputSuhuUp
                , nilaiOutputSuhuDown
                , nilaiOutputPhStabilizer
                , statusRelaySuhuUp
                , statusRelaySuhuDown
                , statusRelayPhStabilizer) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)";

        if ($stmt = $this->conn->prepare($query)) {
            $statusRelaySuhuUp = ($outputSuhuUp >= 1) ? 1 : 0; 
            $statusRelaySuhuDown = ($outputSuhuDown >= 1) ? 1 : 0; 
            $statusRelayPhStabilizer = ($outputPhStabilizer >= 1) ? 1 : 0;

            $stmt->bind_param("idddddiii", $idDevice, $suhu, $ph, $outputSuhuUp, $outputSuhuDown, $outputPhStabilizer, $statusRelaySuhuUp, $statusRelaySuhuDown, $statusRelayPhStabilizer);

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