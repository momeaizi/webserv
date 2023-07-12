


<?php
session_start();

if(isset($_POST['increment']))
{
    if(isset($_SESSION['counter']))
    {
        $_SESSION['counter']++;
    }
    else
    {
        $_SESSION['counter'] = 1;
    }
}

?>

<!DOCTYPE html>
<html>
<head>
	<title>Increment Counter Example</title>
</head>
<body>
	<h1>Counter: <?php echo isset($_SESSION['counter']) ? $_SESSION['counter'] : 0; ?></h1>
	<form method="POST">
		<button type="submit" name="increment">Increment Counter</button>
	</form>
</body>
</html>