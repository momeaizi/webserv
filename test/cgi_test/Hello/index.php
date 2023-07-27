#!/usr/bin/php-cgi
<?php
// Set the content type to plain text
header('Content-Type: text/plain');

// Check if the request method is POST
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    // Check if the 'name' field is set in the POST data
    if (isset($_POST['name'])) {
        $name = $_POST['name'];
        // Display the name back to the user
        echo "Hello, " . $name . "! Your name has been received via POST.";
    } else {
        echo "Error: 'name' field not found in the POST data.";
    }
} else {
    echo "This script only accepts POST requests.";
}
?>
