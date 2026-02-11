# CW5: MQTT Configuration Documentation

## MQTT Broker Details
- **Broker:** broker.hivemq.com (Public HiveMQ broker)
- **Port:** 1883 (standard MQTT)
- **Protocol:** MQTT 3.1.1

## Topics Used
1. `bugema/iot/temp` - Temperature data (float in °C)
2. `bugema/iot/humidity` - Humidity data (float in %)

## Publishing Frequency
- Every 5 seconds (5000ms)
- Simulated data with realistic variations

## Node-RED Dashboard Components
1. **Gauges:** Temperature (0-50°C) and Humidity (0-100%)
2. **Charts:** Real-time line charts for trends
3. **Text Displays:** Latest values
4. **Update Timer:** Shows last data reception time

## Testing Verification
1. ESP32 successfully connects to WiFi (Wokwi-GUEST)
2. MQTT connection established to broker.hivemq.com
3. Data published to both topics every 5 seconds
4. Node-RED receives and displays all data
