#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// sizeof(int) returns the an int's in bytes
// To get the size in bits, we multiply the result from sizeof(int) by 8
// Finally, as an int is signed by default, we subtract 1 to ensure
// this bit isn't included, as it could lead to undefined behavior.
#define INT_SIZE_IN_BITS (sizeof(int) * 8 - 1)

int checkArgs(char *arg);
void countBits(int);
