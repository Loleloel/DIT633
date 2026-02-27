// File: exercise1.ino

/* 
 * WP5 - Exercise 1
 * John Dickson, Oliver Hansson, Sebastian Vingård Larsson
 * 2026-03-XX
 * group: 27
 * Submission code: XXXXXX
 */

// macros
#define RED_LED 12
#define BLUE_LED 11
#define BUTTON 0

#define INTERVAL 1000 // time in ms

// global variables
unsigned long g_lastBlink;
bool g_redLedOn;
bool g_blueLedOn;

void setup() {
  // init pins and their pin modes
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP); // INPUT_PULLUP to avoid noise to mess with the signal

  // init global variables
  g_lastBlink = millis();
  g_redLedOn = g_blueLedOn = false;
}

// main program loop
void loop() {
  // get the current time in millis
  unsigned long now;

  // if the current time minus the time of last blink is larger-or-equal
  // to the defined interval, enter if-block
  if ((now = millis()) - g_lastBlink >= INTERVAL) {
    g_lastBlink = now; // set last blink to now
    digitalWrite(RED_LED, (g_redLedOn = !g_redLedOn)); // turn the red LED on/off
  }

  // if the button is pressed, turn on the blue LED, else turn it off
  digitalWrite(BLUE_LED, !digitalRead(BUTTON) ? HIGH : LOW);
}
