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
  if (millis() - timingC > 1000){ // 0.01s пауза 
      timingC = millis();
      Serial.println(Worker0.timer);
      
  }
    if (millis() - timingB > 500){ // 0.01s пауза 
      timingB = millis();
      Worker0.Reset();
  }
       
  while (Serial.available()) {
    //if (Serial.read() == 0xD){
    //  Worker0.timer = TIMER_VALUE;
    //  Worker0.WorkerReset = STATE_OK;
    //  chbit(PORTB,5);}
    char incByte = Serial.read();
    if (incByte == 'A'){   // сбросить счётчик
      Worker0.timer = TIMER_VALUE;
      Worker0.WorkerReset = STATE_OK;
      chbit(PORTB,5);}
    if (incByte == 'r'){ // отправить r чтобы перезагрузить компьютер
        Serial.println("Reseting!");
        digitalWrite( Worker0.portOut_reset, LOW );     // pull-down   // НЕ МЕНЯТЬ, ИНАЧЕ МОЖЕТ СГОРЕТЬ КАРТА!!!
        pinMode(      Worker0.portOut_reset, OUTPUT);    // as OUTPUT
        delay(300);
        pinMode(      Worker0.portOut_reset, INPUT);
        Serial.println("Delaying...");
        uint32_t counter = DELAYING_TIME_SEC;
        while(counter--){
             delay(1000);
             Serial.print(counter);
             Serial.println("s");
        }
    }
    if (incByte == 'p'){ // отправить p чтобы включить/выключить компьютер
        digitalWrite(   Worker0.portOut_pwr, LOW );       // pull-down   // НЕ МЕНЯТЬ, ИНАЧЕ МОЖЕТ СГОРЕТЬ КАРТА!!!
        pinMode(        Worker0.portOut_pwr, OUTPUT);    // as OUTPUT
        Serial.println("Power OFF");
        delay(5000);
        pinMode(      Worker0.portOut_pwr, INPUT);
        Serial.println("Delaying...");
        uint32_t counter = DELAYING_TIME_SEC;
        while(counter--){
             delay(1000);
             Serial.print(counter);
             Serial.println("s");
        }
    }
    if (incByte == ' '){  // сбросить счётчик
      Worker0.timer = TIMER_VALUE;
      Worker0.WorkerReset = STATE_OK;
      chbit(PORTB,5);}   
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
