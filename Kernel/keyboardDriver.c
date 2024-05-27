extern int getKey();

#include <keyboardDriver.h>
#include <videoDriver.h>
#include <lib.h>

#include <stdlib.h>

#define BUFFER_SIZE 1024

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
char buffer[BUFFER_SIZE] = {0};
int bufferIndex = 0;

// Flags
char enterFlag = 0;
char shiftFlag = 0;
char capsLockFlag = 0;

char isAlpha(char c) {
    return (c >= 'a' && c <= 'z');
} 

//SACAR DE ACA EL SCANCODEE
void keyboardHandler(uint8_t scancode){
  //si hay lugar agregarlo al buffer
  if(bufferIndex < BUFFER_SIZE){
    buffer[bufferIndex++] = scancode;
  }
}

void addToBuffer(char c) {
  // Resets the index if the buffer is full
  if (bufferIndex >= BUFFER_SIZE) bufferIndex = 0;
  buffer[bufferIndex++] = c;
}

void removeCharFromBuffer() {
  buffer[--bufferIndex] = '\0';
}

void cleanBuffer() {
  memset(buffer, '\0', bufferIndex);
  bufferIndex = 0;
}

// Returns the scanned key, and checks various cases
char scanKey() {
  // While enter key is not pressed
  int scancodeKey = getKey();
  // Translate the key to ASCII
  char ASCIIkey = keyboard[scancodeKey];
  // Alternate capslock
  if (scancodeKey == 0x3A) capsLockFlag = !capsLockFlag;
  // Shift released
  else if (scancodeKey == 0xAA) shiftFlag = 0;
  else {
    switch (ASCIIkey) {
      // Key is not valid
      case 0: break;
      // Shift pressed
      case 5: 
        shiftFlag = 1;
        break;
      // Key is 'enter'
      case '\n':
        cleanBuffer();
        break;
      // Key is 'backspace'
      case '\b': 
        removeCharFromBuffer();
        break;
      // Key is valid
      default:
        // Caps
        if (isAlpha(ASCIIkey) && ((capsLockFlag && !shiftFlag) || (!capsLockFlag && shiftFlag))) addToBuffer(ASCIIkey - 'a' + 'A');
        // Not caps
        else addToBuffer(ASCIIkey);
        break;
    }
  }
  return scancodeKey;
}

//cambiar a getKey
void printKey() {
  while (1) {
    // While enter key is not pressed
    while (!enterFlag) {
      int scancodeKey = getKey();
      // Translate the key to ASCII
      char key = keyboard[scancodeKey];
      // Alternate capslock
      if (scancodeKey == 0x3A) capsLockFlag = !capsLockFlag;
      // Shift released
      else if (scancodeKey == 0xAA) shiftFlag = 0;
      else {
        switch (key) {
          // Key is not valid
          case 0: break;
          // Shift pressed
          case 5: 
            shiftFlag = 1;
            break;
          // Key is 'enter'
          case '\n':
            enterFlag = 1;
            putCharCursor(0x00159854, key);
            break;
          // Key is 'backspace'
          case '\b': 
            removeCharFromBuffer();
            putCharCursor(0x00159854, key);
            break;
          // Key is valid
          default:
            // Caps
            if (isAlpha(key) && ((capsLockFlag && !shiftFlag) || (!capsLockFlag && shiftFlag))) {
              key = key - 'a' + 'A';
              addToBuffer(key);
            } 
            // Not caps
            else addToBuffer(key);
            putCharCursor(0x00159854, key);
            break;
        }
      }
    }
    cleanBuffer();
    enterFlag = 0;
  }
}