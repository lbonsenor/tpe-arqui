#include <time.h>
#include <videoDriver.h>
static unsigned long ticks = 0;

void timerHandler() {
	ticks++;
	printNoColor("TimerTick");
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

void timer_wait(int delta) { 
	int initialTicks = ticks;
	while(ticks - initialTicks < delta) {
		_hlt();
	}
}
