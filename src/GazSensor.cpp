#include "GazSensor.hpp"

GazSensor::GazSensor(uint8_t mqSensor)
{
    p_mqSensor = mqSensor;
    pinMode(p_mqSensor, INPUT);
}

GazSensor::~GazSensor(){}

uint8_t GazSensor::getCOConcentrations()
{
    uint8_t readValue = map(analogRead(p_mqSensor), 0, 1023, 0, 255);
    return readValue;
}