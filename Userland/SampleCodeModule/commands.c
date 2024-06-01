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

static char * itoa(uint64_t num){
    int base = 10;
    int i = 0;
    char isNegative = 0;
    char str[8] = {0};

	// If the number is zero...
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }

    // If the number is negative...
    if (num < 0) {
        isNegative = 1;
        num = -num;
    }

    while (num != 0) {
        int rem = num % base;
        str[i++] = rem + '0';
        num = num / base;
    }

    // If the number is negative...
    if (isNegative) str[i++] = '-';

    str[i] = '\0';

    // Reverse the string
    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
    return str;
}


void regs(){
    uint64_t buffer[17];
    print("Registers:");
    getRegisters(buffer);
    for (int i = 0; i < 17; i++)
    {
        print(itoa(buffer[i]));
        print("\n");
    }
    return;
    
}