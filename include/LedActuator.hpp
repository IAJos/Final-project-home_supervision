#ifndef LEDACTUATOR_H
#define LEDACTUATOR_H

#include <Arduino.h>

/// @brief This class allows you to switch a light on or off.
class LedActuator
{
    private:
        /// @brief This property represents the pin to which 
        ///        our LED will be connected.
        uint8_t p_ledActuator;

    public:
        /// @brief LedActuator class constructor
        /// @param ledActuator Represents the pin to which 
        ///                    our LED will be connected
        LedActuator(uint8_t ledActuator);

        /// @brief LedActuator class destructor
        ~LedActuator();

        /// @brief This method turns on the light
        void enableLED();

        /// @brief This method turns off the light
        void desableLED();
};

#endif // LEDACTUATOR_H