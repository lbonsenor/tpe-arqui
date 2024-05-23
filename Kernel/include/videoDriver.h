#include <stdint.h>
void putPixel(uint32_t hexColor, uint64_t x, uint64_t y);
void putCharGlyph(uint32_t hexColor, char c, uint64_t x, uint64_t y);
void print(uint32_t hexColor, char * str, uint64_t line);