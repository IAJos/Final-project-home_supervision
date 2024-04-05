#ifndef CONNEXIONLOGIC_H
#define CONNEXIONLOGIC_H

#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

/// @brief This class manages the connection to the server 
class ConnexionLogic
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

    public:
        /// @brief This property represents our server manager
        AsyncWebServer p_server;

        /// @brief ConnexionLogic class constructor
        /// @param ssid Represents the SSID of our 
        ///             wifi connection
        /// @param pwd Represents the password for 
        ///            our wifi connection
        /// @param port Represents the port on which 
        ///             our server will communicate
        ConnexionLogic(char* ssid, char* pwd, int port);

        /// @brief ConnexionLogic class destructor
        ~ConnexionLogic();

        /// @brief This method establishes a wifi connection 
        ///        with the ssid and password, then generates 
        ///        the server's IP address
        void serverConnexion();

        /// @brief This method checks files in memory 
        void checkFileInMemory();

        /// @brief This method reads files 
        void fileLoading();

        /// @brief This method starts the server
        void serverBegin();
};

#endif // CONNEXIONLOGIC_H