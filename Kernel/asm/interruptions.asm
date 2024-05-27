GLOBAL _cli
GLOBAL _sti
GLOBAL _hlt
GLOBAL int_keyboard
GLOBAL int_exc_divide_by_zero
GLOBAL int_exc_invalid_opcode
GLOBAL int_syscall
GLOBAL int_timer

GLOBAL picMasterMask
GLOBAL picSlaveMask

GLOBAL show_registers_dump
GLOBAL has_regs

EXTERN exceptionDispatcher
EXTERN syscallHandler
EXTERN timerHandler
EXTERN keyboardHandler

;here go the diferent interruptions
;the handlers will execute the response based on the interrupt


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

%macro pushRegisters 0
                    push rax
                    push rbx
                    push rcx
                    push rdx

                    push rsi
                    push rdi

                    push rbp

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

                    pop rbp

                    pop rdi
                    pop rsi

                    pop rdx
                    pop rcx
                    pop rbx
                    pop rax
%endmacro

;each exception has a code -> we pass the code to the handler... 
%macro  exceptionHandler 1

;save registers in data 
    mov [show_registers],   rax
    mov [show_registers+8], rbx
    mov [show_registers+16],rcx
    mov [show_registers+24],rdx

    mov [show_registers+32],rsi
    mov [show_registers+40],rdi

    mov [show_registers+48],rbp

    ;now to get stack pointer we add the pushed bytes to rsp
    mov rax, rsp 
	add rax, 0x28
	mov [show_registers+56], rax

    mov [show_registers+64],r8
    mov [show_registers+72],r9
    mov [show_registers+80],r10
    mov [show_registers+88],r11
    mov [show_registers+96],r12
    mov [show_registers+104],r13
    mov [show_registers+112],r14
    mov [show_registers+120],r15

    ;now to get instruction pointer we use interruption return address
	mov rax, [rsp] 
	mov [show_registers+128], rax

    ;load parameters to pass to exceptions handler
    mov rdi , %1 
    mov rsi , show_registers ; "pointer to string"
    call exceptionDispatcher
%endmacro


int_keyboard:
        pushRegisters
        
        ;read scancode from keyboard 
        mov rax, 0
        in  al , 60h

        ;check if CTRL key was pressed (for register dump)
        cmp al , 0b00011101
        jne .continue

        ;do registerdump (we use diff string than for exceptions)
        mov [show_registers_dump+8], rbx
        mov [show_registers_dump+16],rcx
        mov [show_registers_dump+24],rdx

        mov [show_registers_dump+32],rsi
        mov [show_registers_dump+40],rdi

        mov [show_registers_dump+48],rbp
        ;now to get stack pointer we add the pushed bytes to rsp
        mov rax, rsp 
        add rax, 0x28
        mov [show_registers_dump+56], rax
        mov [show_registers_dump+64],  r8
        mov [show_registers_dump+72],  r9
        mov [show_registers_dump+80], r10
        mov [show_registers_dump+88], r11
        mov [show_registers_dump+96], r12
        mov [show_registers_dump+104],r13
        mov [show_registers_dump+112],r14
        mov [show_registers_dump+120],r15
        ;now to get instruction pointer we use interruption return address
        mov rax, [rsp] 
        mov [show_registers_dump+128], rax

        mov byte [has_regs] , 1
        jmp .end

.continue:
        ;check if we "lifted" the ctrl key (if so dont add to buffer)
        cmp al , 0b10011101
        je .end
        ;call the handler
        mov rdi , rax
        call keyboardHandler
.end:
        ;signal the end of interruption to the pic
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
	mov rcx, r10
	mov r9, rax
    call syscallHandler
	iretq

int_timer:
        pushRegisters
        call timerHandler
        ;end interrupt
        mov al, 20h
        out 20h, al
        popRegisters
        iretq


;for protected mode
picMasterMask:
	push rbp
    mov rbp, rsp
    mov ax, di
    out	21h, al
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