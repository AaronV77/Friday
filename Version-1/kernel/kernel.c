/*
 * This file is where our boot assembly will call to intialize our
 * - kernel and setup our simple operating system.
 */

#include "kernel.h"

char * strtok(char* s, char* delm, int iterator)
{
    if (iterator >= strlen(s))
        return 0;

    if (!s || !delm || s[iterator] == '\0')
        return 0;

    static char W[100];
    memset((int*)W, 0, 100);
    int i = iterator, k = 0, j = 0;

    
    while (s[i] != '\0') {
        j = 0;
        while (delm[j] != '\0') {
            if (s[i] != delm[j])
                W[k] = s[i];
            else
                goto It;
            j++;
        }
        i++;
        k++;
    }
It:
    W[i] = 0;
    return W;
}

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

  char * input = (char*)malloc(20);
  int token_length = 0;

  while(1) {
    input = get_user_input();
    char * token = strtok(input, " ", 0);
    while(strlen(token) != 0) {
      if (strlen(token) <= 10) {
        if (!strcmp(token, "end") || !strcmp(token, "quit") || !strcmp(token, "exit")) {
          kprintf("Stopping the CPU. Bye!\n");
          __asm__ __volatile__("hlt");
        } else if (!strcmp(token, "clear")) {
          clear_screen();
        } else if (!strcmp(token, "cat")) {
          token_length = strlen(token) + 1;
          // token[0] = '\0';
          token = strtok(input, " ", token_length);
          if (token)
            display_file(token);
        } else if (!strcmp(token, "create") || !strcmp(token, "edit")) {
          token_length = strlen(token) + 1;
          // token[0] = '\0';
          token = strtok(input, " ", token_length);
          if (token)
            create_file(token);
        } else if (!strcmp(token, "rm")) {
          token_length = strlen(token) + 1;
          // token[0] = '\0';
          token = strtok(input, " ", token_length);
          if (token)
            delete_file(token);
        }

        token_length = strlen(token) + 1;
        // token[0] = '\0';
        token = strtok(input, " ", token_length);
      } else {
        kprintf("The line is too big...\n");
      }
    }
    free(token);
    kprintf("\n> ");
    free(input);
  }
}