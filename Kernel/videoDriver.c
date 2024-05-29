#include <videoDriver.h>
#include <font.h>
#include <lib.h>

struct vbe_mode_info_structure {
	uint16_t attributes;		// deprecated, only bit 7 should be of interest to you, and it indicates the mode supports a linear frame buffer.
	uint8_t window_a;			// deprecated
	uint8_t window_b;			// deprecated
	uint16_t granularity;		// deprecated; used while calculating bank numbers
	uint16_t window_size;
	uint16_t segment_a;
	uint16_t segment_b;
	uint32_t win_func_ptr;		// deprecated; used to switch banks from protected mode without returning to real mode
	uint16_t pitch;				// number of bytes per horizontal line
	uint16_t width;				// width in pixels
	uint16_t height;			// height in pixels
	uint8_t w_char;				// unused...
	uint8_t y_char;				// ...
	uint8_t planes;
	uint8_t bpp;				// bits per pixel in this mode
	uint8_t banks;				// deprecated; total number of banks in this mode
	uint8_t memory_model;
	uint8_t bank_size;			// deprecated; size of a bank, almost always 64 KB but may be 16 KB...
	uint8_t image_pages;
	uint8_t reserved0;
 
	uint8_t red_mask;
	uint8_t red_position;
	uint8_t green_mask;
	uint8_t green_position;
	uint8_t blue_mask;
	uint8_t blue_position;
	uint8_t reserved_mask;
	uint8_t reserved_position;
	uint8_t direct_color_attributes;
 
	uint32_t framebuffer;				// physical address of the linear frame buffer; write here to draw to the screen
	uint32_t off_screen_mem_off;
	uint16_t off_screen_mem_size;		// size of memory in the framebuffer but not being displayed on the screen
	uint8_t reserved1[206];
} __attribute__ ((packed));

typedef struct vbe_mode_info_structure * VBEInfoPtr;

VBEInfoPtr VBE_mode_info = (VBEInfoPtr) 0x0000000000005C00;

#define MAX_LINES (VBE_mode_info->height / (CHAR_HEIGHT * scale))
#define MAX_CHARS (VBE_mode_info->width / (CHAR_WIDTH * scale))

uint8_t scale = 1;

// Cursor coordinates
uint16_t cursorX = 0;
uint16_t cursorY = 0;

uint16_t getWidthPixels() {
	return VBE_mode_info->width;
}

uint16_t getHeightPixels() {
	return VBE_mode_info->height;
}

uint16_t getWidthChars() {
	return getWidthPixels() / (CHAR_WIDTH * scale);
}

uint16_t getHeightChars() {
	return getHeightPixels() / (CHAR_HEIGHT * scale);
}

// Returns 0 if successful
int setScale(uint8_t newScale) {
	if (newScale > 4 || newScale < 1) return 1;
	scale = newScale;
	return 0;
}

int scaleUp() {
	return setScale(scale + 1);
}

int scaleDown() {
	return setScale(scale - 1);
}

int putPixel(uint32_t hexColor, uint64_t x, uint64_t y) {
	if (x >= getWidthPixels() || y >= getHeightPixels()) return 1;
	// Caso de error: x o y superan el límite (andcho o alto)
    uint8_t * framebuffer = (uint8_t *) VBE_mode_info->framebuffer;
    uint64_t offset = (x * ((VBE_mode_info->bpp) / 8)) + (y * VBE_mode_info->pitch);
    framebuffer[offset]     =  (hexColor) & 0xFF;
    framebuffer[offset+1]   =  (hexColor >> 8) & 0xFF; 
    framebuffer[offset+2]   =  (hexColor >> 16) & 0xFF;
	return 0;
}

int drawRectangle(uint32_t hexColor, uint64_t x, uint64_t y, int width, int height) {
	if (x + width > getWidthPixels() || y + height > getHeightPixels()) return 1;
	for (int i = x; i < x + width; i++)
	for (int j = y; j < y + height; j++)
		putPixel(hexColor, i, j);
	return 0;
}

