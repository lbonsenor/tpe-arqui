#include <stdint.h>

uint64_t syscallHandler(uint64_t rdi, uint64_t rsi , uint64_t rdx , uint64_t r10, uint64_t r8 , uint64_t rax) {
    return 0;
}


/* Lets use the linux syscall codes for read and write
0 - read
1 - write (whole buffer)
2 - time
3 - elapsed millis
4 - new line
5 - read line
6 - clear line
7 - clear screen
8 - put pixel
9 - draw rect
10 - scale up 
11 - scale down 
12 - make sound 
13 - get height pixels
14 - get width pixels
15 - get pixel at

*/ 