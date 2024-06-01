#include <commands.h>
#include <eliminator.h>

#define TIME_LENGTH 9

void help() {
    print("Welcome to caOS Manual! Here's the list of commands available:");
    print("\n   time: Displays the current time");
    print("\n   eliminator: Play Eliminator against yourself or a friend. Use WASD to move Player 1, IJKL to move Player 2");
    print("\n   regs: Display the current value of all registers");
    print("\n   clear: Clean the screen");
    print("\n   scaledown: Reduce the text size (min: 1, default: 1)");
    print("\n   scaleup: Increment the text size (max: 4, default: 1)");
    print("\n");
}

void time() {
    uint64_t time = getTime();
    char toReturn[TIME_LENGTH] = {'\0'};

    print("Current time is: ");
    for (int i = TIME_LENGTH-2; i >= 0 ; i--) {
        if (i == 2 || i == 5) toReturn[i] = ':';
        else {
            toReturn[i] = (time % 10) + '0';
            time = time / 10;
        }
    }
    print(toReturn);
    print("\n");
    return;
}

char* itoa(int num, char* str, int base) {
    int i = 0;
    char isNegative = 0;

	// If the number is zero...
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    // If the number is negative...
    if (num < 0 && base == 10) {
        isNegative = 1;
        num = -num;
    }

    while (num != 0) {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
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

void regs() {
    uint64_t buffer[17];
    char getRegsUnsuccessful = getRegisters(buffer);
    if (getRegsUnsuccessful) {
        print("Press ctrl key to save registers\n");
        return;
    }
    char * registerNames[] = {" RAX", " RBX", " RCX", " RDX", " RSI", " RDI", " RBP", " RSP", "  R8", "  R9", " R10", " R11", " R12",
        " R13", " R14", " R15", " RIP"};
    for (int i = 0; i < 17; i++) {
        char str[8] = {0};
        print(registerNames[i]); print(": ");
        if (i == 9 || i == 10) print(" ");
        print(itoa(buffer[i], str, 16));
        print("h");
        print("\n");
    }
    return;
}