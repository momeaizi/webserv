<?php
// Start the session
session_start();

// Create a cookie named "user" with the value "John Doe"
setcookie("user", "John Doe", time() + (86400 * 30), "/");

// Set a session variable
$_SESSION["favorite_color"] = "blue";

// Retrieve the value of the cookie "user"
if(isset($_COOKIE["user"])) {
  echo "Cookie 'user' is set!<br>";
  echo "Value is: " . $_COOKIE["user"] . "<br>";
}

// Retrieve the value of the session variable "favorite_color"
echo "My favorite color is " . $_SESSION["favorite_color"] . ".";
?>