// File: exercise2_tinkerCAD.ino

/* 
 * WP4 - Exercise 2
 * John Dickson, Oliver Hansson, Sebastian Vingård Larsson
 * 2026-02-24
 * group: 27
 * Submission code: XlvS5W
 */
#define PIN_SERVO 5

// Timer config for 1-second interrupts
#define CLOCK_SPEED 16000000
#define PRESCALER 1024
#define INTERRUPT_FREQ 1

// volatile because these are shared between ISR and loop()
// so they can change,
// seconds is the time that has paased and newSecond is a flag so we know that
// a second has passed (helps keep isr minimal)
volatile unsigned int seconds = 0;
volatile bool newSecond = false;

// Servo pulse width: 544 = 0°, 2400 = 180°
int currentPulseWidth = 544;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_SERVO, OUTPUT);

  // --- Timer1 setup (CTC mode, 1Hz) ---
  cli(); // disable interrupts during config

  TCCR1A = 0; // clear control registers
  TCCR1B = 0;
  TCNT1  = 0; // reset counter

  // 16MHz / (1 * 1024) - 1 = 15624 ticks = exactly 1 second
  OCR1A = (CLOCK_SPEED / (INTERRUPT_FREQ * PRESCALER)) - 1;

  TCCR1B |= (1 << WGM12);               // CTC mode — auto-resets counter at match
  TCCR1B |= (1 << CS12) | (1 << CS10);  // prescaler 1024
  TIMSK1 |= (1 << OCIE1A);              // enable compare match interrupt

  sei(); // re-enable interrupts
}

void loop() {
  // Process new second tick — we do this here instead of ISR
  // because Serial.print uses interrupts and ISRs should stay short
  if (newSecond) {
    newSecond = false;
    seconds++;

    int pos = seconds % 60;

    // 0-29: sweep 0° to 180°, 30-59: sweep 180° back to 0°
    // Full pendulum cycle every 60 seconds
    if (pos < 30) {
      currentPulseWidth = map(pos, 0, 29, 544, 2400); //left
    } else {
      currentPulseWidth = map(pos, 30, 59, 2400, 544); // right
    }

    // Print time to serial
    Serial.print("Time: ");
    Serial.print(seconds);
    Serial.println("s");
  }

  // Servo needs a pulse every 20ish ms to hold position
  digitalWrite(PIN_SERVO, HIGH);
  delayMicroseconds(currentPulseWidth);
  digitalWrite(PIN_SERVO, LOW);
  delay(20 - (currentPulseWidth / 1000));
}

// Fires every 1 second — just set a flag, keep it minimal
ISR(TIMER1_COMPA_vect) {
  newSecond = true;
}
