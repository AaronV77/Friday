; This file is the starting point to the whole operating system. This file
; - is what will be loaded when the BIOS reads from the disk and will be 
; - put into memory at 0x7C00. The system will start out in real mode, then
; - load some more sectors off the hard drive, enter either protected or 
; - long mode, and then start running our kernel. This file is using other
; - files in this directory that are included at the bottom of this file.

[org 0x7C00]						; Sets the offset to which all absolute addresses will be relative to.
[bits 16]							; Tell the assembler that we are in real mode (16-bit).

KERNEL_OFFSET equ 0x1000			; Create a variable that will point to our kernel_entry file to start
									; - running our kernel. This address is hard coded in the linking of the system.
mov [BOOT_DRIVE], dl				; Save the disk number if something changes the dl register.

mov bp, 0x9000						; Create a stack that expands from 0x1000 to 0x9000 so that our kernel has some memory to use.
mov sp, bp							; Move our stack pointer to be at the high end of the datastructure. Remember that the stack 
									; - will grow to lower memory address rather than higher memory addresses.

call load_kernel_into_memory		; Call the procedure to load more sectors from disk into memory.

call switch_to_pm					; Call the procedure to enter protected mode (32-bit).
jmp $								; Loop infinitely if we come back from the previous procedure.

load_kernel_into_memory:
	pusha							; Store all the general purpose registers (edi,esi,ebp,esp,ebx,edx,ecx,eax).
	mov bx, KERNEL_OFFSET			; Store the location of where we want to load our sectors into memory.
	mov dh, 33						; Read 15 (512 bytes) sectors from the disk. 
	mov dl, [BOOT_DRIVE]			; Move the disk number into the dl register.
	call disk_read					; Call the procdeure to read the sectors from the disk.
	popa							; Restore all the previous general purpose registers (edi,esi,ebp,esp,ebx,edx,ecx,eax).
	ret								; Exit this procedure.

[bits 32]							; Now that we have entered either protected or long mode we will tell our assembler to use 32-bits.

begin_pm:
	call execute_kernel				; Call the procedure to run our kernel.
	jmp $							; Loop infinitely if we come back from the previous procedure.

execute_kernel:
	call KERNEL_OFFSET				; Call the procedure at the 0x1000 address witch should be our kernel_entry "_start"
									; - procedure.
	jmp $							; Loop infinitely if we come back from the previous procedure.

BOOT_DRIVE: db 0					; Create a vairable that is one byte for our boot drive structure.

%include "boot/disk_read.asm"
%include "boot/global_descriptor_table.asm"
%include "boot/switch_to_protected_mode.asm"
%include "boot/print_newline.asm"
%include "boot/print_string.asm"

times 510-($-$$) db 0               ; How this works is that it takes the bootloaders starting address and subtract it by the last
									; - address (which ever instruction was ran last.) and then pad what ever is remaining with zeros.
									; - Why we use 510 as our last pointer is because the bootloader is 512 bytes and we have to use a 
									; - double word ( 2 bytes ) to show the ending of our boot sector.

dw 0xAA55                           ; the standard PC boot signature that tells the BIOS that this
                                    ; - sector is bootable.(base) 
