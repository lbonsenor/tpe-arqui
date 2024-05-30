#ifndef _TIME_H_
#define _TIME_H_
#include <stdint.h>

void timerHandler();
int ticksElapsed();
int secondsElapsed();
int millisElapsed();
void timer_wait(int delta);
#endif
