// File: main.c

// (C) John Dickson, Sebastian Vingård Larsson, Oliver Hansson, Group: 27 (2026)
// Work package 0
// Exercise 2
// Submission code: 27jdohsvlwp0
#include <stdio.h>

// Main function in the program, arguments supported.
int main(int argc, char **argv) {
   // Print a string to the console, together with the passed argument
   printf("%s - I'm %s\n", "Hello World!", argv[1]);

   return 0;
}
