#include <stdint.h>
#include <interruptions.h>
#include <videoDriver.h>

//flags for segment access
#define ACS_PRESENT     0x80            /* sgm present in memory */
#define ACS_CSEG        0x18            /* code segment */
#define ACS_DSEG        0x10            /* data segment */
#define ACS_READ        0x02            /* read segment */
#define ACS_WRITE       0x02            /* write segment */
#define ACS_IDT         ACS_DSEG
#define ACS_INT_386 	0x0E            /* Interrupt GATE in 32 bits */
#define ACS_INT         (ACS_PRESENT | ACS_INT_386)

#define ACS_CODE        (ACS_PRESENT | ACS_CSEG | ACS_READ)
#define ACS_DATA        (ACS_PRESENT | ACS_DSEG | ACS_WRITE)
#define ACS_STACK       (ACS_PRESENT | ACS_DSEG | ACS_WRITE)

#define STDIN 0
#define STDOUT 1
#define STDERR 2
#define KBDIN 3

// explicación de esto: pragma son instrucciones al procesador 
// pack indica instrucciones de alineación 
// esto sirve para que guarde la estructura todo junto
#pragma pack(push) // push de la alineación actual 
#pragma pack (1)   // indicar que la alineacion sea a un byte -> buscar mejor qué es

// Descriptor data structure
typedef struct {
    uint16_t offset_l;
    uint16_t selector;
    uint8_t  cero;
    uint8_t  access;
    uint16_t offset_m;
    uint32_t offset_h;
    uint32_t other_cero;
} DESCR_INT;

#pragma pack(pop) // retornar a la alineación anterior

//my idt has 256 entries 
DESCR_INT * IDT = (DESCR_INT *) 0;  

// to setup an idt entry : 
static void setup_IDT_entry (int index, uint64_t offset) {
	IDT[index].offset_l = offset & 0xFFFF;
	IDT[index].selector = 0x08;
	IDT[index].cero = 0;
	IDT[index].access = ACS_INT;
	IDT[index].offset_m = (offset >> 16) & 0xFFFF;
	IDT[index].offset_h = (offset >> 32) & 0xFFFFFFFF;
	IDT[index].other_cero = (uint64_t) 0;
}

// functions from interruptions.asm
extern void int_timer();
extern void int_keyboard();
extern void int_exc_divide_by_zero();
extern void int_exc_invalid_opcode();
extern void int_syscall();


void load_IDT(void) {
    println(0x00159854, "idtLoader Start");
    _cli();
    //each code is based on the linux system -> remember to add this to manual bibliography
    //for exceptions..
    setup_IDT_entry(0x00, (uint64_t)&int_exc_divide_by_zero);
    setup_IDT_entry(0x06, (uint64_t)&int_exc_invalid_opcode);
    //keyboard and timer
    setup_IDT_entry(0x20, (uint64_t)&int_timer);
    setup_IDT_entry(0x21, (uint64_t)&int_keyboard); 
    // syscalls 
    setup_IDT_entry(0x80, (uint64_t)&int_syscall);
    // we need to enable the interruptions... (protected mode)
    //0xFE is only for timertick
    picMasterMask(0xFC);
    picSlaveMask(0xFF);
    _sti();
    println(0x00159854, "idtLoader End");
}