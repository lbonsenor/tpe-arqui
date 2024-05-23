GLOBAL cpuVendor
GLOBAL getKey

section .text
	
cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret

getKey: 
    mov rax, 0
.start: 
    in al, 64h      ; Reads keyboard status  
    and al, 0x01    ; If there isn't any data to read, restart
    je .start
    in al, 60h      ; If there is data, get the scancode of the pressed key
    ret