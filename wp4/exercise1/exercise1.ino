// File: exercise1.ino

/* 
 * WP4 - Exercise 1
 * John Dickson, Oliver Hansson, Sebastian Vingård Larsson
 * 2026-02-24
 * group: 27
 * Submission code: XlvS5W
 */

#include "FspTimer.h"
#include "DHT11.h"

#define PIN_LED_1 13
#define PIN_LED_2 12
#define PIN_LED_3 11
#define PIN_LED_4 10
#define PIN_LED_5 9
#define PIN_TEMP 2

// the ratio in which LEDs will turn on/off
#define TEMP_RATIO 10

#define TIMER_FREQUENCY 0.5f // 0.5Hz = 2s

FspTimer g_timer;
DHT11 dht(PIN_TEMP);
uint8_t g_tempC;
volatile uint8_t g_newTempC;

uint8_t g_ledStateTable[5][2] = {
  {PIN_LED_1, LOW}, // led 1 off
  {PIN_LED_2, LOW}, // led 2 off
  {PIN_LED_3, LOW}, // led 3 off
  {PIN_LED_4, LOW}, // led 4 off
  {PIN_LED_5, LOW}  // led 5 off
};
uint8_t g_numLEDs = sizeof(g_ledStateTable) / sizeof(g_ledStateTable[0]);

// Callback function used with interrupt, only reads the temperature sensor at
// specific intervals.
void timerCallback(timer_callback_args_t __attribute((unused)) *p_args) {
  g_newTempC = dht.readTemperature();
}

// Function to start a timer to handle interrupts
bool beginTimer() {
  // Force the use of a PWM timer reserved by the system
  FspTimer::force_use_of_pwm_reserved_timer();

  if (!g_timer.begin(TIMER_MODE_PERIODIC, GPT_TIMER, 0, TIMER_FREQUENCY, 0.0f, timerCallback)) return false;
  if (!g_timer.setup_overflow_irq()) return false;
  if (!g_timer.open()) return false;
  if (!g_timer.start()) return false;
  
  return true;
}

// setup function
void setup(void) {
  Serial.begin(9600);
  g_tempC = g_newTempC = -50; // -50 as the lowest temperature the sensor can read is -40

  // init the different pins and their modes
  pinMode(PIN_LED_1, OUTPUT);
  pinMode(PIN_LED_2, OUTPUT);
  pinMode(PIN_LED_3, OUTPUT);
  pinMode(PIN_LED_4, OUTPUT);
  pinMode(PIN_LED_5, OUTPUT);

  pinMode(PIN_TEMP, INPUT);

  // start the timer with an interrupt frequency of 0.5 Hz (once every 2 seconds)
  // as the DHT11 temperature sensor requires at least 2 seconds between readings
  // to allow for proper temperature and humidity data
  beginTimer();
}

// main program loop
void loop(void) {
  // if the two temperatures are in different parts of the ratio
  // enter the if-block
  if ((g_newTempC / TEMP_RATIO) != (g_tempC / TEMP_RATIO)) {
    g_tempC = g_newTempC; // set g_tempC to the value of g_newTempC
    Serial.print("New temperature value: ");
    Serial.print(g_tempC);
    Serial.println("°C");

    // for-loop to handle toggling the LEDs on/off
    for (uint8_t i = 0; i < g_numLEDs; i++) {
      // check each individual LED's expected state (on or off)
      uint8_t val = (i * TEMP_RATIO < g_tempC) ? HIGH : LOW;

      // if the current state isn't the same as the expected state, we
      // enter the if-block and toggle the LED on/off
      if (g_ledStateTable[i][1] != val) {
        g_ledStateTable[i][1] = val; // assign the new state to the LED in question
        digitalWrite(g_ledStateTable[i][0], g_ledStateTable[i][1]); // toggle the LED on/off
      }
    }
  }
}
