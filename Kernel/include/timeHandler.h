#ifndef _TIMERHANDLER_H_
#define _TIMERHANDLER_H_

#include <stdint.h>

void timerHandler();
uint64_t getElapsedTicks();
uint64_t getElapsedMillis();
uint64_t getElapsedSeconds();
uint64_t getCurrentTime();

#endif 