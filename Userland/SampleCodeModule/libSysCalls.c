#include<stdint.h>

extern uint64_t syscall(uint64_t rax, uint64_t rdi, uint64_t rsi , uint64_t rdx , uint64_t r10, uint64_t r8);

uint64_t readBuffer(char* buffer, uint64_t length) {
    return syscall(0, 0, (uint64_t) buffer, length, 0, 0); 
}

void print(char* buffer) {
    syscall(1, 1, (uint64_t) buffer, 0, 0, 0); 
}

void putChar(char c) {
    char aux[2] = {c, 0};
    syscall(1, 1, (uint64_t) aux, 0, 0, 0);
}

uint64_t getTime() {
    return syscall(2, 0, 0, 0, 0, 0);
} 

void clearLine(uint64_t line) {
    syscall(6, line, 0, 0, 0, 0);
}

void clearScreen() {
    syscall(7, 0, 0, 0, 0, 0);
}

void drawRectangle(uint64_t color, uint64_t posX, uint64_t posY, uint64_t width, uint64_t height) {
    syscall(9, color, posX, posY, width, height);
}

void scaleUp() {
    syscall(10, 0, 0, 0, 0, 0);
}

void scaleDown() {
    syscall(11, 0, 0, 0, 0, 0);
}

void make_sound(int note, int duration, int wait) {
    syscall((uint64_t) 12, (uint64_t) note, (uint64_t) duration, (uint64_t)wait, 0, 0);
}

uint64_t getMaxHeight() {
    return syscall(13, 0, 0, 0, 0, 0);
}

uint64_t getMaxWidth() {
    return syscall(14, 0, 0, 0, 0, 0);
}

uint64_t getPixelColor(uint64_t x, uint64_t y) {
    return syscall(15, x, y, 0, 0, 0);
}

void setCursorToLine(uint64_t line) {
    syscall(17, line, 0, 0, 0, 0);
}

char getRegisters(uint64_t * buffer) {
    return syscall(18, (uint64_t) buffer, 0, 0, 0, 0);
}

char getChar() {
    char c = syscall(19, 0, 0, 0, 0, 0);
    return c;
}

void setCursor(uint64_t posx, uint64_t line) {
    syscall(36, posx, line, 0, 0, 0);
}