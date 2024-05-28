#include <stdint.h>

#include "timeHandler.h"
#include "keyboardDriver.h"
#include "videoDriver.h"


void intDispatcher(uint64_t code){
    if(code == 0){
        timerHandler();
    }
    else if(code == 1){
        keyboardHandler();
    }
}