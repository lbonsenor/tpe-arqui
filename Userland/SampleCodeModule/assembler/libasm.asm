GLOBAL syscall
GLOBAL divzero
GLOBAL invalidOpCode
section .text

divzero:
	mov rax, 5
	mov ebx, 0
	div ebx
	ret

invalidOpCode:
    mov cr6, rax
    ret

syscall:	
	push rbp;
	mov rbp, rsp;
	int 80h

	mov rsp, rbp;
	pop rbp;
	ret	