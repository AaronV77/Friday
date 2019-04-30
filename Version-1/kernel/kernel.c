/*
 * This file is where our boot assembly will call to intialize our
 * - kernel and setup our simple operating system.
 */

#include "kernel.h"
#include "paging.h"
#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "../libc/string.h"

/*
 * This function will clear the terminal screen, setup our Interrupt
 * - Descriptor Table, our keyboard and timer, and then lastly print
 * - our header for the system.
 */
void kernel_main() {

  clear_screen();
  isr_install();
  irq_install();
  paging_install();

  kprintf("Type something, it will go through the kernel\n");
  kprintf("Type END to halt the CPU\n> ");
}

/*
 * This function gets called by the keybaord_callback() function when
 * - a normal character has been pressed. This function looks for the 
 * - terminating argument "END" to halt the CPU or just echo's out what
 * - was entered back to the user.
 */
void user_input(char *input) {
  if (!strcmp(input, "end") || !strcmp(input, "quit") || !strcmp(input, "exit")) {
    kprintf("Stopping the CPU. Bye!\n");
    __asm__ __volatile__("hlt");
  } else if (!strcmp(input, "clear")) {
    clear_screen();
  } else {
    kprintf("You said: ");
    kprintf(input);
  }
  kprintf("\n> ");
}
