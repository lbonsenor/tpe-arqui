#include <stdint.h>
#include <lib.h>
#include <videoDriver.h>
#include <time.h>
#include <exceptions.h>

#define ZERO_EXCEPTION_CODE 0
#define WRONG_OPCODE_EXC_CODE 6

static void zero_division();
static void wrong_opcode();
//RIP RAX RBX RCX RDX RSI RDI RBP RSP R8 R9 R10 R11 R12 R13 R14 R15 

static const char * registerOrder[17] = {"RIP", "RAX", "RBX", "RCX", 
"RDX","RSI", "RDI","RBP","RSP","R8","R9","R10","R11", "R12", "R13", "R14", "R15"
};
static const char * errorMessage = "Program failed due to unhandled exception:\n";
static const char * waiting = "Restarting...";

void exceptionDispatcher(int exception, uint64_t registers[17]) {
	//rdi, rsi params
	wait(18*3);
	clearScreen();
	// scaleUp();
	print(errorMessage);
	//print("\n");
	char buffer[10];
	intToStr(exception,buffer,10);
	print("Code: ");
	print(buffer);
	print("\n");
	if (exception == ZERO_EXCEPTION_CODE){
		zero_division();
	}
	else if(exception == WRONG_OPCODE_EXC_CODE){
		wrong_opcode();
	}
	else{
		print("Unknown");
		print("\n");
	}
	for(int i = 0; i< 17; i++){
		print(registerOrder[i]);
		print(": ");
		intToStr(registers[i], buffer, 10);
		print(buffer);
		print(", ");
	}
	timer_wait(18*5); // wait so one can see the registers
	print("\n");
	print(waiting);
	timer_wait(18*2);
	scaleDown();
	clearScreen();
	setCursorLine(0);
	resetMain();
}

static void zero_division() {
	// Handler para manejar excepción.
	print("Zero division");
	print("\n");
}
static void wrong_opcode(){
	print("Wrong opcode");
	print("\n");
}