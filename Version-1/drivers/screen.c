/*
 * This file consists of all the utilites in order to display items
 * - onto the users screen. 
 */
#include <stdarg.h>
#include "screen.h"
#include "../cpu/ports.h"
#include "../libc/mem.h"
#include "../libc/string.h"

typedef char* string;
char tbuf[32];
char bchars[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

/*
 * This function will get the total offset.
 */
int get_offset(int col, int row) {
  return 2 * (row * MAX_COLS + col);
}

/*
 * This function will calcualte the given offset for the row.
 */
int get_row_from_offset(int offset) {
  return offset / (2 * MAX_COLS);
}

/*
 * This function will calculate the given offset for the column.
 */
int get_col_from_offset(int offset) {
  return (offset - (get_row_from_offset(offset) * 2 * MAX_COLS)) / 2;
}

/*
 * This function will get the current cursor offset on the screen by
 * - communicating through ports. ** HELP ** I don't know what ports 
 * - these are. 
 */
int get_cursor_offset() {
  port_byte_out(REG_SCREEN_CTRL, 14);
  int offset = port_byte_in(REG_SCREEN_DATA) << 8;
  port_byte_out(REG_SCREEN_CTRL, 15);
  offset += port_byte_in(REG_SCREEN_DATA);

  return offset * 2;
}

/*
 * This function will move the cursor to a different position by 
 * - communicating to some given port. ** HELP ** I'm not really sure
 * - what port this is.
 */
int set_cursor_offset(int offset) {
  offset /= 2;

  port_byte_out(REG_SCREEN_CTRL, 14);
  port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
  port_byte_out(REG_SCREEN_CTRL, 15);
  port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xFF));

  return offset * 2;
}

void __itoa(unsigned i, unsigned base, char* buf) {
	int pos = 0;
	int opos = 0;
	int top = 0;

	if (i == 0 || base > 16) {
		buf[0] = '0';
		buf[1] = '\0';
		return;
	}

	while (i != 0) {
		tbuf[pos] = bchars[i % base];
		pos++;
		i /= base;
	}
	top=pos--;
	for (opos=0; opos<top; pos--,opos++)
		buf[opos] = tbuf[pos];
	buf[opos] = 0;
}

void __itoa_s(int i, unsigned base, char* buf) {
   if (base > 16) return;
   if (i < 0) {
      *buf++ = '-';
      i *= -1;
   }
   __itoa(i, base, buf);
}

/*
 * This function will write a given character at a specified position
 * - through video memory. This function will also handle scrolling and
 * - newline characters.
 */
int print_char(char character, int column, int row, int attribute) {
  if (!attribute) 
    attribute = WHITE_ON_BLACK;

  char *video_memory_ptr = (char*)VIDEO_ADDRESS;

  int offset;
  if (column >= 0 && row >= 0)
    offset = get_offset(column, row);
  else
    offset = get_cursor_offset();

  if (character == '\n') {
    row = get_row_from_offset(offset);
    offset = get_offset(0, row + 1);
  } else {
    video_memory_ptr[offset++] = character;
    video_memory_ptr[offset++] = attribute;
  }

  if (offset >= MAX_ROWS * MAX_COLS * 2) {
    // In case, if we out of bounds
    // Copy each line to a line above
    for (int i = 1; i < MAX_ROWS; i++)
      memcpy((uint8_t*)(get_offset(0, i) + VIDEO_ADDRESS), (uint8_t*)(get_offset(0, i - 1) + VIDEO_ADDRESS), MAX_COLS * 2);

    // Clear the last line after all lines were copied
    char* last_line = (char*)(get_offset(0, MAX_ROWS - 1) + VIDEO_ADDRESS);
    for (int i = 0; i < MAX_COLS * 2; i++)
      last_line[i] = 0;

    // Update current offset to (0, MAX_ROWS - 1)
    offset -= 2 * MAX_COLS;
  }

  // Update cursor position after all calcuations
  set_cursor_offset(offset);
  return offset;
}

void print_at(char message, int column, int row) {
  int offset;

  if (column >= 0 && row >= 0)
    offset = get_offset(column, row);
  else
    offset = get_cursor_offset();

  offset = print_char(message, get_col_from_offset(offset), get_row_from_offset(offset), WHITE_ON_BLACK);
}

void __kprintf_va_list(char * str, va_list ap) {

	char * s = 0;

	for (int i = 0; i < strlen((string)str); i++) {
		if (str[i] == '%') {
			switch(str[i+1])
			{
				/** string **/
				case 's':
					s = va_arg(ap, char*);
					while(*s) {
            print_at((char)*s, -1, -1);
            s++;
          }
					i++;
					continue;
				/** decimal **/
				case 'd': {
					int c = va_arg(ap, int);
					char str[32] = {0};
					__itoa_s(c, 10, str);
          for (int i = 0; i < strlen(str); ++i)
            print_at(str[i], -1, -1);
					i++;
					continue;
				}
				case 'x': {
					int c = va_arg(ap, int);
					char str[32]= {0};
					__itoa(c, 16, str);
          for (int i = 0; i < strlen(str); ++i)
            print_at(str[i], -1, -1);
					i++;
					continue;
				}
				/** character **/
				case 'c': {
					// char gets promoted to int for va_arg!
					// clean it.
					char c = (char)(va_arg(ap, int) & ~0xFFFFFF00);
          print_at(c, -1, -1);
					i++;
					continue;
				}
				default:
					break;
			}
		} else {
      print_at(str[i], -1, -1);
		}
	}
	va_end(ap);
}

int kprintf (const char* str, ...) {
  if(!str)
		return 0;
	va_list ap;
	va_start(ap, str);
	__kprintf_va_list((char *)str, ap);
	return 1;
}

/*
 * This function will take the current cursor position and move it back
 * - two spaces. Then the function will remove the character that needs 
 * - to be erased off the screen. ** HELP ** This function is not working
 * - properly.
 */
void print_backspace() {
  int offset = get_cursor_offset() - 1;
  int row = get_row_from_offset(offset);
  int column = get_col_from_offset(offset);

  int attribute = WHITE_ON_BLACK;
  char character = ' ';
  char *video_memory_ptr = (char*)VIDEO_ADDRESS;

  if (column > 1) {
    offset = get_offset(column, row);
    video_memory_ptr[offset++] = character;
    video_memory_ptr[offset++] = attribute;
    set_cursor_offset(offset - 1);
  }
}

/*
 * This will loop through the entire screen and erase everything
 * - that was printed onto it. We then movethe cursor to the original
 * - position on the screen. *** Bugged *** The return of the cursor
 * - will not work correctly because of the prompt taking over the 0,0
 * - position on the screen. Also don't think this function is being 
 * - used.
 */
void clear_screen() {
  for (int row = 0; row < MAX_ROWS; row++) {
    for (int col = 0; col < MAX_COLS; col++) {
      print_char(' ', col, row, WHITE_ON_BLACK);
    }
  }

  set_cursor_offset(get_offset(0, 0));
}