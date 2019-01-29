#include <SPI.h>
#include "RF24.h" 
RF24 radio(7,8);
const uint64_t pipe = 0xE8E8F0F0E1LL; 

const byte joyStickPin_x = A2;
const byte joyStickPin_y = A3;
int butondurumu = 0;
int deger = 0;

struct MyData {
  int axis_x;
  int axis_y;
  int axis_1;
  byte axis_2;
};

MyData data;

void setup(void){
pinMode(joyStickPin_x, INPUT);
pinMode(joyStickPin_y, INPUT);
pinMode(3, INPUT_PULLUP);
digitalWrite(3, HIGH);
radio.begin();
radio.openWritingPipe(pipe);
}
void loop() {
  data.axis_x = analogRead(joyStickPin_x);
  data.axis_y = analogRead(joyStickPin_y);
  butondurumu = digitalRead(3);

  if(butondurumu == LOW && deger == 0){
    
    data.axis_1 = 1;
    deger=1;
    delay(10);
  }else if(butondurumu == LOW && deger == 1){
    data.axis_1 = 0;
    deger=0;
    delay(10);
  }else{
  }
  radio.write(&data, sizeof(MyData));
  delay(100);
}
