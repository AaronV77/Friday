; This file contains the Global Descriptor Table that will tell
; - the CPU about the available memory segments.

; I don't see the point of having both userland and kernel code and data segments.
; - When in our kernel we really don't have the paradigm of a kernel vs. a user.
[bits 16]									; Tell our assembler to use 16-bits.

gdt_start:									; The start of the GDT.
gdt_null:
	dd 0x0
	dd 0x0

;; Kernel Code Segment
gdt_kernel_code:
	dw 0xFFFF
	dw 0x0
	db 0x0
	db 10011010b
	db 11001111b
	db 0x0

;; Kernel Data Segment
gdt_kernel_data:
	dw 0xFFFF
	dw 0x0
	db 0x0
	db 10010010b
	db 11001111b
	db 0x0

;; Userland Code Segment
gdt_userland_code:
	dw 0xFFFF
	dw 0x0
	db 0x0
	db 11111010b
	db 11001111b
	db 0x0

;; Userland Data Segment
gdt_userland_data:
	dw 0xFFFF
	dw 0x0
	db 0x0
	db 11110010b
	db 11001111b
	db 0x0
gdt_end:                                	; The ending of the GDT.

gdt_pointer:                            	; Create the pointer structure to our GDT.
	dw gdt_end - gdt_start - 1          	; This is for our entire GDT which is 16-bits.
	dd gdt_start                        	; This is for the start of our GDT which is 32-bits.

CODE_SEG equ gdt_kernel_code - gdt_start    ; Set an offset into our GDT for the code segment.
DATA_SEG equ gdt_kernel_data - gdt_start    ; Set an offset into our GDT for the data segment.