#include <stdint.h>
void putPixel(uint32_t hexColor, uint64_t x, uint64_t y);
void putCharGlyph(uint32_t hexColor, char c, uint64_t x, uint64_t y);
int print(uint32_t hexColor, char * str);
void drawRectangle(uint32_t hexColor, uint64_t x, uint64_t y, int width, int height);
void newLine();