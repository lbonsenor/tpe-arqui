#include <stdint.h>
uint16_t getWidthPixels();
uint16_t getHeightPixels();
uint16_t getWidthChars();
uint16_t getHeightChars();
int scaleUp();
int scaleDown();
int putPixel(uint32_t hexColor, uint64_t x, uint64_t y);
int putChar(uint32_t hexColor, char c, uint64_t x, uint64_t y);
void clearScreen();
void print(uint32_t hexColor, char * str);
int drawRectangle(uint32_t hexColor, uint64_t x, uint64_t y, int width, int height);
void newLine();
uint32_t getPixelColor(uint64_t x, uint64_t y);