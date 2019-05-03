/*
 * This file is meant to setup the keyboard interrupt and will be used
 * - every time something is pressed on the keyboard.
 */
#include "keyboard.h"
#include "screen.h"
#include "../cpu/ports.h"
#include "../cpu/isr.h"
#include "../libc/function.h"
#include "../libc/string.h"
#include "../kernel/kernel.h"

#define BACKSPACE 0x0E
#define ENTER 0x1C

static char key_buffer[256];

#define SC_MAX 57

/*
 * Available keys that they system can accept or knows of.
 */
const char sc_ascii[] = {
  '?',
  '?',
  '1',
  '2',
  '3',
  '4',
  '5',
  '6',
  '7',
  '8',
  '9',
  '0',
  '-',
  '=',
  '?',
  '?',
  'Q',
  'W',
  'E',
  'R',
  'T',
  'Y',
  'U',
  'I',
  'O',
  'P',
  '[',
  ']',
  '?',
  '?',
  'A',
  'S',
  'D',
  'F',
  'G',
  'H',
  'J',
  'K',
  'L',
  ';',
  '\'',
  '`',
  '?',
  '\\',
  'Z',
  'X',
  'C',
  'V',
  'B',
  'N',
  'M',
  ',',
  '.',
  '/',
  '?',
  '?',
  '?',
  ' '
};

/*
 * This function works by grabbing the typed letter from the 60h port,
 * - checks to see if it is within the number maximum, then sees if its a 
 * - special character "Backspace", "Enter", or then a known character. 
 * - This function is mapped to IRQ1 for keyboard interrupts and will be
 * - called when ever someone types something onto the screen. The incoming
 * - argument is not needed but other "handlers" will need this argument,
 * - but since this function doesn't and we don't want compiler warnings;
 * - there is a declaration of a methond UNUSED that will act as if it is
 * - using the incoming argument. From there we adjust the screen and return.
 */
static void keyboard_callback(registers_t regs) {
  uint8_t scancode = port_byte_in(0x60);

  if (scancode > SC_MAX) 
    return;
    
  if (scancode == BACKSPACE) {
    truncate_character(key_buffer);
    print_backspace();
  } else if (scancode == ENTER) {
    print("\n");
    user_input(key_buffer);
    key_buffer[0] = '\0';
  } else {
    char letter = sc_ascii[(int)scancode];
    char str[2] = {letter, '\0'};
    concate_character(key_buffer, letter);
    print(str);
  }

  UNUSED(regs);
}

/*
 * This function will map the keyboard interrupt "IRQ1" to the
 * - keyboard_callback(). 
 */
void init_keyboard() {
  register_interrupt_handler(IRQ1, keyboard_callback);
}
