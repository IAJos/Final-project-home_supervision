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
    uint8_t readValue = analogRead(p_mqSensor);
    return readValue;
}

double Sensor::getTemperature()
{
    uint8_t readValue = analogRead(p_lmSensor);
    double data = (double) readValue * (5/10.24);
    return data;
}

uint8_t Sensor::getLightLevel()
{
    uint8_t readValue = analogRead(p_ldrSensor);
    readValue = map(readValue, 0, 1023, 0, 255);
    return readValue;
}