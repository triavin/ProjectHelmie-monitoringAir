<?php 
class database {
    // Host
    private $host = "localhost:3306";

    // Database name
    private $database_name = "db_monitoring_suhu_ph";
    
    // MySQL username & password
    private $username = "root";
    private $password = "";

    public $conn;

    public function getConnection(){
        $this->conn = null;
        
        // Create connection
        $this->conn = new mysqli($this->host, $this->username, $this->password, $this->database_name);

        // Check connection
        if ($this->conn->connect_error) {
            die("Database could not be connected: " . $this->conn->connect_error);
        }

        // Set charset to utf8
        if (!$this->conn->set_charset("utf8")) {
            echo "Error loading character set utf8: " . $this->conn->error;
        }

        return $this->conn;
    }
}
?>
