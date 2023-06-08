<?php

include_once 'sensor.php';

$app = new Sensor();
$app->query_string = $_SERVER['QUERY_STRING'];

if ($app->is_url_query('suhu') && $app->is_url_query('ph')) {
 $suhu = $app->get_url_query_value('suhu');
 $ph = $app->get_url_query_value('ph');
 echo var_dump($ph);
 $app->create_data($suhu, $ph);
}
else{
    echo "link yang dimasukan salah";
}

?>
