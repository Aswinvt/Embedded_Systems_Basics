<?php require_once("initialize.php"); ?>

<?php

// Rather than require setting up a real database, 
// we can fake one instead.
initialize_fake_database();

// initialize variables to default values
$username = "";
$password = "";
$message = "";

if(request_is_post()) {
  
  if(!csrf_token_is_valid() || !csrf_token_is_recent()) {
    $message = "Sorry, request was not valid.";
  } else {
    // CSRF tests passed--form was created by us recently.

    // retrieve the values submitted via the form
    $username = $_POST['username'];
    $password = $_POST['password'];
    
    if(has_presence($username) && has_presence($password)) {
      
      // Search our fake database to retrieve the user data
      $sqlsafe_username = sql_prep($username);
      $user = find_one_in_fake_db('users', 'username', $sqlsafe_username);
  
      if($user && password_verify($password, $user['hashed_password'])) {
        // successful login
        after_successful_login();
        redirect_to('options.php');
      } else {
        // failed login
        $message = "Username/password combination not found.";
      }

    } else {
      // username or password left blank, just re-display the form.
      $message = "Sorry, request was not valid.";
    }
  }
}

?>

<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>iHUB-LOGIN</title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <!-- Bootstrap -->
    <link href="./css/bootstrap.css" rel="stylesheet" media="screen">
    <link href="./css/main.css" rel="stylesheet" media="screen">
  </head>

  <body>
    <div class="container">
      <button class="btn btn-lg btn-primary btn-block"><h2>iHUB-LOGIN</h2></button><br />
      <?php
        if($message != "") {
          echo '<h2><p>' . h($message) . '</p></h2>';
        }
      ?>
    
      <form class="form-signin" name="form1" action="index.php" method="POST" accept-charset="utf-8">
        <?php echo csrf_token_tag(); ?>
        <input type="text" name="username" class="form-control" placeholder="Username" autofocus/><br />
        <br />
        <input type="password" name="password" class="form-control" placeholder="Password" autofocus/><br />
        <br />
        <button name="submit" id="submit" class="btn btn-lg btn-primary btn-block" type="submit">Sign in</button>
      </form>
    </div> <!-- /container -->

    <!-- jQuery (necessary for Bootstrap's JavaScript plugins) -->
    <script src="js/jquery-2.2.4.min.js"></script>
    <!-- Include all compiled plugins (below), or include individual files as needed -->
    <script type="text/javascript" src="js/bootstrap.js"></script>
  </body>
</html>
