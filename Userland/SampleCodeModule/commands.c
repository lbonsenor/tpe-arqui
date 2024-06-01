#include <commands.h>
#include <eliminator.h>

#define TIME_LENGTH 9

void help() {
    print("Welcome to kaOS Manual! Here's the list of commands available");
    print("\n   time: Displays the current time in the format ??");
    print("\n   eliminator: Play Eliminator against yourself or a friend. Use WASD to move Player 1, IJKL to move Player 2");
    print("\n   regs: Display the current value of all registers");
    print("\n   clear: Clean the screen");
    print("\n   scaledown: Reduce the text size (min: 1, default: 1)");
    print("\n   scaleup: Increment the text size (max: 4, default: 1)");
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
    return;
}

// Function to reverse a string
void reverse(char str[], int length) {
    int start = 0;
    int end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

// Function to implement itoa
char* itoa(int num, char* str) {
    int isNegative = 0;
    int i = 0;

    // Handle 0 explicitly
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    // Check if number is negative
    if (num < 0) {
        isNegative = 1;
        num = -num;
    }

    // Process individual digits
    while (num != 0) {
        int rem = num % 10;
        str[i++] = rem + '0';
        num = num / 10;
    }

    // If number is negative, append '-'
    if (isNegative) str[i++] = '-';

    str[i] = '\0'; // Append string terminator

    // Reverse the string
    reverse(str, i);

    return str;
}


void regs() {
    uint64_t buffer[17];
    getRegisters(buffer);
    char * registerNames[] = {"RIP", "RAX", "RBX", "RCX", "RDX", "RSI", "RDI", "RBP", "RSP", "R8", "R9", "R10", "R11", "R12", "R13", "R14", "R15"};
    print("Registers:\n");
    for (int i = 0; i < 17; i++) {
        char str[8] = {0};
        print(registerNames[i]); print(": ");
        print(itoa(buffer[i], str));
        print("\n");
    }
    return;
}