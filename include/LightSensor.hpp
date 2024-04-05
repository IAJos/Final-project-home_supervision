#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H

#include <Arduino.h>

/// @brief This class collects data on the degree of luminosity.
class LightSensor
{
    private:
        /// @brief This property represents the pin to which our 
        ///        brightness sensor will be connected.
        uint8_t p_ldrSensor;

    public:
        /// @brief LightSensor class constructor
        /// @param ldrSensor Represents the pin to which our 
        ///        brightness sensor will be connected.
        LightSensor(uint8_t ldrSensor);

        /// @brief LightSensor class destructor
        ~LightSensor();

        /// @brief This function returns the brightness level 
        ///        read by the sensor
        /// @return uint8_t
        uint8_t getLightLevel();
};

#endif // LIGHTSENSOR_H