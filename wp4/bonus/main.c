#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARG_LEN 10

// ---------- Prototypes ----------
void getSizeToMalloc(int len, size_t *size);
void recFindPerms(int index, int len, char *input, char *permutations, size_t *permsWritten);
void printPerms(int len, char *permutations, size_t count);

// main function
int main(int argc, char *argv[]) {
    char *permutations; // pointer to malloc and hold the permutations
    int len;            // variable to hold the string length
    size_t size, permsWritten = 0;

    // print an error message to console and exit the program if
    // either an invalid number of args are passed, or the passed
    // arg is too long
    if (argc != 2 || (len = strlen(argv[1])) > MAX_ARG_LEN) {
        puts("invalid");

        return 0;
    }

    // get the size based on the length to know how much memory to
    // allocate to be able to contain all the permutations
    getSizeToMalloc(len, &size);

    // allocate the size needed
    permutations = malloc(size * (len + 1));

    // if unable to allocate memory, print error message and 
    // exit program
    if (!permutations) {
        puts("Error: Unable to allocate memory.");
        return 0;
    }

    // start finding the permutations of the input string
    recFindPerms(0, len, argv[1], permutations, &permsWritten);

    // print the found permutations to the console
    printPerms(len, permutations, permsWritten);

    // free the memory and set the permutations variable to NULL
    // to ensure no further operations can be done to it
    free(permutations);
    permutations = NULL;

    return 0;
}

/* Function to get the amount to malloc to the permutations pointer.
 * Takes two adresses as arguments, one for the string length, and
 * another to the size variable to store the values in. */
void getSizeToMalloc(int len, size_t *size) {
    *size = 1;
    // The size to malloc will be the length of the string factorial,
    // which is what this for-loop calculates.
    for (int i = len; i > 0; i--) {
        *size *= i;
    }
}

/* Simple swap function which will be inlined when compiled to reduce
 * time spent calling the function.
 * Takes three arguments, where two of them are indices to swap, and the third
 * is the input string where the swap will occur */
static inline void swap(int index1, int index2, char *input) {
    char temp = input[index1];
    input[index1] = input[index2];
    input[index2] = temp;
}

/* Function to find all permutations of a string through recursion.
 * Takes an index, a string length, an input and the permutations array as
 * arguments. */
void recFindPerms(int index, int len, char *input, char *permutations, size_t *permsWritten) {
    // Base case
    if (index == (len - 1)) {
        // copy the input into memory of permutations at the 
        // location of (permsWritten * (len + 1)) ending each
        // permutation with a null terminator
        memcpy(permutations + (*permsWritten) * (len + 1), input, len + 1);
        (*permsWritten)++;
        return;
    }

    // loop through all letters of the input string
    for (int i = index; i < len; i++) {
        // var to hold a boolean value of duplicates found to
        // prevent duplicate permutations
        int isDuplicate = 0;

        // the duplicate check to ensure no same chars are swapped
        // to create equal permutations
        for (int j = index; j < i; j++) {
            if (input[i] == input[j]) {
                isDuplicate = 1;
                break;
            }
        }

        // if duplicate is found, continue with next iteration
        if (isDuplicate)
            continue;

        // swap the char at pos i with the char at pos index in the input string
        swap(i, index, input);

        // recursive call with index + 1 as argument to navigate the permutation tree
        recFindPerms(index + 1, len, input, permutations, permsWritten);

        // swap back the swapped chars to their original positions
        swap(i, index, input);
    }
}

// Function to print permutations to the console
void printPerms(int len, char *permutations, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        printf("%s\n", permutations + i * (len + 1));
    }
}
