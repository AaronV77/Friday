#include "common.h"

extern void panic(char *message, char *file, int line)
{
    // We encountered a massive problem and have to stop.
    __asm__ __volatile__("cli"); // Disable interrupts.

    print("KERNEL PANIC(");
    print(message);
    print(") at ");
    print(file);
    print(":");
    print((char*)line);
    print("\n");
    // Halt by going into an infinite loop.
    for(;;);
}

extern void panic_assert(char *file, int line, char *desc)
{
    // An assertion failed, and we have to panic.
    __asm__ __volatile__("cli"); // Disable interrupts.

    print("ASSERTION-FAILED(");
    print(desc);
    print(") at ");
    print(file);
    print(":");
    print((char*)line);
    print("\n");
    // Halt by going into an infinite loop.
    for(;;);
}