#ifndef _TIME_H_
#define _TIME_H_
#include <stdint.h>

void timerHandler();
int ticksElapsed();
int secondsElapsed();
uint64_t getTime();
#endif
