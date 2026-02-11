// CW6: ThingSpeak Cloud Integration
// ESP32 sends temperature/humidity to ThingSpeak via HTTP

#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

// WiFi Credentials
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// ThingSpeak Configuration
const char* thingspeak_server = "http://api.thingspeak.com";
const char* writeAPIKey = "S5VM5YBPUZD2B5AS";  // REPLACE WITH YOUR KEY
const int channelID = 1234567;  // REPLACE WITH YOUR CHANNEL ID

// DHT Sensor
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Timing
unsigned long lastUpload = 0;
const unsigned long uploadInterval = 15000;  // 15 seconds (ThingSpeak free limit)

// Simulated data (if sensor not working)
float temperature = 25.0;
float humidity = 60.0;
bool useSimulatedData = true;  // Set to false if DHT11 is working

// ============================================
// WiFi Connection
// ============================================
void connectWiFi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nWiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

// ============================================
// Read Sensor Data
// ============================================
void readSensorData() {
  if (useSimulatedData) {
    // Generate simulated data
    temperature += (random(-10, 11) / 10.0);  // -1.0 to +1.0 change
    humidity += (random(-5, 6) / 10.0);       // -0.5 to +0.5 change
    
    // Keep within bounds
    temperature = constrain(temperature, 20.0, 35.0);
    humidity = constrain(humidity, 40.0, 80.0);
    
    Serial.println("Using simulated data");
  } else {
    // Read actual DHT11
    temperature = dht.readTemperature();
    humidity = dht.readHumidity();
    
    if (isnan(temperature) || isnan(humidity)) {
      Serial.println("DHT read failed, using simulation");
      useSimulatedData = true;
      readSensorData();  // Recursive call for simulated data
      return;
    }
  }
  
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print("°C, Humidity: ");
  Serial.print(humidity);
  Serial.println("%");
}

// ============================================
// Upload Data to ThingSpeak
// ============================================
void uploadToThingSpeak() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected. Reconnecting...");
    connectWiFi();
    return;
  }
  
  HTTPClient http;
  
  // Construct URL
  String url = String(thingspeak_server) + "/update";
  url += "?api_key=" + String(writeAPIKey);
  url += "&field1=" + String(temperature, 2);
  url += "&field2=" + String(humidity, 2);
  url += "&field3=" + String(millis() / 1000);  // Uptime in seconds
  
  Serial.print("Uploading to ThingSpeak... ");
  Serial.println(url);
  
  // Make HTTP GET request
  http.begin(url);
  int httpCode = http.GET();
  
  if (httpCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpCode);
    
    if (httpCode == HTTP_CODE_OK) {
      String response = http.getString();
      Serial.print("ThingSpeak Response: ");
      Serial.println(response);
      
      if (response.toInt() > 0) {
        Serial.println("✓ Data uploaded successfully!");
      } else {
        Serial.println("✗ Upload failed (check API key)");
      }
    }
  } else {
    Serial.print("HTTP Error: ");
    Serial.println(http.errorToString(httpCode));
  }
  
  http.end();
  Serial.println("------------------------");
}

// ============================================
// SETUP
// ============================================
void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("\n=======================================");
  Serial.println("CW6: ThingSpeak Cloud Integration");
  Serial.println("Bugema University - BNCT 2101");
  Serial.println("=======================================");
  
  // Initialize DHT
  dht.begin();
  
  // Connect WiFi
  connectWiFi();
  
  // Display configuration
  Serial.println("\nConfiguration:");
  Serial.print("ThingSpeak Channel ID: ");
  Serial.println(channelID);
  Serial.print("Update Interval: ");
  Serial.print(uploadInterval / 1000);
  Serial.println(" seconds");
  Serial.print("Using ");
  Serial.println(useSimulatedData ? "Simulated Data" : "DHT11 Sensor");
  Serial.println("=======================================\n");
}

// ============================================
// MAIN LOOP
// ============================================
void loop() {
  // Read sensor data
  readSensorData();
  
  // Upload to ThingSpeak every 15 seconds
  unsigned long currentTime = millis();
  if (currentTime - lastUpload >= uploadInterval) {
    lastUpload = currentTime;
    
    Serial.print("\n[Time: ");
    Serial.print(currentTime / 1000);
    Serial.println("s]");
    
    uploadToThingSpeak();
  }
  
  delay(1000);  // Check every second
}
