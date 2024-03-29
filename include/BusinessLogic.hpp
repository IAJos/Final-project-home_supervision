#ifndef BUSINESSLOGIC_H
#define BUSINESSLOGIC_H

#include <cstdint>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <ArduinoJson.h> 

class BusinessLogic
{
    private:
        char* p_ssid;
        char* p_pwd;
        int p_port;
        AsyncWebServer p_server;

    public:
        BusinessLogic(char* ssid, char* pwd, int port);
        ~BusinessLogic();

        void serverConnexion();
        void checkFileInMemory();
        void fileLoading();
        void serverBegin();
        void onLed();
        void offLed();
        void onFan();
        void offFan();
        void onSpeaker();
        uint8_t getLight();
        void displayLightLevelData();
        float getTemperature();
        void displayTemperatureData();
        uint8_t getGaz();
        void displayGazData();
        void displayData();
        void checkCondition();
};

#endif // BUSINESSLOGIC_H