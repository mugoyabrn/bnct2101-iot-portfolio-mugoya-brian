DHT11:
- VCC → 3.3V
- DATA → GPIO4
- GND → GND

LED1 (Temperature) - Red:
- Anode → GPIO13 → 220Ω → 3.3V
- Cathode → GND

LED2 (Humidity) - Blue:
- Anode → GPIO12 → 220Ω → 3.3V
- Cathode → GND

Button:
- One side → GPIO14
- Other side → 3.3V
- Add 10kΩ pull-down resistor between GPIO14 and GND

Buzzer:
- Positive → GPIO27
- Negative → GND
