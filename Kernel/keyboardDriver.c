
#include <keyboardDriver.h>
#include <videoDriver.h>
#include <lib.h>
#include <interruptions.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

extern int getKey();

static const char keyboard[256] = {
    0, 1/*esc*/, '1', '2', '3', '4', '5', '6', '7', '8', 
    '9', '0', '\'', '<', '\b', '\t', 'q', 'w', 'e', 'r', 
    't', 'y', 'u', 'i', 'o', 'p', '\\', '+', '\n', 0, 
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', 
    '{', '|', 5/*shift*/, '}', 'z', 'x', 'c', 'v', 'b', 'n', 
    'm', ',', '.', '-', 0, '*', 0, ' ', 0, 0, 
    0/*60*/, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 17/*up*/, 0, 0, 18/*left*/, 0, 19/*right*/, 0, 0, 
    20/*down*/, 0,
};

// Buffer variables
static char buffer[BUFFER_SIZE] = {0};
static int bufferIndex = 0;
static int readBuffer = 0;

// Flags
char enterFlag = 0;
char shiftFlag = 0;
char capsLockFlag = 0;

char isAlpha(char c) {
    return (c >= 'a' && c <= 'z');
}
void addToBuffer(char c) {
    // Resets the index if the buffer is full
    printNoColor("Added to buffer");
    if (bufferIndex >= BUFFER_SIZE) bufferIndex = 0;
    buffer[bufferIndex++] = c;
}

void keyboardHandler() {
    printNoColor("KeyboardHandler Start");
    unsigned char key = getKey();
    if (key < 83 || key == 0xAA /* Release SHIFT */ || key == 0x3A /* CAPS Lock */) {
        if (bufferIndex >= BUFFER_SIZE) return; // Buffer is full
        if (keyboard[key] == 5 && !shiftFlag) shiftFlag = 1; // Shift key
        else if (key == 0xAA) shiftFlag = 0; // Shift released
        else if (key == 0x3A) capsLockFlag = !capsLockFlag; // Caps Lock
        else {
            char character = keyboard[key];
            if (isAlpha(key)) {
                if ((shiftFlag && !capsLockFlag) || (!shiftFlag && capsLockFlag)) addToBuffer(character - 'a' + 'A');
                else addToBuffer(character);
            } else {
                if (shiftFlag) addToBuffer(keyboard[key]);
                else addToBuffer(character);
            }
            //print(0x00159854, character);
        }
    }
    //_wait();
}

void removeCharFromBuffer() {
    buffer[--bufferIndex] = '\0';
}

void cleanBuffer() {
    memset(buffer, '\0', bufferIndex);
    bufferIndex = 0;
}
char getFromBuffer() {
    if (readBuffer < BUFFER_SIZE) readBuffer = 0;
    return buffer[readBuffer++];
}

//used for debugging lol
void printBuffer() {
    printNoColor("Buffer");
}