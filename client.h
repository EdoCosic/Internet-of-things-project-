const char indexHTML[] PROGMEM = R"=====(

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1, user-scalable=no">
    <title>Water Level Sensor</title>
    <style>
        *{
            font-family: Arial, Helvetica, sans-serif;
        }
    </style>
</head>
<body>
    <center style="margin-top: 50px">
        <h1>Water Level Sensor</h1>
        <img id="img-level-tank" width="400" height="400">
        <a href="/change" style="border:1px solid black; background-color:lightblue">Blink dugme</a>
    </center>
    <script>
        let image = document.getElementById("img-level-tank");
        let level;
        setInterval(() => {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function() {
                level = parseInt(this.responseText);
                if (level >= 500) {
                    image.setAttribute("src", "https://edocosic.github.io/iot/WaterTankRed.png");
                }
                else if (level < 500 && level >= 200) {
                    image.setAttribute("src", "https://edocosic.github.io/iot/WaterTank.png");
                }
                else if(level < 200){
                    image.setAttribute("src", "https://edocosic.github.io/iot/WaterTankYellow.png");
                }
            };
            xhttp.open("GET", "/level", true);
            xhttp.send();
        }, 3000);
    </script>
</body>
</html>

)=====";