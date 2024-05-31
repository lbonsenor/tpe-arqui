#include "libSysCalls.h"
#define BUFFER_SIZE 1024
#define COMMANDS_SIZE 8

char buffer[BUFFER_SIZE];
static char* commands[] = {"help", "time", "eliminator", "eliminator2", "regs", "clear", "scaledown", "scaleup"};

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

}

void shell(){
      print("Welcome to kaOS! Please input your command\n");
      print("kaOS >");
      
      int i;
      while(i<3000){
            i++;
            print("hi");
      }
      readBuffer(buffer, 30);
      make_sound(393,10,0);
      drawRectangle(0xFF0000,100,100,300,100);
      print(buffer);

}