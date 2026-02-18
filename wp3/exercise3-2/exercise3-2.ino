/*
 * John Dickson, Oliver Hansson, Sebastian Vingård Larsson
 * Group 27
 * Submission code: I2c7C5
 * WP3 - Exercise 3(2nd) - Keyboard Scanning
 * Rows on Port B (pins 8-11), Columns on Port D (pins 4-7)
 */

// keypad has 4 rows and colums
#define NUM_ROWS 4 
#define NUM_COLS 4

// map is flipped because ROW4 is on the lowest bit (PB0) and gets scanned first
// same thing with columns, COL4 is on PD4 so it gets read first
// the map is basically "upside down and mirrored" compared to the actual keypad
// * = E and # = F
char keys[NUM_ROWS][NUM_COLS] = {
  {'D', 'F', '0', 'E'}, //row 4 on the actual keypad
  {'C', '9', '8', '7'}, //row 3
  {'B', '6', '5', '4'}, //row 2
  {'A', '3', '2', '1'}  //row 1
};

// goes through every row and column combinaaation to find which key is pressed
char readKey() {
  int r; // row index
  int c; //column index
  
  //loop for each row one at a time
  for (r = 0; r < NUM_ROWS; r++) {
    PORTB = PORTB | 0x0F; // start by setting all rows HIGH (inactive)
    int rowBit = 1 << r; // create a bitmask for current row
    PORTB = PORTB & ~rowBit; // pull just this one row LOW so we can check its keys
    
    delayMicroseconds(50); // need a short delay for the voltage to actually change
    int colBits = PIND & 0xF0; // grab only bits 4-7 since thats where our columns are
	
    //loop for each column in each row
    for (c = 0; c < NUM_COLS; c++) {
      int colBit = 1 << (c + 4); // +4 because columns start at bit 4 not bit 0
      int isPressed = colBits & colBit; //use to "isolate" just this columns bit
      
      if (isPressed == 0) { // LOW means the key connects this row and column
        PORTB |= 0x0F; // clean up rows before returning
        return keys[r][c]; // look up what key it is and return it
      }
    }
  }
  PORTB |= 0x0F; // nothing found, reset rows
  return 0; // 0 means no key was pressed
}

// setup what's needed
// DDRx = Data Direction Register for x port, controls input/output basically
void setup() {
  Serial.begin(9600); //9600 is bits per second, must be same as arduino
  DDRB |= 0x0F; // rows need to be outputs so we can drive them LOW
  DDRD &= ~0xF0; // columns need to be inputs so we can read them
  PORTB |= 0x0F; // start with all rows HIGH
}

void loop() {
  char key = readKey(); // scan the keypad
  if (key != 0) { // only print when something is actually pressed
    Serial.println(key); //send the key to the serial monitor
    delay(1000); // wait 1 sec before scanning again
  }
}

