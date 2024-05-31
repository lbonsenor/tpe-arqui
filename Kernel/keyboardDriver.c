#include <keyboardDriver.h>
#include <videoDriver.h>
#include <interrupts.h>
#include <lib.h>

#define BUFFER_SIZE 1024

// Assembly function
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
static int writeIndex = 0;
static int readIndex = 0;
static int lastIndexFlag = 0;

// Flags
char enterFlag = 0;
char shiftFlag = 0;
char capsLockFlag = 0;

char isAlpha(char c) {
    return (c >= 'a' && c <= 'z');
}

void addToBuffer(char c) {
    // Resets the index if the buffer is full
    if (writeIndex >= BUFFER_SIZE) writeIndex = 0;
    buffer[writeIndex++] = c;
    lastIndexFlag = 1;
    
}

void keyboardHandler() {
  if (buffer[readIndex-1] == '\n') cleanBuffer();
  if (buffer[readIndex-1] == '\b') removeCharFromBuffer();
  
  // While enter key is not pressed
  unsigned char scancodeKey = getKey();
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
        addToBuffer(ASCIIkey);
        // cleanBuffer();
        break;
      // Key is 'backspace'
      case '\b': 
        addToBuffer(ASCIIkey);
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
}

void removeCharFromBuffer() {
  if (writeIndex > 1){
    buffer[--writeIndex] = '\0';
    buffer[--writeIndex] = '\0';    // Una vez que fue devuelto el backspace, borra los dos ultimos caracteres
  }
  
}

void cleanBuffer() {
    memset(buffer, '\0', writeIndex);
    writeIndex = 0;
    readIndex = 0;
}

void cleanRead(){
  readIndex = 0;
}

char getFromBuffer() {
    if (readIndex == writeIndex) return 0;
    if (readIndex >= BUFFER_SIZE) readIndex = 0;
    return buffer[readIndex++];
}

char getLastChar(){
  if (lastIndexFlag == 1)
  {
    lastIndexFlag = 0;
    return buffer[writeIndex-1];
  }
  
}

//used for debugging lol
void printBuffer() {
    print("Buffer");
}