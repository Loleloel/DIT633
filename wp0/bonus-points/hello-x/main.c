// File: main.c

// headers
#include <stdio.h>
#include <string.h>

// macros
#define MIN_NAME_LENGTH 3
#define MAX_NAME_LENGTH 50

// main function in the program, takes command line arguments
int main(int argc, char **argv) {
  // declare a variable to store the length of the name entered
  int lengthOfName;

  // the first element of argv is always the running program e.g., main.exe
  if (argc == 1) {
    printf("%s", "No command line argument provided, please provide a name.\n");

    return 0;
  }

  // assign the length of the name to the previously declared variable
  lengthOfName = strlen(argv[1]);

  // handle invalid name length, (less than 3 chars or greater than 50 chars)
  if (lengthOfName < MIN_NAME_LENGTH) {
    printf("%s", "Name too short, min 3 characters\n");
  } else if (lengthOfName > MAX_NAME_LENGTH) {
    printf("%s", "Name too long, max 50 characters\n");
  }

  // print the greeting message to the user
  printf("%s %s, %s", "Hello", argv[1], "how is your day today?\n");

  return 0;
}
