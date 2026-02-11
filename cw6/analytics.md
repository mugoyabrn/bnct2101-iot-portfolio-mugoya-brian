# CW6: ThingSpeak Analytics Report

## 1. Data Collection Summary
- **Platform:** ThingSpeak IoT Analytics
- **Channel:** Bugema IoT Smart Home (Channel ID: [YOUR_CHANNEL_ID])
- **Data Fields:** 
  - Field 1: Temperature (°C)
  - Field 2: Humidity (%)
  - Field 3: System Uptime (seconds)
- **Collection Period:** [Date Range]
- **Update Interval:** 15 seconds (ThingSpeak free tier limit)

## 2. Observed Trends

### Temperature Trends
- **Average Temperature:** [Calculate from your data]
- **Maximum Temperature:** [Highest value observed]
- **Minimum Temperature:** [Lowest value observed]
- **Pattern:** [Describe any patterns - e.g., gradual increase, stability, fluctuations]

### Humidity Trends
- **Average Humidity:** [Calculate from your data]
- **Range:** [Variation observed]
- **Correlation with Temperature:** [Describe relationship if any]

### Data Visualization Insights
From ThingSpeak charts:
1. **Time-series Analysis:** Data shows [describe pattern]
2. **Peak Detection:** Highest values occurred at [time/conditions]
3. **Stability:** System maintained [describe stability]

## 3. ThingSpeak Features Used

### a) Charts & Visualizations
- **Line Charts:** Real-time temperature and humidity trends
- **Gauges:** Current value displays
- **Histograms:** Data distribution analysis

### b) Data Export
- **CSV Export:** For further analysis in Excel/Python
- **JSON API:** Programmatic access to historical data
- **Embed Options:** Charts can be embedded in websites

### c) Alerts & Reactions
- **Tweet Alert:** Configured to tweet when temperature exceeds 30°C
- **Email Alert:** Set up for humidity below 40%
- **Webhook:** HTTP POST to custom endpoint

## 4. Suggested Improvements

### Improvement 1: Advanced Analytics with MATLAB
**Current Limitation:** Basic charts only show raw data

**Proposed Enhancement:** 
- Use ThingSpeak's built-in MATLAB analysis
- Implement predictive algorithms
- Create moving averages for smoother trends

**MATLAB Code Example:**
```matlab
% Temperature trend analysis
data = thingSpeakRead([channelID], 'Fields', [1], 'NumPoints', 100);
avgTemp = mean(data);
trend = polyfit(1:length(data), data', 1);
forecast = trend(1)*length(data) + trend(2);
