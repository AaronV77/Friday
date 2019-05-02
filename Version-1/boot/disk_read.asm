; This file will be used to read in sectors from the disk
; - and load them into memory for us. If there is an error
; - with the read then we make sure to print a message out
; - to the user.

[bits 16]										; Tell our assembler to use 16-bits.

disk_read_1:
	pusha										; Store all the general purpose registers (edi,esi,ebp,esp,ebx,edx,ecx,eax).
	push dx										; Save the dx register because it is not a general purpose register so that
												; - our kernel offset does not get lost / trashed.

	mov ah, 0x02								; Call the subroutine for reading sectors.
	mov al, dh									; Give the ALU register how many sectors we will be reading in.
	mov ch, 0x00								; Load the cylinder number in.
	mov cl, 0x02								; Give the starting sector number to read from. We use the second sector because the first
												; - one was our MBR.	
	mov dh, 0x00								; Load in the head number in.

	int 0x13									; Call the interupt INT 13 / AH = 02 to read the sectors from the disk and put into memory.

	jc disk_read_error_1						; If the carry flag is set because of an error, then go to the disk_read_error procedure.
	pop dx										; Return of dx value that is not a general purpose register.
	cmp dh, al									; Do a compare to see if the correct number of sectors were read in.
	jne disk_read_error_1						; If the previous line did not match then call the disk_read_error procedure.

	popa										; Restore all the previous general purpose registers (edi,esi,ebp,esp,ebx,edx,ecx,eax).
	ret											; Exit this procedure.

disk_read_2:
	pusha										; Store all the general purpose registers (edi,esi,ebp,esp,ebx,edx,ecx,eax).
	push dx										; Save the dx register because it is not a general purpose register so that
												; - our kernel offset does not get lost / trashed.

	mov ah, 0x02								; Call the subroutine for reading sectors.
	mov al, dh									; Give the ALU register how many sectors we will be reading in.
	mov ch, 0x01								; Load the cylinder number in.
	mov cl, 0x00	
	mov dh, 0x00								; Load in the head number in.

	int 0x13									; Call the interupt INT 13 / AH = 02 to read the sectors from the disk and put into memory.

	jc disk_read_error_2_1						; If the carry flag is set because of an error, then go to the disk_read_error procedure.
	pop dx										; Return of dx value that is not a general purpose register.
	cmp dh, al									; Do a compare to see if the correct number of sectors were read in.
	jne disk_read_error_2_2						; If the previous line did not match then call the disk_read_error procedure.

	popa										; Restore all the previous general purpose registers (edi,esi,ebp,esp,ebx,edx,ecx,eax).
	ret											; Exit this procedure.

disk_read_error_1:
	call print_nl								; Call the print_new_line procedure to well print a new line.
	mov bx, DISK_READ_ERROR_MSG_1				; Load our disk error message for output.
	call print_string							; Call the print_string procedure to print the previously loaded message.
	call print_nl								; Call the print_new_line procedure to well print a new line.
	jmp $										; Loop infinitely if we come back from the previous procedure.

disk_read_error_2_1:
	call print_nl								; Call the print_new_line procedure to well print a new line.
	mov bx, DISK_READ_ERROR_MSG_2				; Load our disk error message for output.
	call print_string							; Call the print_string procedure to print the previously loaded message.
	call print_nl								; Call the print_new_line procedure to well print a new line.
	jmp $										; Loop infinitely if we come back from the previous procedure.

disk_read_error_2_2:
	call print_nl								; Call the print_new_line procedure to well print a new line.
	mov bx, DISK_READ_ERROR_MSG_3				; Load our disk error message for output.
	call print_string							; Call the print_string procedure to print the previously loaded message.
	call print_nl								; Call the print_new_line procedure to well print a new line.
	jmp $										; Loop infinitely if we come back from the previous procedure.

DISK_READ_ERROR_MSG_1: db "Disk read error-1!", 0	; Save a byte for our disk read error message. 
DISK_READ_ERROR_MSG_2: db "Disk read error-2!", 0	; Save a byte for our disk read error message. 
DISK_READ_ERROR_MSG_3: db "Disk read error-3!", 0	; Save a byte for our disk read error message. 