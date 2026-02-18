/*
 * John Dickson, Oliver Hansson, Sebastian Vingård Larsson
 * Group 27
 * Submission code: I2c7C5
 * WP3 - Exercise 4 - Keyboard Scanning v2.0
 * Same keypad as exercise 3 but using Keypad.h instead of manual port stuff...
 * Rows on pins 8-11, Columns on pins 4-7
 */

// handles all the scanning and pin config
#include <Keypad.h>

// keypad has 4 rows and columns
#define NUM_ROWS 4
#define NUM_COLS 4

// normal reading order here, compared to exercise 3
// since the library handles the pins and scanning
// basically means we dont need to deal with DDRx, PORTx and PINx manually
// * = E and # = F
char keys[NUM_ROWS][NUM_COLS] = {
  {'1', '2', '3', 'A'}, // top row of keypad
  {'4', '5', '6', 'B'}, // second row
  {'7', '8', '9', 'C'}, // third row
  {'E', '0', 'F', 'D'}  // bottom row
};

// need to tell the library which pins go where, order has to match the physical keypad
byte rowPins[NUM_ROWS] = {11, 10, 9, 8}; // ROW1 is on pin 11, ROW2 on 10, etc
byte colPins[NUM_COLS] = {7, 6, 5, 4}; // COL1 is on pin 7, COL2 on 6, etc

// make a keypad object, this sets up everything internally, pin directions and all
// the makeKeymap() takes our 2D arachter array and formats it so the library understands
Keypad myKeypad = Keypad(makeKeymap(keys), rowPins, colPins, NUM_ROWS, NUM_COLS);

void setup() {
  Serial.begin(9600); 
  // nothing else needed here, library already configured the pins
}
void loop() {
  char key = myKeypad.getKey(); // does the same thing as our readKey() from ex3
  if (key) { // only print when something is actually pressed
    Serial.println(key); // send the key character to serial monitor
    delay(1000); // wait 1 second before scanning again
  }
}

