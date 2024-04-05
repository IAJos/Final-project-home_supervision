#ifndef BUSINESSLOGIC_H
#define BUSINESSLOGIC_H

#include "ConnexionLogic.hpp"

/// @brief This class manages system logic
class BusinessLogic
{
    private:
        /// @brief This property represents the SSID of our 
        ///        wifi connection
        char* p_ssid;

        /// @brief This property represents the password for 
        ///        our wifi connection
        char* p_pwd;

        /// @brief This property represents the port on which 
        ///        our server will communicate
        int p_port;

        /// @brief This property represents our server connection logic
        ConnexionLogic p_connexion;

    public:
        BusinessLogic(char* ssid, char* pwd, int port);
        ~BusinessLogic();

        /// @brief This method establishes a wifi connection 
        ///        with the ssid and password, then generates 
        ///        the server's IP address
        void serverConnexion();

        /// @brief This method checks files in memory 
        void checkFileInMemory();

        /// @brief This method reads files 
        void fileLoading(AwsTemplateProcessor callback);

        /// @brief This method starts the server
        void serverBegin();

        /// @brief This method turns on the light from the servert 
        void onLed(AwsTemplateProcessor callback);

        /// @brief This method turns off the light from the server
        void offLed(AwsTemplateProcessor callback);

        /// @brief This method turns on the fan from the server
        void onFan(AwsTemplateProcessor callback);

        /// @brief This method turns off the fan from the server
        void offFan(AwsTemplateProcessor callback);

        /// @brief This function returns the carbon monoxide 
        ///        air concentration value
        /// @return uint8_t
        uint8_t getGazData();

        /// @brief This function returns the brightness level 
        ///        read by the sensor
        /// @return uint8_t
        uint8_t getLightLevelData();

        /// @brief This function returns the ambient temperature
        ///        read by the sensor
        /// @return float
        float getTemperatureData();

        /// @brief 
        void enableFan();

        /// @brief 
        void desableFan();

        /// @brief 
        void enableLED();

        /// @brief 
        void desableLED();

        /// @brief 
        void enableSpeaker();

        /// @brief 
        void desableSpeaker();

};

#endif // BUSINESSLOGIC_H