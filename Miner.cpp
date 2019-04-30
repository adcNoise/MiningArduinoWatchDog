#include "Miner.h"
#include <avr/io.h>

void Miner::Reset(){    
    uint32_t counter;
    switch(WorkerReset){
      case STATE_RESET_1:
        Serial.println("Reseting!");
        digitalWrite( portOut_reset, LOW );     // pull-down   // НЕ МЕНЯТЬ, ИНАЧЕ МОЖЕТ СГОРЕТЬ КАРТА!!!
        pinMode(      portOut_reset, OUTPUT);    // as OUTPUT
        WorkerReset++;
      break;
      case STATE_DELAY_1:
        WorkerReset++;
      break;
      case STATE_RESET_2:
         pinMode(      portOut_reset, INPUT);
         WorkerReset++;
      break;
      case STATE_DELAY_2:
        Serial.println("Delaying...");
        counter = DELAYING_TIME_SEC;
        while(counter--&&((timer!=1)||(timer!=0))){
             delay(1000);
             Serial.print(counter);
             Serial.println("s");
          }
         WorkerReset++;
      break;
      case STATE_RESET_3:
        Serial.println("Reseting!");
        digitalWrite( portOut_reset, LOW );     // pull-down   // НЕ МЕНЯТЬ, ИНАЧЕ МОЖЕТ СГОРЕТЬ КАРТА!!!
        pinMode(      portOut_reset, OUTPUT);    // as OUTPUT
        WorkerReset++;
      break;
      case STATE_DELAY_3:
        WorkerReset++;
      break;
      case STATE_RESET_4:
         pinMode(      portOut_reset, INPUT);
         WorkerReset++;
      break;
      case STATE_DELAY_4:
        Serial.println("Delaying...");
        counter = DELAYING_TIME_SEC;
        while(counter--&&((timer!=1)||(timer!=0))){
             delay(1000);
             Serial.print(counter);
             Serial.println("s");
          }
        WorkerReset++;
      break;

      case STATE_PWR_OFF_1:
        digitalWrite(   portOut_pwr, LOW );       // pull-down   // НЕ МЕНЯТЬ, ИНАЧЕ МОЖЕТ СГОРЕТЬ КАРТА!!!
        pinMode(        portOut_pwr, OUTPUT);    // as OUTPUT
        Serial.println("Power OFF");
        counter = 5;
        while(counter--){ // условие не добавлять, т.к. после нужно включить кнопку обратно
             delay(1000);
             Serial.print(counter);
             Serial.println("s");
          }
        pinMode(      portOut_pwr, INPUT);
        Serial.println("Power ON");
        counter = DELAYING_TIME_SEC_PW;
        while(counter--&&((timer!=1)||(timer!=0))){
             delay(1000);
             Serial.print(counter);
             Serial.println("s");
          }
        WorkerReset++;
      break;
      case STATE_REPEAT:
        WorkerReset = STATE_RESET_1;
      break;
      case STATE_OK:
        pinMode(      portOut_reset, INPUT);
      break;
      default:
       WorkerReset++;
       break;
      }
  }

void Miner::StatusUpdate(){
    if(timer!=0)
      timer--;
    
    if(timer==1){
      WorkerReset = STATE_RESET_1;
      timer--;
      }
  }

Miner::Miner(unsigned char _portIn, unsigned char _portOut_reset, unsigned char _portOut_pwr){
    pinMode(      _portIn, INPUT);     // as INPUT
    digitalWrite( _portIn, HIGH );     // pull-up

    //digitalWrite( _portOut_reset, LOW );     // pull-down   // НЕ МЕНЯТЬ, ИНАЧЕ МОЖЕТ СГОРЕТЬ КАРТА!!!
    //digitalWrite( _portOut_pwr,   LOW );     // pull-down
    
    pinMode(      _portOut_reset, INPUT);    // as OUTPUT
    pinMode(      _portOut_pwr,   INPUT);    // as OUTPUT

    portIn = _portIn;
    portOut_reset = _portOut_reset;
    portOut_pwr   = _portOut_pwr;
  }
