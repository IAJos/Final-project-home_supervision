#include "Actuator.hpp"
#include <cstdint>
#include <Arduino.h>

Actuator::Actuator(uint8_t fanActuator, uint8_t speakerActuator, uint8_t ledActuator)
{
    p_fanActuator = fanActuator;
    p_speakerActuator = speakerActuator;
    p_ledActuator = ledActuator;
}

Actuator::~Actuator(){}

bool Actuator::enableFan()
{
    pinMode(p_fanActuator, OUTPUT);
    for(int motorSpeed = 0 ; motorSpeed <= 255; motorSpeed+=5)
        analogWrite(p_fanActuator, motorSpeed); 
    
    return true;
}

void Actuator::desableFan()
{
    pinMode(p_fanActuator, OUTPUT);
    if (enableFan())
        for(int motorSpeed = 255 ; motorSpeed >= 0; motorSpeed-=5)
        {
            analogWrite(p_fanActuator, motorSpeed);
            delay(30);
        }    
}

void Actuator::enableSpeaker()
{
    
}

void Actuator::desableSpeaker()
{

}

void Actuator::enableLED()
{
    pinMode(p_ledActuator, OUTPUT);
    digitalWrite(p_ledActuator, HIGH);
}

void Actuator::desableLED()
{
    pinMode(p_ledActuator, OUTPUT);
    digitalWrite(p_ledActuator, LOW);
}