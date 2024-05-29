#include <stdint.h>
#include <videoDriver.h>
#include <keyboardDriver.h>
#include <time.h>

#define STDIN 0
#define STDOUT 0
#define STDERR 2
#define KBDIN 3

//from interruptions we get the register array to read it
extern const uint64_t show_registers_dump[17];

uint64_t syscallHandler(uint64_t rdi, uint64_t rsi , uint64_t rdx , uint64_t r10, uint64_t r8 , uint64_t rax) {
    return 0;
}


/* Lets use the linux syscall codes for read and write
0 - read (whole buffer)
1 - write (whole buffer) ¿? esto estará bien ?
2 - time
3 - elapsed millis
4 - read line
5 - clear line
6 - clear screen
7 - put pixel
8 - draw rect
9 - scale up 
10 - scale down 
11 - make sound 
12 - get height pixels
13 - get width pixels
14 - get pixel at 
15 - get max lines
16 - set cursor line
*/ 


static uint64_t read(uint64_t fileDescriptor , uint64_t buffer , uint64_t length){
    //then turn this into
    if (fileDescriptor != STDIN ){
        return 0;
    }
    char * bufferPosition = (char *) buffer;
    int i =0;
    char readCharacter;
    while (i< length && (readCharacter= getFromBuffer) != 0 ){
            bufferPosition[i] = readCharacter;
            i++;
    }
    return i;
} 
// i s
static uint64_t write(uint64_t fileDescriptor, uint64_t buffer , uint64_t length){
    if(fileDescriptor != STDOUT){
        return 1;
    }
    else {
        print(buffer);
        return 0;
    }
}
static uint64_t time (){
    return getTime();
}

static uint64_t elapsed_millis(){
    return millisElapsed();
}
static uint64_t read_line(uint64_t destination , uint64_t line){
    
}

