/*
 * This file consists of all the utilites in order to display items
 * - onto the users screen. 
 */
#include "screen.h"
#include "../cpu/ports.h"
#include "../libc/mem.h"

int print_char(char character, int column, int row, int attribute);
int get_cursor_offset();
int set_cursor_offset(int offset);
int get_offset(int col, int row);
int get_row_from_offset(int offset);
int get_col_from_offset(int offset);


/*
 * This function will print the message at the current location on
 * - the screen.
 */
void print(char *message) {
  print_at(message, -1, -1);
}

/*
 * This function will print anything at a given location that either
 * - the cursor is at or the current offest from both row and column.
 */
void print_at(char *message, int column, int row) {
  int offset;

  if (column >= 0 && row >= 0)
    offset = get_offset(column, row);
  else
    offset = get_cursor_offset();

  while (*message) {
    offset = print_char((char)*message, get_col_from_offset(offset), get_row_from_offset(offset), WHITE_ON_BLACK);
    message++;
  }
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
  print("In Clear_Screen\n");
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
    for (int i = 1; i < MAX_ROWS; i++) {
      memory_copy((uint8_t*)(get_offset(0, i) + VIDEO_ADDRESS), (uint8_t*)(get_offset(0, i - 1) + VIDEO_ADDRESS), MAX_COLS * 2);
    }

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
