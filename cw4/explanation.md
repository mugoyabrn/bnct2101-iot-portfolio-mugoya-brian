# CW4: Embedded Programming Tasks Explanation

## Task 1: Conditions (IF/ELSE) for Automation Control
### Implementation:
- **Temperature Control:** 
  - IF temp > 30°C → Red LED ON (cooling needed)
  - ELSE IF temp < 18°C → Red LED OFF (heating needed)
  - ELSE → Red LED blinks (normal range)
  
- **Humidity Control:**
  - IF humidity > 70% → Blue LED ON (dehumidify)
  - ELSE IF humidity < 30% → Blue LED OFF (humidify)
  - ELSE → Blue LED ON steady (normal)

- **Emergency Override:**
  - IF emergencyMode == true → Override all normal logic

## Task 2: Loops and Timing (Read every 2 seconds)
### Implementation:
- Used `millis()` for non-blocking timing
- `sensorInterval = 2000` milliseconds
- Checks: `if (currentTime - lastSensorRead >= sensorInterval)`
- Ensures precise 2-second intervals without blocking other operations

## Task 3: Interrupt/Event Control
### Implementation:
- Button connected to GPIO14
- Interrupt Service Routine: `toggleEmergency()`
- Trigger: RISING edge (button press)
- `IRAM_ATTR` ensures code runs from IRAM (fast)
- Toggles `emergencyMode` variable
- Buzzer sounds during emergency

## Files in this Folder:
1. `automation.ino` - Complete Arduino code
2. `explanation.md` - This documentation
3. `screenshots/` - Evidence images

## Screenshots Taken:
1. `normal-operation.png` - System in normal mode
2. `high-temp.png` - Temperature above 30°C
3. `emergency-mode.png` - Button pressed, emergency active
4. `serial-output.png` - Serial Monitor showing timing
