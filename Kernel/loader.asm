GLOBAL loader
GLOBAL resetMain
extern main
extern initializeKernelBinary
extern getStackBase
section .text

loader:
	call initializeKernelBinary	; Set up the kernel binary, and get thet stack address
	jmp continue
resetMain: ; to reset after exceptions
	call getStackBase
continue:
	mov rsp, rax				; Set up the stack with the returned address
	call main
hang:
	cli
	hlt	; halt machine should kernel return
	jmp hang
