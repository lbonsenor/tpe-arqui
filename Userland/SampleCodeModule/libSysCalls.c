#include<stdint.h>
extern uint64_t syscall(uint64_t rax, uint64_t rdi, uint64_t rsi , uint64_t rdx , uint64_t r10, uint64_t r8);

//0 en rax, en realidad deberia ser 3
uint64_t readBuffer(char* buffer, uint64_t length){
    return syscall(0,0,(uint64_t )buffer,length,0,0); 
}
void print(char* buffer){
    syscall(1,1,(uint64_t)buffer,1,0,0); 
}
uint64_t getTime(){
    syscall(2,0,0,0,0,0);
} 
void clearScreen(){
    syscall(7,0,0,0,0,0);
}
void drawRectangle(uint64_t color, uint64_t posX, uint64_t posY, uint64_t width, uint64_t height){
    //agregar validaciones: que el x sea valido, que la y no se pase, etc. 
    syscall(9,color,posX,posY,width,height);
}
void scaleUp(){
    syscall(10,0,0,0,0,0);
}
void scaleDown(){
    syscall(11,0,0,0,0,0);
}
void make_sound(int note, int duration, int wait){
    syscall((uint64_t) 12, (uint64_t) note, (uint64_t) duration, (uint64_t)wait, 0,0);
}
uint64_t getMaxHeight(){
    return syscall(13,0,0,0,0,0);
}
uint64_t getMaxWidth(){
    return syscall(14,0,0,0,0,0);
}
uint64_t getPixelColor(uint64_t x, uint64_t y){
    return syscall(15,x,y,0,0,0);
}
void getRegisters(uint64_t * buffer){
    syscall(18,(uint64_t)buffer,0,0,0,0);
}
char getChar(){
    char c = syscall(19,0,0,0,0,0);
    return c;
}