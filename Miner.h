#ifndef __MINER_H__
#define __MINER_H__
#include <inttypes.h>
#include <Arduino.h>

#define TIMER_VALUE 0x00004650
//#define TIMER_VALUE 0x0000150// for debug!!!!!!!!!!!!!!!!!!!!

#define DELAYING_TIME_SEC     100
#define DELAYING_TIME_SEC_PW  200


enum{
  STATE_OK,
  STATE_RESET_1,
  STATE_DELAY_1,
  STATE_RESET_2,
  STATE_DELAY_2,
  STATE_RESET_3,
  STATE_DELAY_3,
  STATE_RESET_4,
  STATE_DELAY_4,
  STATE_PWR_OFF_1, 
  STATE_REPEAT
  };

struct Miner
{
 uint32_t timer = TIMER_VALUE;     // таймер обратного отсчёта
 uint8_t  WorkerReset = false;
 uint8_t  prevState;
 uint8_t  portIn;

 uint8_t portOut_reset = 2;
 uint8_t portOut_pwr   = 3;
 
 Miner(unsigned char portIn, unsigned char portOut_reset, unsigned char portOut_pwr);
 void StatusUpdate();
 void Reset();
 
//variables
private:	
public:
};

#endif //__MINER_H__
