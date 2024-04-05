#include "BusinessLogic.hpp"

/// @brief Represents connection information 
int port = 80;
/*char ssid[] = "238lavigne";
char pass[] = "238lavigne";*/
char ssid[] = "UNIFI_IDO1";
char pass[] = "41Bidules!";

/// @brief Creation of the structure that will enable me to build 
///        the data that will be transformed and sent to the chart
typedef struct DataMapping DataMapping;
struct DataMapping
{
  uint8_t light;
  float temperature;
  uint8_t gaz;
};
DataMapping dataMapping;

/// @brief Creation of array structure
std::vector<DataMapping> dataMappingArray;

/// @brief Variable for reading different sensors
uint8_t readDataLdr = 0;
float temperature = 0;
uint8_t readDataMq7 = 0;

/// @brief The data to be sent to the chart
String data = "";

BusinessLogic businessLogic = BusinessLogic(ssid, pass, port);

/// @brief This method allows string binding of data in my html file
/// @param label Represents the string to be replaced in the html file
/// @return string
String mapping(const String& label);

/// @brief This method constructs the data to be displayed in the graph
/// @param dataArray Represents the structure array containing the data to be transformed
void chartData(std::vector<DataMapping>& dataArray);

/// @brief This function is used to check data in order to activate or 
///        deactivate actuators if necessary.
void checkData(std::vector<DataMapping>& dataArray);

void setup() {

  Serial.begin(115200);

  //******************* check files in memory *******************
  businessLogic.checkFileInMemory();

  //******************* wifi connection *******************
  businessLogic.serverConnexion();

  //*******************  loading files ******************* 
  businessLogic.fileLoading(mapping);

  //******************* responses to client requests *******************
  businessLogic.onLed(mapping);
  businessLogic.offLed(mapping);
  businessLogic.onFan(mapping);
  businessLogic.offFan(mapping);

  businessLogic.serverBegin();
}

void loop() {
  
  readDataLdr = businessLogic.getLightLevelData();
  dataMapping.light = readDataLdr; 

  temperature = businessLogic.getTemperatureData();
  dataMapping.temperature = temperature;

  readDataMq7  = businessLogic.getGazData();
  dataMapping.gaz = readDataMq7;

  dataMappingArray.push_back(dataMapping);

  if(dataMappingArray.size() > 8 && !dataMappingArray.empty())
    dataMappingArray.erase(dataMappingArray.begin());

  chartData(dataMappingArray);
  Serial.println("\n");
  
  delay(1000);
}

/// @brief This method constructs the data to be displayed in the graph
/// @param dataArray Represents the structure array containing the data to be transformed
void chartData(std::vector<DataMapping>& dataArray)
{
  String dataHeadder = "['Time', 'Light level', 'Temeprature', 'Air quality'], ";
  String dataCol = "";
  int i = 10;
  for (DataMapping elt : dataArray)
  {
    dataCol = dataCol + "['" + String(i) + "s', " + String(elt.light) + ", " + String(elt.temperature) + ", " + String(elt.gaz) + "], \n";
    i += 10;
  }

  data = dataHeadder + "\n" + dataCol;
  Serial.println(data);
}

/// @brief This method allows string binding of data in my html file
/// @param label Represents the string to be replaced in the html file
/// @return string
String mapping(const String& label) 
{
  if(label == "DATA")
    return data;
  else if(label == "LIGHT")
    return String(readDataLdr);
  else if(label == "TEMP")
    return String(temperature);
  else if(label == "GAZ")
    return String(readDataMq7);

  return String();
}

/// @brief This function is used to check data in order to activate or 
///        deactivate actuators if necessary.
void checkData(std::vector<DataMapping>& dataArray)
{
  DataMapping data = dataArray.back();

  if (data.temperature > 24)
    businessLogic.enableFan();
  else
    businessLogic.desableFan();
    
  if (data.light < 110)
    businessLogic.enableLED();
  else
    businessLogic.desableLED();

  if (data.gaz > 160)
    businessLogic.enableSpeaker();
  else
    businessLogic.desableSpeaker();
}