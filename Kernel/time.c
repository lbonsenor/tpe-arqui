#include <time.h>
#include <videoDriver.h>
#include <interrupts.h>
#include <lib.h>

extern uint64_t getMinutes();
extern uint64_t getSeconds();
extern uint64_t getHours();
static unsigned long ticks = 0;

void timerHandler() {
	ticks++;
}

int ticksElapsed() {
	return ticks;
}
// probs will need it for snake
int millisElapsed() {
	return ticks * (1000 / 18);
}
//rounding up slightly
int secondsElapsed() {
	return ticks / 18;
	
}

void timer_wait(int delta) { 
	int initialTicks = ticks;
	while(ticks - initialTicks < delta) {
		_hlt();
	}
}
