#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266Firebase.h>
#include <Arduino.h>
#include <Hash.h>
#include <math.h>
#include "index.h"

const char* ssid = "iPhone od: Edo";
const char* pass = "edo12345";
int water_level;
bool upaljeno = false;
ESP8266WebServer server(80);
Firebase firebase("https://water-level-dcfb8-default-rtdb.europe-west1.firebasedatabase.app");

void setup() {
  Serial.begin(9600);

  pinMode(D0, OUTPUT);

  WiFi.begin(ssid, pass);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("WiFi Connected! ");
  Serial.println(WiFi.localIP());

  server.on("/", []() {
    server.send(200, "text/html", indexHTML);
  });

  server.on("/level", []() {
    server.send(200, "text/plain", String(firebase.getInt("level")).c_str());
  });
  server.on("/change", []() {
    upaljeno=!upaljeno;
    server.send(200, "text/plain", "Blink");
  });

  server.begin();
  Serial.println("HTTP Server Started!");

  delay(100);
}

void loop() {
  server.handleClient();
  digitalWrite(D0, LOW);
  if(upaljeno)
  {
    digitalWrite(D0,HIGH);
    delay(200);
    digitalWrite(D0,LOW);
    delay(100);
    digitalWrite(D0,HIGH);
    delay(200);
    digitalWrite(D0,LOW);
    delay(100);
    digitalWrite(D0,HIGH);
    delay(100);
    digitalWrite(D0,LOW);
  }
  water_level = analogRead(A0);
  Serial.println(water_level);
  if(water_level >= 500) {
    digitalWrite(D0, HIGH);
  }
  firebase.setInt("level", water_level);
}