// CW4: Embedded Programming - Smart Home Automation
// Combines: Conditions, Timing, and Interrupts

#include <DHT.h>

// Pin Definitions
#define DHTPIN 4
#define DHTTYPE DHT11
#define TEMP_LED_PIN 13    // Red LED for temperature
#define HUMID_LED_PIN 12   // Blue LED for humidity
#define BUTTON_PIN 14      // Emergency button
#define BUZZER_PIN 27      // Alarm buzzer

// Thresholds
#define HIGH_TEMP 30.0     // °C - trigger cooling
#define LOW_TEMP 18.0      // °C - trigger heating
#define HIGH_HUMID 70.0    // % - too humid
#define LOW_HUMID 30.0     // % - too dry

// Global Variables
DHT dht(DHTPIN, DHTTYPE);
volatile bool emergencyMode = false;  // Changed by interrupt
unsigned long lastSensorRead = 0;
const unsigned long sensorInterval = 2000;  // Read every 2 seconds

// ============================================
// TASK 3: INTERRUPT SERVICE ROUTINE
// ============================================
void IRAM_ATTR toggleEmergency() {
  emergencyMode = !emergencyMode;  // Toggle emergency mode
  digitalWrite(BUZZER_PIN, emergencyMode);  // Buzzer ON in emergency
}

void setup() {
  Serial.begin(115200);
  Serial.println("========================================");
  Serial.println("CW4: Smart Home Automation System");
  Serial.println("Combining Conditions, Timing & Interrupts");
  Serial.println("========================================");
  
  // Initialize pins
  pinMode(TEMP_LED_PIN, OUTPUT);
  pinMode(HUMID_LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLDOWN);  // Internal pull-down
  
  // Initialize DHT sensor
  dht.begin();
  
  // TASK 3: Attach interrupt to button
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), toggleEmergency, RISING);
  
  Serial.println("System Initialized");
  Serial.println("Press button to toggle Emergency Mode");
  Serial.println("----------------------------------------");
}

void loop() {
  // ============================================
  // TASK 2: TIMING - Read sensor every 2 seconds
  // ============================================
  unsigned long currentTime = millis();
  
  if (currentTime - lastSensorRead >= sensorInterval) {
    lastSensorRead = currentTime;
    
    // Read sensor data
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();
    
    // Check if readings are valid
    if (isnan(temperature) || isnan(humidity)) {
      Serial.println("Error: Failed to read from DHT sensor!");
      return;
    }
    
    // Display readings
    Serial.print("Time: ");
    Serial.print(currentTime / 1000);
    Serial.print("s | Temp: ");
    Serial.print(temperature);
    Serial.print("°C | Humidity: ");
    Serial.print(humidity);
    Serial.print("% | Emergency: ");
    Serial.println(emergencyMode ? "ON" : "OFF");
    
    // ============================================
    // TASK 1: CONDITIONAL LOGIC (IF/ELSE)
    // ============================================
    
    // EMERGENCY MODE OVERRIDE (Highest Priority)
    if (emergencyMode) {
      digitalWrite(TEMP_LED_PIN, HIGH);    // Both LEDs ON
      digitalWrite(HUMID_LED_PIN, HIGH);
      Serial.println("  ALERT: Emergency Mode Active!");
      return;  // Skip normal automation
    }
    
    // NORMAL AUTOMATION MODE
    
    // Temperature Control Logic
    if (temperature > HIGH_TEMP) {
      digitalWrite(TEMP_LED_PIN, HIGH);    // LED ON - Too hot
      Serial.println("  Action: Temperature HIGH - Cooling needed");
    } 
    else if (temperature < LOW_TEMP) {
      digitalWrite(TEMP_LED_PIN, LOW);     // LED OFF - Too cold
      Serial.println("  Action: Temperature LOW - Heating needed");
    } 
    else {
      // Blink LED for normal temperature range
      digitalWrite(TEMP_LED_PIN, !digitalRead(TEMP_LED_PIN));
      Serial.println("  Status: Temperature NORMAL");
    }
    
    // Humidity Control Logic
    if (humidity > HIGH_HUMID) {
      digitalWrite(HUMID_LED_PIN, HIGH);   // LED ON - Too humid
      Serial.println("  Action: Humidity HIGH - Dehumidify needed");
    } 
    else if (humidity < LOW_HUMID) {
      digitalWrite(HUMID_LED_PIN, LOW);    // LED OFF - Too dry
      Serial.println("  Action: Humidity LOW - Humidify needed");
    } 
    else {
      // Steady ON for normal humidity
      digitalWrite(HUMID_LED_PIN, HIGH);
      Serial.println("  Status: Humidity NORMAL");
    }
    
    Serial.println("----------------------------------------");
  }
  
  // Small delay to prevent watchdog timer issues
  delay(10);
}

// ============================================
// ADDITIONAL TASK: POLLING EXPLANATION
// (Alternative to Interrupts)
// ============================================
/*
POLLING METHOD vs INTERRUPTS:

POLLING (What we're NOT using here):
void checkButton() {
  if (digitalRead(BUTTON_PIN) == HIGH) {
    emergencyMode = !emergencyMode;
    delay(50);  // Debounce
  }
}
// Called repeatedly in loop()

INTERRUPT (What we ARE using):
- Immediate response to button press
- Doesn't wait for loop() cycle
- More efficient for quick events
- Better for battery-powered devices
*/
