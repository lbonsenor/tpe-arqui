#include "shell.h"
#include "libSysCalls.h"
#include "commands.h"
#include "eliminator.h"
#define BUFFER_SIZE 1024
#define COMMANDS_SIZE 7

static char* commands[] = {"help", "time", "eliminator", "regs", "clear", "scaledown", "scaleup"};

int isCommand(char * str, int command){
      if (command >= COMMANDS_SIZE) return -1;

      int i = 0;
      for (; str[i] != '\0' && commands[command][i] != '\0'; i++)
            if (str[i] != commands[command][i]) return 0;   
      
      return str[i] == commands[command][i];    // Checking if they have the same length 
}

int findCommand(char * str){
      for (int i = 0; i < COMMANDS_SIZE; i++)
            if (isCommand(str, i)) return i;
            
      return -1;
}

void executeCommand(char * str){
      switch (findCommand(str))
      {
      case 0: help(); break;
      case 1: time(); break;
      case 2: eliminator(); break;
      case 3: regs(); break;
      case 4: clearScreen(); break;
      case 5: scaleDown(); break;
      case 6: scaleUp(); break;
      
      default:
            break;
      }
}

void insertCommand(){
      print("kaOS > ");
      char buffer[BUFFER_SIZE] = {'\0'};
      int bufferIndex = 0;
      char c = 0;
      while ((c = getChar()) != '\n' && bufferIndex < BUFFER_SIZE)
      {
            if (c != '\0'){
                  char aux[2] = {c,'\0'};
                  if (c == '\b' && bufferIndex > 0) {
                        buffer[--bufferIndex] = '\0';
                        print(aux);
                  }
                  else if (c != '\b') {
                        buffer[bufferIndex++] = c;
                        print(aux);
                  }
            }
      }
      print("\n\n");
      executeCommand(buffer);
      print("\n");
      insertCommand();
}


void shell(){
      print("Welcome to kaOS! Please input your command\n");
      insertCommand();

}