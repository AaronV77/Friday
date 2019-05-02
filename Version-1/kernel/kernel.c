/*
 * This file is where our boot assembly will call to intialize our
 * - kernel and setup our simple operating system.
 */

#include "kernel.h"

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
  heap_install();

  kprintf("Type something, it will go through the kernel\n");
  kprintf("Type END to halt the CPU\n> ");

  char * input;
  while(1) {
    input = get_user_input();
    kprintf("\n");
    char * token = strtok(input, " ");
    while(token != 0) {
      // if (!strcmp(token, "end") || !strcmp(token, "quit") || !strcmp(token, "exit")) {
      //   kprintf("Stopping the CPU. Bye!\n");
      //   __asm__ __volatile__("hlt");
      // } else if (!strcmp(token, "clear")) {
      //   clear_screen();
      // } else if (!strcmp(token, "cat")) {
      //   free(token);
      //   token = strtok(input, " ");
      //   if (token)
      //     display_file(token);
      // } else if (!strcmp(token, "create") || !strcmp(token, "edit")) {
      //   free(token);
      //   token = strtok(input, " ");
      //   if (token)
      //     create_file(token);
      // } else if (!strcmp(token, "rm")) {
      //   free(token);
      //   token = strtok(input, " ");
      //   if (token)
      //     delete_file(token);
      // } else {
      //   kprintf("You said: %s", token);
      // }
      kprintf("Looking at: %s\n", token);
      token[0] = '\0';
      token = strtok(input, " ");
    }
    free(token);
    kprintf("\n> ");
    free(input);
  }
}