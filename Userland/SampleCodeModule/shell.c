#include "shell.h"
#include "libSysCalls.h"
#include "commands.h"
#include "eliminator.h"
#include "music.h"
#define BUFFER_SIZE 1024
#define COMMANDS_SIZE 9

static char* commands[] = {"help", "time", "eliminator", "regs", "clear", "scaledown", "scaleup", "divzero", "invalidopcode"};

int isCommand(char * str, int command) {
      if (command >= COMMANDS_SIZE) return -1;

      int i = 0;
      for (; str[i] != '\0' && commands[command][i] != '\0'; i++)
            if (str[i] != commands[command][i]) return 0;   
      
      return str[i] == commands[command][i];    // Checking if they have the same length 
}

int findCommand(char * str) {
      for (int i = 0; i < COMMANDS_SIZE; i++)
            if (isCommand(str, i)) return i;
      return -1;
}

void executeCommand(char * str) {
      switch (findCommand(str)) {
      case 0: help(); break;
      case 1: time(); break;
      case 2: eliminator(); break;
      case 3: regs(); break;
      case 4: clearScreen(); break;
      case 5: 
            scaleDown();
            clearScreen(); 
            break;
      case 6: 
            scaleUp(); 
            clearScreen();
            break;
      case 7: divzero(); break;
      case 8: invalidOpCode(); break;
      
      default: print("Unrecognized command\n");
               errorSound();
            break;
      }
}

void insertCommand() {
      print("caOS>");
      char buffer[BUFFER_SIZE] = {'\0'};
      int bufferIndex = 0;
      char c = 0;
      while ((c = getChar()) != '\n' && bufferIndex < BUFFER_SIZE) {
            if (c != '\0') {
                  if (c == '\b' && bufferIndex > 0) {
                        buffer[--bufferIndex] = '\0';
                        putChar(c);
                  }
                  else if (c != '\b') {
                        buffer[bufferIndex++] = c;
                        putChar(c);
                  }
            }
      }
      print("\n");
      executeCommand(buffer);
      insertCommand();
}

void shell() {
      print("Welcome to caOS! Please input your command\n");
      print("Please choose from the following:\n");
      print("\n* time: Displays the current time");
      print("\n* eliminator: Play Eliminator against yourself or a friend. Use WASD to move Player 1, IJKL to move Player 2");
      print("\n* regs: Display the last saved value of registers, press CTRL to save");
      print("\n* clear: Clean the screen");
      print("\n* scaledown: Reduce the text size (min: 1, default: 1)");
      print("\n* scaleup: Increment the text size (max: 4, default: 1)");
      print("\n* divzero: Divide by 0 to trigger a zero division exception");
      print("\n* invalidopcode: Make an invalid opcode to trigger an invalid opcode exception");
      print("\n");
      insertCommand();
}

