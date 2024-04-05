#include "LightSensor.hpp"

LightSensor::LightSensor(uint8_t ldrSensor)
{
    p_ldrSensor = ldrSensor;
    pinMode(p_ldrSensor, INPUT);
}

LightSensor::~LightSensor(){}

uint8_t LightSensor::getLightLevel()
{
    uint8_t readValue = map(analogRead(p_ldrSensor), 0, 1023, 0, 255);
    return readValue;
}