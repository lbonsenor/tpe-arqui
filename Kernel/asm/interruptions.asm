GLOBAL _cli
GLOBAL _sti
GLOBAL _hlt
GLOBAL int_keyboard
GLOBAL int_exc_divide_by_zero
GLOBAL int_exc_invalid_opcode
GLOBAL int_syscall


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
    ; call the exception hanlder TODO
%endmacro


; now the routines for each exception..

int_keyboard:
        pushRegisters
        ; ... whatever
        ; call the keyboard handler with params, etc
        ;signal the end of interruption to the pic
        mov al, 20h
        out 20h, al
        popRegisters
        iretq 

;creo que hará falta el timerTick del tp5 tmb (para el getTime)

int_exc_divide_by_zero: 
        ;call the exception handler with code 00h

int_exc_invalid_opcode:
        ;call the exception handler with code 06h 

int_syscall:
; syscalls params:	RDI	RSI	RDX	R10	R8	R9
; syscallHandler:	RDI RSI RDX R10 R8  RAX
; params in C are:	RDI RSI RDX RCX R8  R9
	mov rcx, r10
	mov r9, rax
	; call syscalls handler
	iretq
section .bss
show_registers resq 17 ; reserve a qword for each register 



