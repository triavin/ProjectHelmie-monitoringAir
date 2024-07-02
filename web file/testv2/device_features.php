<?php
// Function to add navbar
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
    echo '<div class="clear">';
    echo '</div>';
    
}

// Call navbar function
generateNavbar('');

// Assume you already have the logic to handle device actions and database connection

// Retrieve device ID
$idDevice = isset($_GET['idDevice']) ? $_GET['idDevice'] : '';

// Check if device ID is provided
if (!empty($idDevice)) {
    // Check if action is specified
    if (isset($_GET['action'])) {
        $action = $_GET['action'];

        // Redirect based on the action
        switch ($action) {
            case 'update':
                header("Location: update_device.php?idDevice=$idDevice");
                exit();
            case 'delete':
                header("Location: delete_device.php?idDevice=$idDevice");
                exit();
            case 'history':
                header("Location: device_history.php?idDevice=$idDevice");
                exit();
            default:
                // Invalid action, handle accordingly
                echo "Invalid action";
                break;
        }
    }
} else {
    // Device ID not provided, handle accordingly
    echo "Device ID not provided";
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <title>Device Features</title>
    <link href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" rel="stylesheet">
    <link href="css/fontawesome/css/fontawesome.css" rel="stylesheet"> <!-- Path to your local Font Awesome CSS -->
    <link href="css/fontawesome/css/brands.css" rel="stylesheet"> <!-- Path to your local Font Awesome CSS -->
    <link href="css/fontawesome/css/solid.css" rel="stylesheet"> <!-- Path to your local Font Awesome CSS -->
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
    </style>
</head>
<body>
    <div class="container">
        <h2 class="mb-4 text-center">Device Features</h2>
        <div class="row" style="justify-content:center;">
            <!-- <div class="col-md-6 col-lg-3 mb-4">
                <div class="card">
                    <div class="card-body text-center">
                        <i class="fa-solid fa-circle-plus fa-4x mb-3 text-primary"></i>
                        <h5 class="card-title">Add Device</h5>
                        <a href="device_features.php?action=add&idDevice=<?= $idDevice ?>" class="btn btn-primary">Add</a>
                    </div>
                </div>
            </div> -->
            <div class="col-md-6 col-lg-3 mb-4">
                <div class="card">
                    <div class="card-body text-center">
                        <i class="fas fa-edit fa-4x mb-3 text-warning"></i>
                        <h5 class="card-title">Update Device Data</h5>
                        <a href="device_features.php?action=update&idDevice=<?= $idDevice ?>" class="btn btn-warning">Update</a>
                    </div>
                </div>
            </div>
            <div class="col-md-6 col-lg-3 mb-4">
                <div class="card">
                    <div class="card-body text-center">
                        <i class="fas fa-trash-alt fa-4x mb-3 text-danger"></i>
                        <h5 class="card-title">Delete Device Data</h5>
                        <a href="device_features.php?action=delete&idDevice=<?= $idDevice ?>" class="btn btn-danger">Delete</a>
                    </div>
                </div>
            </div>
            <div class="col-md-6 col-lg-3 mb-4">
                <div class="card">
                    <div class="card-body text-center">
                        <i class="fas fa-history fa-4x mb-3 text-info"></i>
                        <h5 class="card-title">View Device History</h5>
                        <a href="device_features.php?action=history&idDevice=<?= $idDevice ?>" class="btn btn-info">History</a>
                    </div>
                </div>
            </div>
        </div>
    </div>
</body>
</html>
