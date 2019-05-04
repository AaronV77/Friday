; This files main purpose is to print a newline character to the 
; - screen. That is it.

[bits 16]							; Tell our assembler to use 16-bits.

print_nl:
	pusha							; Store all the general purpose registers (edi,esi,ebp,esp,ebx,edx,ecx,eax).
	mov ah, 0x0E					; Subroutine to print characters in TTY Mode.
	mov al, 0x0A					; Load the character to print "\n".
	int 0x10						; Call the interrupt to print the character.
	mov al, 0x0D					; Load the character to print "\r".
	int 0x10						; Call the interrupt to print the character.
	popa							; Restore all the previous general purpose registers that were in use previously.
	ret								; Exit this procedure.
