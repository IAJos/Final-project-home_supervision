#include "Sensor.hpp"
#include <cstdint>
#include <Arduino.h>

Sensor::Sensor(uint8_t mqSensor, uint8_t lmSensor, uint8_t ldrSensor)
{
    p_mqSensor = mqSensor;
    p_lmSensor = lmSensor;
    p_ldrSensor = ldrSensor;
}

Sensor::~Sensor(){}

uint8_t Sensor::getCOConcentrations()
{
    uint8_t readValue = map(analogRead(p_mqSensor), 0, 1023, 0, 255);
    return readValue;
}

float Sensor::getTemperature(DallasTemperature sensors_ds, DeviceAddress ds_address)
{
    sensors_ds.requestTemperaturesByAddress(ds_address);
    float temperature = sensors_ds.getTempC(ds_address);
    return temperature;
}

uint8_t Sensor::getLightLevel()
{
    uint8_t readValue = map(analogRead(p_ldrSensor), 0, 1023, 0, 255);
    return readValue;
}