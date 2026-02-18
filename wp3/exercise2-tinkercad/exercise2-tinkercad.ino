// File: exercise2-tinkercad.ino

/* wp3 - exercise 2
 * John Dickson, Oliver Hansson, Sebastian Vingård Larsson
 * 2026-02-17
 * group: 27
 * Submission code: I2c7C5 */

#define LED_RED 11
#define LED_YELLOW 12
#define LED_GREEN 13
#define TEMP_PIN A0
#define LIGHT_PIN A1

// time in ms
#define READING_INTERVAL 1000

// For readability, we define a Dependency enum
enum Dependency : uint8_t {
  NORMAL = 0,
  HIGHER,
  LOWER
};

// prototypes
float convertVToDegC(int rawTempReading);
Dependency checkDependency(int lightIntensityPercentage, float tempC);

// global variables
int g_tempReading;
int g_lightReading;
int g_lastReading;
int g_lightIntensityPercentage;
float g_tempC;
Dependency g_dep;
int g_lightStateTable[3][3] = {
  {HIGH, LOW, LOW}, // Normal state
  {LOW, HIGH, LOW}, // Temp too high for dependency
  {LOW, LOW, HIGH}  // Temp too low for dependency
};

// function to convert the rawTempReading into degrees C
float convertVToDegC(int rawTempReading) {
  return (((rawTempReading * 5.0) / 1023) - 0.5) * 100;
}

// return the corresponding dependency based on the current temp in
// degrees C compared to the lightIntensityPercentage
Dependency checkDependency(int lightIntensityPercentage, float tempC) {
  if (lightIntensityPercentage < 1) {
    if (tempC >= -12) return HIGHER;
  } else if (lightIntensityPercentage <= 20) {
    if (tempC < -12) return LOWER;
    if (tempC > 0) return HIGHER;
  } else if (lightIntensityPercentage <= 60) {
    if (tempC < 0) return LOWER;
    if (tempC > 20) return HIGHER;
  } else if (lightIntensityPercentage > 60) {
    if (tempC < 21) return LOWER;
  }
  
  return NORMAL;
}
  
// setup function
void setup()
{
  // init serial bus
  Serial.begin(115200);
  
  // init pins and their modes
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(TEMP_PIN, INPUT);
  pinMode(LIGHT_PIN, INPUT);
  
  // init the g_lastReading var with the current time in millis
  g_lastReading = millis();
}

// main program loop
void loop() {
  unsigned long now = millis();

  // if the time since last reading is greater-equal the pre-defined
  // READING_INTERVAL, enter if-block
  if (now - g_lastReading >= READING_INTERVAL) {
    g_lastReading = now;
  	g_tempReading = analogRead(TEMP_PIN);
  	g_lightReading = analogRead(LIGHT_PIN);
  	g_lightIntensityPercentage = map(g_lightReading, 0, 706, 0, 100);
  	g_tempC = convertVToDegC(g_tempReading);
    Dependency depCurrReading = checkDependency(g_lightIntensityPercentage, g_tempC);
    
    // if the new dependency is different from the old one, enter if-block
    if (g_dep != depCurrReading) {
      g_dep = depCurrReading;
	  digitalWrite(LED_GREEN, g_lightStateTable[g_dep][0]);
	  digitalWrite(LED_RED, g_lightStateTable[g_dep][1]);
	  digitalWrite(LED_YELLOW, g_lightStateTable[g_dep][2]);
    }
    
    Serial.println(g_lightReading);
	Serial.println(g_lightIntensityPercentage);
    Serial.println(g_tempC);
  }
  
}
