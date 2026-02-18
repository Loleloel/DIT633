#include "main.h"

// ------ Global Variables --------------
int max;
int maxNumber;

// ------ Function definitions ----------

// ------ Main --------------------------
// The main entry point for the program
//
// If you choose to go for the optional part
// Please modify it accordingly
int main(int argc, char **argv) {
  // check if mandatory args have been passed
  if (argc < 3)
    return 1;

  max = atoi(argv[1]);       // cast max arg to an int
  maxNumber = atoi(argv[2]); // cast max number arg to an int
  int table[max], n;
  int frequency[maxNumber];

  // initialize the frequency array
  for (int i = 0; i < maxNumber; i++) {
    frequency[i] = 0;
  }

  create_random(table); // generate random numbers for the table array
  count_frequency(table, frequency); // count the frequency of each generated
                                     // number in the table array

  if (argc == 4 &&
      strcmp("-v", argv[3]) == 0) { // check if the vertical flag is passed
    draw_histogram_vertical(
        frequency); // draw the frequency as a vertical histogram
  } else {
    draw_histogram_horizontal(
        frequency); // draw the frequency as a horizontal histogram
  }
}

// function to generate random numbers between 0 and MAXNUMBER, which are then
// assigned to the available indices of the tab variable
void create_random(int *tab) {
  srandom((unsigned)time(
      NULL)); // seed the random function to make it less predictable

  for (int i = 0; i < max; i++) {
    tab[i] =
        random() %
        maxNumber; // assign the random number mod MAXNUMBER to each table index
  }
}

// function to count the frequency of each generated number in the tab variable
void count_frequency(int *tab, int *freq) {
  for (int i = 0; i < max; i++) {
    ++freq[tab[i]]; // increment elements in the frequency array with each
                    // element in the tab array's as the index
  }
}

// function to draw a histogram of all frequencies horizontally
void draw_histogram_horizontal(int *freq) {
  for (int i = 0; i < maxNumber; i++) {
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

// function to draw a histogram of all frequencies vertically
void draw_histogram_vertical(int *freq) {
  int maxFreq = 0; // variable to store the max counted frequency

  // find max counted frequency
  for (int i = 0; i < maxNumber; i++) {
    // check if the count at index i of the freq array is larger than the value
    // the maxFreq currently holds
    if (freq[i] > maxFreq) {
      maxFreq = freq[i]; // set maxFreq to the value of freq[i]
    }
  }

  // newline
  putchar('\n');

  // print the histogram by printing the same number of rows as the maxFreq
  // holds
  for (int row = 0; row < maxFreq; row++) {
    for (int col = 0; col < maxNumber; col++) {
      // if the frequency is 0, continue to the next element
      if (freq[col] == 0) {
        continue;
      }

      // if the maxFreq minus the row is <= the value of freq[col] we print " *
      // " basically we're printing the histogram top-down
      if (maxFreq - row <= freq[col]) {
        printf(" * ");
      } else { // if the value of maxFreq - row is greater than freq[col], just
               // print whitespace
        printf("   ");
      }
    }

    putchar('\n');
  }

  for (int i = 0; i < maxNumber; i++) {
    if (freq[i] != 0) {
      printf("%2d ", i);
    }
  }

  putchar('\n');
}
