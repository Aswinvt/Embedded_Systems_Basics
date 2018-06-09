<?php

// Perform all initialization here, in private

// Set constants to easily reference public 
// and private directories
define("APP_ROOT", dirname(dirname(__FILE__)));

session_start();

require_once("fake_database.php");
require_once("functions/general_functions.php");
require_once("functions/csrf_request_type_functions.php");
require_once("functions/csrf_token_functions.php");
require_once("functions/request_forgery_functions.php");
require_once("functions/session_hijacking_functions.php");
require_once("functions/sqli_escape_functions.php");
require_once("functions/validation_functions.php");
require_once("functions/xss_sanitize_functions.php");

?>
