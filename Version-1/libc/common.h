#ifndef COMMON_H
#define COMMON_H

#include "../drivers/screen.h"

#define PANIC(msg) panic(msg, __FILE__, __LINE__);
#define ASSERT(b) ((b) ? (void)0 : panic_assert(__FILE__, __LINE__, #b))

extern void panic(char *message, char *file, int line);
extern void panic_assert(char *file, int line, char *desc);

#endif