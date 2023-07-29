
<?php
    // Set the content type to plain text

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
    }
?>


<!DOCTYPE html>
<html>
<head>
    <title>PHP CGI POST Example</title>
</head>
<body>
    <h1>Enter your name:</h1>
    <form  method="POST">
        <input type="text" name="name">
        <input type="submit" value="Submit">
    </form>
</body>
</html>
