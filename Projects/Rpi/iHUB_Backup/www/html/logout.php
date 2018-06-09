<?php
	session_start();
	session_destroy();
	require_once("initialize.php");

	// Do the logout processes and redirect to login page.
	after_successful_logout();
	redirect_to('index.php');
?>
