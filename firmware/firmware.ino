#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_AHTX0.h>
#include <Preferences.h>
#include "config.h"
#include "web_interface.h"

// System Singletons & Hardware Interfaces
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
Adafruit_SSD1306 display(128, 64, &Wire, -1);
Adafruit_AHT10 aht;
Preferences preferences;

// Runtime Calibration Boundaries (Stored in NVS)
float d_empty = 200.0; 
float d_full = 30.0;   

// Global System Variables
float currentDistance = 0.0;
float waterLevelPercent = 0.0;
float currentTemp = 25.0;
float currentHum = 50.0;
bool pumpState = false;

// Non-blocking loop trackers
unsigned long lastSensorPoll = 0;
const long pollInterval = 1000; 

void setup() {
  Serial.begin(115200);
  
  // Initialize Hardware I2C Bus using configured pins
  Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);[cite: 1]
  
  // Initialize UART Serial1 for JSN-SR04M
  Serial1.begin(9600, SERIAL_8N1, ULTRASONIC_RX_PIN, ULTRASONIC_TX_PIN);[cite: 1]
  
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(MANUAL_BUTTON_PIN, INPUT_PULLUP);
  digitalWrite(RELAY_PIN, LOW);
  
  // Initialize Local Hardware OLED Display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("OLED SSD1306 allocation failed."));
  }
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0,0);
  display.println("ULTRAFLOAT Booting...");
  display.display();
  
  // Initialize AHT20 Sensor Module over shared I2C bus
  if (!aht.begin()) {
    Serial.println("Could not find a valid AHT20 sensor!");[cite: 1]
  }

  // Load persistent configurations from NVS
  preferences.begin("ultrafloat", false);[cite: 1]
  d_empty = preferences.getFloat("empty", 200.0);
  d_full = preferences.getFloat("full", 30.0);
  
  setupWiFi();
  setupWebServer();
}

void loop() {
  ws.cleanupClients();
  unsigned long currentMillis = millis();
  
  // Entire tracking schedule operates on non-blocking loops
  if (currentMillis - lastSensorPoll >= pollInterval) {
    lastSensorPoll = currentMillis;
    executeMonitoringSequence();
  }
}

void executeMonitoringSequence() {
  // Fetch real-time localized metrics from AHT20
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);
  currentTemp = temp.temperature;       // Real degrees Celsius from tank env[cite: 1]
  currentHum = humidity.relative_humidity; // Real % Relative Humidity[cite: 1]

  // Dynamic Acoustic Velocity Temperature Compensation Step
  float calculatedSpeedOfSound = 331.3 + (0.606 * currentTemp); // m/s[cite: 1]
  
  // Fetch raw time of flight from JSN-SR04M via UART
  long rawTimeOfFlight = readJSNSR04M(); 
  
  if(rawTimeOfFlight > 0) {
    // Process distance parsing out round trip echo paths
    currentDistance = (calculatedSpeedOfSound * (rawTimeOfFlight / 1000000.0) / 2.0) * 100.0; // cm[cite: 1]
    
    // Compute current volumetric footprint allocation percentage
    waterLevelPercent = ((d_empty - currentDistance) / (d_empty - d_full)) * 100.0;[cite: 1]
    if(waterLevelPercent > 100) waterLevelPercent = 100;
    if(waterLevelPercent < 0) waterLevelPercent = 0;
    
    // Automated Finite State Machine Process Controls
    if (waterLevelPercent <= LEVEL_AUTO_ON) {
      pumpState = true;   // Low limit hit -> turn pump ON[cite: 1]
    } else if (waterLevelPercent >= LEVEL_AUTO_OFF) {
      pumpState = false;  // High limit hit -> turn pump OFF[cite: 1]
    }
    
    // Absolute Hardware Safety Overflow Protection Cutoff
    if (currentDistance <= d_full) {
      pumpState = false;  // Forced physical safety override to stop flooding[cite: 1]
    }
    
    digitalWrite(RELAY_PIN, pumpState ? HIGH : LOW);
    updateLocalOLED();
    broadcastTelemetry();
  }
}

long readJSNSR04M() {
  if (Serial1.available() >= 4) {
    uint8_t data[4];
    for (int i = 0; i < 4; i++) data[i] = Serial1.read();[cite: 1]
    if (data[0] == 0xFF) {
      int distanceSum = (data[1] << 8) + data[2];[cite: 1]
      return distanceSum * 58.2; // Convert raw reading to microseconds
    }
  }
  return -1;
}

void setupWiFi() {
  WiFi.begin("YOUR_WIFI_SSID", "YOUR_WIFI_PASSWORD"); // Change these when ready!
  while (WiFi.status() != WL_CONNECTED) { 
    delay(100); 
  }
}

void setupWebServer() {
  ws.onEvent(onWsEvent);
  server.addHandler(&ws);
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", HTML_DASHBOARD);[cite: 1]
  });
  server.begin();[cite: 1]
}

void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  if (type == WS_EVT_DATA) {
    AwsFrameInfo *info = (AwsFrameInfo*)arg;
    if (info->final && info->index == 0 && info->len == len && info->opcode == WS_OPTEXT) {
      data[len] = 0;
      StaticJsonDocument<128> doc;
      deserializeJson(doc, (char*)data);
      if (!doc.isNull()) {
        if (doc.containsKey("empty")) d_empty = doc["empty"];
        if (doc.containsKey("full")) d_full = doc["full"];
        
        // Save runtime calibrations permanently to flash storage
        preferences.putFloat("empty", d_empty);
        preferences.putFloat("full", d_full);
      }
    }
  }
}

void updateLocalOLED() {
  display.clearDisplay();
  display.setCursor(0,0);
  display.printf("ULTRAFLOAT SYSTEM\n");
  display.printf("---------------------\n");
  display.printf("Water Level: %.0f%%\n", waterLevelPercent);[cite: 1]
  display.printf("Distance:    %.1f cm\n", currentDistance);[cite: 1]
  display.printf("Pump Status: %s\n", pumpState ? "RUNNING" : "STOPPED");[cite: 1]
  display.printf("Temp/Hum:    %.1fC / %.0f%%\n", currentTemp, currentHum);[cite: 1]
  display.display();
}

void broadcastTelemetry() {
  StaticJsonDocument<200> jsonPayload;
  jsonPayload["level"] = round(waterLevelPercent);
  jsonPayload["distance"] = round(currentDistance * 10) / 10;
  jsonPayload["pump"] = pumpState;
  jsonPayload["temp"] = round(currentTemp * 10) / 10;
  jsonPayload["humidity"] = round(currentHum * 10) / 10;
  
  String buffer;
  serializeJson(jsonPayload, buffer);
  ws.textAll(buffer); // Stream data packet directly to web clients via socket channel[cite: 1]
}
