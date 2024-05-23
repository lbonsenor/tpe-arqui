GLOBAL cpuVendor
GLOBAL bringMinutes
GLOBAL bringHours
GLOBAL bringSeconds
GLOBAL whatKeyPressed

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


bringSeconds:   
            cli
            ;config del número n binario
            mov al, 0x0B 
            out 70h, al
            in al, 71h
            or al,4 
            out 71h, al 


            ;lectura de los segundos
            mov al, 0x00
            out 70h, al
            in al, 71h
            sti

            ret
bringMinutes:
            cli
            ;config del numero n binario
            mov al, 0x0B 
            out 70h, al
            in al, 71h
            or al,4 
            out 71h, al 

            ;lectura de los minutos 
            mov al, 0x02
            out 70h, al
            in al, 71h
            sti

            ret
bringHours:
            cli

            ;config del número n binario
            mov al, 0x0B 
            out 70h, al
            in al, 71h
            or al,4 
            out 71h, al 

            ;lectura de los minutos
            mov al, 0x04
            out 70h, al
            in al, 71h
            sti

            ret

whatKeyPressed: 
        ;make sure register is empty
        mov rax, 0
    .inicio: 
        ;64h status register
        in al, 64h
        ;does signal status port have data for system?
        and al, 0x01
        ;if not, return to cycle
        je .inicio
        ;else read the data
        in al, 60h

        ret