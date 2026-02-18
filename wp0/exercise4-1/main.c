// File: main.c

// (C) John Dickson, Sebastian Vingård Larsson, Oliver Hansson, Group: 27 (2026)
// Work package 0
// Exercise 4
// Submission code: 27jdohsvlwp0

// Gen AI prompt response:

// EXERCISE 4: RETURN CODES AND LOGIC
// In C, the main function usually returns an integer. This "Exit Code" tells
// the operating system if the program finished successfully (0) or encountered
// an error (not 0).
// Your Task: Modify your program from Exercise 3 so that:
// The main function signature is changed to int main(int argc, char *argv[]).
// If the program runs successfully (exactly one argument provided), it prints
// the message and returns 0. If the program fails (wrong number of arguments),
// it prints the error message and returns 1.
// Bonus: Research how to check the "exit code" of the last run command in
// your terminal (e.g., echo $? on Linux/Mac or echo %errorlevel% on Windows).

#include <stdio.h>
#include <string.h>

// Main function in the program, arguments supported and some error handling
int main(int argc, char *argv[]) {
   // argc is the number of arguments passed.
   // First argument is always the program execution.
   // That's why we must check for argc != 2 for exactly ONE argument passed.
   if (argc != 2) {
      // Print an error message to the console.
      printf("%s", "Error: Incorrect number of arguments passed.\n");

      // Inform the user of the '-h' flag for more help.
      printf("%s", "For help, please run this program with the '-h' flag.\n");

      // Return exit code 1, as the program encountered an error.
      return 1;
   } else if (strcmp(argv[1], "-h") == 0) {
      printf("Help Menu:\n"); //print help menu header
      printf("This program accepts one name and prints it to the console.\n"); //print help description
      printf("Usage: ./program_name <argument>\n"); //print usage instruction
   } else {
      // Print a string to the console, together with the passed argument
      printf("%s - I'm %s\n", "Hello World!", argv[1]);
   }

   // If the program finishes without any errors, return exit code 0.
   return 0;
}
