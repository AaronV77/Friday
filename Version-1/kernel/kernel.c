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
  file_system_install();
  heap_install();

  kprintf("Type something, it will go through the kernel\n");
  kprintf("Type END to halt the CPU\n> ");

  char * input = (char*)malloc(20);
  // int token_length = 0;

  while(1) {
    input = get_user_input();
    // char * token = strtok(input, " ", 0);
    // while(strlen(token) != 0) {
    //   if (strlen(token) <= 10) {
        if (!strcmp(input, "end") || !strcmp(input, "quit") || !strcmp(input, "exit")) {
          kprintf("Stopping the CPU. Bye!\n");
          __asm__ __volatile__("hlt");
        } else if (!strcmp(input, "clear")) {
          clear_screen();
        } else if (!strcmp(input, "cat")) {
          // token_length = strlen(token) + 1;
          // token[0] = '\0';
          // token = strtok(input, " ", token_length);
          // if (token)
          kprintf("\nName of file to display?: ");
          char * file = get_user_input();
          kprintf("\n");
          create_file(file);
          free(file);
        } else if (!strcmp(input, "create") || !strcmp(input, "edit")) {
          // token_length = strlen(token) + 1;
          // token[0] = '\0';
          // token = strtok(input, " ", token_length);
          // if (token)
          kprintf("\nName of file to create?: ");
          char * file = get_user_input();
          kprintf("\n");
          create_file(file);
          free(file);
        } else if (!strcmp(input, "rm")) {
          // token_length = strlen(token) + 1;
          // token[0] = '\0';
          // token = strtok(input, " ", token_length);
          // if (token)
          kprintf("\nWhat file would you like to delete?: ");
          char * file = get_user_input();
          kprintf("\n");
          delete_file(file);
          free(file);
        }

        // token_length = strlen(token) + 1;
        // token[0] = '\0';
        // token = strtok(input, " ", token_length);
      // } else {
      //   kprintf("The line is too big...\n");
      // }
    // }
    // free(token);
    kprintf("\n> ");
    input[0] = '\0';
  }
  free(input);
}