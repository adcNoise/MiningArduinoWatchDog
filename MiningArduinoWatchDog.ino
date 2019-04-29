#include "Miner.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define WORKER0 12

#define WORKER0_OUT_RESET_SW  2
#define WORKER0_OUT_PWR_SW    3

Miner Worker0(WORKER0,WORKER0_OUT_RESET_SW,WORKER0_OUT_PWR_SW);

unsigned long timingA;
unsigned long timingB;
unsigned long timingC;

#define chbit(reg,bit)  reg ^= (1<<bit)
#define sbit(reg,bit)  reg |= (1<<bit)

void setup() {
  // initialize serial:
  Serial.begin(19200);

  PCICR   |= _BV(PCIE0);
  PCMSK0  |= _BV(PCINT0);

  sbit(DDRB,5);
}

void loop() {
  if (millis() - timingA > 10){ // 0.01s пауза 
      timingA = millis();
      Worker0.StatusUpdate();
  }

    if (millis() - timingB > 500){ // 0.01s пауза 
      timingB = millis();
      Worker0.Reset();
  }
      
  while (Serial.available() > 0) {
    if (Serial.read() == '\n') {
      
    }
  }
}

ISR(PCINT0_vect)
{
  if (PINB & _BV(PB0)){
      Worker0.timer = TIMER_VALUE;  // сброс
      Worker0.WorkerReset = STATE_OK;
      
      chbit(PORTB,5);
    }
}