int putChar(uint32_t hexColor, char c, uint64_t x, uint64_t y) {
	if (c < FIRST_CHAR || c > LAST_CHAR) return 1;
	const uint8_t * charGlyph = IBM_VGA_8x16_glyph_bitmap + 16 * (c - FIRST_CHAR);
	for (int i = 0; i < CHAR_HEIGHT; i++) {
		for (int j = 0; j < CHAR_WIDTH; j++) {
			uint32_t color = charGlyph[i] & (1 << (CHAR_WIDTH - 1 - j)) ? hexColor : 0x000000;
			for (int scaleX = 0; scaleX < scale; scaleX++) {
				for (int scaleY = 0; scaleY < scale; scaleY++) {
					putPixel(color, cursorX + j * scale + scaleX, cursorY + i * scale + scaleY);
				}
			}
		}
	}
	return 0;
}

void clearScreen() {
	for (int i = 0; i < getWidthPixels(); i++)
	for (int j = 0; j < getHeightPixels(); j++)
		putPixel(0x00000000, i, j);
	cursorX = 0;
	cursorY = 0;
}

uint32_t getPixelColor(uint64_t x, uint64_t y) {
	uint8_t *framebuffer = (uint8_t *) VBE_mode_info->framebuffer;
    uint64_t offset = (x * (VBE_mode_info->bpp / 8)) + (y * VBE_mode_info->pitch);
    uint32_t hexColor = 0;
    hexColor |= framebuffer[offset];          	// Blue
    hexColor |= framebuffer[offset + 1] << 8; 	// Green
    hexColor |= framebuffer[offset + 2] << 16;	// Red
	return hexColor;
}

// Sets the cursor position
void setCursor(uint16_t x, uint16_t y) {
	uint16_t maxX = getWidthPixels() - CHAR_WIDTH * scale;
	uint16_t maxY = getHeightPixels() - CHAR_HEIGHT * scale; 
	if (x < maxX) cursorX = x;
	else cursorX = maxX;
	if (y < maxY) cursorY = y;
	else cursorY = maxY;
}

int putCharCursor(uint32_t hexColor, char c) {
	if (c == '\n') {
		newLine();
		return 0;
	}
	if (c == '\b') {
		if (cursorX >= CHAR_WIDTH * scale) {
			cursorX -= CHAR_WIDTH * scale;
			putCharCursor(0x000000, ' ');
			cursorX -= CHAR_WIDTH * scale;
			return 0;
		}
		return 1;
	}
	// Not a valid character
	if (c < FIRST_CHAR || c > LAST_CHAR) return 1;
	const uint8_t * charGlyph = IBM_VGA_8x16_glyph_bitmap + 16 * (c - FIRST_CHAR);
	for (int i = 0; i < CHAR_HEIGHT; i++) {
		for (int j = 0; j < CHAR_WIDTH; j++) {
			uint32_t color = charGlyph[i] & (1 << (CHAR_WIDTH - 1 - j)) ? hexColor : 0x000000;
			for (int scaleX = 0; scaleX < scale; scaleX++) {
				for (int scaleY = 0; scaleY < scale; scaleY++) {
					putPixel(color, cursorX + j * scale + scaleX, cursorY + i * scale + scaleY);
				}
			}
		}
	}
	cursorX += CHAR_WIDTH * scale;
	if (cursorX >= getWidthPixels() - CHAR_WIDTH * scale) newLine();
	return 0;
}

void print(uint32_t hexColor, char * str) {
	for (; *str != '\0'; *str++) putCharCursor(hexColor, *str);
}

void printNoColor(char * str) {
	for (; *str != '\0'; *str++) putCharCursor(0x00159854, *str);
}

void println(uint32_t hexColor, char * str) {
	print(hexColor, str);
	newLine();
}

void newLine() {
	cursorX = 0;
	if (cursorY + 2 * CHAR_HEIGHT * scale <= getHeightPixels()) cursorY += CHAR_HEIGHT * scale;
	else {
		// Pointer to framebuffer
        void * dst = (void*) ((uint64_t) VBE_mode_info->framebuffer);
		// Pointer to framebuffer + offset (one line down)
        void * src = (void*) (dst + 3 * (CHAR_HEIGHT * scale * (uint64_t) getWidthPixels()));
        // Number of bytes to copy (multiplied by 3 because of RGB). Copies all but the first line
		uint64_t len = 3 * ((uint64_t) getWidthPixels() * (getHeightPixels() - CHAR_HEIGHT * scale));
        // Copies len bytes of data from src to dst
		memcpy(dst, src, len);
		// Sets the rest to zero
        memset(dst + len, 0, 3 * (uint64_t) getWidthPixels() * CHAR_HEIGHT * scale);
    }
}
