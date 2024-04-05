#ifndef TEMPERATURESENSOR_H
#define TEMPERATURESENSOR_H

#include "DallasTemperature.h"

/// @brief This class is used to collect ambient temperature data.
class TemperatureSensor
{
    private:
        /// @brief This property represents the pin to which our 
        ///        temperature sensor will be connected.
        uint8_t p_dsSensor;

    public:
        /// @brief TemperatureSensor class constructor
        /// @param dsSensor Represents the pin to which our 
        ///        temperature sensor will be connected.
        TemperatureSensor(uint8_t dsSensor);

        /// @brief TemperatureSensor class destructor
        ~TemperatureSensor();

        /// @brief This function returns the ambient temperature
        ///        read by the sensor
        /// @return float
        float getTemperature();
};

#endif // TEMPERATURESENSOR_H