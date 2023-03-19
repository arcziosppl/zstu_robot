#include "Arduino.h"
#include "config.h"
#include "Servo.h"
#include "ESPAsyncTCP.h"
#include "ESPAsyncWebServer.h"
#include "ESP8266WiFi.h"
#include "ESP8266mDNS.h"

const char *ssid = "";
const char *password = "";


Servo servo1;

AsyncWebServer server(80);


class Robot{
  private:
  long time,distance;

  public:

  int get_distance(){
    digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  time = pulseIn(echoPin, HIGH);
  distance = time/58;
  return distance;
  }

  void forward(){
digitalWrite(in1, LOW);
digitalWrite(in2, HIGH);
digitalWrite(in3, LOW);
digitalWrite(in4, HIGH);
}

void backward(){
  digitalWrite(in1, HIGH);
digitalWrite(in2, LOW);
digitalWrite(in3, HIGH);
digitalWrite(in4, LOW);
}

void stop(){
  digitalWrite(in1, LOW);
digitalWrite(in2, LOW);
digitalWrite(in3, LOW);
digitalWrite(in4, LOW);
}

void right(){
  digitalWrite(in1, HIGH);
digitalWrite(in2, LOW);
digitalWrite(in3, LOW);
digitalWrite(in4, HIGH);
}

void left(){
  digitalWrite(in1, LOW);
digitalWrite(in2, HIGH);
digitalWrite(in3, HIGH);
digitalWrite(in4, LOW);
}
};

Robot New_robot;

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="pl">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ZSTU ROBOT</title>
    <link rel="shortcut icon" href="https://cdn.icon-icons.com/icons2/1648/PNG/512/10103robotface_109992.png" type="image/x-icon">
</head>
<style>
    @import url('https://fonts.googleapis.com/css2?family=Play&family=Roboto+Condensed:wght@300&display=swap');
    </style>
<style>
    body,html{
        margin: 0;
        padding: 0;
        width: 100%;
        height: 100%;
        background-image: radial-gradient(circle, #33bb7f, #47c971, #63d65e, #84e143, #a8eb12);
    }

    .main{
        display: flex;
    }

    .left{
        width: 50%;
        height: 100vh;
        border-right: 1px solid white;
        display: flex;
        justify-content: center;
        align-items: center;
    }
    .right{
        width: 50%;
        height: 100vh;
        display: flex;
        justify-content: center;
        align-items: center;
    }

    .right > iframe{
        width: 90%;
        height: 60%;
        border-radius: 20px;
    }

    .logo{
        position: absolute;
        width: 70px;
        right: 10px;
        top: 10px;
    }

    .ind{
        width: 300px;
        height: 300px;
        border: 1px solid white;
        border-radius: 20px;
        margin: 20px;
        display: flex;
        align-items: center;
        justify-content: center;
    }

    .distance{
        height: 100px;
    }

    .ind > p{
        font-size: 30px;
        color: white;
        font-family: 'Play', sans-serif;
        font-family: 'Play', sans-serif;
        font-family: 'Roboto Condensed', sans-serif;
    }

    .ind > img{
        width: 60px;
    }

    .for{
        transform: rotate(-90deg);
        position: relative;
        top: -100px;
        left: 90px;
    }

    .back{
        transform: rotate(90deg);
        position: relative;
        top: 100px;
        left: 30px;
    }

    .le{
        transform: rotate(180deg);
        position: relative;
        left: -120px;
    }

</style>
<body>
    <img src="http://zstu.edu.pl/wp-content/uploads/2022/04/rsz_logo-tarcza.png" alt="ZSTU Logo" class="logo">
    <div class="main">
        <div class="left">
            <div class="indicators">
            <div class="ind distance">
                <img src="https://cdn-icons-png.flaticon.com/512/3789/3789467.png" alt="distance">
                <p id="distance">0.00 cm</p>
            </div>
            <div class="ind">
                <img class="for" src="https://cdn-icons-png.flaticon.com/512/660/660276.png" alt="indicator">
                <img class="back" src="https://cdn-icons-png.flaticon.com/512/660/660276.png" alt="indicator">
                <img class="le" src="https://cdn-icons-png.flaticon.com/512/660/660276.png" alt="indicator">
                <img class="ri" src="https://cdn-icons-png.flaticon.com/512/660/660276.png" alt="indicator">
            </div>
            </div>
        </div>
        <div class="right">
            <iframe src="https://www.google.com" frameborder="0"></iframe>
        </div>
    </div>

    <script>

        const distance = document.querySelector('#distance');
        const forward = document.querySelector('.for');
        const backward = document.querySelector('.back');
        const left = document.querySelector('.le');
        const right = document.querySelector('.ri');


        setInterval(()=>{
        const req = async () =>{
            try{
            let req = await fetch('/distance',{
                method: "GET"
            });
            let res = await req.text();
            return res;
        }catch(e){
            console.log(e);
        }
        }

        req().then((res)=>{
            console.log(res);
            distance.innerHTML = res + " cm";
        })
    },100);

    window.addEventListener("gamepadconnected",()=>{
        setInterval(()=>{
        const gamepad = navigator.getGamepads()[0];
        let direction_left_right = Math.floor(gamepad.axes[0]*255)
        let direction_for_back = Math.floor(gamepad.axes[1]*255)
        let camera = Math.floor(gamepad.axes[2]*90)

        fetch('/camera?value='+camera)

        if(direction_left_right < -100){
            fetch('/left');
            left.style.visibility = 'visible';
        }else if(direction_left_right > 100){
            fetch('/right');
            right.style.visibility = 'visible';
        }else if(direction_for_back < -100){
            fetch('/for');
            forward.style.visibility = 'visible';
        }else if(direction_for_back > 100){
            fetch('/back');
            backward.style.visibility = 'visible';
        }else{
            fetch('/stop');
            forward.style.visibility = 'hidden';
            backward.style.visibility = 'hidden';
            left.style.visibility = 'hidden';
            right.style.visibility = 'hidden';

        }
        },100)
    })



    </script>
</body>
</html>
)rawliteral";

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT); 
  servo1.attach(D8);
  servo1.write(90);

  pinMode(en, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  digitalWrite(en, 100);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connecting...");
    return;
  }
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  if (!MDNS.begin("robot")) {     
    Serial.println("Error setting up MDNS responder!");
  }

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  server.on("/distance", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", String(New_robot.get_distance()));
  });

  server.on("/for", HTTP_GET, [](AsyncWebServerRequest *request){
    New_robot.forward();
    request->send(200);
  });

  server.on("/back", HTTP_GET, [](AsyncWebServerRequest *request){
    New_robot.backward();
    request->send(200);
  });

  server.on("/left", HTTP_GET, [](AsyncWebServerRequest *request){
    New_robot.left();
    request->send(200);
  });

  server.on("/right", HTTP_GET, [](AsyncWebServerRequest *request){
    New_robot.right();
    request->send(200);
  });

  server.on("/stop", HTTP_GET, [](AsyncWebServerRequest *request){
    New_robot.stop();
    request->send(200);
  });

  server.on("/camera", HTTP_GET, [](AsyncWebServerRequest *request){
    String camera_value;
    if(request->hasParam("value")){
        camera_value = request->getParam("value")->value();

        servo1.write(90-camera_value.toInt());
    }
    request->send(200);
  });


  server.onNotFound(notFound);
  server.begin();
}

void loop() {
}