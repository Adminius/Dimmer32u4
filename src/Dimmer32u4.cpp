/*
  Dimmer32u4.cpp - Library for dimmer application on ATmega32U4.
  Created by E.Burkowski, February 14, 2017.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Dimmer32u4.h"

/*
Timer 1&3 resolutions/pwm frequencys for pwm pins 11,10,9,5:
Main Clock (MHz):   16	16	16	16	16	16	16	16	16		8	8	8	8	8	8	8	8	8	8	8
Prescaler:			1	1	1	1	8	8	8	64	64		1	1	1	1	1	8	8	8	8	64	64
Resolution (bits):  16	15	14	13	12	11	10	9	8		16	15	14	13	12	12	11	10	9	9	8
PWM Frequency (Hz): 122	244	488	976	244	488	978	244	490		61	122	244	488	976	122	244	488	978	122	245

only 1000Hz and 12bit@8MHz or 10bit@16Mhz supported

Register:
TCCRxB: COMxA1,COMxA0,COMxB1,COMxB0,COMxC1,COMxC0,WGMx1,WGMx0
TCCRxB: x,x,x,WGMx3,WGMx2,CSx2,CSx1,CSx0

*/



Dimmer32u4::Dimmer32u4(int pin)
{
  pinMode(pin, OUTPUT);
  _pin = pin;
  _invert = false;
}

Dimmer32u4::Dimmer32u4(int pin, bool invert)
{
  pinMode(pin, OUTPUT);
  _pin = pin;
  _invert = invert;
}


void Dimmer32u4::init()
{	
	bool timer1 = false;
	bool timer3 = false;
	pinMode(_pin, OUTPUT);
	switch (_pin) {
		case 11:
			if (_invert){
				bitSet  (TCCR1A,COM1C1);
				bitSet  (TCCR1A,COM1C0);
			}else{
				bitSet  (TCCR1A,COM1C1);
				bitClear(TCCR1A,COM1C0);
			}
			timer1 = true;
			break;
		case 10:
			if (_invert){
				bitSet  (TCCR1A,COM1B1);
				bitSet  (TCCR1A,COM1B0);
			}else{
				bitSet  (TCCR1A,COM1B1);
				bitClear(TCCR1A,COM1B0);
			}
			timer1 = true;
			break;
		case 9:
			if (_invert){
				bitSet  (TCCR1A,COM1A1);
				bitSet  (TCCR1A,COM1A0);
			}else{
				bitSet  (TCCR1A,COM1A1);
				bitClear(TCCR1A,COM1A0);
			}
			timer1 = true;
			break;
		case 5:
			if (_invert){
				bitSet  (TCCR3A,COM3A1);
				bitSet  (TCCR3A,COM3A0);
			}else{
				bitSet  (TCCR3A,COM3A1);
				bitClear(TCCR3A,COM3A0);
			}
			timer3 = true;
			break;
		default:
			break;
	}
	if (F_CPU <= 8000000L) {
		_resolution = 12;
		_maxValue = 4000; //12bit
	}else{
		_resolution = 10;
		_maxValue = 1000; //10bit
	}
	if (timer1){
		ICR1 = _maxValue;
		//PWM, Phase Correct, counts up to ICR1, Atmel Datasheet, Table 14-4
		bitSet  (TCCR1B,WGM13);
		bitClear(TCCR1B,WGM12);
		bitSet  (TCCR1A,WGM11);
		bitClear(TCCR1A,WGM10);
		//set prescaler, Atmel Datasheet, Table 14-5
		bitClear(TCCR1B,CS12);
		if (_resolution == 12){
			//set prescaler to 1
			bitClear(TCCR1B,CS11);
			bitSet  (TCCR1B,CS10);
		}else{
			//set prescaler to 8
			bitSet  (TCCR1B,CS11);
			bitClear(TCCR1B,CS10);
		}
	}
	if (timer3){
		ICR3 = _maxValue;
		//PWM, Phase Correct, counts up to ICR3, Atmel Datasheet, Table 14-4
		bitSet  (TCCR3B,WGM33);
		bitClear(TCCR3B,WGM32);
		bitSet  (TCCR3A,WGM31);
		bitClear(TCCR3A,WGM30);
		//set prescaler, Atmel Datasheet, Table 14-5
		bitClear(TCCR3B,CS32);
		if (_resolution == 12){
			//set prescaler to 1
			bitClear(TCCR3B,CS31);
			bitSet  (TCCR3B,CS30);
		}else{
			//set prescaler to 8
			bitSet  (TCCR3B,CS31);
			bitClear(TCCR3B,CS30);
		}
	}
#ifndef __AVR_ATmega32U4__
    #error "This library only supports ATmega32U4 based boards (e.g. Leonardo/Micro...)"
#endif

}

void Dimmer32u4::setValue(int value)
{
	int normalizedValue = value;
	if (value > _maxValue){
		normalizedValue = _maxValue;
	}
	if (value < 0){
		normalizedValue = 0;
	}
	switch(_pin){
		case 11:
			OCR1C = normalizedValue;
			break;
		case 10:
			OCR1B = normalizedValue;
			break;
		case 9:
			OCR1A = normalizedValue;
			break;
		case 5:
			OCR3A = normalizedValue;
	}
}

int Dimmer32u4::getMaxValue(){
	return _maxValue;
}

int Dimmer32u4::getResolution(){
	return _resolution;
}

