/*
John Dickson, Sebastian Vingård Larsson, Oliver Hansson
Group 27
WP4 - exercise 5 - tinkerCAD version
Submission code: XlvS5W
*/

#include <LiquidCrystal.h>

// button pin assignments — matching the tinkercad wiring
#define YELLOW_BUTTON 7
#define RED_BUTTON 8
#define GREEN_BUTTON 9

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

// pointer to our dynamically allocated array — starts empty
// we allocate the right size once we know how many numbers we need
int *elements = NULL;

// lcd wired to these pins: RS=12, EN=11, D4=5, D5=4, D6=3, D7=2
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// brings everything back to the initial state
void resetProgram() {
  // reset all state variables
  g_nums = 0;
  g_inputRead = false;
  g_canIncrement = false;
  g_lastYellow = LOW;
  g_lastRed = LOW;
  g_lastGreen = LOW;

  // free the array if one exists so we don't leak memory
  if (elements != NULL) {
    free(elements);
    elements = NULL;
  }

  // show the start message
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("PRESS RED BUTTON");
}

// handles red button logic — either enters increment mode or starts sorting
void handleButtonRed() {
  // ignore if we already read input, or if we're in increment mode with 0 numbers
  if (g_inputRead || (g_canIncrement && g_nums == 0)) return;

  lcd.clear();
  lcd.setCursor(0, 0);

  // if we were incrementing, that means red is confirming — time to sort
  if (g_canIncrement) {
    g_inputRead = true;
    generateElements();  // fill array with random numbers
    sortElements();      // sort them with bubble sort
    printNumbersArray(); // display them on LCD in a loop
  } else {
    // first red press — enter increment mode
    lcd.print("INCREMENTING");
  }

  // flip to increment mode unless we just started sorting
  g_canIncrement = !g_inputRead;
}

// each green press adds 10 to the count and shows it on the lcd
void incrementNumbers() {
  // only count if we're in increment mode
  if (!g_canIncrement) return;

  g_nums += 10;

  // show current count on the second row
  lcd.setCursor(0, 1);
  lcd.print(g_nums);
}

void setup() {
  Serial.begin(9600);

  // set all button pins as inputs
  pinMode(YELLOW_BUTTON, INPUT);
  pinMode(RED_BUTTON, INPUT);
  pinMode(GREEN_BUTTON, INPUT);

  // 16 columns, 2 rows
  lcd.begin(16, 2);

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
    elements[i] = random(1, 100);
  }
}

// displays sorted numbers on the lcd one at a time
// loops back to the start after showing all of them
// exits when yellow button is pressed
void printNumbersArray() {
  int i = 0;

  // keep showing numbers until yellow is pressed to reset
  while (!digitalRead(YELLOW_BUTTON)) {
    // if we've shown all numbers or just started, show the header and loop back
    if (i == g_nums || i == 0) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("RESULT");
      i = 0;
    }

    // show current number on second row and move to the next
    lcd.setCursor(0, 1);
    lcd.print(elements[i++]);
    delay(500); // half second between each number
  }
}

// sorts the array smallest to largest using bubble sort
// shows a loading animation on the lcd while working
void sortElements() {
  lcd.print("SORTING");

  // outer loop — each pass locks one more number at the end
  for (int i = 0; i < g_nums - 1; i++) {
    // print a dot every 20% to show progress
    if (i % (g_nums / 5) == 0) {
      lcd.print(".");
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
}

//ggwp
