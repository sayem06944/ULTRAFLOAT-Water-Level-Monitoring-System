# ULTRAFLOAT: Intelligent Ultrasonic Water Level Control System 🌊📱

ULTRAFLOAT is an open-source, industrial-grade, non-contact liquid level monitoring and automated control appliance driven by the **ESP32-S3** microcontroller. 

Unlike traditional mechanical float switches—which suffer from rapid corrosion, algal jamming, and binary state limits—ULTRAFLOAT implements real-time **acoustic velocity temperature compensation** alongside an embedded WebSocket server to deliver continuous volume insights with sub-centimeter accuracy.

---

## 🚀 Key Functional Features

- **Dynamic Temperature Compensation:** Evaluates a co-located AHT20 sensor to modify velocity vectors at every polling step via $V = 331.3 + 0.606 \times T$, filtering ambient thermal measurement drift.
- **Asynchronous Loop Architecture:** Embedded C++ platform implementation relying strictly on non-blocking `millis()` event tracking to guarantee responsive WebSocket dashboard connections.
- **Persistent Local Engine Profile:** Preserves user system calibration constraints inside native microchip Non-Volatile Storage (NVS) blocks across unexpected grid failures.
- **Two-Unit Structural Distribution:** Features separate electrical zones isolating high-power elements indoors while power and data signals stream over a single standard CAT5/RJ45 connection to the tank.
- **High-Efficiency Custom SMPS Integration:** Includes a bespoke converter topology transforming 240V AC to stable 12V DC running at a validated 96% operational efficiency factor.

---

## 🛠️ System Architecture

```text
       [ 240V AC Mains Input ]
                 │
                 ▼
     ┌───────────────────────┐
     │   Custom 96% SMPS     │───( Stable 12V DC Line )───┐
     └───────────────────────┘                            │
                 │                                        ▼
                 ▼                            ┌───────────────────────┐
     ┌───────────────────────┐                │  AMS1117 Regulator    │
     │   Main Control Unit   │                └───────────────────────┘
     │      (ESP32-S3)       │                            │
     └───────────────────────┘                            ▼
        │        │        │                   ┌───────────────────────┐
        ▼        ▼        ▼                   │  Remote Sensor Unit   │
     [Relay]  [OLED]  [Buzzer]                │ (JSN-SR04M + AHT20)   │
        │                                     └───────────────────────┘
        ▼                                                 │
 [AC Water Pump]                                          ▼
                                                 [Tank Asset Target]


---

## 📌 Pin Allocation Configuration

| Functional Block Module | Peripherals Pin Target | ESP32-S3 Target Pin | System Connection Layout |
| :--- | :--- | :--- | :--- |
| **Relay System Actuator** | IN Signal Driver Pin | **GPIO 4** | Automated Pump Controller Loop |
| **Passive Warning Buzzer**| Dynamic Signal Input | **GPIO 41** | Tone Frequency Modulation Engine |
| **RGB Indicator LED** | System State Nodes | **GPIO 48** | Active Mode Status Array[cite: 1] |
| **Physical Reset Trigger** | Override Input Port | **GPIO 13** | Core System Override (5s Hold Safeguard)[cite: 1] |
| **Local Dashboard Screen**| Shared SDA Channel | **GPIO 21** | I2C High-Speed Bus Data Node[cite: 1] |
| **Local Dashboard Screen**| Shared SCL Channel | **GPIO 22** | I2C High-Speed Bus Clock Node[cite: 1] |
| **Ultrasonic Distance RX**| TX Module Line Output| **GPIO 2** | UART Hardware Serial Port Stream[cite: 1] |
| **Ultrasonic Distance TX**| RX Module Line Input | **GPIO 1** | UART Hardware Serial Port Stream[cite: 1] |

---
