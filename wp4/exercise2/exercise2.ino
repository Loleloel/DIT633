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
#define PULSE_DELAY 3 // 3 ms to allow the stepper motor to move

FspTimer g_timer;

/* To allow the highest precision, we use half-steps by
 * toggling between one and two phases, giving us a total of
 * 4096 steps to rotate the motor 360 degrees. */
const int g_servoStepTable[8][4] = {
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
volatile bool g_shouldStepMotor = false;
unsigned long g_lastStep;
uint8_t g_pulseCounter;

// helper function to step motor the equivalent distance to one second on a clock
void stepMotor() {
  uint8_t currentStep, pulseCounter = 0;
  unsigned long now;

  while (pulseCounter < STEPS_PER_SECOND) {
    if ((now = millis()) - g_lastStep >= PULSE_DELAY) {
      currentStep = pulseCounter % 8; // get the current step in the stepTable to use

      // send the pulse to the stepper motor on the four phases
      digitalWrite(PIN_SERVO_1, g_servoStepTable[currentStep][0]);
      digitalWrite(PIN_SERVO_2, g_servoStepTable[currentStep][1]);
      digitalWrite(PIN_SERVO_3, g_servoStepTable[currentStep][2]);
      digitalWrite(PIN_SERVO_4, g_servoStepTable[currentStep][3]);

      // increment the pulse counter
      pulseCounter++;
      g_lastStep = now;
    }
  }

  digitalWrite(PIN_SERVO_1, LOW);
  digitalWrite(PIN_SERVO_2, LOW);
  digitalWrite(PIN_SERVO_3, LOW);
  digitalWrite(PIN_SERVO_4, LOW);
}

// Callback function used with interrupt, only reads the temperature sensor at
// specific intervals.
void timerCallback(timer_callback_args_t __attribute((unused)) *p_args) {
  g_shouldStepMotor = true;
}

// Function to start a timer to handle interrupts
bool beginTimer() {
  // Force the use of a PWM timer reserved by the system
  FspTimer::force_use_of_pwm_reserved_timer();

  // init the timer
  if (!g_timer.begin(TIMER_MODE_PERIODIC, GPT_TIMER, 0, TIMER_FREQUENCY, 0.0f, timerCallback)) return false;
  // allow the interrupt to trigger when overflow occurs
  if (!g_timer.setup_overflow_irq()) return false;
  // open and start the timer
  if (!g_timer.open()) return false;
  if (!g_timer.start()) return false;
  
  return true;
}

// setup function
void setup(void) {
  Serial.begin(9600);
  g_lastStep = millis();
  g_pulseCounter = 0;

  // Set the pinModes of the servo pins to OUTPUT
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
void loop(void) {
  // if interrupt told to move stepper motor, enter if-block
  uint8_t currentStep;
  unsigned long now = millis();

  if (g_shouldStepMotor && (now  - g_lastStep >= PULSE_DELAY)) {
    currentStep = g_pulseCounter % 8; // get the current step in the stepTable to use

    // send the pulse to the stepper motor on the four phases
    digitalWrite(PIN_SERVO_4, g_servoStepTable[currentStep][0]);
    digitalWrite(PIN_SERVO_3, g_servoStepTable[currentStep][1]);
    digitalWrite(PIN_SERVO_2, g_servoStepTable[currentStep][2]);
    digitalWrite(PIN_SERVO_1, g_servoStepTable[currentStep][3]);

    // increment the pulse counter
    g_lastStep = now;
    g_shouldStepMotor = ++g_pulseCounter < STEPS_PER_SECOND;
  } else if (g_pulseCounter == STEPS_PER_SECOND){
    digitalWrite(PIN_SERVO_1, LOW);
    digitalWrite(PIN_SERVO_2, LOW);
    digitalWrite(PIN_SERVO_3, LOW);
    digitalWrite(PIN_SERVO_4, LOW);
    g_pulseCounter = 0;
  }

}
