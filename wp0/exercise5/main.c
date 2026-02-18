// File: exercise-05.c

// (C) John Dickson, Sebastian Vingård Larsson, Oliver Hansson, Group: 27 (2026)
// Work package 0
// Exercise 4
// Submission code: 27jdohsvlwp0

// Gen AI prompt response:

// EXERCISE 5: MULTIPLE ARGUMENTS & LOOPS
// In real-world applications, programs often need to process more than one
// piece of data. This exercise introduces the for loop to handle multiple
// inputs. Your Task: Create a new program that can greet multiple people at
// once. The program should accept any number of names as arguments.
// Use a for loop to iterate through all provided arguments. Example Execution:
// my_program.exe Alice Bob Charlie Expected Output:
// Hello World! – I’m Alice!
// Hello World! – I’m Bob!
// Hello World! – I’m Charlie!
// Requirement: If no arguments are provided, it should still show the help
// message you created in Exercise 3.

#include <stdio.h>
#include <string.h>

// Main function in the program, arguments supported and some error handling
int main(int argc, char **argv) {
   // argc is the number of arguments passed.
   // First argument is always the program execution.
   // That's why we must check for argc < 2 to ensure AT LEAST one argument
   // is passed.
   if (argc < 2) {
      // Print an error message to the console.
      printf("%s", "Error: Incorrect number of arguments passed.\n");

      // Inform the user of the '-h' flag for more help.
      printf("%s", "For help, please run this program with the '-h' flag.\n");

      // Return exit code 1, as the program encountered an error.
      return 1;
   } else if (strcmp(argv[1], "-h") == 0) {
      printf("Help Menu:\n"); //print help menu header
      printf("This program accepts multiple names and prints them to the console.\n"); //print help description
      printf("Usage: ./program_name <argument1> <argument2> <argument3>\n"); //print usage instruction

   } else {
      for (int i = 1; i < argc; i++) {
         // Print a string to the console, together with the passed argument
         printf("%s - I'm %s\n", "Hello World!", argv[i]);
      }
   }

   // If the program finishes without any errors, return exit code 0.
   return 0;
}
