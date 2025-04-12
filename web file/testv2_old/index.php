<?php
require_once __DIR__ . '/config/database.php';

// Function to fetch the latest data for each device
function fetchLatestDataForAllDevices($db) {
    $query = "
        SELECT t3.deviceName,t1.idDevice, t1.suhu, t1.ph, t1.inputTime 
        FROM dt_sensor t1
        INNER JOIN (
            SELECT idDevice, MAX(inputTime) as latest_inputTime 
            FROM dt_sensor 
            GROUP BY idDevice
        ) t2 
        ON t1.idDevice = t2.idDevice AND t1.inputTime = t2.latest_inputTime
        INNER JOIN dt_device t3 on t1.idDevice = t3.idDevice
        ORDER BY t1.idDevice";
    $result = $db->query($query);

    $data = [];
    while ($row = $result->fetch_assoc()) {
        $data[] = $row;
    }
    return $data;
}

// Function to add navbar
function generateNavbar($activePage) {
    $pages = [
        'index.php' => 'Home',
        'features/add_device.php' => 'Add Device',
        'history.php' => 'History'
    ];

    echo '<nav class="navbar navbar-expand-lg navbar-dark bg-dark">';
    echo '<a class="navbar-brand" href="#">Dashboard</a>';
    echo '<button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarNav" aria-controls="navbarNav" aria-expanded="false" aria-label="Toggle navigation">';
    echo '<span class="navbar-toggler-icon"></span>';
    echo '</button>';
    echo '<div class="collapse navbar-collapse" id="navbarNav">';
    echo '<ul class="navbar-nav ml-auto">'; // ml-auto aligns menu to the right

    foreach ($pages as $url => $title) {
        $isActive = ($activePage === $url) ? 'active' : '';
        echo '<li class="nav-item">';
        echo '<a class="nav-link ' . $isActive . '" href="' . $url . '">' . $title;
        if ($isActive === 'active') {
            echo ' <span class="sr-only">(current)</span>';
        }
        echo '</a>';
        echo '</li>';
    }

    echo '</ul>';
    echo '</div>';
    echo '</nav>';
    echo '<div class="clear">';
    echo '</div>';
    
}

// Call navbar function
generateNavbar('index.php');

// Create a database connection
$database = new Database();
$db = $database->getConnection();
$latestData = fetchLatestDataForAllDevices($db);
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <title>Real-Time Sensor Data Dashboard</title>
    <link href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" rel="stylesheet">
    <link href="css/fontawesome/css/fontawesome.css" rel="stylesheet"> <!-- Path to your local Font Awesome CSS -->
    <link href="css/fontawesome/css/brands.css" rel="stylesheet"> <!-- Path to your local Font Awesome CSS -->
    <link href="css/fontawesome/css/solid.css" rel="stylesheet"> <!-- Path to your local Font Awesome CSS -->
    <style>
        body {
            background-color: #343a40;
            color: #fff;
        }
        .nav-item {
            font-size: 14px;
        }
        .navbar-brand {
            font-weight: 400;
            font-size: 20px;
            margin-left: 8%;
            margin-top: 8px;
            margin-bottom: 8px;
        }
        .navbar-nav {
            margin-right: 10%;
            font-size: larger;
        }
        .container {
            background-color: #343a40;
            padding: 30px;
        }
        .clear {
            background-color: #fff;
            width: 100%;
            height: 0.5px;
            opacity: 50%;
        }
        .card {
            margin: 20px 0;
        }
        .card .btn {
            border-radius: 30px;
        }
        .card {
            margin: 20px;
        }
        .card-header a {
            color: inherit;
            text-decoration: none;
        }
        .card-text {
            margin-bottom: 3px;
        }
        .btn {
            margin-top: 2px;
            margin-bottom: 2px;
        }
    </style>
