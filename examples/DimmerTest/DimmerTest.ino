#include <Dimmer32u4.h>

//Create an instance for channel1 on pin D10
Dimmer32u4 channel1(10);
//Create an instance for channel2 on pin D5 in inverted mode
Dimmer32u4 channel2(5,true);

void setup() {
  //initialize channel1 and channel2
  channel1.init();
  channel2.init();
}

void loop() {
    //fade in
    for (int c1 = 0; c1 <= channel1.getMaxValue();c1+=20){
        channel1.setValue(c1);
        delay(20);
    }
    delay(500);
    //fade out
    for (int c1 = channel1.getMaxValue(); c1 >= 0;c1-=20){
        channel1.setValue(c1);
        delay(20);
    }
    delay(500);
    //fade in
    for (int c2 = 0; c2 <= channel2.getMaxValue();c2+=20){
        channel2.setValue(c2);
        delay(20);
    }
    delay(500);
    //fade out
    for (int c2 = channel2.getMaxValue(); c2 >= 0;c2-=20){
        channel2.setValue(c2);
        delay(20);
    }
    delay(500);
}