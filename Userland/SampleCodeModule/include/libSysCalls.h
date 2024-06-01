
#include<stdint.h>

uint64_t readBuffer(char* buffer, uint64_t length);
uint64_t print(char* buffer);
uint64_t getTime();
void clearScreen();
void drawRectangle(uint64_t color, uint64_t posX, uint64_t posY, uint64_t width, uint64_t height);
void scaleUp();
void scaleDown();
void make_sound(int note, int duration, int wait);
uint64_t getMaxHeight();
uint64_t getMaxWidth();
uint64_t getPixelColor(uint64_t x, uint64_t y);
void getRegisters(uint64_t * buffer);
char getChar(); 
