#define SOIL_PIN 34
#define RELAY_PIN 26

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
}

void loop() {
  int soilValue = analogRead(SOIL_PIN);

  Serial.print("Soil Moisture: ");
  Serial.println(soilValue);

  if (soilValue > 2000) {   // DRY soil
    digitalWrite(RELAY_PIN, HIGH); // Pump ON
    Serial.println("Pump ON - Soil is dry");
  } 
  else {                   // WET soil
    digitalWrite(RELAY_PIN, LOW);  // Pump OFF
    Serial.println("Pump OFF - Soil is wet");
  }

  delay(2000);
}
