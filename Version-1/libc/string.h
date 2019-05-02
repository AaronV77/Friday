#ifndef STRING_H
#define STRING_H

#include "mem.h"

void itoa(int n, char str[]);
void reverse(char s[]);
int strlen(const char s[]);
void truncate_character(char s[]);
void concate_character(char s[], char n);
int strcmp(char s1[], char s2[]);
int strcpy(char s1[], char s2[]);
char * strtok(char* s, char* delm);

#endif