/*
 * John Dickson, Oliver Hansson, Sebastian Vingård Larsson
 * Group 27
 * Submission code: I2c7C5
 * WP3 - Exercise 3(1st) - Temperature Meter v2.0
 */

int sensorPin = A0; // TMP36 output is connected here

void setup() {
  Serial.begin(9600); // need serial to print temperature readings
}

// main loop, void no return
void loop() 
{
  int rawValue = analogRead(sensorPin); // read the 10-bit value (0-1023)
  float vOut = rawValue * (5000.0 / 1023.0); // convert to millivolts (0-5000mV range)
  float temperature = (vOut - 500.0) / 10.0; // TMP36 formula from the assignment

  Serial.print("Temperature: "); //label so its easier to read
  Serial.print(temperature); // the actual value
  Serial.println(" C"); // unit and newline

  delay(500); // check every 500ms
}

