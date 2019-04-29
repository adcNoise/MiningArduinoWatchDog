#ifndef __MINER_H__
#define __MINER_H__
#include <inttypes.h>
#include <Arduino.h>

#define TIMER_VALUE 0x0000FFFF

struct Miner
{
 uint32_t timer = TIMER_VALUE;     // таймер обратного отсчёта
 uint8_t  WorkerReset = false;
 Miner(unsigned char portIn, unsigned char portOut);
 void StatusUpdate();
 
//variables
private:	
public:
};

#endif //__MINER_H__
