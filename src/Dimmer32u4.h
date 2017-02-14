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
    Dimmer32u4(int pin);
    Dimmer32u4(int pin, bool invert);
    void setValue(int value);
	int getMaxValue();
	int getResolution();
	void init();
  private:
	int _maxValue;
    int _pin;
	int _frequency;
	int _value;
	int _resolution;
	bool _invert;
	

};

#endif