/*
 * This file holds the functions to communicate with various 
 * - hardware through ports.
 */
#include "ports.h"


/*
 * This function will read a byte sized piece of data from a 
 * - given port.
 */
unsigned char port_byte_in(unsigned short port) {
  unsigned char result;
  __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
  return result;
}

/*
 * This function will write a byte sized piece of data from a
 * - given port.
 */
void port_byte_out(unsigned short port, unsigned char data) {
  __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}

/*
 * This function will read a word sized piece of data from a 
 * - given port.
 */
unsigned short port_word_in(unsigned short port) {
  unsigned short result;
  __asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
  return result;
}

/*
 * This function will write a word sized piece of data from a
 * - given port.
 */
void port_word_out(unsigned short port, unsigned short data) {
  __asm__("out %%ax, %%dx" : : "a" (data), "d" (port));
}
