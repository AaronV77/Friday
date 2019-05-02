#include "common.h"

extern void panic(char *message, char *file, int line)
{
    // We encountered a massive problem and have to stop.
    __asm__ __volatile__("cli"); // Disable interrupts.

    kprintf("KERNEL PANIC( %s ) at %s: %s\n", message, file, (char*)line);
    // Halt by going into an infinite loop.
    for(;;);
}

extern void panic_assert(char *file, int line, char *desc)
{
    // An assertion failed, and we have to panic.
    __asm__ __volatile__("cli"); // Disable interrupts.

    kprintf("ASSERTION-FAILED( %s ) at %s: %s\n", desc, file, (char*)line);
    // Halt by going into an infinite loop.
    for(;;);
}