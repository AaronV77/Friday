#ifndef KEY_BOARD_H
#define KEY_BOARD_H

#include "screen.h"
#include "../cpu/ports.h"
#include "../cpu/isr.h"
#include "../libc/mem.h"
#include "../libc/string.h"
#include "../libc/function.h"
#include "../include/stdint.h"

void init_keyboard();
char * get_user_input();

#endif