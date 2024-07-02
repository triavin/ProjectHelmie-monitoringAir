<?php
// require_once __DIR__ . '../config/database.php';
require_once '../config/database.php';

// Function to check if a device ID already exists
function isDeviceIdExists($db, $idDevice) {
    $query = "SELECT idDevice FROM dt_device WHERE idDevice = ?";
    $stmt = $db->prepare($query);
    $stmt->bind_param("s", $idDevice);
    $stmt->execute();
    $stmt->store_result();
    return $stmt->num_rows > 0;
}

// Function to add a device to the dt_device table
function addDevice($db, $idDevice, $deviceName) {
    if (isDeviceIdExists($db, $idDevice)) {
        return false; // Device ID already exists
    }
    $query = "INSERT INTO dt_device (idDevice, deviceName) VALUES (?, ?)";
    $stmt = $db->prepare($query);
    $stmt->bind_param("ss", $idDevice, $deviceName);
    if ($stmt->execute()) {
        return true;
    } else {
        return false;
    }
}

// Function to add navbar
function generateNavbar($activePage) {
    $pages = [
        '../index.php' => 'Home',
        'add_device.php' => 'Add Device',
        '../history.php' => 'History'
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
    echo '<div class="clear"></div>';
}

// Call navbar function
generateNavbar('add_device.php');

// Create a database connection
$database = new Database();
$db = $database->getConnection();

$successMessage = '';
$errorMessage = '';

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $idDevice = $_POST['idDevice'];
    $deviceName = $_POST['deviceName'];

    if (!empty($idDevice) && !empty($deviceName)) {
        if (addDevice($db, $idDevice, $deviceName)) {
            $successMessage = 'Device added successfully!';
        } else {
            $errorMessage = 'Device ID already exists or failed to add device. Please try again.';
        }
    } else {
        $errorMessage = 'Both fields are required.';
    }
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <title>Add Device</title>
    <link href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" rel="stylesheet">
    <style>
        /* Additional custom styles */
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
    <div class="container">
        <h2 class="text-center mb-4">Add Device</h2>
        
        <?php if (!empty($successMessage)): ?>
            <div class="alert alert-success" role="alert">
                <?= htmlspecialchars($successMessage) ?>
            </div>
        <?php endif; ?>
        
        <?php if (!empty($errorMessage)): ?>
            <div class="alert alert-danger" role="alert">
                <?= htmlspecialchars($errorMessage) ?>
            </div>
        <?php endif; ?>
        
        <div class="row">
            <div class="col-md-4"></div>
                <div class="text-dark col-md-4" style="background-color: #fff; padding: 20px; border-radius: 15px;">
                    <form method="POST" action="add_device.php">
                        <div class="form-group">
                            <label for="idDevice">Device ID</label>
                            <input type="text" class="form-control" id="idDevice" name="idDevice" required>
                            <div class="invalid-feedback">
                                Please enter a valid Device ID.
                            </div>
                        </div>
                        <div class="form-group">
                            <label for="deviceName">Device Name</label>
                            <input type="text" class="form-control" id="deviceName" name="deviceName" required>
                            <div class="invalid-feedback">
                            Please enter a device name.
                            </div>
                        </div>
                        <div class="col-md-12">
                            <button style="width: 100%; margin-top: 30px; border-radius: 30px" type="submit" class="btn btn-primary">Add Device</button>
                        </div>
                    </form>
                </div>
            <div class="col-md-4"></div>
        </div>
    </div>

    <script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.12.9/umd/popper.min.js"></script>
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/js/bootstrap.min.js"></script>
    <script>
        // Bootstrap form validation
        (function() {
            'use strict';
            window.addEventListener('load', function() {
                var forms = document.getElementsByClassName('needs-validation');
                var validation = Array.prototype.filter.call(forms, function(form) {
                    form.addEventListener('submit', function(event) {
                        if (form.checkValidity() === false) {
                            event.preventDefault();
                            event.stopPropagation();
                        }
                        form.classList.add('was-validated');
                    }, false);
                });
            }, false);
        })();
    </script>
</body>
</html>

<?php
// Close database connection
$db->close();
?>
