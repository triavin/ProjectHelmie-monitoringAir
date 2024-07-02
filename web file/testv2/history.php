<?php

use LDAP\Result;

require_once __DIR__ . '/config/database.php';

// Create a database connection
$database = new Database();
$db = $database->getConnection();

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

// Function to fetch data with pagination
function fetchSensorData($db, $limit, $offset) {
    if ($db->connect_error) {
        die("Connection failed: " . $db->connect_error);
    }

    $query = "SELECT id, idDevice, suhu, ph, inputTime FROM dt_sensor ORDER BY inputTime DESC LIMIT $limit OFFSET $offset";
    $result = $db->query($query);

    if ($result->num_rows > 0) {
        echo '<table class="table table-bordered table-striped mt-3">';
        echo '<thead class="thead-dark">';
        echo '<tr>';
        echo '<th style="border-top-left-radius: 10px;border-bottom-left-radius: 10px;">ID</th>';
        echo '<th>Device ID</th>';
        echo '<th>Temperature (Suhu)</th>';
        echo '<th>pH Level</th>';
        echo '<th style="border-top-right-radius: 10px;border-bottom-right-radius: 10px;">Timestamp</th>';
        echo '</tr>';
        echo '</thead>';
        echo '<tbody>';
        
        $flag = $result->num_rows;
        $row = $result->fetch_assoc();    
        // echo $row['idDevice'];
        while ($row = $result->fetch_assoc()) {
            $hasilMod = $flag % 2;
            if ($hasilMod == 0) {
                echo '<tr style="background-color: #8f8f8f;">';
                echo '<td style="border-top-left-radius: 10px;border-bottom-left-radius: 10px; border: 0;">' . htmlspecialchars($row['id']) . '</td>';
                echo '<td style="border: 0;">' . htmlspecialchars($row['idDevice']) . '</td>';
                echo '<td style="border: 0;">' . htmlspecialchars($row['suhu']) . '</td>';
                echo '<td style="border: 0;">' . htmlspecialchars($row['ph']) . '</td>';
                echo '<td style="border: 0;border-top-right-radius: 10px;border-bottom-right-radius: 10px;">' . htmlspecialchars($row['inputTime']) . '</td>';
                echo '</tr>';
            } else {
                echo '<tr>';
                echo '<td>' . htmlspecialchars($row['id']) . '</td>';
                echo '<td>' . htmlspecialchars($row['idDevice']) . '</td>';
                echo '<td>' . htmlspecialchars($row['suhu']) . '</td>';
                echo '<td>' . htmlspecialchars($row['ph']) . '</td>';
                echo '<td>' . htmlspecialchars($row['inputTime']) . '</td>';
                echo '</tr>';
            }

            $flag -= 1;
        }
        // while ($row = $result->fetch_assoc()) {
        // }
        echo '</tbody>';
        echo '</table>';
    } else {
        echo '<p class="text-center">No data available</p>';
    }
    $result->close();
}

// Pagination variables
$limit = 10; // Number of entries to show per page
$page = isset($_GET['page']) ? (int)$_GET['page'] : 1; // Current page number
$offset = ($page - 1) * $limit; // Offset calculation

// Fetch total number of rows in dt_sensor table
$total_query = "SELECT COUNT(*) AS total FROM dt_sensor";
$total_result = $db->query($total_query);
$total_row = $total_result->fetch_assoc();
$total = $total_row['total'];

// Calculate total pages
$total_pages = ceil($total / $limit);

// Calling navbar
generateNavbar('history.php');
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <title>Data Table</title>
    <link href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" rel="stylesheet">
    <style>
        body {
            background-color: #343a40;
            color: #fff;
        }
        .navbar-brand {
            font-weight: 400;
            font-size: 28px;
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
        .card {
            margin: 20px 0;
        }
        .card .btn {
            border-radius: 30px;
        }
        .clear {
            background-color: #fff;
            width: 100%;
            height: 0.5px;
            opacity: 50%;
        }
        .table {
            margin-top: 20px;
        }
        .pagination {
            margin-top: 20px;
        }
    </style>
</head>
<body>
    <div class="container mt-3" style="padding-top: 0px;">
        <h2 class="text-center mb-2">Sensor Data Table</h2>
        <div id="sensor-data" class="table-responsive">
            <?php fetchSensorData($db, $limit, $offset); ?>
        </div>
        <!-- Pagination -->
        <nav aria-label="Page navigation">
            <ul class="pagination justify-content-center">
                <?php if ($page > 1): ?>
                    <li class="page-item">
                        <a class="page-link" href="?page=<?php echo $page - 1; ?>" aria-label="Previous">
                            <span aria-hidden="true">&laquo;</span>
                            <span class="sr-only">Previous</span>
                        </a>
                    </li>
                <?php endif; ?>
                
                <?php for ($i = 1; $i <= $total_pages; $i++): ?>
                    <li class="page-item <?php if ($i == $page) echo 'active'; ?>">
                        <a class="page-link" href="?page=<?php echo $i; ?>"><?php echo $i; ?></a>
                    </li>
                <?php endfor; ?>
                
                <?php if ($page < $total_pages): ?>
                    <li class="page-item">
                        <a class="page-link" href="?page=<?php echo $page + 1; ?>" aria-label="Next">
                            <span aria-hidden="true">&raquo;</span>
                            <span class="sr-only">Next</span>
                        </a>
                    </li>
                <?php endif; ?>
            </ul>
        </nav>
    </div>

    <script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.11.0/umd/popper.min.js"></script>
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/js/bootstrap.min.js"></script>
</body>
</html>

<?php
// Close database connection
$db->close();
?>
