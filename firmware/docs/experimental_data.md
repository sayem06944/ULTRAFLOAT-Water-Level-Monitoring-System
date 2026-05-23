# ULTRAFLOAT: System Validation & Experimental Performance Data

This document contains the verified laboratory datasets and benchmarking results compiled during the testing phases of the ULTRAFLOAT system.

---

## ⚡ 1. Power Supply Verification (Custom SMPS Layout)
The custom-designed Switched-Mode Power Supply (SMPS) was tested under full load using a **GW INSTEK GDS-1102B Digital Storage Oscilloscope** to analyze noise ripples and power conversion stability:

* **Target Output Profile:** 12.0V DC @ 1A[cite: 1]
* **Measured Peak Output:** 12.1V DC[cite: 1]
* **Peak-to-Peak Voltage Ripple:** 80 mV[cite: 1]
* **Measured Operational Efficiency:** 96%[cite: 1]

The exceptionally low voltage ripple (80 mV) ensures that high-frequency noise does not interfere with the analogue or digital logic lines of the co-located sensors[cite: 1].

---

## 🎯 2. Distance Ranging Accuracy Evaluation
 Ranging evaluations were executed by comparing the temperature-compensated JSN-SR04M sensor output against known reference gaps measured physically with a calibrated steel tape[cite: 1]:

| Reference Target Gap (cm) | Compensated Sensor Readout (cm) | Absolute Deviation (cm) | Logged Relative Error (%) |
| :--- | :--- | :--- | :--- |
| 20 | 20.4 | +0.4 | 2.00%[cite: 1] |
| 40 | 40.6 | +0.6 | 1.50%[cite: 1] |
| 60 | 60.5 | +0.5 | 0.83%[cite: 1] |
| 80 | 80.7 | +0.7 | 0.88%[cite: 1] |
| 100 | 100.8 | +0.8 | 0.80%[cite: 1] |

The systemic accuracy comfortably satisfies the design parameter goal of remaining well within a $\pm1$ cm maximum error envelope across standard operations[cite: 1].

---

## 🌡️ 3. Thermal Drift Mitigation Analysis
To prove the necessity of the compensation algorithm, measurements were cross-referenced at a fixed reference distance of 60 cm across varying thermal profiles[cite: 1]:

| Ambient Temperature (°C) | Corrected Speed of Sound (m/s) | Ultrafloat Reading (Compensated) (cm) | Standard Sensor Reading (Fixed 343 m/s) (cm) | Linear Error Deviation (cm) |
| :--- | :--- | :--- | :--- | :--- |
| **15°C** | 340.39 | 60.0 | 60.5 | +0.5 (Overestimation)[cite: 1] |
| **22°C** | 344.63 | 60.0 | 60.0 | 0.0 (Neutral Baseline)[cite: 1] |
| **30°C** | 349.48 | 60.0 | 59.4 | -0.6 (Underestimation)[cite: 1] |
| **36°C** | 353.12 | 60.0 | 58.8 | -1.2 (Underestimation)[cite: 1] |

### 🏭 Volumetric Risk Projections (Industrial Scalability Modeling)
In heavy industrial operations—such as power generation demineralized water storage tanks—operating with a deep 6.0-meter profile and a cross-sectional area of $50\text{ m}^2$, uncompensated acoustic tracking introduces critical hazards under thermal changes[cite: 1]:

* **At 25°C ambient:** Introduces a systematic error of 5.3 cm, leading to **2,650 Liters** of unregistered water deficit[cite: 1].
* **At 45°C ambient:** Introduces a systematic error of 25.4 cm, leading to **12,700 Liters** of completely invisible, unregistered volume loss[cite: 1].

By implementing localized, real-time recalculations based on the AHT20 data vectors, the ULTRAFLOAT system eliminates this temperature-dependent scaling drift entirely, reporting an error-free 600.0 cm depth profile regardless of weather fluctuations[cite: 1].
