Introduction
Smallholder farmers in Uganda struggle with unpredictable rainfall, poor soil monitoring, and delayed irrigation. Crops often fail due to lack of real-time data on soil moisture and temperature.

Problem Statement
Farmers currently rely on guesswork to irrigate crops, leading to water wastage or crop stress.

Proposed IoT Solution
We propose a Smart Farm IoT system using:
- ESP32 microcontroller
- Soil moisture sensor
- Temperature sensor (DHT11)
- Wi-Fi communication using MQTT
- ThingSpeak cloud platform
- Web dashboard for monitoring

System Architecture
1. Sensors collect soil moisture and temperature data.
2. ESP32 processes and sends data via Wi-Fi.
3. Data is published to MQTT broker.
4. Node-RED receives data and visualizes it.
5. ThingSpeak stores historical data for analysis.

Expected Benefits
- Reduced water wastage
- Improved crop yield
- Real-time monitoring
- Data-driven farming decisions

