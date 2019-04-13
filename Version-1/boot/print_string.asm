; This file takes an incoming string in the bx register to print
; - to the screen. 

[bits 16]					; Tell our assembler to use 16-bits.

print_string:
	pusha					; Store all the general purpose registers (edi,esi,ebp,esp,ebx,edx,ecx,eax).

print_string_loop:
	mov al, [bx]			; Get a character of the string from the bx register.
	cmp al, 0				; Check to make sure that it is not zero (end).
	je print_string_ret		; If the al register contains a zero then we are finished. Call the print_
							; - string_ret procedure.

	mov ah, 0x0E			; Subroutine to print characters in TTY Mode.
	int 0x10				; Call the interrupt to print the character.
	inc bx					; Increment the position of the register so that we get the next character.
	jmp print_string_loop	; Jump to the top of this procedure and restart.

print_string_ret:
	popa					; Restore all the previous general purpose registers (edi,esi,ebp,esp,ebx,edx,ecx,eax).
	ret						; Exit this procedure.
