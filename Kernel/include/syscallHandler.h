#ifndef _SYSCALLHANDLER_H_
#define _SYSCALLHANDLER_H_

#include <stdint.h>

uint64_t syscallHandler(uint64_t rdi, uint64_t rsi , uint64_t rdx , uint64_t r10, uint64_t r8 , uint64_t rax);

uint64_t read(uint64_t fileDescriptor , uint64_t buffer , uint64_t length);
uint64_t write(uint64_t fileDescriptor, uint64_t buffer , uint64_t length);

uint64_t get_current_time();
uint64_t elapsed_millis();

uint64_t get_height_ch();
uint64_t get_width_ch();

void clear_line(uint64_t line);
void clear_screen();

uint64_t put_pixel(uint64_t color , uint64_t x, uint64_t y);
uint64_t draw_rect(uint64_t hexColor, uint64_t x, uint64_t y, uint64_t width , uint64_t height);

uint64_t scale_up();
uint64_t scale_down();

uint64_t make_sound(uint64_t freq, uint64_t duration , uint64_t wait);

uint64_t get_height_pix();
uint64_t get_width_pix();
uint32_t get_pix(uint64_t x, uint64_t y);
uint64_t get_max_lines();

uint64_t set_cursor_to_line(uint64_t line);

uint64_t get_registers(uint64_t buffer );

uint64_t wait(uint64_t time_in_millis);

#endif