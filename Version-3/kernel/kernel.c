/*
 * This file is where our boot assembly will call to intialize our
 * - kernel and setup our simple operating system.
 */

#include "kernel.h"

/*
 * This function will clear the terminal screen, and setup our Interrupt
 * - Descriptor Table, keyboard and timer. Once the basice components of
 * - of the kernel has started this function will go into a loop that will
 * - collect user input until the user gives the exiting command.
 */
void kernel_main() {

  clear_screen();
  isr_install();
  irq_install();
  heap_install();
  file_system_install();
  
  kprintf("Type something, it will go through the kernel\n");
  kprintf("Type END to halt the CPU\n> ");

  char * input = (char*)malloc(20);

  while(1) {
    input = get_user_input();
    if (!strcmp(input, "end") || !strcmp(input, "quit") || !strcmp(input, "exit")) {
      kprintf("\nStopping the CPU. Bye!\n");
      __asm__ __volatile__("hlt");
      break;
    } else if (!strcmp(input, "clear")) {
      clear_screen();
    } else {
      kprintf("\nNo command for the following input: %s",input);
    }
        
    kprintf("\n> ");
    input[0] = '\0';
  }
  free(input);
  for(;;);
}