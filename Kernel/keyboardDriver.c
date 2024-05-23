extern int getKey();
#include <keyboardDriver.h>

#define isVisibleChar(a) 

void printKey() {
    // Key map
    char kbd_US [128] =
    {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',   
  '\t', /* <-- Tab */
  'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',     
    0, /* <-- control key */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',  0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',   0,
  '*',
    0,  /* Alt */
  ' ',  /* Space bar */
    0,  /* Caps lock */
    0,  /* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,  /* < ... F10 */
    0,  /* 69 - Num lock*/
    0,  /* Scroll Lock */
    0,  /* Home key */
    0,  /* Up Arrow */
    0,  /* Page Up */
  '-',
    0,  /* Left Arrow */
    0,
    0,  /* Right Arrow */
  '+',
    0,  /* 79 - End key*/
    0,  /* Down Arrow */
    0,  /* Page Down */
    0,  /* Insert Key */
    0,  /* Delete Key */
    0,   0,   0,
    0,  /* F11 Key */
    0,  /* F12 Key */
    0,  /* All other keys are undefined */
    };
    
    char flag = 0;
    char buffer[1024] = {0};
    int currentChar = 0;
    while (!flag)
    {
      char shiftFlag = 0;
      int scancodeKey = getKey();
      
      char key[2] = {kbd_US[scancodeKey], 0};
      // Unknown key
      if(kbd_US[scancodeKey] == 0);
      else {
        switch (key[0])
        {
        case '\n':
          flag = 1;
          break;
        case 0:
          break;
        default:
          if (key[0] < 126 && key[0] > 0)
          {
            buffer[currentChar++] = key[0];
          }
          
          break;
        }
        print(0x00159854, buffer, 10);
      }
    }
    
    
    // Execute constantly
    while(1);
}