// File: exercise1_tinkerCAD.ino

/* 
 * WP4 - Exercise 1
 * John Dickson, Oliver Hansson, Sebastian Vingård Larsson
 * 2026-02-24
 * group: 27
 * Submission code: XlvS5W
 */

#define PIN_TEMP  A0

// LED pin definitions
#define PIN_LED_1 13
#define PIN_LED_2 12
#define PIN_LED_3 11
#define PIN_LED_4 10
#define PIN_LED_5  9

// TEMP_RANGE is defining the range in which
// each LED may turn on. 0C-9C, 10C-19C, 20C-29C and so on
#define TEMP_RANGE 10

// INTERRUPT_FREQ is in seconds
#define CLOCK_SPEED 16000000
#define PRESCALER 1024
#define INTERRUPT_FREQ 1

void lightLEDs();

// A table with the current state of the LEDs on the 
// breadboard, where [i][0] = the pin, and [i][1] = its current 
// state (on / off)
int g_ledStateTable[5][2] = {
  {PIN_LED_1, LOW}, // LED 1 and its current state (LOW = off)
  {PIN_LED_2, LOW}, // LED 2 and its current state (LOW = off)
  {PIN_LED_3, LOW}, // LED 3 and its current state (LOW = off)
  {PIN_LED_4, LOW}, // LED 4 and its current state (LOW = off)
  {PIN_LED_5, LOW}  // LED 5 and its current state (LOW = off)
};

// global variables
const int g_numLEDs = sizeof(g_ledStateTable) / sizeof(g_ledStateTable[0]);
int volatile g_shouldToggleLEDs = false;
int volatile g_tempC = -50; // Set value to-50 as the lowest the 
					 // temp sensor can read is -40

// setup function
void setup() {
  Serial.begin(9600);
  // init the pins and their modes
  pinMode(PIN_LED_1, OUTPUT);
  pinMode(PIN_LED_2, OUTPUT);
  pinMode(PIN_LED_3, OUTPUT);
  pinMode(PIN_LED_4, OUTPUT);
  pinMode(PIN_LED_5, OUTPUT);
  
  pinMode(PIN_TEMP, INPUT);
  
  // set up the interrupt functionality
  // to perform an interrupt once every second
  cli(); // stop interrupts
  
  TCCR1A = 0; // set TCCR1A reg to 0
  TCCR1B = 0; // set TCCR1B reg to 0
  TCNT0 =  0; // init counter to 0
  
  // IMPORTANT! Value MUST be less than 65536 for
  // timer1. Even less for timer0 and timer2.
  // Set compare match regs to 1Hz (1 second)
  OCR1A = CLOCK_SPEED / (INTERRUPT_FREQ * PRESCALER) - 1; // (16*10⁶) / (1 * 1024) - 1
    
  // Turn on CTC mode
  TCCR1B |= (1 << WGM12);
  
  // Set CS10 and CS12 bits for the 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);
  
  // Enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  
  sei(); // allow interrupts
}

// main program loop
void loop() {
  // only enter the if-block if the variable g_shouldToggleLEDs
  // value is true to ensure we don't make more function calls
  // than necessary
  if (g_shouldToggleLEDs) {
    g_shouldToggleLEDs = false;
    lightLEDs();
  }
}

// helper function to handle the lighting of the LEDs
void lightLEDs() {
  // for loop to handle the LEDs turning on and off
  for (int i = 0; i < g_numLEDs; i++) {
    // Get the current value/state an LED should have
    // where i * TEMP_RANGE gets the lower boundaries of each 
    // range (ex. 0 * 10 = 0, 1 * 10 = 10). Then checking if
    // the lower boundary is less than the temp read will
    // then tell us if we need to turn on the light, or off.
    int val = (i * TEMP_RANGE) < g_tempC ? HIGH : LOW;

    // If the current state of an LED is different from what
    // the variable val calculated, we update the corresponding
    // LED with this new state and either turn the LED on or off
    // depending on this new state.
    // We do this to avoid unnecessary assignments and writes.
    if (g_ledStateTable[i][1] != val) {
      g_ledStateTable[i][1] = val;
      digitalWrite(g_ledStateTable[i][0], g_ledStateTable[i][1]);
    }
  }
}

// Interrupt Service Routine
ISR(TIMER1_COMPA_vect) {
  cli(); // stop interrupts
  int tempReading = analogRead(PIN_TEMP);
  // since we're using integers as our ranges, we're OK with 
  // using a truncated value, hence the implicit cast in the
  // variable below
  int tempReadingInC = (((tempReading * 5.0) / 1023) - 0.5) * 100;
  
  // only if the new reading / 10 (to get the 10's) and the
  // prev temp reading which changed the LED state / 10 is not
  // equal (ex. (12 / 10) != (23 / 10) => 1 != 2 => true)
  // we assign the g_tempC variable with the value from the
  // tempReadingInC variable.
  if ((g_shouldToggleLEDs = (tempReadingInC / 10) != (g_tempC / 10))) {
    g_tempC = tempReadingInC;
  }  
  sei(); // allow interrupts
}
