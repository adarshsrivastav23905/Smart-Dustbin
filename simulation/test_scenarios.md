# Virtual Simulation Test Scenarios (Wokwi / Tinkercad)

This document contains step-by-step procedures to validate all functional states of the Smart Dustbin embedded system virtually without physical hardware.

---

## Pre-Simulation Checklist
1. Open the project in Wokwi (using `diagram.json` and `src/main.cpp` or `arduino_code/smart_dustbin.ino`).
2. Open the built-in Serial Monitor (set to 9600 Baud).
3. Hit the **Start Simulation** (Green Play) button.

---

## Scenario 1: Initial Boot & Idle / Normal State
* **User Action**: Do not interact with sensor sliders.
* **Hand Sensor Slider (`handSensor`)**: Set to `50 cm` (> 20 cm threshold).
* **Level Sensor Slider (`levelSensor`)**: Set to `30 cm` (Empty bin distance).
* **Observed System Reaction**:
  - Servo horn angle: $10^\circ$ (Lid CLOSED).
  - Green LED: **ON (LIT)**.
  - Red LED: **OFF**.
  - Buzzer: **SILENT**.
  - Serial Log: `[TELEMETRY] Hand: 50.0 cm | Waste Depth: 30.0 cm | Fill: 0% | Lid: CLOSED | Status: NORMAL (READY)`

---

## Scenario 2: Touchless Hand Proximity & Automatic Lid Actuation
* **User Action**: Click the `handSensor` part and adjust the distance slider to `12 cm` (within $\le 20\text{ cm}$).
* **Observed System Reaction**:
  - Servo horn rotates immediately from $10^\circ \to 100^\circ$ (Lid OPEN).
  - Serial Log shows `Lid: OPEN`.
  - Leave hand slider undisturbed: After $3000\text{ ms}$ (3 seconds hold time), servo automatically returns to $10^\circ$ (Lid CLOSED).
  - Retest with hand slider moved back to `50 cm`. Lid remains securely CLOSED.

---

## Scenario 3: Progressive Waste Fill Monitoring (25%, 50%, 75%)
* **User Action**: Adjust the internal `levelSensor` distance slider progressively:
  - **At 24 cm**: `Fill: 25%` | Green LED ON, Red LED OFF, Buzzer OFF.
  - **At 18 cm**: `Fill: 50%` | Green LED ON, Red LED OFF, Buzzer OFF.
  - **At 12 cm**: `Fill: 75%` | Green LED ON, Red LED OFF, Buzzer OFF.
* **Observed System Reaction**:
  - Lid actuation remains active and responsive to hand sensor.
  - Telemetry outputs exact calculated fill percentages.

---

## Scenario 4: Critical Full-Bin Threshold & Emergency Safety Interlock
* **User Action**: Set `levelSensor` to `8.0 cm` (Calculated fill level = $\ge 90\%$).
* **Observed System Reaction**:
  - System enters `CRITICAL (FULL)` state.
  - Green LED switches **OFF**.
  - Red LED switches **ON (LIT)**.
  - Buzzer emits periodic audible alarm beeps (100ms chirp every 2 seconds).
  - **Safety Interlock Test**: Now move `handSensor` to `5 cm` (hand approaching).
  - **Verification**: Servo **DOES NOT OPEN** and stays locked at $10^\circ$ (Lid CLOSED) to prevent overflowing.

---

## Scenario 5: Bin Emptied / Waste Cleared Event
* **User Action**: Reset `levelSensor` distance back to `30 cm`.
* **Observed System Reaction**:
  - System automatically recovers to `NORMAL (READY)`.
  - Red LED turns OFF, Green LED turns ON.
  - Buzzer stops immediately.
  - Hand proximity actuation is re-enabled.
