/*#include "Sensor.hpp"
#include "Actuator.hpp"
#include "BusinessLogic.hpp"
#include "OneWire.h"

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

BusinessLogic::BusinessLogic(char* ssid, char* pwd, int port) : p_ssid(ssid), p_pwd(pwd), p_port (port), p_server(port){}
BusinessLogic::~BusinessLogic(){}

void BusinessLogic::checkFileInMemory()
{    
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
}

void BusinessLogic::serverConnexion()
{  
    WiFi.begin(p_ssid, p_pwd);
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
}

void BusinessLogic::fileLoading()
{    
    p_server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
    {
        request->send(SPIFFS, "/index.html", "text/html");
    });

    p_server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request)
    {
        request->send(SPIFFS, "/style.css", "text/css");
    });

    p_server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request)
    {
        request->send(SPIFFS, "/script.js", "text/javascript");
    });
}

void BusinessLogic::serverBegin()
{    
    p_server.begin();
}

void BusinessLogic::onLed()
{
  p_server.on("/led/on", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    actuator.enableLED();
    request->redirect("/");
  });
}

void BusinessLogic::offLed()
{
  p_server.on("/led/off", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    actuator.desableLED();
    request->redirect("/");
  });
}

void BusinessLogic::onFan()
{
  p_server.on("/fan/on", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    actuator.enableFan();
    request->redirect("/");
  });
}

void BusinessLogic::offFan()
{
  p_server.on("/fan/off", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    actuator.desableFan();
    request->redirect("/");
  });
}

void BusinessLogic::onSpeaker()
{
    int melody[] = {NOTE_E4, NOTE_E4, NOTE_E4, NOTE_C4, NOTE_E4, NOTE_G4, NOTE_G3};
    int noteDurations[] = {8, 4, 4, 8, 4, 2, 2};
    actuator.enableSpeaker(melody, noteDurations);
}

uint8_t BusinessLogic::getLight()
{
  return sensor.getLightLevel();
}

void BusinessLogic::displayLightLevelData()
{
  uint8_t readDataLdr = sensor.getLightLevel();
  dataMapping.light = readDataLdr;
  Serial.println((String)"LDR value: " + readDataLdr);
    
  p_server.on("/readLight", HTTP_GET, [readDataLdr](AsyncWebServerRequest *request)
  {
    String value = String(readDataLdr);
    request->send(200, "text/plain", value);

    if (readDataLdr < 252)
      actuator.enableLED();
    else
      actuator.desableLED();
  });
}


float BusinessLogic::getTemperature()
{
  sensors_ds.begin();
  return sensor.getTemperature(sensors_ds, ds_address);
}

void BusinessLogic::displayTemperatureData()
{
  sensors_ds.begin();
  float temperature = sensor.getTemperature(sensors_ds, ds_address);
  dataMapping.temperature = temperature;
  Serial.println((String)"\tTemp value: " + temperature);

  p_server.on("/readtemperature", HTTP_GET, [temperature](AsyncWebServerRequest *request)
  {
    if (temperature > 24)
      actuator.enableFan();
    else
      actuator.desableFan();

    String value = String(temperature);
    request->send(200, "text/plain", value);
  });
}

uint8_t BusinessLogic::getGaz()
{
  return sensor.getCOConcentrations();
}

void BusinessLogic::displayGazData()
{
  uint8_t readDataMq7  = sensor.getCOConcentrations();
  dataMapping.gaz = readDataMq7;
  Serial.print((String)"\tGas value : " + readDataMq7);

  p_server.on("/readGaz", HTTP_GET, [readDataMq7](AsyncWebServerRequest *request)
  {
    int melody[] = {NOTE_E4, NOTE_E4, NOTE_E4, NOTE_C4, NOTE_E4, NOTE_G4, NOTE_G3};
    int noteDurations[] = {8, 4, 4, 8, 4, 2, 2};

    if (readDataMq7 > 220)
      actuator.enableSpeaker(melody, noteDurations);
    else
      actuator.desableSpeaker();

    String value = String(readDataMq7);
    request->send(200, "text/plain", value);
  });
}

void BusinessLogic::displayData()
{
  dataMappingArray.push_back(dataMapping);

  if(dataMappingArray.size() > 8 && !dataMappingArray.empty())
    dataMappingArray.erase(dataMappingArray.begin());

  JsonDocument jsonData;
  JsonArray jsonArray = jsonData.to<JsonArray>();
  String output;

  for (int i = 0; i < dataMappingArray.size(); i++)
  {
    JsonObject obj = jsonArray.createNestedObject();
    obj["light"] = dataMappingArray[i].light;
    obj["temperature"] = dataMappingArray[i].temperature;
    obj["gaz"] = dataMappingArray[i].gaz;
  }


  serializeJson(jsonData, output);
  Serial.println(output);

  p_server.on("/", HTTP_GET, [output](AsyncWebServerRequest *request)
  {
    request->send(200, "text/plain", output);
  });
}

void BusinessLogic::checkCondition()
{
  sensors_ds.begin();

  float meanLightLevel;
  float meanTemperature;
  float meanGaz;

  int lightLevelSum = 0;
  int temperatureSum = 0;
  int gazSum = 0;

  for (int i = 0; i < 10; i++)
  {
    Serial.println((String)"light: " + i + "= " + sensor.getLightLevel() + " temp: " + i + "= " + sensor.getTemperature(sensors_ds, ds_address) + " gaz: " + i + "= " + sensor.getCOConcentrations());
    lightLevelSum  += sensor.getLightLevel();
    temperatureSum += sensor.getTemperature(sensors_ds, ds_address);
    gazSum += sensor.getCOConcentrations();
  }

  meanLightLevel = lightLevelSum/10.0;
  meanTemperature = temperatureSum/10.0;
  meanGaz = gazSum/10.0;
  Serial.println((String)"mean light: " + meanLightLevel + " mean temp: " + meanTemperature + " mean gaz: " + meanGaz);
}

*/