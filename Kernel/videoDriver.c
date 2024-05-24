#include <videoDriver.h>
#include <font.h>
struct vbe_mode_info_structure {
	uint16_t attributes;		// deprecated, only bit 7 should be of interest to you, and it indicates the mode supports a linear frame buffer.
	uint8_t window_a;			// deprecated
	uint8_t window_b;			// deprecated
	uint16_t granularity;		// deprecated; used while calculating bank numbers
	uint16_t window_size;
	uint16_t segment_a;
	uint16_t segment_b;
	uint32_t win_func_ptr;		// deprecated; used to switch banks from protected mode without returning to real mode
	uint16_t pitch;			// number of bytes per horizontal line
	uint16_t width;			// width in pixels
	uint16_t height;			// height in pixels
	uint8_t w_char;			// unused...
	uint8_t y_char;			// ...
	uint8_t planes;
	uint8_t bpp;			// bits per pixel in this mode
	uint8_t banks;			// deprecated; total number of banks in this mode
	uint8_t memory_model;
	uint8_t bank_size;		// deprecated; size of a bank, almost always 64 KB but may be 16 KB...
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
 
	uint32_t framebuffer;		// physical address of the linear frame buffer; write here to draw to the screen
	uint32_t off_screen_mem_off;
	uint16_t off_screen_mem_size;	// size of memory in the framebuffer but not being displayed on the screen
	uint8_t reserved1[206];
} __attribute__ ((packed));

typedef struct vbe_mode_info_structure * VBEInfoPtr;

VBEInfoPtr VBE_mode_info = (VBEInfoPtr) 0x0000000000005C00;

#define MAX_LINES (VBE_mode_info->height / (CHAR_HEIGHT*zoom))
#define MAX_CHARS (VBE_mode_info->width / (CHAR_WIDTH*zoom))

uint8_t zoom = 1;

void setZoom(uint8_t newZoom){
	if (newZoom > 4 || newZoom < 1) return;
	zoom = newZoom;
}

void putPixel(uint32_t hexColor, uint64_t x, uint64_t y) {
    uint8_t * framebuffer = (uint8_t *) VBE_mode_info->framebuffer;
    uint64_t offset = (x * ((VBE_mode_info->bpp)/8)) + (y * VBE_mode_info->pitch);
    framebuffer[offset]     =  (hexColor) & 0xFF;
    framebuffer[offset+1]   =  (hexColor >> 8) & 0xFF; 
    framebuffer[offset+2]   =  (hexColor >> 16) & 0xFF;
}

void drawRectangle(uint32_t hexColor, uint64_t x, uint64_t y, int width, int height){
	if (x+width > VBE_mode_info->width || y+height > VBE_mode_info->height || x < 0 || y < 0 || width < 0 || height < 0) return;
	for (int i = x; i < x+width; i++)
	for (int j = y; j < y+height; j++)
		putPixel(hexColor, i, j);
}

void putCharGlyph(uint32_t hexColor, char c, uint64_t x, uint64_t y){
	if (c < FIRST_CHAR || c > LAST_CHAR) return;
	const uint8_t * charGlyph = IBM_VGA_8x16_glyph_bitmap + 16 * (c - FIRST_CHAR);

	for (int i = 0; i < 16; i++)
	for (int j = 0; j < 8; j++)
		if (charGlyph[i] & 1<<j)
			for (int zoomx = 0; zoomx < zoom; zoomx++)
			for (int zoomy = 0; zoomy < zoom; zoomy++)
				putPixel(hexColor, x+(7-j)*zoom+zoomx, (y+i)*zoom+zoomy);
				
				
}

void clearScreen(){
	for (int i = 0; i < VBE_mode_info->width; i++)
	for (int j = 0; j < VBE_mode_info->height; j++)
		putPixel(0x00000000, i, j);
}

void print(uint32_t hexColor, char * str, uint64_t line){
	if (line > MAX_LINES || line < 0) return;
	for (int i = 0; str[i] != '\0'; i++) {
		if(i < MAX_CHARS) putCharGlyph(hexColor, str[i], i*8*zoom, line*16);
		else {
			print(hexColor, str + i, ++line);
			return;
		}
	}
}