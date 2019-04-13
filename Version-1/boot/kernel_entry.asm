; This file is getting linked in at a specific memory location 0x1000 and will be
; - called by the boot.asm when the system has loaded the sectors from the disk, and
; - has entered protected or long mode. When the memory location 0x1000 is called the
; - the symbol associated to it "_start" which is done by the global instruction will
; - be ran. The extern part is what will grab the symbol that corolates to the name
; - that is used with the instruction and grab the symbol from our linking of object
; - files. This symbol is the method of kernel_main() in kernel.h. From there it is 
; - pretty self explanatory. The method gets called and then we loop infinitely.

; How this file wor

global _start             ; Export the symbol "_start" for this file.

[bits 32]                 ; Tell the assembler we are using 32-bits.
[extern kernel_main]      ; Grab the kernel_main() symbol from the object files.

section .text.entry

_start:                   ; The start of our procdedure for calling our kernel.
  call kernel_main        ; Call our kernel_main() method in our C files.
  jmp $                   ; Loop infinitely. 
