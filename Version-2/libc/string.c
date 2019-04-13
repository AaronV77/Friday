#include "string.h"

/*
 * This function will take the incoming number and convert it into a 
 * - string to store in the incoming char array. The algorthim works 
 * - by checking to see if the incoming number is negative and if so 
 * - convert it to positive. Next we have to loop through the entire
 * - number to take the modulus and then add 30 to it since 0 in ascii
 * - is equal to 48. We keep getting the remainder until it is less than
 * - zero. Then we add the negative size if the original number was 
 * - negative and add the null terminating character to the end of the
 * - string. Our number is backwards in ascii values and needs to be 
 * - reversed. Thats it.
 */
void itoa(int number, char str[]) {
  int i = 0, c = 0, length = 0, sign = number;

  if (sign < 0) 
    number = -number;

  do {
    str[length++] = number % 10 + '0';
  } while ((number /= 10) > 0);

  if (sign < 0) 
    str[length++] = '-';
  str[length] = '\0';

  for (i = 0; i < length/2; i++) {
    c = str[i];
    str[i] = str[length-i-1];
    str[length-i-1] = c;
  }
}

/*
 * This function loops through an entire string, incrementing the iterator
 * - until the end of the string is reached. The value afterwards is returned.
 */
int strlen(char s[]) {
  int i = 0;
  while (s[i] != '\0') ++i;
  return i;
}

/*
 * This function will add a letter onto the end of an original string.
 */
void concate_character(char s[], char n) {
  int len = strlen(s);
  s[len] = n;
  s[len+1] = '\0';
}

/*
 * This function will remove a character on the end of a string.
 */
void truncate_character(char s[]) {
  int len = strlen(s);
  s[len-1] = '\0';
}

/*
 * This function will loop through each of the passed in strings to be 
 * - compared. If they are equal then return zero, else return their 
 * - difference.
 */
int strcmp(char s1[], char s2[]) {
  int i;
  for (i = 0; s1[i] == s2[i]; i++) {
    if (s1[i] == '\0') 
      return 0;
  }
  return s1[i] - s2[i];
}
