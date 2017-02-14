# Library for easy use of PWM-outputs on ATmega32U4 based Arduinos (e.g. Leonardo, Micro...)

Supported pwm pins (Arduino Leonardo/Micro): 5, 9, 10, 11

Create an instance:
normal mode (0 to max)
**Dimmer32u4 channel1(pinnumber);** 

or inverted mode (max to 0)
**Dimmer32u4 channel2(pinnumber, true);**

Instance initialization:
channel1.init();
channel2.init();

Functions:
**getMaxValue()**: returns max possible value. 

**setValue(value)**, where value=0..maxValue sets timer to "value" duty-cycle