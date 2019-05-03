/*
 * This file is meant to setup the keyboard interrupt and will be used
 * - every time something is pressed on the keyboard.
 */
#include "keyboard.h"

int SHIFT = 0;
int start_grabbing_input = 0;
int enter_has_been_pressed = 0;

static char key_buffer[256];

/*
 * This function works by grabbing the typed letter from the 60h port,
 * - then goes through a switch statment looking for the character to 
 * - be printed to the screen. If the user has pressed the shift key
 * - and has not released it then any key that has a shift component
 * - to it will be printed instead. Every key on the keyboard has been
 * - incorporated into this switch statment and the keyboard is without
 * - the arrow or numberpad. 
 */
static void keyboard_callback(registers_t regs) {
  if (start_grabbing_input == 0)
    return;

  uint8_t scancode = port_byte_in(0x60);
  
  char str[5];
  int print_switch = 0;
  switch(scancode) {
    case 0x01:
      // Esc 
      break;
    case 0x02:
      // 1 
      if (SHIFT == 0) {
        str[0] = '1';
        str[1] = '\0';
      } else {
        str[0] = '!';
        str[1] = '\0';
      } 
      print_switch = 1;     
      break;
    case 0x03:
      // 2 
      if (SHIFT == 0) {
        str[0] = '2';
        str[1] = '\0';
      } else {
        str[0] = '@';
        str[1] = '\0';
      }   
      print_switch = 1;          
      break;
    case 0x04:
      // 3
      if (SHIFT == 0) {
        str[0] = '3';
        str[1] = '\0';
      } else {
        str[0] = '#';
        str[1] = '\0';
      }   
      print_switch = 1;          
      break;            
    case 0x05:
      // 4 
      if (SHIFT == 0) {
        str[0] = '4';
        str[1] = '\0';
      } else {
        str[0] = '$';
        str[1] = '\0';
      }     
      print_switch = 1;        
      break;      
    case 0x06:
      // 5 
      if (SHIFT == 0) {
        str[0] = '5';
        str[1] = '\0';
      } else {
        str[0] = '%';
        str[1] = '\0';
      }    
      print_switch = 1;         
      break;
    case 0x07:
      // 6
      if (SHIFT == 0) {
        str[0] = '6';
        str[1] = '\0';
      } else {
        str[0] = '^';
        str[1] = '\0';
      }   
      print_switch = 1;          
      break;
    case 0x08:
      // 7
      if (SHIFT == 0) {
        str[0] = '7';
        str[1] = '\0';
      } else {
        str[0] = '&';
        str[1] = '\0';
      }      
      print_switch = 1;       
      break;
    case 0x09:
      // 8 
      if (SHIFT == 0) {
        str[0] = '8';
        str[1] = '\0';
      } else {
        str[0] = '*';
        str[1] = '\0';
      } 
      print_switch = 1;            
      break;
    case 0x0A:
      // 9
      if (SHIFT == 0) {
        str[0] = '9';
        str[1] = '\0';
      } else {
        str[0] = '(';
        str[1] = '\0';
      }   
      print_switch = 1;          
      break;
    case 0x0B:
      // 0
      if (SHIFT == 0) {
        str[0] = '0';
        str[1] = '\0';
      } else {
        str[0] = ')';
        str[1] = '\0';
      }  
      print_switch = 1;           
      break;
    case 0x0C:
      // -
      if (SHIFT == 0) {
        str[0] = '-';
        str[1] = '\0';
      } else {
        str[0] = '_';
        str[1] = '\0';
      }     
      print_switch = 1;        
      break;
    case 0x0D:
      // =
      if (SHIFT == 0) {
        str[0] = '=';
        str[1] = '\0';
      } else {
        str[0] = '+';
        str[1] = '\0';
      }   
      print_switch = 1;          
      break;
    case 0x0E:
      // BACKSPACE
      truncate_character(key_buffer);
      print_backspace();      
      break;
    case 0x0F:
      // TAB
      str[0] = ' ';
      str[1] = ' ';
      str[2] = ' ';
      str[3] = ' ';
      str[4] = '\0';
      print_switch = 1; 
      break;
    case 0x10:
      // Q
      if (SHIFT == 0) {
        str[0] = 'q';
        str[1] = '\0';
      } else {
        str[0] = 'Q';
        str[1] = '\0';
      }    
      print_switch = 1; 
      break;
    case 0x11:
      // W
      if (SHIFT == 0) {
        str[0] = 'w';
        str[1] = '\0';
      } else {
        str[0] = 'W';
        str[1] = '\0';
      }
      print_switch = 1;           
      break;
    case 0x12:
      // E 
      if (SHIFT == 0) {
        str[0] = 'e';
        str[1] = '\0';
      } else {
        str[0] = 'E';
        str[1] = '\0';
      }  
      print_switch = 1;         
      break;
    case 0x13:
      // R
      if (SHIFT == 0) {
        str[0] = 'r';
        str[1] = '\0';
      } else {
        str[0] = 'R';
        str[1] = '\0';
      }  
      print_switch = 1;      
      break;
    case 0x14:
      // T
      if (SHIFT == 0) {
        str[0] = 't';
        str[1] = '\0';
      } else {
        str[0] = 'T';
        str[1] = '\0';
      }  
      print_switch = 1;        
      break;
    case 0x15:
      // Y
      if (SHIFT == 0) {
        str[0] = 'y';
        str[1] = '\0';
      } else {
        str[0] = 'Y';
        str[1] = '\0';
      }    
      print_switch = 1;      
      break;
    case 0x16:
      // U
      if (SHIFT == 0) {
        str[0] = 'u';
        str[1] = '\0';
      } else {
        str[0] = 'U';
        str[1] = '\0';
      }   
      print_switch = 1;       
      break;   
    case 0x17:
      // I
      if (SHIFT == 0) {
        str[0] = 'i';
        str[1] = '\0';
      } else {
        str[0] = 'I';
        str[1] = '\0';
      }   
      print_switch = 1;       
      break;
    case 0x18:
      // O
      if (SHIFT == 0) {
        str[0] = 'o';
        str[1] = '\0';
      } else {
        str[0] = 'O';
        str[1] = '\0';
      }    
      print_switch = 1;      
      break;
    case 0x19:
      // P
      if (SHIFT == 0) {
        str[0] = 'p';
        str[1] = '\0';
      } else {
        str[0] = 'P';
        str[1] = '\0';
      }    
      print_switch = 1;      
      break;
    case 0x1A:
      // [
      if (SHIFT == 0) {
        str[0] = '[';
        str[1] = '\0';
      } else {
        str[0] = '{';
        str[1] = '\0';
      }       
      print_switch = 1;       
      break;            
    case 0x1B:
      // ]
      if (SHIFT == 0) {
        str[0] = ']';
        str[1] = '\0';
      } else {
        str[0] = '}';
        str[1] = '\0';
      }     
      print_switch = 1;       
      break;      
    case 0x1C:
      // ENTER
      str[0] = '\n';
      enter_has_been_pressed = 1;
      break;
    case 0x1D:
      // LEFT CONTROL
      break;
    case 0x1E:
      // A
      if (SHIFT == 0) {
        str[0] = 'a';
        str[1] = '\0';
      } else {
        str[0] = 'A';
        str[1] = '\0';
      }    
      print_switch = 1;
      break;
    case 0x1F:
      // S
      if (SHIFT == 0) {
        str[0] = 's';
        str[1] = '\0';
      } else {
        str[0] = 'S';
        str[1] = '\0';
      }  
      print_switch = 1;        
      break;
    case 0x20:
      // D
      if (SHIFT == 0) {
        str[0] = 'd';
        str[1] = '\0';
      } else {
        str[0] = 'D';
        str[1] = '\0';
      }    
      print_switch = 1;      
      break;
    case 0x21:
      // F
      if (SHIFT == 0) {
        str[0] = 'f';
        str[1] = '\0';
      } else {
        str[0] = 'F';
        str[1] = '\0';
      }    
      print_switch = 1;      
      break;
    case 0x22:
      // G
      if (SHIFT == 0) {
        str[0] = 'g';
        str[1] = '\0';
      } else {
        str[0] = 'G';
        str[1] = '\0';
      }    
      print_switch = 1;      
      break;
    case 0x23:
      // H
      if (SHIFT == 0) {
        str[0] = 'h';
        str[1] = '\0';
      } else {
        str[0] = 'H';
        str[1] = '\0';
      }    
      print_switch = 1;      
      break;
    case 0x24:
      // J
      if (SHIFT == 0) {
        str[0] = 'j';
        str[1] = '\0';
      } else {
        str[0] = 'J';
        str[1] = '\0';
      }    
      print_switch = 1;      
      break;
    case 0x25:
      // K
      if (SHIFT == 0) {
        str[0] = 'k';
        str[1] = '\0';
      } else {
        str[0] = 'K';
        str[1] = '\0';
      }    
      print_switch = 1;      
      break;
    case 0x26:
      // L
      if (SHIFT == 0) {
        str[0] = 'l';
        str[1] = '\0';
      } else {
        str[0] = 'L';
        str[1] = '\0';
      }    
      print_switch = 1;      
      break;
    case 0x27:
      // ;
      if (SHIFT == 0) {
        str[0] = ';';
        str[1] = '\0';
      } else {
        str[0] = ':';
        str[1] = '\0';
      }     
      print_switch = 1;       
      break;
    case 0x28:
      // '
      if (SHIFT == 0) {
        str[0] = '\'';
        str[1] = '\0';
      } else {
        str[0] = '"';
        str[1] = '\0';
      }      
      print_switch = 1;      
      break;
    case 0x29:
      // `
      if (SHIFT == 0) {
        str[0] = '`';
        str[1] = '\0';
      } else {
        str[0] = '~';
        str[1] = '\0';
      }    
      print_switch = 1;        
      break;
    case 0x2A:
      // Left SHIFT
      SHIFT = 1;
      break;
    case 0x2B:
      // \'
      if (SHIFT == 0) {
        str[0] = '\\';
        str[1] = '\0';
      } else {
        str[0] = '|';
        str[1] = '\0';
      }      
      print_switch = 1;      
      break;
    case 0x2C:
      // Z
      if (SHIFT == 0) {
        str[0] = 'z';
        str[1] = '\0';
      } else {
        str[0] = 'Z';
        str[1] = '\0';
      }    
      print_switch = 1;      
      break; 
    case 0x2D:
      // X
      if (SHIFT == 0) {
        str[0] = 'x';
        str[1] = '\0';
      } else {
        str[0] = 'X';
        str[1] = '\0';
      }    
      print_switch = 1;      
      break;
    case 0x2E:
      // C
      if (SHIFT == 0) {
        str[0] = 'c';
        str[1] = '\0';
      } else {
        str[0] = 'C';
        str[1] = '\0';
      }    
      print_switch = 1;      
      break;
    case 0x2F:
      // V
      if (SHIFT == 0) {
        str[0] = 'v';
        str[1] = '\0';
      } else {
        str[0] = 'V';
        str[1] = '\0';
      }    
      print_switch = 1;      
      break;
    case 0x30:
      // B
      if (SHIFT == 0) {
        str[0] = 'b';
        str[1] = '\0';
      } else {
        str[0] = 'B';
        str[1] = '\0';
      }    
      print_switch = 1;      
      break;            
    case 0x31:
      // N
      if (SHIFT == 0) {
        str[0] = 'n';
        str[1] = '\0';
      } else {
        str[0] = 'N';
        str[1] = '\0';
      }    
      print_switch = 1;      
      break;      
    case 0x32:
      // M
      if (SHIFT == 0) {
        str[0] = 'm';
        str[1] = '\0';
      } else {
        str[0] = 'M';
        str[1] = '\0';
      }    
      print_switch = 1;      
      break;
    case 0x33:
      // ,
      if (SHIFT == 0) {
        str[0] = ',';
        str[1] = '\0';
      } else {
        str[0] = '<';
        str[1] = '\0';
      }      
      print_switch = 1;      
      break;
    case 0x34:
      // .
      if (SHIFT == 0) {
        str[0] = '.';
        str[1] = '\0';
      } else {
        str[0] = '>';
        str[1] = '\0';
      }      
      print_switch = 1;      
      break;
    case 0x35:
      // /
      if (SHIFT == 0) {
        str[0] = '/';
        str[1] = '\0';
      } else {
        str[0] = '?';
        str[1] = '\0';
      }      
      print_switch = 1;      
      break;
    case 0x36:
      // Right SHIFT
      SHIFT = 1;
      break;
    case 0x38:
      // Left ALT
      break;
    case 0x39:
      // SPACE
      str[0] = ' ';
      str[1] = '\0';
      print_switch = 1;
      break;
    case 0x3A:
      // CAPS
      if (SHIFT == 0)
        SHIFT = 1;
      else
        SHIFT = 0;
      break; 
    case 0xAA:
      // Left SHIFT Released
      SHIFT = 0;
      break;
    case 0xB6:
      // Right SHIFT Released
      SHIFT = 0;
      break;   
    case 0xBA:
      // CAPS Released
      // SHIFT = 0;    
      break;                                                                                          
    default:
      break;
  };
  
  if (print_switch == 1) {
    for (int i = 0; i < strlen(str); ++i)
      concate_character(key_buffer, str[i]);
    kprintf(str);
  }

  UNUSED(regs);
}

/*
 * This function is what will capture the userinput until the
 * - enter key has been pressed. They system will do an infinite loop
 * - until the enter key has been pressed.
 */
char * get_user_input() {
  start_grabbing_input = 1;
  while(1) {
    if (enter_has_been_pressed == 1)
      break;
  }
  char * buffer = (char*)malloc(strlen(key_buffer));
  strcpy(buffer, key_buffer);
  start_grabbing_input = 0;
  enter_has_been_pressed = 0;
  key_buffer[0] = '\0';
  return buffer;
}

/*
 * This function will map the keyboard interrupt "IRQ1" to the
 * - keyboard_callback(). 
 */
void init_keyboard() {
  register_interrupt_handler(IRQ1, keyboard_callback);
}
