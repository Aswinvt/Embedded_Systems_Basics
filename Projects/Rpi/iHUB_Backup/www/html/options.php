<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>iHUB-OPTIONS</title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <!-- Bootstrap -->
    <link href="./css/bootstrap.css" rel="stylesheet" media="screen">
    <link href="./css/main.css" rel="stylesheet" media="screen">
  </head>

  <body>
    <div class="container">
      <button class="btn btn-lg btn-primary btn-block"><h2>iHUB-OPTIONS</h2></button><br />
        <form class="form-signin" name="form1" action="http:\/\/10.67.51.193:8082/online.php" method="POST" accept-charset="utf-8">    
        <button name="online" id="submit" class="btn btn-lg btn-primary btn-block" type="submit">ONLINE ACCESS</button>
        </form>
        <form class="form-signin" name="form2" action="http:\/\/192.168.1.200:8082/offline.php" method="POST" accept-charset="utf-8">
        <button name="offline" id="submit" class="btn btn-lg btn-primary btn-block" type="submit">OFFLINE ACCESS</button>
        </form>
    </div> <!-- /container -->

    <!-- jQuery (necessary for Bootstrap's JavaScript plugins) -->
    <script src="js/jquery-2.2.4.min.js"></script>
    <!-- Include all compiled plugins (below), or include individual files as needed -->
    <script type="text/javascript" src="js/bootstrap.js"></script>
  </body>
</html>
