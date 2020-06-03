<?php

$val = $_GET["data"];
$split = explode("-",$val);
date_default_timezone_set('Asia/Karachi');
$fileContent=$val."\n";
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "project";
$curr_date = date("Y-m-d H:i:s");        
var_dump($curr_date);
// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$sql_smoke = "INSERT INTO smoke (smoke_id, smoke_date, smoke_value)
VALUES ('', '$curr_date', '$split[0]')";

$sql_gass = "INSERT INTO gass (gass_id, gass_date, gass_value)
VALUES ('', '$curr_date', '$split[1]')";

$sql_co = "INSERT INTO co (co_id, co_date, co_value)
VALUES ('', '$curr_date', '$split[2]')";

$sql_temp = "INSERT INTO temp (temp_id, temp_date, temp_value)
VALUES ('', '$curr_date', '$split[3]')";

$sql_dust = "INSERT INTO dust (dust_id, dust_date, dust_value)
VALUES ('', '$curr_date', '$split[4]')";


$conn->query($sql_smoke);
$conn->query($sql_gass);
$conn->query($sql_co);
$conn->query($sql_temp);
$conn->query($sql_dust);


$conn->close();

?>