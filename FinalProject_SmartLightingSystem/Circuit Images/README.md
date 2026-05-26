# Task 4.1P: Handling Interrupts — Smart Lighting System

This project implements an interrupt-driven **Smart Lighting System** using an **Arduino Nano 33 IoT**. The system automatically controls home lighting based on motion and ambient light levels, while providing a manual backup switch.

---

##  System Description
The system is designed to automatically turn on porch and hallway lights when Linda enters the house, but *only* if it is dark enough to require them. 

* Automatic Mode: A PIR motion sensor detects presence, and a BH1750 light sensor verifies if the ambient light is below the threshold.
* Manual Backup: A slider switch allows Linda to bypass the sensors and turn the lights on manually if no motion is detected or if the automatic system fails.
* Efficiency: Hardware interrupts are utilized so the microcontroller responds instantly to inputs without constantly polling them in a loop.

---

##  Connection Summary

| Component | Component Pin | Arduino Nano 33 IoT Pin |
| :--- | :--- | :--- |
| **BH1750 (Light)** | VCC / GND | 3.3V / GND |
| | SDA / SCL | A4 / A5 |
| **PIR (Motion)** | VCC / GND / OUT | 3.3V / GND / **D2** (Interrupt) |
| **Slider Switch** | Middle Pin / Side Pin | **D3** (Interrupt) / GND |
| **LED 1 (Porch)** | Anode / Cathode | D11 (via Resistor) / GND |
| **LED 2 (Hallway)** | Anode / Cathode | D12 (via Resistor) / GND |

---

##  Interrupt & Decision Logic

* **Interrupt Service Routines (ISRs):** Pin `D2` (PIR) and Pin `D3` (Slider Switch) trigger lightweight ISR functions (`motionISR()` and `switchISR()`) that instantly update volatile flags. This keeps the ISRs fast and safe, leaving the heavy lifting for the main loop.
* **Light-Based Decision:** When motion is detected, the system reads the light intensity in lux from the BH1750. If the value is below the threshold, both LEDs turn on. If it is bright, the lights remain off.
* **Backup Override:** Activating the slider switch triggers an interrupt that immediately turns on both LEDs, completely bypassing the BH1750 lux threshold check.

---

##  Testing & Verification
Testing was successfully completed across three distinct phases:
1. **Sensor Calibration:** Verified changing lux values on the BH1750 by covering it and exposing it to light.
2. **Motion Isolation:** Confirmed the PIR sensor accurately flagged movement.
3. **System Integration:** Verified via the Serial Monitor that LEDs trigger on motion *only* when dark, and that the manual slider switch successfully overrides the light sensor conditions to turn the LEDs on instantly.
