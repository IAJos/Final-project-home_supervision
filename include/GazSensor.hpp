#ifndef GAZSENSOR_H
#define GAZSENSOR_H

#include <Arduino.h>

/// @brief This class collects data on carbon 
///        monoxide concentration in air.
class GazSensor
{
    private:
        /// @brief This property represents the pin to 
        ///        which our gas sensor will be connected.
        uint8_t p_mqSensor;

    public:
        /// @brief GazSensor class constructor
        /// @param mqSensor Represents the pin to which 
        ///                 our gas sensor will be connected.
        GazSensor(uint8_t mqSensor);

        /// @brief GazSensor class destructor
        ~GazSensor();

        /// @brief This function returns the carbon monoxide 
        ///        air concentration value
        /// @return uint8_t
        uint8_t getCOConcentrations();
};

#endif // GAZSENSOR_H