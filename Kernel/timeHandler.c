#include <stdint.h>
//TODO falta la libreria .h

extern uint8_t bringSeconds();
extern uint8_t bringMinutes();
extern uint8_t bringHours();


static uint64_t ticks;

void timerHandler(){
    ticks++;
}

uint64_t getElapsedTicks(){
    return ticks;
}

uint64_t getElapsedMillis(){
    return (ticks*5000)/91 ;
}

uint64_t getElapsedSeconds(){
    return (ticks * 5)/91;
}
uint64_t getCurrentTime(){
    return bringHours() | (uint64_t) bringMinutes() << 8 | ((uint64_t) bringSeconds() <<16);
}
