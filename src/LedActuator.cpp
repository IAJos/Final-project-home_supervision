#include "LedActuator.hpp"

LedActuator::LedActuator(uint8_t ledActuator)
{
    p_ledActuator = ledActuator;
    pinMode(p_ledActuator, OUTPUT);
}

LedActuator::~LedActuator(){}

void LedActuator::enableLED()
{
    digitalWrite(p_ledActuator, HIGH);
}

void LedActuator::desableLED()
{
    digitalWrite(p_ledActuator, LOW);
}