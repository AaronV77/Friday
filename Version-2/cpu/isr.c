/*
 * This file is meant to setup our Interrupt Desccriptor Table with
 * - Interrupt Requests (IRQ's) and Interrupt Service Routines (IRS's).
 * - This file will also assign functions to use to handle the issued
 * - interrupts.
 */

#include "isr.h"
#include "idt.h"
#include "ports.h"
#include "timer.h"
#include "../drivers/keyboard.h"
#include "../drivers/screen.h"
#include "../libc/mem.h"
#include "../libc/string.h"

isr_t interrupt_handlers[256];

/* Here is an array of messages that will map to the interrupt 
 * codes. This will help debbuging when an error occurs.
 */
char *exception_messages[] = {
  "Division By Zero",
  "Debug",
  "Non Maskable Interrupt",
  "Breakpoint",
  "Into Detected Overflow",
  "Out of Bounds",
  "Invalid Opcode",
  "No Coprocessor",

  "Double Fault",
  "Coprocessor Segment Overrun",
  "Bad TSS",
  "Segment Not Present",
  "Stack Fault",
  "General Protection Fault",
  "Page Fault",
  "Unknown Interrupt",

  "Coprocessor Fault",
  "Alignment Check",
  "Machine Check",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",

  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved"
};

/*
 * This function is what will setup the Interrupt Descriptor Table (IDT)
 * - array. A gate is just considered to be an entry into the table. 
 */
void isr_install() {
  set_idt_gate(0, (uint32_t)isr0);
  set_idt_gate(1, (uint32_t)isr1);
  set_idt_gate(2, (uint32_t)isr2);
  set_idt_gate(3, (uint32_t)isr3);
  set_idt_gate(4, (uint32_t)isr4);
  set_idt_gate(5, (uint32_t)isr5);
  set_idt_gate(6, (uint32_t)isr6);
  set_idt_gate(7, (uint32_t)isr7);
  set_idt_gate(8, (uint32_t)isr8);
  set_idt_gate(9, (uint32_t)isr9);
  set_idt_gate(10, (uint32_t)isr10);
  set_idt_gate(11, (uint32_t)isr11);
  set_idt_gate(12, (uint32_t)isr12);
  set_idt_gate(13, (uint32_t)isr13);
  set_idt_gate(14, (uint32_t)isr14);
  set_idt_gate(15, (uint32_t)isr15);
  set_idt_gate(16, (uint32_t)isr16);
  set_idt_gate(17, (uint32_t)isr17);
  set_idt_gate(18, (uint32_t)isr18);
  set_idt_gate(19, (uint32_t)isr19);
  set_idt_gate(20, (uint32_t)isr20);
  set_idt_gate(21, (uint32_t)isr21);
  set_idt_gate(22, (uint32_t)isr22);
  set_idt_gate(23, (uint32_t)isr23);
  set_idt_gate(24, (uint32_t)isr24);
  set_idt_gate(25, (uint32_t)isr25);
  set_idt_gate(26, (uint32_t)isr26);
  set_idt_gate(27, (uint32_t)isr27);
  set_idt_gate(28, (uint32_t)isr28);
  set_idt_gate(29, (uint32_t)isr29);
  set_idt_gate(30, (uint32_t)isr30);
  set_idt_gate(31, (uint32_t)isr31);

  /*
   * We are going to remap the PIC here because of us entering
   * - protected mode due to some CPU conflictions. Some things 
   * - to keep in mind:
   * Master PIC - COMMAND - 0x0020
   * Master PIC - DATA    - 0x0021
   * Slave PIC  - COMMAND - 0x00A0
   * Slave PIC  - DATA    - 0x00A1
   * - Next I will label what each line is doing and to remind
   * - you that this needs to be done before adding the IRQ's to
   * - our ID Table so that our (8259 PIC) chip is working correctly.
   */
  port_byte_out(0x20, 0x11);    // Initialize the MASTER PIC.
  port_byte_out(0xA0, 0x11);    // Initialize the SLAVE PIC.
  port_byte_out(0x21, 0x20);    // Set the offset for the MASTER PIC Data.
  port_byte_out(0xA1, 0x28);    // Set the offset for the SLAVE PIC Data.
  port_byte_out(0x21, 0x04);    // Tell the MASTER PIC that there is a slave PIC at IRQ2.
  port_byte_out(0xA1, 0x02);    // Tell the SLAVE PIC its cascade identity.
  port_byte_out(0x21, 0x01);    // Write ICW4 to MASTER PIC.
  port_byte_out(0xA1, 0x01);    // Write ICW4 to SLAVE PIC.
  port_byte_out(0x21, 0x0);     // Enable all IRQs on MASTER PIC
  port_byte_out(0xA1, 0x0);     // enable all IRQs on SLAVE PIC

  // Install IRQs into our IDT
  set_idt_gate(32, (uint32_t)irq0);
  set_idt_gate(33, (uint32_t)irq1);
  set_idt_gate(34, (uint32_t)irq2);
  set_idt_gate(35, (uint32_t)irq3);
  set_idt_gate(36, (uint32_t)irq4);
  set_idt_gate(37, (uint32_t)irq5);
  set_idt_gate(38, (uint32_t)irq6);
  set_idt_gate(39, (uint32_t)irq7);
  set_idt_gate(40, (uint32_t)irq8);
  set_idt_gate(41, (uint32_t)irq9);
  set_idt_gate(42, (uint32_t)irq10);
  set_idt_gate(43, (uint32_t)irq11);
  set_idt_gate(44, (uint32_t)irq12);
  set_idt_gate(45, (uint32_t)irq13);
  set_idt_gate(46, (uint32_t)irq14);
  set_idt_gate(47, (uint32_t)irq15);

  set_idt();
}

