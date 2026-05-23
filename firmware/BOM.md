# ULTRAFLOAT: Complete Bill of Materials (BOM)

This document provides a breakdown of all core components, hardware modules, and physical pricing metrics required to reproduce the ULTRAFLOAT system prototype.

---

## 🛒 Budget Summary & Itemized Component List

The cumulative prototype expense caps out around **3,610 BDT** (roughly under $33 USD)[cite: 1]. This structural baseline presents an incredibly rich feature map at a highly accessible price point[cite: 1].

| Item No. | Component Description | Target Quantity | Unit Cost (BDT) | Extended Total Cost (BDT) |
| :--- | :--- | :--- | :--- | :--- |
| 1 | ESP32-S3 Microcontroller Unit (240MHz Twin-Core MCU) | 1 | 850 | 850[cite: 1] |
| 2 | JSN-SR04M Waterproof Ultrasonic Sensor Module | 1 | 650 | 650[cite: 1] |
| 3 | AHT20 Calibrated Temperature & Humidity Sensor | 1 | 250 | 250[cite: 1] |
| 4 | 0.96" I2C OLED Display Module (SSD1306 Layout) | 1 | 220 | 220[cite: 1] |
| 5 | RGB Visual Notification LEDs | 2 | 5 | 10[cite: 1] |
| 6 | Passive Frequency Warning Buzzer | 1 | 30 | 30[cite: 1] |
| 7 | 5V Low-Level Relay Module (Pump Isolation Interface) | 1 | 120 | 120[cite: 1] |
| 8 | AMS1117-5.0 LDO Linear Voltage Regulator | 2 | 20 | 40[cite: 1] |
| 9 | RJ45 PCB-Mount Female Jacks | 2 | 60 | 120[cite: 1] |
| 10 | Standard CAT5/CAT5e Twisted-Pair Ethernet Cable (3m) | 1 | 150 | 150[cite: 1] |
| 11 | Discrete SMPS Component Kit (Capacitors, Inductors, ICs) | 1 | Bundle | 380[cite: 1] |
| 12 | Custom Switched-Mode Power Supply PCB Fabrication | 1 | 300 | 300[cite: 1] |
| 13 | High-Quality Prototyping Stripboard/Veroboard | 2 | 60 | 120[cite: 1] |
| 14 | Manual Override Push Button Tactile Switch | 1 | 20 | 20[cite: 1] |
| 15 | Structural Enclosure Shell Housings (Custom Enclosure Box) | 1 | 350 | 350[cite: 1] |
| 16 | Miscellaneous Workshop Assets (Solder, Wiring Harnesses) | 1 | Bundle | 200[cite: 1] |
| **-** | **Total Project Bill of Materials Cost** | **-** | **-** | **3,610 BDT**[cite: 1] |

---

## ⚙️ Hardware Environment Constraints & Engineering Code Notes

- **Linear vs. Switching Regulators at the Tank:** The remote sensor array maps its 12V down using a smooth **AMS1117 linear chip** rather than a secondary switching unit[cite: 1]. This eliminates high-frequency noise ripple variations, providing maximum signal read accuracy[cite: 1].
- **Cable Link Transmission Safety:** Using standard Ethernet wires protects signal integrity across distance runs through tight matching lines, and handles combined I2C, UART, and 12V power paths effortlessly[cite: 1].
- **Software Dependencies:** All backend scripts use open-source modules (`ESPAsyncWebServer`, `ArduinoJson`, and `Adafruit` drivers) meaning there are zero ongoing software tool licensing fees required[cite: 1].
