#ifndef KHEAP_H
#define KHEAP_H

#include "../include/stdint.h"

void memory_copy(uint8_t *source, uint8_t *destination, int bytes);
void memset(int *dest, int val, int len);
// int kmalloc(int sz, int align, int *phys);

#endif