</head>
<body>
    <div class="container mt-1">
        <h2 class="text-center mb-3">Real-Time Sensor Data Dashboard</h2>
        <div id="sensor-data" class="row">
            <!-- Real-time data will be loaded here -->
            <?php
            if (!empty($latestData)) {
                foreach ($latestData as $data) {
                    // Determine card header color based on conditions
                    $cardClass = '';
                    $styleCardClassTitle = '';
                    if (($data['suhu'] < 28 && $data['ph'] < 6) || ($data['suhu'] > 32 && $data['ph'] > 7.5)) {
                        $cardClass = 'bg-danger text-white';
                        $styleCardClassTitle = ' margin-bottom: auto; padding-bottom: 20px; background-color: rgba(220, 53, 69, 0.2);';
                    } elseif (($data['suhu'] < 28 || $data['suhu'] > 32) && ($data['ph'] > 7 || $data['ph'] < 7.5)) {
                        $cardClass = 'bg-warning text-white';
                        $styleCardClassTitle = ' margin-bottom: auto; padding-bottom: 20px; background-color: rgba(255, 193, 7, 0.2);';
                    } elseif (($data['suhu'] > 28 && $data['suhu'] < 32) && ($data['ph'] < 7 || $data['ph'] > 7.5)) {
                        $cardClass = 'bg-warning text-white';
                        $styleCardClassTitle = ' margin-bottom: auto; padding-bottom: 20px; background-color: rgba(255, 193, 7, 0.2);';
                    } elseif ($data['suhu'] >= 28 && $data['suhu'] <= 32 && $data['ph'] > 6 && $data['ph'] < 7.5) {
                        $cardClass = 'bg-success text-white';
                        $styleCardClassTitle = ' margin-bottom: auto; padding-bottom: 20px; background-color: rgba(40, 167, 69, 0.2);';
                    }
                    
                    echo '
                    <div class="col-md-6 col-lg-4">
                        <div class="card" style="border-radius: 20px;">
                            <div style="border-top-right-radius: 20px; border-top-left-radius: 20px;" class="card-header ' . $cardClass . '">Latest Data ' . $data['deviceName']. '</div>
                            <div class="card-body ' . $cardClass . ' text-center" style="opacity: 20%; padding-top:0;">
                            </div>
                            <!-- <h5 class="card-title">Device ID: ' . htmlspecialchars($data['idDevice']) . '</h5> -->
                            <h5 class="card-title text-dark text-center" style="font-weight: 700; padding-bottom: 20px; ' . $styleCardClassTitle . '">Device ID: ' . htmlspecialchars($data['idDevice']) . '</h5>
                                <div class="card-footer text-dark text-center">
                                    
                                    <p class="card-text">Temperature: ' . htmlspecialchars($data['suhu']) . '°C</p>
                                    <p class="card-text">pH Level: ' . htmlspecialchars($data['ph']) . '</p>
                                    <p class="card-text"><small class="text-muted">Last updated: ' . htmlspecialchars($data['inputTime']) . '</small></p>
                                    <a href="device_features.php?idDevice=' . htmlspecialchars($data['idDevice']) . '" class="btn btn-primary">
                                        Lihat Fitur
                                        <i style="margin-left: 2px;" class="fa-solid fa-arrow-right"></i>
                                    </a>
                                
                                </div>
                        </div>
                    </div>';
                }
            } else {
                echo '<p class="text-center">No data available</p>';
            }
            ?>
        </div>
    </div>

    <script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/js/bootstrap.min.js"></script>
    <script>
        // Function to fetch and update real-time data
        function fetchAndUpdateRealTimeData() {
            $.ajax({
                url: 'index.php', // PHP script itself to fetch data
                type: 'GET',
                dataType: 'html',
                success: function(response) {
                    var newData = $(response).find('#sensor-data').html();
                    $('#sensor-data').html(newData); // Replace content with fetched data
                },
                error: function(xhr, status, error) {
                    console.error('Error fetching data:', status, error);
                }
            });
        }

        // Load initial data and start updating every 5 seconds
        $(document).ready(function() {
            fetchAndUpdateRealTimeData(); // Load data initially

            // Refresh data every 5 seconds
            setInterval(fetchAndUpdateRealTimeData, 5000); // Adjust interval as needed
        });
    </script>
</body>
</html>

<?php
// Close database connection
$db->close();
?>
