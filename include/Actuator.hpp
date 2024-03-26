#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <cstdint>

class Actuator
{
private:
    uint8_t p_fanActuator;
    uint8_t p_speakerActuator;
    uint8_t p_ledActuator;
public:
    Actuator(uint8_t fanActuator, uint8_t speakerActuator, uint8_t ledActuator);
    ~Actuator();

    bool enableFan();
    void desableFan();
    void enableSpeaker();
    void desableSpeaker();
    void enableLED();
    void desableLED();
};

#endif // ACTUATOR_H