#include <Arduino.h>
#include "Sensor.hpp"
#include "Actuator.hpp"
//#include "BusinessLogic.hpp"
#include "OneWire.h"
#include <cstdint>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <ArduinoJson.h> 

char ssid[] = "238lavigne";
char pass[] = "238lavigne";
/*char ssid[] = "UNIFI_IDO1";
char pass[] = "41Bidules!";*/

#define NOTE_G3  196
#define NOTE_C4  262
#define NOTE_E4  330
#define NOTE_G4  392

#define MQ 34
#define LDR 35
#define DS 32
#define SPK 33
#define LED 2
#define FAN 4

OneWire oneWire(DS);
DallasTemperature sensors_ds(&oneWire);
DeviceAddress ds_address = {0x28, 0xAF, 0x2B, 0xE3, 0x08, 0x00, 0x00, 0x0A};

Sensor sensor = Sensor(MQ, DS, LDR);
Actuator actuator = Actuator(FAN, SPK, LED);

typedef struct DataMapping DataMapping;
struct DataMapping
{
  uint8_t light;
  float temperature;
  uint8_t gaz;
} ;

DataMapping dataMapping;
std::vector<DataMapping> dataMappingArray;
String dataMappingArrayOutPut;

//BusinessLogic logic = BusinessLogic(ssid, pass, 80);
AsyncWebServer server(80);

uint8_t readDataLdr = 0;
float temperature = 0;
uint8_t readDataMq7 = 0;

String convertDataArrayToJson(std::vector<DataMapping>& dataArray);
void setup() {

  Serial.begin(115200);

  //******************* vérification des fichiers dans la mémoire *******************
  //logic.checkFileInMemory();    
  if(!SPIFFS.begin())
  {
      Serial.println("Test SPIFFS error...");
      return;
  }

  File root = SPIFFS.open("/");
  File file = root.openNextFile();

  while(file)
  {
      Serial.print("File: ");
      Serial.println(file.name());
      file.close();
      file = root.openNextFile();
  }

  //******************* connexion au wifi *******************
  //logic.serverConnexion();
  WiFi.begin(ssid, pass);
	Serial.print("Tentative de connexion...");
	
	while(WiFi.status() != WL_CONNECTED)
	{
		Serial.print(".");
		delay(100);
	}
	
	Serial.println("\n");
	Serial.println("Connexion etablie!");
	Serial.print("Adresse IP: ");
	Serial.println(WiFi.localIP());

  //*******************  chargement des fichiers ******************* 
  //logic.fileLoading();
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
  {
      request->send(SPIFFS, "/index.html", "text/html");
  });

  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request)
  {
      request->send(SPIFFS, "/style.css", "text/css");
  });

  server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request)
  {
      request->send(SPIFFS, "/script.js", "text/javascript");
  });

  //******************* réponses aux requetes du client *******************
  //logic.onLed();
  server.on("/led/on", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    actuator.enableLED();
    request->redirect("/");
  });
  //logic.offLed();
  server.on("/led/off", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    actuator.desableLED();
    request->redirect("/");
  });
  //logic.onFan();
  server.on("/fan/on", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    actuator.enableFan();
    request->redirect("/");
  });
  //logic.offFan();
  server.on("/fan/off", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    actuator.desableFan();
    request->redirect("/");
  });
  //logic.displayLightLevelData();
  server.on("/readLight", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    int data = readDataLdr;
    request->send(200, "text/plain", String(data));

    if (readDataLdr < 110)
      actuator.enableLED();
    else
      actuator.desableLED();
  });
  //logic.displayTemperatureData();
  sensors_ds.begin();
  server.on("/readtemperature", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    float data = temperature;
    request->send(200, "text/plain", String(data));

    if (data > 24)
      actuator.enableFan();
    else
      actuator.desableFan();
  });
  //logic.displayGazData();
  server.on("/readGaz", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    int melody[] = {NOTE_E4, NOTE_E4, NOTE_E4, NOTE_C4, NOTE_E4, NOTE_G4, NOTE_G3};
    int noteDurations[] = {8, 4, 4, 8, 4, 2, 2};
    int data = readDataMq7;

    request->send(200, "text/plain", String(data));

    if (data > 160)
      actuator.enableSpeaker(melody, noteDurations);
    else
      actuator.desableSpeaker();
  });
  //logic.displayData();
  server.on("/data", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    String data = dataMappingArrayOutPut;
    request->send(200, "text/plain", data);
    request->redirect("/");
  });
    
  //logic.serverBegin();
  server.begin();
  Serial.println("Serveur actif!");
}

void loop() {
  readDataLdr = sensor.getLightLevel();
  dataMapping.light = readDataLdr;

  temperature = sensor.getTemperature(sensors_ds, ds_address);
  dataMapping.temperature = temperature;

  readDataMq7  = sensor.getCOConcentrations();
  dataMapping.gaz = readDataMq7;

  dataMappingArray.push_back(dataMapping);

  if(dataMappingArray.size() > 8 && !dataMappingArray.empty())
    dataMappingArray.erase(dataMappingArray.begin());

  dataMappingArrayOutPut = convertDataArrayToJson(dataMappingArray);
  Serial.println(dataMappingArrayOutPut);  
  
  delay(1000);
}

String convertDataArrayToJson(std::vector<DataMapping>& dataArray)
{
  JsonDocument jsonData;
  JsonArray jsonArray = jsonData.to<JsonArray>();
  String output; 

  for (DataMapping elt : dataArray)
  {
    JsonObject obj = jsonArray.createNestedObject();
    obj["light"] = elt.light;
    obj["temperature"] = elt.temperature;
    obj["gaz"] = elt.gaz;
  }
  
  serializeJson(jsonData, output);

  return output;
}