/*
 * This file will setup our Programmable Interval Timer
 * - that will be used for anything involving time.
 */
 
#include "timer.h"
#include "isr.h"
#include "ports.h"
#include "../libc/function.h"

uint32_t tick = 0;

/*
 * This function will be called when a hardware timer interrupt
 * - is made and this will inreament our iterator. This can be
 * - used as a system uptime counter and anything that may be needed.
 */
static void timer_callback(registers_t regs) {
  tick++;
  UNUSED(regs);
}

/*
 * This function is setting up our Programmable Interval Timer.
 * - The first line is registering our timer_callback() function
 * - and then setting up the timer. Then we create the frequency
 * - of the clock, and then send the "command byte" to our "command
 * - register" at 0x43 which will set "repeating mode" with 0x36.  
 * - Lastly, we send our Least significant bit of our divisor and 
 * - our Most significant bit
 */
void init_timer(uint32_t freq) {
  register_interrupt_handler(IRQ0, timer_callback);

  uint32_t divisor = 1193180 / freq;
  uint8_t low = (uint8_t)(divisor & 0xFF);
  uint8_t high = (uint8_t)((divisor >> 8) & 0xFF);

  port_byte_out(0x43, 0x36);
  port_byte_out(0x40, low);
  port_byte_out(0x40, high);
}
