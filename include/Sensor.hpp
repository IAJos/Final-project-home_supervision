#ifndef SENSOR_H
#define SENSOR_H

#include <cstdint>
#include "DallasTemperature.h"

class Sensor
{
    private:
        uint8_t p_mqSensor;
        uint8_t p_lmSensor;
        uint8_t p_ldrSensor;
    public:
        Sensor(uint8_t mqSensor, uint8_t lmSensor, uint8_t ldrSensor);
        ~Sensor();

        uint8_t getCOConcentrations();
        float getTemperature(DallasTemperature sensors_ds, DeviceAddress ds_address);
        uint8_t getLightLevel();
};

#endif // SENSOR_H