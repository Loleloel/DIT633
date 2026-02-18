// File: main.c

// (C) John Dickson, Sebastian Vingård Larsson, Oliver Hansson, Group: 27 (2026)
// Work package 0
// Exercise 3
// Submission code: 27jdohsvlwp0
#include <stdio.h>
#include <string.h>

// Main function in the program, arguments supported and some error handling
int main(int argc, char **argv) {
   // argc is the number of arguments passed.
   // First argument is always the program execution.
   // That's why we must check for argc != 2 for exactly ONE argument passed.
   if (argc != 2) {
      // Print an error message to the console.
      printf("%s", "Error: Incorrect number of arguments passed.\n");

      // Inform the user of the '-h' flag for more help.
      printf("%s", "For help, please run this program with the '-h' flag.\n");

      return 1;
   } else if (strcmp(argv[1], "-h") == 0) {
      printf("Help Menu:\n"); //print help menu header
      printf("This program accepts one name and prints it to the console.\n"); //print help description
      printf("Usage: ./program_name <argument>\n"); //print usage instruction
   } else {
      // Print a string to the console, together with the passed argument
      printf("%s - I'm %s\n", "Hello World!", argv[1]);
   }

   return 0;
}
