/*
 * This file is where our boot assembly will call to intialize our
 * - kernel and setup our simple operating system.
 */

#include "kernel.h"
#include "paging.h"
#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "../drivers/keyboard.h"
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
  heap_install();

  kprintf("Type something, it will go through the kernel\n");
  kprintf("Type END to halt the CPU\n> ");

  char * input;

  while(1) {
    input = get_user_input();
    if (strlen(input) > 0) {
      if (!strcmp(input, "end") || !strcmp(input, "quit") || !strcmp(input, "exit")) {
        kprintf("Stopping the CPU. Bye!\n");
        __asm__ __volatile__("hlt");
      } else if (!strcmp(input, "clear")) {
        clear_screen();
      } else {
        kprintf("You said: %s", input);
      }
      kprintf("\n> ");
    }
    free(input);
  }
}