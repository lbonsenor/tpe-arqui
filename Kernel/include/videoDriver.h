#include <stdint.h>

/* Get width and height functions */
uint16_t getWidthPixels();
uint16_t getHeightPixels();
uint16_t getWidthChars();
uint16_t getHeightChars();

/* Scale functions */
int scaleUp();
int scaleDown();

/* Put functions */
int putPixel(uint32_t hexColor, uint64_t x, uint64_t y);
int putChar(uint32_t hexColor, char c, uint64_t x, uint64_t y);
int putCharCursor(uint32_t hexColor, char c);

/* Print functions */
void print(uint32_t hexColor, char * str);
void println(uint32_t hexColor, char * str);
void printNoColor(char * str);
void newLine();

void clearScreen();

uint32_t getPixelColor(uint64_t x, uint64_t y);

int drawRectangle(uint32_t hexColor, uint64_t x, uint64_t y, int width, int height);
