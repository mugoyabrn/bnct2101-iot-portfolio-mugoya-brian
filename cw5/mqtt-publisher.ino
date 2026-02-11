// CW5: MQTT Publisher for Smart Home
// Publishes temperature & humidity to MQTT broker

#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

// WiFi Credentials (using public test WiFi)
const char* ssid = "Wokwi-GUEST";
const char* password = "";  // No password

// MQTT Configuration
const char* mqtt_server = "broker.hivemq.com";  // Public MQTT broker
const int mqtt_port = 1883;                     // Standard MQTT port

// Topic Structure (as required by coursework)
const char* temp_topic = "bugema/iot/temp";
const char* humidity_topic = "bugema/iot/humidity";

// DHT Sensor Simulation (since we don't have physical sensor in this setup)
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// WiFi and MQTT Clients
WiFiClient espClient;
PubSubClient client(espClient);

// Variables
unsigned long lastPublish = 0;
const unsigned long publishInterval = 5000;  // Publish every 5 seconds
float simulatedTemp = 25.0;                  // Starting temperature
float simulatedHumidity = 60.0;              // Starting humidity

// ============================================
// WiFi Connection
// ============================================
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

// ============================================
// MQTT Callback (for receiving messages)
// ============================================
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message received on topic: ");
  Serial.println(topic);
  
  Serial.print("Message: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

// ============================================
// Reconnect to MQTT Broker
// ============================================
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    
    // Create a random client ID
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected to MQTT broker!");
      Serial.print("Broker: ");
      Serial.println(mqtt_server);
      Serial.print("Topics: ");
      Serial.print(temp_topic);
      Serial.print(", ");
      Serial.println(humidity_topic);
      
      // Subscribe to topics if needed
      // client.subscribe("bugema/iot/control");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" trying again in 5 seconds");
      delay(5000);
    }
  }
}

// ============================================
// Generate Simulated Sensor Data
// ============================================
void generateSensorData() {
  // Simulate realistic temperature changes
  simulatedTemp += (random(-10, 11) / 10.0);  // Change by -1.0 to +1.0°C
  
  // Keep within reasonable bounds
  if (simulatedTemp < 15.0) simulatedTemp = 15.0;
  if (simulatedTemp > 35.0) simulatedTemp = 35.0;
  
  // Simulate humidity changes
  simulatedHumidity += (random(-5, 6) / 10.0);  // Change by -0.5 to +0.5%
  
  // Keep within reasonable bounds
  if (simulatedHumidity < 40.0) simulatedHumidity = 40.0;
  if (simulatedHumidity > 80.0) simulatedHumidity = 80.0;
}

// ============================================
// Publish Data to MQTT Topics
// ============================================
void publishData() {
  // Generate new sensor data
  generateSensorData();
  
  // Convert to strings
  char tempString[8];
  char humidString[8];
  
  dtostrf(simulatedTemp, 4, 2, tempString);
  dtostrf(simulatedHumidity, 4, 2, humidString);
  
  // Publish temperature
  if (client.publish(temp_topic, tempString)) {
    Serial.print("Published to ");
    Serial.print(temp_topic);
    Serial.print(": ");
    Serial.println(tempString);
  } else {
    Serial.println("Failed to publish temperature");
  }
  
  // Publish humidity
  if (client.publish(humidity_topic, humidString)) {
    Serial.print("Published to ");
    Serial.print(humidity_topic);
    Serial.print(": ");
    Serial.println(humidString);
  } else {
    Serial.println("Failed to publish humidity");
  }
  
  Serial.println("----------------------------");
}

// ============================================
// SETUP
// ============================================
void setup() {
  Serial.begin(115200);
  
  // Initialize DHT (for simulation)
  dht.begin();
  
  // Connect WiFi
  setup_wifi();
  
  // Configure MQTT
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  
  Serial.println("\n==================================");
  Serial.println("CW5: MQTT Publisher - Smart Home");
  Serial.println("==================================");
  Serial.println("Using Public MQTT Broker: broker.hivemq.com");
  Serial.print("Temperature Topic: ");
  Serial.println(temp_topic);
  Serial.print("Humidity Topic: ");
  Serial.println(humidity_topic);
  Serial.println("Publishing every 5 seconds...");
  Serial.println("==================================\n");
}

// ============================================
// MAIN LOOP
// ============================================
void loop() {
  // Ensure MQTT connection
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  
  // Publish data every 5 seconds
  unsigned long currentTime = millis();
  if (currentTime - lastPublish >= publishInterval) {
    lastPublish = currentTime;
    publishData();
  }
  
  delay(100);  // Small delay
}
