#ifndef KHEAP_H
#define KHEAP_H

#include "../include/stdint.h"
#include "../drivers/screen.h"

void memset(int *dest, int val, int len);
void memory_copy(unsigned char *source, unsigned char *destination, int bytes);
void * malloc();
void heap_install();
int find_memory_hole();
void free(int * pointer);

#endif
