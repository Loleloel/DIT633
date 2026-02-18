#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void getMatrixSize(int *mSize);
int readInput(int *matrix, int expectedNumItems);

int main(void) {
  int mSize[3] = {0}; // 0 = rows, 1 = cols, 2 = checksum
  int *m1, *m2, expectedNumItems, m1InputOk, m2InputOk;

  getMatrixSize(mSize); // read the user's requested matrix size

  /* For readability, assign the product of the rows * the cols
   * to the expectedNumItems. */
  expectedNumItems = mSize[0] * mSize[1];

  // allocate memory on the heap to the matrices
  m1 = malloc(expectedNumItems * sizeof(int));
  m2 = malloc(expectedNumItems * sizeof(int));

  // read the values to the matrices
  m1InputOk = readInput(m1, expectedNumItems);
  m2InputOk = readInput(m2, expectedNumItems);

  /* If invalid input is entered, such as too few or too many
   * values, or a non-digit entry, print an error message
   * to the console and exit the program. */
  if (!m1InputOk || !m2InputOk) {
    puts("invalid");
    exit(0);
  }

  puts("The sum is:");
  // Print the sum of the two matrices to the console
  for (int i = 0; i < expectedNumItems; i++) {
    printf("%d ", m1[i] + m2[i]);

    // if i + 1 % cols == 0, put a newline.
    if ((i + 1) % mSize[1] == 0) {
      puts("");
    }
  }

  // free the memory of the two matrices
  free(m1);
  free(m2);

  // Ensure both matrices are inaccessible by setting them
  // both to NULL
  m1 = NULL;
  m2 = NULL;

  return 0;
}

/* Get the matrix sizes from the user.
 * Argument is a pointer to the mSize array. */
void getMatrixSize(int *mSize) {
  // declare a char array big enough to comfortably take
  // the largest valid matrix size of 4x4
  char input[8];

  // Read input string to input variable
  fgets(input, 8, stdin);

  /* Read three decimals from the input variable.
   * If sscanf doesn't read exactly two decimals,
   * print an error message and exit the program. */
  if (2 != sscanf(input, "%d %d %d", &mSize[0], &mSize[1], &mSize[2])) {
    puts("invalid");
    exit(0);
  }

  /* Ensure the user has entered the correct amount of numbers required, as well
   * as the rows and cols entered being in a valid range (between 2 - 4). Else,
   * print an error message and exit the program. */
  if (0 != mSize[2] || 2 > mSize[0] || 2 > mSize[1] || 4 < mSize[0] ||
      4 < mSize[1]) {
    puts("invalid");
    exit(0);
  }
}

/* Read the values of the matrices and put them into a matrix passed as an
 * argument. Must pass the expected number of items as an argument too (rows *
 * cols). */
int readInput(int *matrix, int expectedNumItems) {
  // Declare a string variable to read the line entered by the user
  // Ensure its size is large enough for the input + any white space chars
  char input[256];

  // if unsuccessful in reading input, return 0 (false)
  if (!fgets(input, sizeof(input), stdin)) return 0;

  // init a counter to 0, and declare a variable to read how far the pointer p should move
  // in the input string
  int ptrDistanceToMove, count = 0;
  char *p = input; // pointer to the first element in the input string

  // while we successfully read a decimal, and the incrementing count is < than the expectedNumItems
  // we move the pointer the distance stored in the ptrDistanceToMove after each read.
  while (sscanf(p, "%d%n", &matrix[count], &ptrDistanceToMove) == 1 && ++count < expectedNumItems) {
    p += ptrDistanceToMove;
  }

  // returns 1 (true) if i == expectedNumItems, else 0 (false)
  return (count == expectedNumItems); // set the flag in case the input of m1 is wrong
}
