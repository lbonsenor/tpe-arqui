extern int getKey();
#include <keyboardDriver.h>

#define BUFFER_SIZE 1024
static const char kbd_US[256] = {
   /* 0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\\', '+', '\n',
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',
    0, 0, 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 0, 0, 0, 0 */       
        0,  1/*esc*/,  '1',  '2',  '3',  '4',  '5',  '6',   '7',  '8',  '9',   '0',   '\'',  '<', '\b',
    '\t', 'q',  'w',  'e',  'r',  't',  'y',  'u',  'i',   'o',  'p',  '\\',   '+', '\n',   
        0,     'a',  's', 'd',  'f',  'g',  'h',  'j',  'k',  'l',  ';',  '{',
    '|',  5/*shift*/,  '}',  'z',  'x', 'c', 'v',  'b',  'n',  'm',  ',',  '.',  '-',    0,  
    '*',     0,  ' ',    0,     0,     0/*60*/,    0,       0,         0, 
    0,     0,     0,    0,      0,      0,      0,      0,         17/*up*/,
    0,      0,      18/*left*/,    0,     19/*right*/,     0,      0,      20/*down*/,      0,
};

void printKey() {
    char flag = 0;
    char buffer[1024] = {0};
    int currentChar = 0;
    while (!flag)
    {
      int scancodeKey = getKey();
      
      char key = kbd_US[scancodeKey];
      // Unknown key
      if(kbd_US[scancodeKey] == 0);
      else {
        switch (key)
        {
        case '\n':
          flag = 1;
          break;
        case 0:
          break;
        default:
          if (key < 126 && key > 0)
          {
            buffer[currentChar++] = key;
          }
          
          break;
        }
        print(0x00159854, buffer, 10);
      }
    }
    
    
    // Execute constantly
    while(1);
}