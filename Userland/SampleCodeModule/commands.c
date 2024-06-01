#include <commands.h>
#include <eliminator.h>

#define TIME_LENGTH 9

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

char * time(){
    uint64_t time = getTime();
    char toReturn[TIME_LENGTH] = {'\0'};

    print("Current time is: ");
    for (int i = TIME_LENGTH-2; i >= 0 ; i--)
    {
        if (i == 2 || i == 5) toReturn[i] = ':';
        else {
            toReturn[i] = (time % 10) + '0';
            time = time / 10;
        }
    }
    print(toReturn);
    return toReturn;
}


void regs(){

}