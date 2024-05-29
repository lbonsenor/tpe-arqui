#include <time.h>
#include <videoDriver.h>

extern uint64_t getMinutes();
extern uint64_t getSeconds();
extern uint64_t getHours();
static unsigned long ticks = 0;

void timerHandler() {
	ticks++;
	printNoColor("TimerTick");
}

uint64_t getTime(){
    return (uint64_t) getHours() | ((uint64_t)getMinutes() << 8) | ((uint64_t)getSeconds() << 16);
}

int ticksElapsed() {
	return ticks;
}
// probs will need it for snake
int millisElapsed(){
	return ticks * (1000 / 18);
}
//rounding up slightly
int secondsElapsed() {
	return ticks / 18;
}
