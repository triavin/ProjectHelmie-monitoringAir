<?php

/**
 *
 * Class sensor untuk function CREATE data dari sensor kedalam database berdasarkan urd yang diakses oleh NodeMCU
 *
 **/

class Sensor
{
    public $query_string;
    function __construct()
    {
        $this->connection = $this->open_connection();
    }
    private function open_connection()
    {
        $servername = "localhost";
        $username = "root";
        $password = "";
        $dbname = "db_monitoring_suhu_ph";
        $conn = new mysqli(
            $servername,
            $username,
            $password,
            $dbname
        ) or die("Failed connect: %s\n" . $conn->error);
        return $conn;
    }
    function create_data($suhu, $ph)
    {
        $sql_query = "INSERT INTO DTsensor (suhu, ph)
        VALUES ('" . $suhu . "','" . $ph . "')";
        echo $this->execute_query($sql_query);
    }
    private function execute_query($sql, $data = [], $is_read = null)
    {
        $executed = $this->connection->query($sql);
        if ($executed == TRUE) {
            $data['status'] = true;
            $data['message'] = 'data operation success';
            if (!is_null($is_read) && $is_read) {
                $data['data'] = [];
                if ($executed->num_rows != 0) {
                    while ($row = $executed->fetch_assoc()) {
                        $data['data'][] = $row;
                    }
                }
            }
            return json_encode($data);
        }
        $data['status'] = false;
        $data['message'] = 'data operation failed';
        return json_encode($data);
    }
    /**
     *
     * Function untuk mengurai string url menjadi sebuah variabel
     * dan memeriksa apakah string url sudah tersipan kedalam variabel
     *
     */
    function is_url_query($string_value)
    {
        $query = array();
        parse_str($this->query_string, $query);
        if (array_key_exists($string_value, $query)) {
            return true;
        }
        return false;
    }
    /**
     *
     * Function untuk mengurai url menjadi sebuah variabel
     * dan mengembalikan nilai variabel yang diminta
     *
     */
    function get_url_query_value($string_value)
    {
        $query = array();
        parse_str($this->query_string, $query);
        return $query[$string_value];
    }
}
