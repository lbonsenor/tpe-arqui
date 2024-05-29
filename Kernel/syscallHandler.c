#include <stdint.h>
#include <videoDriver.h>
#include <keyboardDriver.h>
#include <time.h>
#include <sound.h>
#include <interrupts.h>

#include <syscallHandler.h>

#define STDIN 0
#define STDOUT 0
#define STDERR 2
#define KBDIN 3

//from interruptions we get the register array to read it
extern const uint64_t show_registers_dump[17];
extern const uint64_t has_regs;

// syscalls params:	RDI	RSI	RDX	R10	R8	R9
// syscallHandler:	RDI RSI RDX R10 R8  RAX
// params in C are:	RDI RSI RDX RCX R8  R9

uint64_t syscallHandler(uint64_t rdi, uint64_t rsi , uint64_t rdx , uint64_t r10, uint64_t r8 , uint64_t rax) {
    switch (rax){
        case 0:
            return read(rdi, rsi , rdx);
        case 1:
            return write(rdi,rsi,rdx);
        case 2:
            return time();
        case 3:
            return elapsed_millis();
        case 4:
            return get_height_ch();
        case 5:
            return get_width_ch();
        case 6:
            clear_line(rdi);
            break;
        case 7:
            clear_screen();
            break;
        case 8:
            return put_pixel(rdi,rdi,rdx);
        case 9:
            return draw_rect(rdi,rsi,rdx,r10,r8);
        case 10:
            return scale_up();
        case 11:
            return scale_down();
        case 12:
            return make_sound(rdi,rsi,rdx);
        case 13:
            return get_height_pix();
        case 14:
            return get_width_pix();
        case 15:
            return get_pix(rdi,rsi);
        case 16:
            return get_max_lines();
            break;
        case 17: 
            set_cursor_to_line(rdi);
            break;
        case 18:
            return save_registers(rdi);
        case 35:
            wait(rdi);
            break;
        default:
            return 1;
    }
    return 0;

}


/* Lets use the linux syscall codes for read and write
0 - read (whole buffer)
1 - write (whole buffer) ¿? esto estará bien ?
2 - time
3 - elapsed millis
4 - get height char
5 - get width char
6 - clear line
7 - clear screen
8 - put pixel
9 - draw rect
10 - scale up 
11 - scale down 
12 - make sound 
13 - get height pixels
14 - get width pixels
15 - get pixel at 
16 - get max lines
17 - set cursor line
18 - get registers
35 - wait (copying linux system call nanosleep)
*/ 


static uint64_t read(uint64_t fileDescriptor , uint64_t buffer , uint64_t length){
    //then turn this into
    if (fileDescriptor != STDIN ){
        return 0;
    }
    char * bufferPosition = (char *) buffer;
    int i =0;
    char readCharacter;
    while (i< length && (readCharacter= getFromBuffer) != 0 ){
            bufferPosition[i] = readCharacter;
            i++;
    }
    return i;
} 
// i s
static uint64_t write(uint64_t fileDescriptor, uint64_t buffer , uint64_t length){
    if(fileDescriptor != STDOUT){
        return 1;
    }
    else {
        print(buffer);
        return 0;
    }
}

static uint64_t time(){
    return getTime();
}

static uint64_t elapsed_millis(){
    return millisElapsed();
}

static uint64_t get_height_ch(){
    return getHeightChars();
}

static uint64_t get_width_ch(){
    return getWidthChars();
}

static void clear_line(uint64_t line){
    int startY = lineToHeight(line); 
    for(int i = 0; i< getWidthPixels(); i++){
        int heightCounter=0;
        while(heightCounter < 16 ){
            putPixel(0x000000, i , heightCounter+startY);
        }
    }
}

static void clear_screen(){
    clearScreen();
}

static uint64_t put_pixel(uint64_t color , uint64_t x, uint64_t y){
    return putPixel((uint32_t) color,  (uint64_t) x , (uint64_t) y);
}

static uint64_t draw_rect(uint64_t hexColor, uint64_t x, uint64_t y, uint64_t width , uint64_t height){
    return drawRectangle((uint64_t) hexColor, (uint64_t) x, (uint64_t) y, (int) width, (int) height);
}

static uint64_t scale_up(){
    return scaleUp();
}

static uint64_t scale_down(){
    return scaleDown();
}

static uint64_t make_sound(uint64_t freq, uint64_t duration , uint64_t wait){
    playNoteSound((uint64_t) freq, (uint64_t) duration, (uint64_t) wait);
    return 1;
}

static uint64_t get_height_pix(){
    return (uint64_t)getHeightPixels();
}

static uint64_t get_width_pix(){
    return (uint64_t)getWidthPixels();
}

static uint32_t get_pix(uint64_t x, uint64_t y){
    return getPixelColor((uint64_t) x, (uint64_t) y);
}

static uint64_t get_max_lines(){
    getHeightChars();
    return 1;
}
static uint64_t set_cursor_to_line(uint64_t line){
    if(line >= get_max_lines()){
        return 1;
    }
    setCursor(0, heightToLine(line));
    return 0;
}
static uint64_t save_registers(uint64_t buffer ){
    if(has_regs){
        for(int i = 0; i<17 ; i++){
            ((uint64_t * ) buffer)[i] = show_registers_dump[i];
        }
    }
    return 1;
}

static uint64_t wait(uint64_t time_in_millis){
    uint64_t time = millisElapsed();
    do{ _hlt(); }
    while(millisElapsed()- time > time_in_millis);
    return 0;
}