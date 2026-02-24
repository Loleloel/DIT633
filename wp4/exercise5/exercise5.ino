/*
John Dickson, Sebastian Vingård Larsson, Oliver Hansson
Group 27
WP4 - exercise 5
Submission code: XlvS5W
*/

#include "Arduino_LED_Matrix.h"

// button pin assignments — matching the tinkercad wiring
#define YELLOW_BUTTON 7
#define RED_BUTTON 8
#define GREEN_BUTTON 9

ArduinoLEDMatrix matrix;

// store previous button states so we can detect edges (press/release)
uint8_t g_lastYellow = LOW;
uint8_t g_lastRed = LOW;
uint8_t g_lastGreen = LOW;

// tracks whether green button presses should count
bool g_canIncrement = false;
// tracks whether red has already confirmed the input
bool g_inputRead = false;
// how many random numbers to generate (grows by 10 per green press)
int g_nums = 0;
byte frame[8][12] = {0};


// pointer to our dynamically allocated array — starts empty
// we allocate the right size once we know how many numbers we need
int *elements = NULL;

// brings everything back to the initial state
void resetProgram() {
  // reset all state variables
  g_nums = 0;
  g_inputRead = false;
  g_canIncrement = false;
  g_lastYellow = LOW;
  g_lastRed = LOW;
  g_lastGreen = LOW;
  memset(frame, 0, sizeof(frame));
  matrix.renderBitmap(frame, 8, 12);

  // free the array if one exists so we don't leak memory
  if (elements != NULL) {
    free(elements);
    elements = NULL;
  }
}

// handles red button logic — either enters increment mode or starts sorting
void handleButtonRed() {
  // ignore if we already read input, or if we're in increment mode with 0 numbers
  if (g_inputRead || (g_canIncrement && g_nums == 0)) return;

  // if we were incrementing, that means red is confirming — time to sort
  if (g_canIncrement) {
    g_inputRead = true;
    generateElements();  // fill array with random numbers
    sortElements();      // sort them with bubble sort
    printNumbersArray(); // display them on LCD in a loop
  }

  // flip to increment mode unless we just started sorting
  g_canIncrement = !g_inputRead;
}

// each green press adds 10 to the count and shows it on the lcd
void incrementNumbers() {
  // only count if we're in increment mode
  if (!g_canIncrement) return;

  g_nums += 10;
}

void setup() {
  matrix.begin();

  // set all button pins as inputs
  pinMode(YELLOW_BUTTON, INPUT);
  pinMode(RED_BUTTON, INPUT);
  pinMode(GREEN_BUTTON, INPUT);

  // start in the waiting state
  resetProgram();
}

void loop() {
  // read current state of each button
  uint8_t yellowNow = digitalRead(YELLOW_BUTTON);
  uint8_t redNow = digitalRead(RED_BUTTON);
  uint8_t greenNow = digitalRead(GREEN_BUTTON);

  // edge detection — only act when a button state changes
  // yellow always takes priority since it's the reset button
  if (yellowNow != g_lastYellow) {
    if (yellowNow) resetProgram(); // rising edge = button just pressed
    g_lastYellow = yellowNow;      // remember state for next loop
  } else if (redNow != g_lastRed) {
    if (redNow) handleButtonRed();
    g_lastRed = redNow;
  } else if (greenNow != g_lastGreen) {
    if (greenNow) incrementNumbers();
    g_lastGreen = greenNow;
  }
}

// fills the array with random numbers between 1 and 99
void generateElements() {
  // free old array if one exists so we don't leak memory
  if (elements != NULL) {
    free(elements);
  }

  // allocate exactly enough space for g_nums integers
  elements = (int *)malloc(g_nums * sizeof(int));

  // seed from floating analog pin so numbers differ each run
  randomSeed(analogRead(A0));

  // fill each slot with a random value
  for (int i = 0; i < g_nums; i++) {
    elements[i] = random(1, 97);
  }
}

void printNumbersArray() {
  int elementIndex = 0;

  // keep showing numbers until yellow is pressed to reset
  while (!digitalRead(YELLOW_BUTTON)) {
    
    // clear the frame to display on the LED matrix
    memset(frame, 0, sizeof(frame));

    // get the current number to display from the elements array
    int numToLight = elements[elementIndex];

    // set the individual values in frame with the correct number of LEDs
    // to be lit.
    for (int i = 0; i < numToLight; i++) {
      int row = i / 12; // row index 0 to 7
      int col = i % 12; // col index 0 to 11
      frame[row][col] = 1;
    }

    // light the LEDs on the LED matrix
    matrix.renderBitmap(frame, 8, 12);

    // move to next element if still below g_nums, else start over
    if (++elementIndex >= g_nums) {
      elementIndex = 0; 
    }

    // a 1 second delay to let the user see the LEDs
    delay(1000); 
  }
}

// sorts the array smallest to largest using bubble sort
// shows a loading animation on the lcd while working
void sortElements() {
  // outer loop — each pass locks one more number at the end
  for (int i = 0; i < g_nums - 1; i++) {
    // print a dot every 20% to show progress
    if (i % (g_nums / 5) == 0) {
      matrix.loadSequence(LEDMATRIX_ANIMATION_SPINNING_COIN);
      matrix.play(true);
      delay(500);
    }

    // inner loop — compare neighbors and swap if left is bigger
    for (int j = 0; j < g_nums - i - 1; j++) {
      if (elements[j] > elements[j + 1]) {
        // classic three-variable swap
        int temp = elements[j];
        elements[j] = elements[j + 1];
        elements[j + 1] = temp;
      }
    }
  }

  matrix.play(false);
}

