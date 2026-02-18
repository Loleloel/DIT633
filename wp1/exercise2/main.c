// File: main.c

// (C) John Dickson, Sebastian Vingård Larsson, Oliver Hansson, Group: 27 (2026)
// Work package 1
// Exercise 2
// Submission code: Qc0rbE

#include <stdio.h>  // getchar, putchar, fprintf
#include <stdlib.h>  // atoi

// main function
// argc: number of command line arguments
// argv: array of command line argument strings
int main(int argc, char *argv[]) {
    int inputChar;  // must be int so EOF works
    int shift;  // how many letters to move
    int output;  // the encrypted character to print

    if (argc < 2) {  // shift must be given as argument
        fprintf(stderr, "HOW TO: ./main + 1-25, dont use 26.\n"); // tell user how to use program
        puts("Then type sentences to encrypt with ROT13");
        return 1; //exit with "error"
    }
    shift = atoi(argv[1]);  // convert string to number so we can use it for shifting
    if (shift == 26) {  // special case: 26 wraps to 0, not twice as secure as ROT13
        fprintf(stderr, "I told you... Shift 26 == 0. Use 1-25.\n");
        return 1;
    }

    while ((inputChar = getchar()) != EOF) {  // read one char at a time until EOF (Ctrl+Z/Ctrl+D)
        if (inputChar >= 'A' && inputChar <= 'Z')  // uppercase: shift within A-Z, single quote is used to call the ASCII value of the character
            output = (inputChar - 'A' + shift) % 26 + 'A';  // 0-25, + shift, wrap, back to letter
        else if (inputChar >= 'a' && inputChar <= 'z')  // lowercase: shift within a-z
            output = (inputChar - 'a' + shift) % 26 + 'a'; // 0-25 + shift, wrap, and then back to letter
        else  // spaces, digits, newline, åäö: leave unchanged
            output = inputChar; // leave unchanged
        putchar(output);  // print the encrypted characters
    }
    return 0; //exit program successfully
}
