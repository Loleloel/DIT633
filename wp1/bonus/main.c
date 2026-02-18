#include "main.h"

int main(int argc, char **argv) {
    if (argc < 2) { // check if an argument was passed
        puts("Error: No number provided. Please provide a number as a command line argument.");
        return 0;
    }

    if (checkArgs(argv[1]) == 1) { // check if the argument is a valid number
        puts("Error: Invalid number.");
        return 0;
    }
    
    int number = atoi(argv[1]); // convert ascii values of argument to int
    printf("Number: %d\n", number);
    countBits(number); // count the number of bits

    return 0;
}

// check if the arg passed is a valid decimal number
int checkArgs(char *arg) {
    for (int i = 0; i < strlen(arg); i++) { // check each char in the argument
        if (!isdigit(arg[i])) { // ensure that chars are digits, if not return 1
            return 1;
        }
    }

    return 0;
}

// function to count the number of bits (1s and 0s) without any leading 0s
void countBits(int number) {
    int numZeroes = 0;
    int numOnes = 0;

    printf("Binary: 0b");
    for (int i = INT_SIZE_IN_BITS; i >= 0; i--) {
        // check if the number shifted i steps to the right and 1 are of equal value
        if (number >> i & 1) {
            printf("1");
            numOnes++; // increment the numOnes by 1
        } else if (numOnes != 0) { // otherwise, increment numZeroes only if
            printf("0");           // numOnes is not 1 to ensure no leading zeroes are present
            numZeroes++;
        }
    }

    printf("\nNumber of 0s: %d\n", numZeroes);
    printf("Number of 1s: %d\n", numOnes);
}

