#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include "home.h"

#define LED 2
#define FAN 4

const char *ssid = "UNIFI_IDO1";
const char *password = "41Bidules!"; 
/*const char *ssid = "238lavigne";
const char *password = "238lavigne"; */

WebServer server(80);

void onLed();
void offLed();
void onFan();
void offFan();
void pageIntrouvable();
void homePage();

void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println("\n");

  pinMode(LED, OUTPUT);
  pinMode(FAN, OUTPUT);

  WiFi.persistent(false);
  WiFi.begin(ssid, password);
  Serial.print("Tentative de connexion...");

  while (WiFi.status() != WL_CONNECTED)
  {
      Serial.print(".");
      delay(100);
  }

  Serial.println("\n");
  Serial.println("Connexion etablie!");
  Serial.print("Adresse IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", homePage);
  server.on("/led/on", onLed);
  server.on("/led/off", offLed);
  server.on("/fan/on", onFan);
  server.on("/fan/off", offFan);
  server.onNotFound(pageIntrouvable);
  server.begin();

  Serial.println("Serveur web disponible!");
}

void loop() {
  server.handleClient();
}

void onLed()
{
    digitalWrite(LED, HIGH);
    server.sendHeader("Location","/");
    server.send(303);
}

void offLed()
{
    digitalWrite(LED, LOW);
    server.sendHeader("Location","/");
    server.send(303);
}

void onFan()
{  
  for(int motorSpeed = 0 ; motorSpeed <= 255; motorSpeed+=5)
  {
    analogWrite(FAN, motorSpeed); 
  }
    server.sendHeader("Location","/");
    server.send(303);
}

void offFan()
{
  for(int motorSpeed = 255 ; motorSpeed >= 0; motorSpeed-=5)
  {
    analogWrite(FAN, motorSpeed);   //PWM speed control
    delay(30);
  }
    server.sendHeader("Location","/");
    server.send(303);
}

void pageIntrouvable()
{
    server.send(404, "text/plain", "404: page no found");
}

void homePage()
{
    server.send(200, "text/html", Home);
}