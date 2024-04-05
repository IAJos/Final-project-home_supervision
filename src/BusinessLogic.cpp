#include "BusinessLogic.hpp"
#include "LedActuator.hpp"
#include "SpeakerActuator.hpp"
#include "FanActuator.hpp"
#include "LightSensor.hpp"
#include "TemperatureSensor.hpp"
#include "GazSensor.hpp"

#define MQ 34
#define LDR 35
#define DS 32
#define SPK 33
#define LED 2
#define FAN 4

/*pinMode(SPK, OUTPUT);
pinMode(LED, OUTPUT);
pinMode(FAN, OUTPUT);

pinMode(MQ, INPUT);
pinMode(LDR, INPUT);
pinMode(DS, INPUT);*/

LedActuator light = LedActuator(LED);
SpeakerActuator speaker = SpeakerActuator(SPK);
FanActuator fan = FanActuator(FAN);

BusinessLogic::BusinessLogic(char* ssid, char* pwd, int port) : 
p_ssid(ssid), p_pwd(pwd), p_port (port), p_connexion(ssid, pwd, port){}

BusinessLogic::~BusinessLogic(){}

void BusinessLogic::checkFileInMemory()
{    
  p_connexion.checkFileInMemory();
}

void BusinessLogic::serverConnexion()
{  
  p_connexion.serverConnexion();
}

void BusinessLogic::fileLoading(AwsTemplateProcessor callback)
{    
  p_connexion.p_server.on("/", HTTP_GET, [callback](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/index.html", "text/html", false, callback);
  });

  p_connexion.p_server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(SPIFFS, "/style.css", "text/css");
  });

  p_connexion.p_server.on("/loader.js", HTTP_GET, [](AsyncWebServerRequest *request)
  {
      request->send(SPIFFS, "/loader.js", "text/javascript");
  });
}

void BusinessLogic::serverBegin()
{    
  p_connexion.serverBegin();
}

void BusinessLogic::onLed(AwsTemplateProcessor callback)
{
  p_connexion.p_server.on("/ledon", HTTP_GET, [callback](AsyncWebServerRequest *request)
  {
    light.enableLED();
    request->send(SPIFFS, "/index.html", "text/html", false, callback);
    request->redirect("/index.html");
  });
}

void BusinessLogic::offLed(AwsTemplateProcessor callback)
{
  p_connexion.p_server.on("/ledoff", HTTP_GET, [callback](AsyncWebServerRequest *request)
  {
    light.desableLED();
    request->send(SPIFFS, "/index.html", "text/html", false, callback);
    request->redirect("/index.html");
  });
}

void BusinessLogic::onFan(AwsTemplateProcessor callback)
{
  p_connexion.p_server.on("/fanon", HTTP_GET, [callback](AsyncWebServerRequest *request)
  {
    fan.enableFan();
    request->send(SPIFFS, "/index.html", "text/html", false, callback);
    request->redirect("/index.html");
  });
}

void BusinessLogic::offFan(AwsTemplateProcessor callback)
{
  p_connexion.p_server.on("/fanoff", HTTP_GET, [callback](AsyncWebServerRequest *request)
  {
    fan.desableFan();
    request->send(SPIFFS, "/index.html", "text/html", false, callback);
    request->redirect("/index.html");
  });
}

uint8_t BusinessLogic::getGazData()
{
  GazSensor gaz = GazSensor(MQ);
  return gaz.getCOConcentrations();
}

uint8_t BusinessLogic::getLightLevelData()
{
  LightSensor light_level = LightSensor(LDR);
  return light_level.getLightLevel();
}

float BusinessLogic::getTemperatureData()
{
  TemperatureSensor temperature = TemperatureSensor(DS);
  return temperature.getTemperature();
}

void BusinessLogic::enableFan()
{
  fan.enableFan();
}

void BusinessLogic::desableFan()
{  
  fan.desableFan();
}

void BusinessLogic::enableLED()
{
  light.enableLED();
}

void BusinessLogic::desableLED()
{
  light.desableLED();
}

void BusinessLogic::enableSpeaker()
{
  speaker.enableSpeaker();
}

void BusinessLogic::desableSpeaker()
{
  speaker.desableSpeaker();
}