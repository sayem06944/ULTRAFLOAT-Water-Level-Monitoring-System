#ifndef CONFIG_H
#define CONFIG_H

// --- Hardware Pin Configurations ---
#define RELAY_PIN               4    // Digital Output to Water Pump Relay[cite: 1]
#define MANUAL_BUTTON_PIN      13    // Digital Input (PULLUP) for Manual Control[cite: 1]
#define PASV_BUZZER_PIN        41    // PWM Output for Audible Notifications[cite: 1]
#define RGB_LED_PIN            48    // Digital Output for System State LED[cite: 1]

// I2C Pins (Shared between SSD1306 OLED and AHT20 Sensor)
#define I2C_SDA_PIN            21    // Shared I2C Data Node[cite: 1]
#define I2C_SCL_PIN            22    // Shared I2C Clock Node[cite: 1]

// UART Pins for JSN-SR04M Waterproof Ultrasonic Sensor
#define ULTRASONIC_TX_PIN       1    // Microcontroller TX -> Sensor RX[cite: 1]
#define ULTRASONIC_RX_PIN       2    // Microcontroller RX -> Sensor TX[cite: 1]

// --- System Operational Thresholds ---
#define LEVEL_AUTO_ON          20    // Pump automatically starts below 20%[cite: 1]
#define LEVEL_AUTO_OFF         90    // Pump automatically stops above 90%[cite: 1]
#define OVERRIDE_HOLD_TIME   5000    // Required button hold time in milliseconds (5s)[cite: 1]

#endif