/*
 * This function handles interrupt service routines that occur in the CPU,
 * - to communicate with the user of what interrupt occured and took place.
 * - This function gets called by the interrupt.asm file to be able to 
 * - communicate with the kernel.
 */
void isr_handler(registers_t r) {
  char s[3];

  print("Received interrupt: ");
  itoa(r.int_no, s);
  print(s);
  print("\n");
  print(exception_messages[r.int_no]);
  print("\n");
}

/*
 * This function will setup the timer, the keyboard, and we will set
 * - the interrupt flag. I really don't know what setting the interrupt
 * - flag will do. ** HELP **
 */
void irq_install() {
  __asm__ __volatile__("sti");

  init_timer(50);
  init_keyboard();
}

// Calls every time when hardware interrupt is occured
/*
 * This function is working with handling the hardware interrupts that 
 * - will be communicated with the Programmable Interrupt Controller (PIC).
 * - What this function is doing is checking our IDT array to see if the
 * - interrupt is either 0 - 7 (Master PIC) or 8 - 15 (Slave PIC). With the
 * - check at 40 this is at IRQ 8. If the interrupt number is greater than 40
 * - then we need to communicate with the slave PIC to issued the command "end
 * - interrupt". We don't have to communicate with the slave PIC if the interrupt
 * - is less than 40. Lastly, we get what interrupt occured for what hardware and
 * - pass it the incoming structure of registers. The handler should either be
 * - keyboard_callback() or the timer_callback().
 */
void irq_handler(registers_t r) {
  if (r.int_no >= 40)
    port_byte_out(0xA0, 0x20);

  port_byte_out(0x20, 0x20);

  if (interrupt_handlers[r.int_no] != 0) {
    isr_t handler = interrupt_handlers[r.int_no];
    handler(r);
  }
}

/*
 * This function will asscoiate a function to when an interrupt occurs.
 * - This will allow the kernel to handle the interrupt by calling the 
 * - correct handler function. There are only two as of right now and
 * - they are for the timer and keyboard.
 */
void register_interrupt_handler(uint8_t n, isr_t handler) {
  interrupt_handlers[n] = handler;
}
