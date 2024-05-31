#include<stdint.h>
extern uint64_t sysCall(uint64_t rax, uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t , uint64_t);


// deberia usar el strlen en vez del 1 despues del buffer.
// aca en vez de 1 deberia ser 4
uint64_t print(char* buffer){
    return sysCall(1,1,buffer,1,0,0); 
   
}

//0 en rax, en realidad deberia ser 3
uint64_t readBuffer(char* buffer){
    return sysCall(0,0,buffer, 5,0,0); 
}

void clearScreen(){
    return sysCall(7,0,0,0,0,0);
}

void drawRectangle(int posX, int posY){
    
}

void showTime(){
    // readBuffer(sysCall(2,0,0,0,0,0)); no me funciona esto
} 

// case 2:
//             return get_current_time();
//         case 3:
//             return elapsed_millis();
//         case 4:
//             return get_height_ch();
//         case 5:
//             return get_width_ch();
//         case 6:
//             clear_line(rdi);
//             break;
//         case 7:
//             clear_screen();
//             break;
//         case 8:
//             return put_pixel(rdi,rdi,rdx);
//         case 9:
//             return draw_rect(rdi,rsi,rdx,r10,r8);
//         case 10:
//             return scale_up();
//         case 11:
//             return scale_down();
//         case 12:
//             return make_sound(rdi,rsi,rdx);
//         case 13:
//             return get_height_pix();
//         case 14:
//             return get_width_pix();
//         case 15:
//             return get_pix(rdi,rsi);
//         case 16:
//             return get_max_lines();
//             break;
//         case 17: 
//             set_cursor_to_line(rdi);
//             break;
//         case 18:
//             return get_registers(rdi);
//         case 35:
//             wait(rdi);