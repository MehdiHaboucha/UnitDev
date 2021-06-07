<html>
  <head>
    <meta charset="utf-8" />
<!-- Latest compiled and minified CSS -->
<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/css/bootstrap.min.css">

<!-- jQuery library -->
<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>

<!-- Latest compiled JavaScript -->
<script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/js/bootstrap.min.js"></script>
    <link rel="stylesheet" href="style.css" />
   
 <title>SmarTracker Maps</title>
<style>
body {font-family: Arial, Helvetica, sans-serif;}

/* Full-width input fields */
input[type=text]{
  width: 100%;
  padding: 12px 20px;
  margin: 8px 0;
  display: inline-block;
  border: 1px solid #ccc;
  box-sizing: border-box;
}

/* Set a style for all buttons */
button {
  background-color: #04AA6D;
  color: white;
  padding: 14px 20px;
  margin: 8px 0;
  border: none;
  cursor: pointer;
  width: 100%;
}

button:hover {
  opacity: 0.8;
}


/* The Modal (background) */
.modal {
  display: block; 
  position: fixed; /* Stay in place */
  z-index: 1; /* Sit on top */
  left: 0;
  top: 0;
  width: 100%; /* Full width */
  height: 100%; /* Full height */
  overflow: auto; /* Enable scroll if needed */
  background-color: rgb(0,0,0); /* Fallback color */
  background-color: rgba(0,0,0,0.4); /* Black w/ opacity */
  padding-top: 60px;
}

/* Modal Content/Box */
.modal-content {
  background-color: #fefefe;
  margin: 5% auto 15% auto; /* 5% from the top, 15% from the bottom and centered */
  border: 1px solid #888;
  width: 80%; /* Could be more or less, depending on screen size */
}



/* Add Zoom Animation */
.animate {
  -webkit-animation: animatezoom 0.6s;
  animation: animatezoom 0.6s
}

@-webkit-keyframes animatezoom {
  from {-webkit-transform: scale(0)} 
  to {-webkit-transform: scale(1)}
}
  
@keyframes animatezoom {
  from {transform: scale(0)} 
  to {transform: scale(1)}
}

/* Change styles for span and cancel button on extra small screens */
@media screen and (max-width: 300px) {
  span.psw {
     display: block;
     float: none;
  }
  .cancelbtn {
     width: 100%;
  }
}
</style>

<?php


$user = "60b3a354988a3744fd7c38c5";
$password = "10fb13ac9f4925f8016ca0201e1d6c61";
$url ="https://api.sigfox.com/v2/devices";
$ch = curl_init();
curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, true);
curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
curl_setopt($ch, CURLOPT_URL,$url);
curl_setopt($ch, CURLOPT_USERPWD, "$user:$password");
$result=curl_exec($ch);
curl_close($ch);
$data = (json_decode($result, true));

$id= $data['data'][0]['id'];
//echo $id;
?>

</head>
<body>



<div id="id01" class="modal">
  
  <div class="modal-content animate">

    <div class="container">

      <label for="uname"><b>Identifiant Sigfox</b></label>
 		<p id="erreur" style="color: red; visibility: hidden">Identifiant incorrect</p>
      <input id="ident" type="text" placeholder="Entrer Vote identifiant Sigfox" name="uname" required>
      <button onclick="changeVisibility()" type="submit">Authentification</button>
 	 
    </div>
  </div>
</div>

<script>
// Get the modal
var verif = "<?php echo ($id)?>";
function changeVisibility(){
if(document.getElementById('ident').value == verif){
document.getElementById('map').style.visibility='visible';
document.getElementById('id01').style.visibility='hidden';
document.getElementById('erreur').style.visibility='hidden';
}
else{
document.getElementById('erreur').style.visibility='visible';
document.getElementById('erreur').value='Identifiant incorrect';
}


}
</script>

<div id="map" style="visibility: hidden">
<h2>Géolocatisation du SmartTracker</h2>  
    



<?php

$url ="https://api.sigfox.com/v2/devices/".$id."/locations";
$ch = curl_init();
curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, true);
curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
curl_setopt($ch, CURLOPT_URL,$url);
curl_setopt($ch, CURLOPT_USERPWD, "$user:$password");
$result=curl_exec($ch);
curl_close($ch);
$data = (json_decode($result, true));

echo('<br/>');
$long=$data['data'][0]['lng'];
$lat=$data['data'][0]['lat'];
$time=$data['data'][0]['time'];
/*
echo "Longitude:".$long;
echo('<br/>');
echo "Latitude:".$lat;
echo('<br/>');
*/
echo "Date et Heure:".date(DATE_RFC2822, $time);
echo('<br/>');
?>
        <iframe width="100%" height="500"  src="https://maps.google.com/maps?q=<?php echo $lat; ?>,<?php echo $long; ?>&radius=2000&output=embed"></iframe>
 
<div>
</body>

</html>