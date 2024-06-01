#include <stdint.h>

/* Get width and height functions */
uint16_t getWidthPixels();
uint16_t getHeightPixels();
uint16_t getWidthChars();
uint16_t getHeightChars();

/* Scale functions */
int scaleUp();
int scaleDown();
uint8_t getScale();

/* Put functions */
int putPixel(uint32_t hexColor, uint64_t x, uint64_t y);
int putChar(char c, uint64_t x, uint64_t y);
int putCharCursor(char c);

/* Print functions */
void print(char * str);
void printlnchar(char * str);
void newLine();

void clearScreen();

int setCursorLine(unsigned int line);
void setCursor(uint16_t x, uint16_t y);

void setColor(uint32_t newColor);

uint32_t getPixelColor(uint64_t x, uint64_t y);

int drawRectangle(uint32_t hexColor, uint64_t x, uint64_t y, int width, int height);

uint16_t lineToHeight(unsigned int line);
int heightToLine(uint16_t height);