/*
 * This file is what will be used to setup our Interrupt
 * - Descriptor Table structure and tell the CPU where
 * - it will be located.
 */

#include "idt.h"

/*
 * This function will be called by the isr.c file to setup
 * - all of the Interrupt Requests and Interrupt Service 
 * - routines. 
 */
void set_idt_gate(int n, uint32_t handler) {
  idt[n].low_offset = LOW_16(handler);
  idt[n].sel = KERNEL_CS;
  idt[n].always0 = 0;
  idt[n].flags = 0x8E;
  idt[n].high_offset = HIGH_16(handler);
}

/*
 * This function will set the base address of where the Interrupt
 * - Descriptor Table starts and then the length of the table as 
 * - well. Then we will allow the lidtl command to point to where
 * - it is located. ** HELP ** I could not find anything with the
 * - following command "lidtl" I think this is a miss type and is
 * - meant to be lidt. This needs to be tested.
 */
void set_idt() {
  idt_reg.base = (uint32_t)&idt;
  idt_reg.limit = IDT_ENTRIES * sizeof(idt_gate_t) - 1;
  __asm__ __volatile__("lidt (%0)" : : "r" (&idt_reg));   // <--- This line was changed from lidtl to lidt.
}
