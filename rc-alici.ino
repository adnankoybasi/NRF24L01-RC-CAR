#include <SPI.h>
#include "RF24.h"

RF24 radio(8, 7);
const uint64_t pipe = 0xE8E8F0F0E1LL;

//Joystick input variables
int joyValueMax = 1023;
int joyValueMin = 0;
int joyValueMid = 508;
int joyValueMidUpper = joyValueMid + 15;
int joyValueMidLower = joyValueMid - 15;

int in1 = 3;
int in2 = 5;
int in3 = 6;
int in4 = 9;

struct MyData {
  int axis_x;
  int axis_y;
  int axis_1;
  byte axis_2;
};

MyData data;

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  radio.begin();
  radio.openReadingPipe(1, pipe);
  radio.startListening();
}

void loop(void) {
  while (radio.available()) {
    radio.read(&data, sizeof(MyData));
  }
  if (data.axis_1 == 1) {
    digitalWrite(2, HIGH);
    digitalWrite(4, HIGH);
  } else {
    digitalWrite(2, LOW);
    digitalWrite(4, LOW);
  }
  if (data.axis_x > joyValueMidUpper) {
    int ileri_Speed = map(data.axis_x, joyValueMidUpper, joyValueMax, 120, 255);
    analogWrite(in2, ileri_Speed);
    analogWrite(in1, 0);
  } else if (data.axis_x < joyValueMidLower) {
    int geri_Speed = map(data.axis_x, joyValueMidLower, joyValueMin, 120, 255);
    analogWrite(in2, 0);
    analogWrite(in1, geri_Speed);
  } else {
    analogWrite(in1, 0);
    analogWrite(in2, 0);
  }
  if (data.axis_y > joyValueMidUpper) {
    analogWrite(in4, 255);
    analogWrite(in3, 0);
  } else if (data.axis_y < joyValueMidLower) {
    analogWrite(in4, 0);
    analogWrite(in3, 255);
  } else {
    analogWrite(in3, 0);
    analogWrite(in4, 0);
  }
  delay(50);
}

