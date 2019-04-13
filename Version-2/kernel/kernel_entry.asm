global _start

bits 32
extern kernel_main
extern __bss_start
extern __bss_sizel

section .text.entry

_start:
  ; Zero out the BSS memory area a DWORD at a time
  ; since the memory isn't guaranteed to already be zero
  xor eax, eax
  mov ecx, __bss_sizel
  mov edi, __bss_start
  rep stosd

  ; Call C entry point of kernel
  call kernel_main
  jmp $