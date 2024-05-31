
#include<stdint.h>

uint64_t print(char* buffer);
uint64_t readBuffer(char* buffer, uint64_t length);
void clearScreen();
void showTime();
void drawRectangle(uint64_t color, uint64_t posX, uint64_t posY, uint64_t width, uint64_t height);
void scaleUp();
void scaleDown();
char getChar();
uint64_t getPixelColor(uint64_t x, uint64_t y);
uint64_t getMaxWidth();
uint64_t getMaxHeight();