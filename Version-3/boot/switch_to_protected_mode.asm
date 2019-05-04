; This file will see if we can enter protected mode and start using
; - 32-bit registers and more memory. 

[bits 16]						; Tell our assembler to use 16-bits.

switch_to_pm:
	cli							; Clear out the interrupt flag.
	lgdt [gdt_pointer]			; Load our global descriptor table that is located in the global_descriptor_table.asm.
	mov eax, 1                  ; Setup a general register with a one to turn on protected mode (32-bit).
	mov cr0, eax                ; Set the control register 0, to the value specified in the previous instruction to enable pm.
	jmp CODE_SEG:init_pm		; Do a long jump to 32 bit instructions. We are leaving real mode, but what this actually does
								; - has me confused. *** HELP ***

[bits 32]						; Tell our assembler that we are now in protected mode and to start using 32-bits.

init_pm:
	mov ax, DATA_SEG			; Update all of our segment registers.
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	mov ebp, 0x90000			; Set our 32-bit stack base value to 0x9000.
	mov esp, ebp				; Set our 32-bit stack pointer to the previous value.

	call begin_pm				; Lets call the kernel now back in boot.asm.
