// File: exercise1.ino

/* wp3 - exercise 1
 * John Dickson, Oliver Hansson, Sebastian Vingård Larsson
 * 2026-02-17
 * group: 27
 * Submission code: I2c7C5 */

#define LED_RED 13
#define LED_BLUE 12
#define BUTTON 0

// global variables
unsigned long lastBlink;
int ledRedOn = 0;

// Setup funcion
void setup() {
    // init pins and their modes
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_BLUE, OUTPUT);
    pinMode(BUTTON, INPUT_PULLUP);
  
    // init the lastBlink var with the current time in millis()
    lastBlink = millis();
}

// main program loop
void loop() {
    const unsigned long interval = 1000; // 1 second in ms
	unsigned long now = millis(); // grab the current time in millis

    // if the current time subtracted by the value of lastBlink is greater-equal to 
    // the value of interval, enter the if-block
  	if (now - lastBlink >= interval) {
  	    // if the red LED is NOT on, turn it on
    	if (!ledRedOn) {
    		digitalWrite(LED_RED, HIGH);
        } else { // otherwise, turn it off
          	digitalWrite(LED_RED, LOW);
        }

        // set lastBlink to the time of now and invert the value of ledRedOn
      	lastBlink = now;
      	ledRedOn = !ledRedOn;
    }

    // if the button is pressed, enter this if-block
    if (digitalRead(BUTTON)) {
        // as the button has mode INPUT_PULLUP defined, to turn on the blue LED
        // we need to set the value to LOW
        digitalWrite(LED_BLUE, LOW);
    } else { // If the button is NOT pressed, turn off the blue LED
        digitalWrite(LED_BLUE, HIGH);
    }
}
