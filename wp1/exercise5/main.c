// File: main.c

// (C) John Dickson, Sebastian Vingård Larsson, Oliver Hansson, Group: 27 (2026)
// Work package 1
// Exercise 5
// Submission code: Qc0rbE

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100      // Defines the maximum number of the values in the table
#define MAXNUMBER 20 // Defines the maximum value of random numbers

// ------ Function declarations ----------
// This function generates a set of random numbers
// and fills the table *tab with these numbers
void create_random(int *tab);
// This function takes the *tab of random numbers
// and creates a table with the frequency counts for these numbers
void count_frequency(int *tab, int *freq);
// This function takes the frequency count table
// and draws a histogram of the values in that frequency table
void draw_histogram(int *freq);

// ------ Function definitions ----------

// ------ Main --------------------------
// The main entry point for the program
//
// If you choose to go for the optional part
// Please modify it accordingly
int main(void) {
  int table[MAX], n;
  int frequency[MAXNUMBER] = {0};

  create_random(table); // generate random numbers for the table array
  count_frequency(table, frequency); // count the frequency of each generated
                                     // number in the table array
  draw_histogram(frequency);         // draw the frequency as a histogram
}

// function to generate random numbers between 0 and MAXNUMBER, which are then
// assigned to the available indices of the tab variable
void create_random(int *tab) {
  srandom((unsigned)time(
      NULL)); // seed the random function to make it less predictable

  for (int i = 0; i < MAX; i++) {
    tab[i] =
        random() %
        MAXNUMBER; // assign the random number mod MAXNUMBER to each table index
  }
}

// function to count the frequency of each generated number in the tab variable
void count_frequency(int *tab, int *freq) {
  for (int i = 0; i < MAX; i++) {
    ++freq[tab[i]]; // increment elements in the frequency array with each
                    // element in the tab array's as the index
  }
}

// function to draw a histogram of all frequencies
void draw_histogram(int *freq) {
  for (int i = 0; i < MAXNUMBER; i++) {
    // only print elements with a frequency > 0
    if (freq[i] != 0) {
      printf("%2d ", i); // print the number of the frequencies to print

      // to print the asterisks, we need to loop over the range of 0 to the
      // frequency and print once per iteration
      for (int j = 0; j < freq[i]; j++) {
        putchar('*'); // print an asterisk to the console
      }

      putchar('\n'); // ensure next element starts on a new line
    }
  }
}
