#ifndef SPEAKERACTUATOR_H
#define SPEAKERACTUATOR_H

#include <Arduino.h>

/// @brief This class is used to activate or deactivate a speaker.
class SpeakerActuator
{
    private:
        /// @brief This property represents the pin to which our 
        ///        speaker will be connected.
        uint8_t p_speakerActuator;

    public:
        /// @brief SpeakerActuator class constructor
        /// @param speakerActuator Represents the pin to which our 
        ///                        speaker will be connected.
        SpeakerActuator(uint8_t speakerActuator);

        /// @brief SpeakerActuator class destructor
        ~SpeakerActuator();

        /// @brief This method turns on the speaker
        /// @param melody 
        /// @param noteDurations 
        void enableSpeaker();

        /// @brief This method turns off the speaker
        void desableSpeaker();
};

#endif // SPEAKERACTUATOR_H