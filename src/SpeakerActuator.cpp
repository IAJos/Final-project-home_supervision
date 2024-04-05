#include "SpeakerActuator.hpp"

#define NOTE_G3  196
#define NOTE_C4  262
#define NOTE_E4  330
#define NOTE_G4  392

SpeakerActuator::SpeakerActuator(uint8_t speakerActuator)
{
    p_speakerActuator = speakerActuator;
    pinMode(p_speakerActuator, OUTPUT);
}

SpeakerActuator::~SpeakerActuator(){}

void SpeakerActuator::enableSpeaker()
{
    int melody[] = {NOTE_E4, NOTE_E4, NOTE_E4, NOTE_C4, NOTE_E4, NOTE_G4, NOTE_G3};
    int noteDurations[] = {8, 4, 4, 8, 4, 2, 2};

  for (int thisNote = 0; thisNote < 7; thisNote)
  {
    int noteDuration = 800/noteDurations[thisNote];
    tone(p_speakerActuator, melody[thisNote],noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(p_speakerActuator);
  }
}

void SpeakerActuator::desableSpeaker()
{
    noTone(p_speakerActuator);
}