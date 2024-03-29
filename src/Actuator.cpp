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
    
    fanStatus = true;
    return fanStatus;
}

void Actuator::desableFan()
{
    pinMode(p_fanActuator, OUTPUT);
    if (fanStatus)
        for(int motorSpeed = 255 ; motorSpeed >= 0; motorSpeed-=5)
        {
            analogWrite(p_fanActuator, motorSpeed);
            delay(30);
        }    
}

void Actuator::enableSpeaker(int melody[], int noteDurations[])
{
  for (int thisNote = 0; thisNote < 7; thisNote)
  {
    int noteDuration = 800/noteDurations[thisNote];
    tone(p_speakerActuator, melody[thisNote],noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(p_speakerActuator);
  }
}

void Actuator::desableSpeaker()
{
    noTone(p_speakerActuator);
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