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
  // paging_install();

  print("Type something, it will go through the kernel\n");
  print("Type END to halt the CPU\n> ");
}

/*
 * This function gets called by the keybaord_callback() function when
 * - a normal character has been pressed. This function looks for the 
 * - terminating argument "END" to halt the CPU or just echo's out what
 * - was entered back to the user.
 */
void user_input(char *input) {
  if (strcmp(input, "END") == 0 || strcmp(input, "QUIT") == 0 || strcmp(input, "EXIT") == 0) {
    print("Stopping the CPU. Bye!\n");
    __asm__ __volatile__("hlt");
  }

  print("You said: ");
  print(input);
  print("\n> ");
}
