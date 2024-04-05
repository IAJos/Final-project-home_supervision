#include "TemperatureSensor.hpp"
#include <OneWire.h>

TemperatureSensor::TemperatureSensor(uint8_t dsSensor)
{
    p_dsSensor = dsSensor;
    pinMode(p_dsSensor, INPUT);
}

TemperatureSensor::~TemperatureSensor(){}

float TemperatureSensor::getTemperature() {
  OneWire ow(p_dsSensor); 
  byte data[12];
  byte addr[8];

  if ( !ow.search(addr)) {
      //no more sensors on chain, reset search
      ow.reset_search();
      return -1000;
  }

  if ( OneWire::crc8( addr, 7) != addr[7]) {
      Serial.println("CRC is not valid!");
      return -1000;
  }

  if ( addr[0] != 0x10 && addr[0] != 0x28) {
      Serial.print("Device is not recognized");
      return -1000;
  }

  ow.reset();
  ow.select(addr);
  ow.write(0x44,1); // start conversion, with parasite power on at the end

  byte present = ow.reset();
  ow.select(addr);
  ow.write(0xBE); // Read Scratchpad


  for (int i = 0; i < 9;  i++  ) { // we need 9 bytes
    data[i] = ow.read();
  }

  ow.reset_search();

  byte MSB = data[1];
  byte LSB = data[0];

  float tempRead = ((MSB << 8) | LSB); //using two's compliment
  float Temperature = tempRead / 16;

  return Temperature;
}