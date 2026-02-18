// File: exercise2.ino

/* wp3 - exercise 2
 * John Dickson, Oliver Hansson, Sebastian Vingård Larsson
 * 2026-02-17
 * group: 27
 * Submission code: I2c7C5 */

#include <DHT11.h>

#define LED_GREEN 13
#define LED_YELLOW 12
#define LED_RED 11
#define LIGHT_PIN A0
#define TEMP_PIN A1

// time in ms
#define READING_INTERVAL 2000 // set to 2s to allow for the temp sensor to get a proper reading

// For readability, we define a Dependency enum
enum Dependency : uint8_t {
  NORMAL = 0, // Temperature and light sensor are both within valid ranges to eachother
  HIGHER,     // Temperature is too high compared to the light sensor's % value
  LOWER       // Temperature is too low compared to the light sensor's % value
};

// Prototypes
Dependency checkDependency(int lightIntensityPercentage, float tempC);

// Global variables
DHT11 dht(TEMP_PIN);
unsigned long g_lastReading;
int g_lightReading;
int g_tempC;
Dependency g_dep;
int g_lightStateTable[3][3] = {
  {HIGH, LOW, LOW}, // Normal state
  {LOW, HIGH, LOW}, // Temp too high for dependency
  {LOW, LOW, HIGH}  // Temp too low for dependency
};

// Function to return the corresponding dependency with regards to the
// current percentage of light intensity, as well as the temperature in Celsius.
Dependency checkDependency(int lightIntensityPercentage, int tempC) {
  // First check the light percentage and enter the corresponding if-block.
  // Then check the value of the temperature to check if it is within bounds or not.
  // If the temperature is too warm, return HIGHER, if too low, return LOWER.
  if (lightIntensityPercentage < 1) {
    if (tempC > -12) return HIGHER;
  } else if (lightIntensityPercentage <= 20) {
    if (tempC <= -12) return LOWER;
    if (tempC >= 0) return HIGHER;
  } else if (lightIntensityPercentage <= 60) {
    if (tempC <= 0) return LOWER;
    if (tempC >= 20) return HIGHER;
  } else if (lightIntensityPercentage > 60) {
    if (tempC < 20) return LOWER;
  }
  
  // If the temperature is withing bounds, return NORMAL in all cases.
  return NORMAL;
}
  
// Setup function
void setup() {
  // Init the serial bus
  Serial.begin(9600);

  // Init the pins and their modes
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(TEMP_PIN, INPUT);
  pinMode(LIGHT_PIN, INPUT);
  
  // Init the last reading, and the initial dep by assigning some values to them
  g_lastReading = millis();
  g_dep = NORMAL;

  // Turn on the LEDs based on the current dependency in g_dep
  // index 0 of each g_dep index, is the value for the green LED.
  // index 1 is the value for the red LED, and index 2 is for the yellow LED.
	digitalWrite(LED_GREEN, g_lightStateTable[g_dep][0]);
	digitalWrite(LED_RED, g_lightStateTable[g_dep][1]);
	digitalWrite(LED_YELLOW, g_lightStateTable[g_dep][2]);
}

// Main program loop
void loop() {
  // Read the current millis
  unsigned long now = millis();
  int lightIntensityPercentage;

  // if the value of now subtracted with g_lastReading is greater-equal to the
  // value defined in the READING_INTERVAL, enter the if-block
  if (now - g_lastReading >= READING_INTERVAL) {
    g_lastReading = now; // Set g_lastReading to the value of the now-variable
    g_tempC = dht.readTemperature(); // read the temperature from the temp sensor
  	g_lightReading = analogRead(LIGHT_PIN); // read the raw light value from the light sensor
  	lightIntensityPercentage = map(g_lightReading, 0, 1023, 0, 100); // convert the raw value from the raw light reading to percentages between 0-100
    Dependency depCurrReading = checkDependency(lightIntensityPercentage, g_tempC); // Check the dependency of the current reading
    
    // If the dependency in d_dep is not the same as depCurrReading, enter this if-block
    if (g_dep != depCurrReading) {
      // Assign g_dep to the value of depCurrReading
      g_dep = depCurrReading;

	    // update the lights with this new state based on the new dependency value
	    digitalWrite(LED_GREEN, g_lightStateTable[g_dep][0]);
	    digitalWrite(LED_RED, g_lightStateTable[g_dep][1]);
	    digitalWrite(LED_YELLOW, g_lightStateTable[g_dep][2]);
    }
    
    Serial.print("Raw light reading: ");
    Serial.println(g_lightReading);
	  Serial.print("Light intensity %: ");
	  Serial.println(lightIntensityPercentage);
    Serial.print("Temperature: ");
    Serial.println(g_tempC);
  }
}
