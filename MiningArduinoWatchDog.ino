#include "Miner.h"

#define WORKER0 A0
#define WORKER1 A1
#define WORKER2 A2
#define WORKER3 A3
#define WORKER4 A4
#define WORKER5 A5
#define WORKER6 A6

#define WORKER0_OUT 2
#define WORKER1_OUT 3
#define WORKER2_OUT 4
#define WORKER3_OUT 5
#define WORKER4_OUT 6
#define WORKER5_OUT 7
#define WORKER6_OUT 8

Miner Worker0(WORKER0,WORKER0_OUT);
Miner Worker1(WORKER1,WORKER1_OUT);
Miner Worker2(WORKER2,WORKER2_OUT);
Miner Worker3(WORKER3,WORKER3_OUT);
Miner Worker4(WORKER4,WORKER4_OUT);
Miner Worker5(WORKER5,WORKER5_OUT);
Miner Worker6(WORKER6,WORKER6_OUT);

const int redPin = 3;
const int greenPin = 5;
const int bluePin = 6;

void setup() {
  // initialize serial:
  Serial.begin(19200);
}

void loop() {


      
  while (Serial.available() > 0) {
    int red = Serial.parseInt();
    int green = Serial.parseInt();
    int blue = Serial.parseInt();

    if (Serial.read() == '\n') {
      red = 255 - constrain(red, 0, 255);
      green = 255 - constrain(green, 0, 255);
      blue = 255 - constrain(blue, 0, 255);

      analogWrite(redPin, red);
      analogWrite(greenPin, green);
      analogWrite(bluePin, blue);

      Serial.print(red, HEX);
      Serial.print(green, HEX);
      Serial.println(blue, HEX);
    }
  }
}
