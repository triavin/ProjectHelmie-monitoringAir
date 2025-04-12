<?php
require_once __DIR__ . '/config/database.php';

// Create a database connection
$database = new Database();
$db = $database->getConnection();

function generateNavbar($activePage) {
    $pages = [
        'index.php' => 'Home',
        'add_device.php' => 'Add Device',
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
}

// Function to fetch data with pagination
function fetchSensorData($db, $limit, $offset) {
    // Verify connection status
    if ($db->connect_error) {
        die("Connection failed: " . $db->connect_error);
    }

    $query = "SELECT id, idDevice, suhu, ph, inputTime FROM dt_sensor ORDER BY inputTime DESC LIMIT $limit OFFSET $offset";
    $result = $db->query($query);

    if ($result->num_rows > 0) {
        echo '<table class="table table-bordered table-striped mt-3">';
        echo '<thead class="thead-dark">';
        echo '<tr>';
        echo '<th>ID</th>';
        echo '<th>Device ID</th>';
        echo '<th>Temperature (Suhu)</th>';
        echo '<th>pH Level</th>';
        echo '<th>Timestamp</th>';
        echo '</tr>';
        echo '</thead>';
        echo '<tbody>';
        while ($row = $result->fetch_assoc()) {
            echo '<tr>';
            echo '<td>' . htmlspecialchars($row['id']) . '</td>';
            echo '<td>' . htmlspecialchars($row['idDevice']) . '</td>';
            echo '<td>' . htmlspecialchars($row['suhu']) . '</td>';
            echo '<td>' . htmlspecialchars($row['ph']) . '</td>';
            echo '<td>' . htmlspecialchars($row['inputTime']) . '</td>';
            echo '</tr>';
        }
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
    <!-- Fetch data for current page -->
    <div class="container mt-5">
        <h2 class="text-center mb-4">Sensor Data Table</h2>
        <div id="sensor-data" class="table-responsive">
            <?php fetchSensorData($db, $limit, $offset); ?>
        </div>
    </div>
    <?php
    // Close database connection
    $db->close();
    ?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <title>Data Table</title>
    <link href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" rel="stylesheet">
</head>
<body>
    <div class="container mt-5">
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
    <script>
        // Function to fetch and update real-time data
        function fetchAndUpdateRealTimeData() {
            $.ajax({
                url: 'history.php?'. $page, // PHP script itself to fetch data
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
