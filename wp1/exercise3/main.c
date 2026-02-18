// File: main.c

// (C) John Dickson, Sebastian Vingård Larsson, Oliver Hansson, Group: 27 (2026)
// Work package 1
// Exercise 3
// Submission code: Qc0rbE

#include <stdio.h>  // printf, scanf, getchar
#include <stdlib.h>  // rand

#define MAX_TRIES 10 // max number of tries


// main function takes no arguments (void = no arguments)
int main(void)
{
    int target; // "secret" number
    int guess; // user input
    int tries; // guess count
    char again; // y/n for another round

    do {  // outer loop: one round per iteration
        target = rand() % 100 + 1;
        tries = 0;  // reset count for this round

        while (1) {  // inner loop: one guess per iteration 
            printf("You have %d tries to guess the number (1-100): ", MAX_TRIES - tries);
            if (scanf("%d", &guess) != 1) {  // if user typed non-number 
                printf("Invalid input. Please enter a number.\n");
                while (getchar() != '\n');  // clear the bad input from buffer
                continue;  // don't count as a guess, ask again
            }
            if (guess < 1 || guess > 100) {  // only accept 1-100
                printf("Must be between 1 and 100.\n");
                continue;  // ask again without incrementing tries
            }
            tries++;  // valid guess, so count it

            if (guess == target) { // correct guess
                printf("You have guessed %d times and your guess is correct\n", tries); // tell user how many tries it took
                break;  // end this round
            }
            if(guess < target) // too low 
                printf("Your guess is too low\n");
            else // too high
                printf("Your guess is too high\n");

                
            if (tries >= MAX_TRIES) {  // limit reached without guessing right
                printf("Max guesses reached.\n");
                break; // end this round
            }
        }
        printf("Play again? (y/n): "); // ask user if they want to play again
        while (getchar() != '\n')  // clear newline left by last scanf
            ;
        again = getchar();  // read single character (y/n)
        while (getchar() != '\n')  // clear rest of line
            ;
    } while (again == 'y' || again == 'Y');  // loop again only if user said yes

    return 0;
}

//end of file
