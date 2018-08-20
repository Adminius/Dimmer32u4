/*
  Dimmer32u4.h - Library for PWM on ATmega32U4.
  Created by E.Burkowski, February 14, 2017.
  Released into the public domain.
*/
#ifndef Dimmer32u4_h
#define Dimmer32u4_h

#include "Arduino.h"

class Dimmer32u4
{
    public:
        Dimmer32u4(uint8_t pin);
        Dimmer32u4(uint8_t pin, bool invert);
        void setValue(uint16_t value);
        uint16_t getMaxValue();
        uint8_t  getResolution();
        void init();
    private:
        uint16_t _maxValue;
        uint8_t  _pin;
        uint16_t _frequency;
        uint16_t _value;
        uint8_t  _resolution;
        bool     _invert;

};

#endif