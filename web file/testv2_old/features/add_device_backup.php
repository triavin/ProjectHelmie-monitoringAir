<?php
require_once __DIR__ . '/config/database.php';

// Function to add a device to the dt_device table
function addDevice($db, $idDevice, $deviceName) {
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
            $errorMessage = 'Failed to add device. Please try again.';
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
</head>
<body>
    <div class="container mt-5">
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
        
        <form method="POST" action="add_device.php">
            <div class="form-group">
                <label for="idDevice">Device ID</label>
                <input type="text" class="form-control" id="idDevice" name="idDevice" required>
            </div>
            <div class="form-group">
                <label for="deviceName">Device Name</label>
                <input type="text" class="form-control" id="deviceName" name="deviceName" required>
            </div>
            <button type="submit" class="btn btn-primary">Add Device</button>
        </form>
    </div>

    <script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/js/bootstrap.min.js"></script>
</body>
</html>

<?php
// Close database connection
$db->close();
?>
