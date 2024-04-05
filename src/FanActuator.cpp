#include "FanActuator.hpp"

FanActuator::FanActuator(uint8_t fanActuator)
{
    p_fanActuator = fanActuator;
    pinMode(p_fanActuator, OUTPUT);
}

FanActuator::~FanActuator(){}

void FanActuator::enableFan()
{
    for(int motorSpeed = 0 ; motorSpeed <= 255; motorSpeed+=5)
        analogWrite(p_fanActuator, motorSpeed); 
}

void FanActuator::desableFan()
{
    for(int motorSpeed = 255 ; motorSpeed >= 0; motorSpeed-=5)
    {
        analogWrite(p_fanActuator, motorSpeed);
        delay(30);
    }    
}