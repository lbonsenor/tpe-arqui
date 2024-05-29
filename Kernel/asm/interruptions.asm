GLOBAL _cli
GLOBAL _sti
GLOBAL _hlt
GLOBAL _wait

GLOBAL int_timer
GLOBAL int_keyboard
GLOBAL int_exc_divide_by_zero
GLOBAL int_exc_invalid_opcode
GLOBAL int_syscall

GLOBAL picMasterMask
GLOBAL picSlaveMask

GLOBAL show_registers_dump
GLOBAL has_regs

EXTERN exceptionDispatcher
EXTERN syscallHandler
EXTERN intDispatcher
EXTERN printBuffer

;here go the diferent interruptions
;the dispatchers will execute the response based on the interrupt

;first we define macros we'll be using often
section .text

;will need these for idt loading (no interruptions during load)
_cli:
	cli
	ret

_sti:
	sti
	ret

_hlt:
	sti
	hlt
	ret

_wait:
        hlt
        ret

%macro pushRegisters 0
                    push rax
                    push rbx
                    push rcx
                    push rdx  
                    push rbp

                    push rsi
                    push rdi

                    push r8
                    push r9
                    push r10
                    push r11
                    push r12
                    push r13
                    push r14
                    push r15
%endmacro

%macro popRegisters 0
                    pop r15
                    pop r14
                    pop r13
                    pop r12
                    pop r11
                    pop r10
                    pop r9
                    pop r8

                    pop rdi
                    pop rsi

                    pop rbp
                    pop rdx
                    pop rcx
                    pop rbx
                    pop rax
%endmacro

;each exception has a code -> we pass the code to the handler aas param...

%macro  exceptionHandler 1
;save registers in data 
;order: RIP RAX RBX RCX RDX RSI RDI RBP RSP R8 R9 R10 R11 R12 R13 R14 R15 
    
    mov [show_registers + (1*8)] , rax
    mov rax, [rsp]
    mov [show_registers], rax ;rip
    mov [show_registers + (2*8)], rbx
    mov [show_registers + (3*8)], rcx
    mov [show_registers + (4*8)], rdx
    mov [show_registers + (5*8)], rsi 
    mov [show_registers + (6*8)], rdi
    mov [show_registers + (7*8)], rbp

    ;rsp from stack (flags, CS and RIP where pushed when int occurs)
    mov rax, [rsp + 3*8]
    mov [show_registers + (8*8)], rax
    
    mov [show_registers + (9*8)], r8
    mov [show_registers + (10*8)], r9
    mov [show_registers + (11*8)], r10
    mov [show_registers + (12*8)], r11
    mov [show_registers + (13*8)], r12
    mov [show_registers + (14*8)], r13
    mov [show_registers + (15*8)], r14
    mov [show_registers + (16*8)], r15

    ;load parameters to pass to exceptions handler
    mov rdi, %1 
    mov rsi, show_registers ; "pointer to string"
    call exceptionDispatcher

    iretq
%endmacro

;added macro to add a dispatcher (for keyboard and etc)
%macro intHandlerMaster 1
        pushRegisters

        mov rdi, %1 ; macro parameter                                           ; Esto antes era un $
        call intDispatcher 

        ;signal EOI
        mov al, 20h
        out 20h, al

        popRegisters
        iretq ; return from interruption
%endmacro

;function to sav registers in keyboard interruption
; order same as before (exc) but rax at the end
saveRegs:
        mov [show_registers_dump + (1*8)], rbx 
        mov [show_registers_dump + (2*8)], rcx
        mov [show_registers_dump + (3*8)],rdx 
        mov [show_registers_dump + (4*8)], rsi 
        mov [show_registers_dump + (5*8)],rdi
        mov [show_registers_dump + (6*8)],rbp 
        mov [show_registers_dump + (8*8)],r8
        mov [show_registers_dump + (9*8)],r9
        mov [show_registers_dump + (10*8)],r10
        mov [show_registers_dump + (11*8)],r11
        mov [show_registers_dump + (12*8)], r12
        mov [show_registers_dump + (13*8)],r13
        mov [show_registers_dump + (14*8)],r14
        mov [show_registers_dump + (15*8)], r15 

        ;RSP && RIP && RAX
        mov rax , [rsp + 18*8] 
        mov [show_registers_dump + (7*8)], rax
        mov rax, [rsp + 15*8]
        mov [show_registers_dump + (16*8)], rax
        mov rax , [rsp + 14*8]
        mov [show_registers_dump], rax

        ; EOI
        mov al, 20h
        out 20h, al

        popRegisters
        iretq

int_timer:
        intHandlerMaster 0 ; 00 code for the timer tick

int_keyboard:
        call printBuffer
        pushRegisters
        
        in al, 0x60 ; readKey
        cmp al, 0x1D ; check if left CTRL is pressed (used to save registers)
        je saveRegs

        mov rdi, 1 ; param for dispatcher
        call intDispatcher
        
        ;EOI
        mov al, 20h
        out 20h, al

        popRegisters
        iretq

; now the routines for each exception..
int_exc_divide_by_zero: 
        exceptionHandler 00h

int_exc_invalid_opcode:
        exceptionHandler 06h 

int_syscall:
; syscalls params:	RDI	RSI	RDX	R10	R8	R9
; syscallHandler:	RDI RSI RDX R10 R8  RAX
; params in C are:	RDI RSI RDX RCX R8  R9
        pushRegisters

        mov rcx, r10
	mov r9, rax
        call syscallHandler

        popRegisters
	iretq

;for protected mode
picMasterMask:
        push rbp
        mov rbp, rsp
        mov ax, di
        out 21h, al
        pop rbp
        retn    

picSlaveMask:
	push rbp
        mov rbp, rsp
        mov ax, di
        out 0A1h, al
        pop rbp
        retn

section .bss
        show_registers resq 17 ; reserve a qword for each register 
        has_regs resb 1; to check whether we have saved or not!
        show_registers_dump resq 17 ;aditionally for dumping (isnt passed as a param but is accessed directly)