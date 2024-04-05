#include "ConnexionLogic.hpp"

ConnexionLogic::ConnexionLogic(char* ssid, char* pwd, int port) : p_ssid(ssid), p_pwd(pwd), p_port (port), p_server(port){}

ConnexionLogic::~ConnexionLogic()
{
}

void ConnexionLogic::checkFileInMemory()
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

void ConnexionLogic::serverConnexion()
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

void ConnexionLogic::fileLoading()
{    
    p_server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
    {
        request->send(SPIFFS, "/index.html", "text/html");
    });

    p_server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request)
    {
        request->send(SPIFFS, "/style.css", "text/css");
    });
}

void ConnexionLogic::serverBegin()
{    
    p_server.begin();
    Serial.println("Serveur actif!");
}
