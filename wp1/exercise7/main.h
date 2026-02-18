#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ------ Function declarations ----------
// This function generates a set of random numbers
// and fills the table *tab with these numbers
void create_random(int *tab);
// This function takes the *tab of random numbers
// and creates a table with the frequency counts for these numbers
void count_frequency(int *tab, int *freq);
// This function takes the frequency count table
// and draws a histogram of the values in that frequency table
void draw_histogram_horizontal(int *freq);
void draw_histogram_vertical(int *freq);
