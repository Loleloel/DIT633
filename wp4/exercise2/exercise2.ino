// File: exercise2.ino

/* 
 * WP4 - Exercise 2
 * John Dickson, Oliver Hansson, Sebastian Vingård Larsson
 * 2026-02-24
 * group: 27
 * Submission code: 
 */

#include "FspTimer.h"

#define PIN_SERVO_1 11
#define PIN_SERVO_2 10
#define PIN_SERVO_3 9
#define PIN_SERVO_4 8

#define TIMER_FREQUENCY 1.0f // 1.0Hz == 1s
#define STEPS_PER_SECOND 68 // to be exact, I'd need 68.2666666... steps to have the steps be accurate to the seconds

#define BIT(n) (1U << (n))

FspTimer g_timer;

/* To allow the highest precision, we use half-steps by
 * toggling between one and two phases, giving us a total of
 * 4096 steps to rotate the motor 360 degrees. */
int g_servoStepTable[8][4] = {
  // PIN_SERVO_1 - PIN_SERVO_2 - PIN_SERVO_3 - PIN_SERVO_4
  {  HIGH,         LOW,          LOW,          LOW },  // Step 1
  {  HIGH,         HIGH,         LOW,          LOW },  // Step 2
  {  LOW,          HIGH,         LOW,          LOW },  // Step 3
  {  LOW,          HIGH,         HIGH,         LOW },  // Step 4
  {  LOW,          LOW,          HIGH,         LOW },  // Step 5
  {  LOW,          LOW,          HIGH,         HIGH }, // Step 6
  {  LOW,          LOW,          LOW,          HIGH }, // Step 7
  {  HIGH,         LOW,          LOW,          HIGH }  // Step 8
};

// Callback function used with interrupt, only reads the temperature sensor at
// specific intervals.
void timerCallback(timer_callback_args_t __attribute((unused)) *p_args) {
  for (int i = STEPS_PER_SECOND; i >= 0; --i) {
    uint8_t currentStep = i % 8;

    digitalWrite(PIN_SERVO_1, g_servoStepTable[currentStep][0]);
    digitalWrite(PIN_SERVO_2, g_servoStepTable[currentStep][1]);
    digitalWrite(PIN_SERVO_3, g_servoStepTable[currentStep][2]);
    digitalWrite(PIN_SERVO_4, g_servoStepTable[currentStep][3]);

    delay(3); // TODO: swap delay for something that doesn't lock
  }

  // R_PORT4->PODR &= ~BIT(11);
  // R_PORT1->PODR &= ~BIT(3);
  // R_PORT3->PODR &= (~BIT(3) | ~BIT(4));
  digitalWrite(PIN_SERVO_1, LOW);
  digitalWrite(PIN_SERVO_2, LOW);
  digitalWrite(PIN_SERVO_3, LOW);
  digitalWrite(PIN_SERVO_4, LOW);
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

  // Set the pinModes of the servo pins to OUTPUT
  // R_PORT4->PDR |= BIT(11); // PIN_SERVO_1
  // R_PORT1->PDR |= BIT(3);  // PIN_SERVO_2
  // R_PORT3->PDR |= (BIT(3) | BIT(4));  // PIN_SERVO_3 and PIN_SERVO_4
  pinMode(PIN_SERVO_1, OUTPUT);
  pinMode(PIN_SERVO_2, OUTPUT);
  pinMode(PIN_SERVO_3, OUTPUT);
  pinMode(PIN_SERVO_4, OUTPUT);

  // start the timer with an interrupt frequency of 0.5 Hz (once every 2 seconds)
  // as the DHT11 temperature sensor requires at least 2 seconds between readings
  // to allow for proper temperature and humidity data
  beginTimer();
}

// main program loop
void loop(void) {}
