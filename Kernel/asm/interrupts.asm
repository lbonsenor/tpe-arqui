GLOBAL _cli
GLOBAL _sti
GLOBAL _hlt
GLOBAL haltcpu

GLOBAL picMasterMask
GLOBAL picSlaveMask

GLOBAL _irq00Handler
GLOBAL _irq01Handler
GLOBAL _int80Handler

GLOBAL _exception0Handler
GLOBAL _exception6Handler

GLOBAL show_registers_dump
GLOBAL has_regs
GLOBAL show_registers
EXTERN exceptionDispatcher
EXTERN syscallHandler
EXTERN irqDispatcher

EXTERN print

SECTION .text

%macro pushState 0
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
%endmacro

%macro popState 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro

%macro irqHandlerMaster 1
	pushState

	mov rdi, %1 
	call irqDispatcher

	; Signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al

	popState
	iretq
%endmacro

%macro  exceptionHandler 1
	; Save registers in data 
	; Order: RIP RAX RBX RCX RDX RSI RDI RBP RSP R8 R9 R10 R11 R12 R13 R14 R15 
    mov [show_registers + (1*8)] , rax
    mov rax, [rsp]
    mov [show_registers], rax ;rip
    mov [show_registers + (2*8)], rbx
    mov [show_registers + (3*8)], rcx
    mov [show_registers + (4*8)], rdx
    mov [show_registers + (5*8)], rsi 
    mov [show_registers + (6*8)], rdi
    mov [show_registers + (7*8)], rbp

    ; RSP from stack (flags, CS and RIP where pushed when int occurs)
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
    mov rax, [rsp+16] ; RFLAGS (in stack bc interruption happened).
    mov [show_registers + (17*8)], rax    ; rflags

    ; Load parameters to pass to exceptions handler
    mov rdi, %1 
    mov rsi, show_registers ; "pointer to string"
    call exceptionDispatcher

    iretq
%endmacro

_hlt:
	sti
	hlt
	ret

_cli:
	cli
	ret

_sti:
	sti
	ret

picMasterMask:
	push rbp
    mov rbp, rsp
    mov ax, di
    out	21h,al
    pop rbp
    retn

picSlaveMask:
	push rbp
    mov rbp, rsp
    mov ax, di
    out	0A1h, al
    pop rbp
    retn

; 8254 Timer (Timer Tick)
_irq00Handler:
	irqHandlerMaster 0

; Keyboard
_irq01Handler:
	pushState
    in al, 0x60 ; readKey
    cmp al, 0x1D ; check if left CTRL is pressed (used to save registers)
    jne .continue
        ;mov [show_registers_dump],         rax -> dont do this, it only gets iD from ctrl key
        mov [show_registers_dump + (1*8)], rbx 
        mov [show_registers_dump + (2*8)], rcx
        mov [show_registers_dump + (3*8)], rdx 
        mov [show_registers_dump + (4*8)], rsi 
        mov [show_registers_dump + (5*8)], rdi
        mov [show_registers_dump + (6*8)], rbp 
        mov [show_registers_dump + (8*8)], r8
        mov [show_registers_dump + (9*8)], r9
        mov [show_registers_dump + (10*8)], r10
        mov [show_registers_dump + (11*8)], r11
        mov [show_registers_dump + (12*8)], r12
        mov [show_registers_dump + (13*8)], r13
        mov [show_registers_dump + (14*8)], r14
        mov [show_registers_dump + (15*8)], r15 

        ;RSP && RIP && RAX
        mov rax , [rsp + 18*8] 
        mov [show_registers_dump + (7*8)], rax
        mov rax, [rsp + 15*8]
        mov [show_registers_dump + (16*8)], rax
        mov rax , [rsp + 14*8]
        mov [show_registers_dump], rax
        mov byte[has_regs], 1

.continue:
    mov rdi, 1 ; param for dispatcher
    call irqDispatcher
        
    ;EOI
    mov al, 20h
    out 20h, al

    popState
    iretq

; Zero Division Exception
_exception0Handler:
	exceptionHandler 0

; Invalid Opcode Exception
_exception6Handler:
	exceptionHandler 6

_int80Handler:
	; syscalls params:	RDI	RSI	RDX	R10	R8	R9
	; syscallHandler:	RDI RSI RDX R10 R8  RAX
	; params in C are:	RDI RSI RDX RCX R8  R9
    ; pushState
    ; mov rcx, r10
	; mov r9, rax -> we will be calling all params from c so its the same
    call syscallHandler
    ; popState
	iretq

haltcpu:
	cli
	hlt
	ret


SECTION .bss
    has_regs resb 1; to check whether we have saved or not!
    show_registers resq 18 ; reserve a qword for each register 
    show_registers_dump resq 17 ;aditionally for dumping (isnt passed as a param but is accessed directly)