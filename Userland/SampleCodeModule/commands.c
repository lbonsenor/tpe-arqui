#include <commands.h>
#include <eliminator.h>

static char* commands[] = {"help", "time", "eliminator", "eliminator2", "regs", "clear", "scaledown", "scaleup"};

void help(){
    print("Welcome to kaOS Manual! Here's the list of commands available");
    print("\n   time: Displays the current time in the format ??");
    print("\n   eliminator: Play Eliminator in Single-Player mode. Use WASD to move");
    print("\n   eliminator2: Play Eliminator in Multi-Player mode. Use WASD to move Player 1 and IJKL to move Player 2");
    print("\n   regs: Display the current value of all registers");
    print("\n   clear: Clean the screen");
    print("\n   scaledown: Reduce the text size (min: 1, default: 1)");
    print("\n   scaleup: Increment the text size (max: 4, default: 1)");
}

void time(){

}


void regs(){

}