# 📸 Project Visual Evidence & Screenshot Checklist

This directory contains visual validation evidence captured during virtual simulation on **Wokwi** and **Tinkercad Circuits**.

---

## 📋 Screenshot Catalog & Verification Matrix

| Filename | Description | Operational State | Expected Sensor Input | Expected Hardware Output |
|---|---|---|---|---|
| `01_project_structure.png` | Repository folder layout in VS Code | File System Setup | N/A | All directories and source files present |
| `02_circuit_diagram.png` | Complete circuit wiring diagram | Schematics | N/A | Clear pin connections between UNO, sensors, servo, LEDs, buzzer |
| `03_complete_wokwi_circuit.png` | Wokwi interactive canvas overview | Idle System | Hand: 50 cm, Waste: 30 cm | Green LED ON, Red LED OFF, Servo at 10° (Closed) |
| `04_lid_closed_state.png` | Lid in closed position | Idle Normal | Hand > 20 cm | Servo angle = 10°, Green LED ON |
| `05_hand_approaching_state.png` | Object/Hand proximity detection | Triggered | Hand <= 20 cm | Detection registered on Serial Monitor |
| `06_lid_open_state.png` | Servo actuates lid open | Actuated | Hand <= 20 cm | Servo angle = 100° (Open), Hold timer = 3000 ms |
| `07_empty_bin_reading.png` | Bin level distance = 30 cm | Fill State: 0% | Waste: 30 cm | Serial telemetry: Fill: 0%, Status: NORMAL |
| `08_50_percent_bin_reading.png` | Bin level distance = 18 cm | Fill State: 50% | Waste: 18 cm | Serial telemetry: Fill: 50%, Status: NORMAL |
| `09_75_percent_bin_reading.png` | Bin level distance = 12 cm | Fill State: 75% | Waste: 12 cm | Serial telemetry: Fill: 75%, Status: NORMAL |
| `10_full_bin_reading.png` | Bin level distance <= 8.4 cm | Fill State: 90%+ | Waste: 8.4 cm | Serial telemetry: Fill: 90%, Status: CRITICAL |
| `11_red_led_alert.png` | Visual warning indicator active | Full-Bin Alarm | Fill >= 90% | Red LED ON, Green LED OFF |
| `12_buzzer_alert.png` | Acoustic beep pulse active | Full-Bin Alarm | Fill >= 90% | Buzzer pin D4 pulsed HIGH (2s interval) |
| `13_safety_interlock_active.png` | Hand detected while bin is full | Overflow Prevention | Hand <= 20 cm, Fill >= 90% | Lid remains locked closed (Servo at 10°) |
| `14_serial_monitor_output.png` | Live ASCII telemetry stream | Serial Debugging | Continuous | Clean telemetry stream displaying distance, %, status |
| `15_source_code_screenshot.png` | Clean C++ modular code structure | IDE Code View | N/A | VS Code with `main.cpp`, `config.h`, and `smart_dustbin.ino` |
| `16_github_repository_preview.png` | GitHub repository homepage preview | GitHub Web UI | N/A | Repository header, topics, badges, and project README |

---

## 📌 How to Capture Simulation Proof for GitHub

1. Run the **Wokwi Simulator** (in VS Code or browser).
2. Adjust slider values for `handSensor` and `levelSensor`.
3. Capture full-screen or component-focused screenshots using `Win + Shift + S`.
4. Save images into `screenshots/` using the exact filenames listed above.
5. Embed screenshots into `README.md` and `reports/test_report.md`.
