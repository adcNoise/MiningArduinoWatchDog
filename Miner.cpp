#include "Miner.h"
#include <avr/io.h>

void Miner::StatusUpdate(){
    timer--;
    if(timer==1){
      timer = TIMER_VALUE;
      WorkerReset = true;}

    if(digitalRead(portIn)){
      timer = TIMER_VALUE;
    }        
  }

Miner::Miner(unsigned char portIn, unsigned char portOut){
    pinMode(      portIn, INPUT);     // as input
    digitalWrite( portIn, HIGH );     // pull-up

    pinMode(      portOut, OUTPUT);    // as input
    digitalWrite( portOut, HIGH );     // pull-up
  }
