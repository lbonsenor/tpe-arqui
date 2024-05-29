#include <stdint.h>

#include "timeHandler.h"
#include "keyboardDriver.h"
#include "videoDriver.h"


void intDispatcher(uint64_t code){
    if(code == 0){
        timerHandler();
        //printBuffer();
        print(0x00159854, 'T');
    }
    else if(code == 1){
        keyboardHandler();
        print(0x00159854, 'u');
    }
}