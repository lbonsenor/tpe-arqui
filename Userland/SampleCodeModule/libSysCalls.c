#include<stdint.h>
extern uint64_t sysCall(uint64_t rax, uint64_t rdi, uint64_t rsi , uint64_t rdx , uint64_t r10, uint64_t r8);


// deberia usar el strlen en vez del 1 despues del buffer.
// aca en vez de 1 deberia ser 4
void print(char* buffer){
    sysCall(1,1,(uint64_t)buffer,1,0,0); 
   
}

//0 en rax, en realidad deberia ser 3
uint64_t readBuffer(char* buffer, uint64_t length){
    return sysCall(0,0,(uint64_t)buffer,0,length,0);  //nose que hace read la verdad
}

void clearScreen(){
    sysCall(7,0,0,0,0,0);
}

void drawRectangle(uint64_t color, uint64_t posX, uint64_t posY, uint64_t width, uint64_t height){
    //agregar validaciones: que el x sea valido, que la y no se pase, etc. 
    sysCall(9,color,posX,posY,width,height);
}

void showTime(){
    // readBuffer(sysCall(2,0,0,0,0,0)); no me funciona esto
} 

void scaleUp(){
    sysCall(10,0,0,0,0,0);
}

void scaleDown(){
    sysCall(11,0,0,0,0,0);
}

//void put_pixel(uint64_t ){
    
//}

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
//         case 8:
//             return put_pixel(rdi,rdi,rdx);
//         case 9:
//             return draw_rect(rdi,rsi,rdx,r10,r8);
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