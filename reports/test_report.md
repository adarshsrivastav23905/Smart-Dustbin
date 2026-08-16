# System Verification & Test Execution Report

| Project Name | Smart Dustbin – Industry-Oriented Embedded System |
|---|---|
| Platform | Arduino UNO (ATmega328P) Virtual Wokwi Environment |
| Test Engineer | Embedded Systems Student / Project Lead |
| Test Date | August 2026 |
| Target Firmware | `src/main.cpp` / `arduino_code/smart_dustbin.ino` |
| Test Verdict | **100% PASSED (14/14 Test Cases)** |

---

## Comprehensive Test Execution Matrix

| Test ID | Test Category | Input Condition / Action | Expected Output | Actual Output | Verdict |
|---|---|---|---|---|---|
| **TC-01** | Initialization | Power-on / System Reset | All GPIO pins configured, servo home at 10°, Green LED ON, Red LED OFF, Serial banner printed | Boot banner displayed, servo locked at 10°, Green LED lit | **PASS** |
| **TC-02** | Idle State | Hand sensor = 50 cm, Waste sensor = 30 cm | Lid remains closed (10°), Green LED ON, Red LED OFF, Fill = 0% | Fill: 0%, Lid: CLOSED, Status: NORMAL | **PASS** |
| **TC-03** | Lid Actuation | Hand sensor = 15 cm ($\le 20\text{ cm}$) | Servo horn actuates to 100° (OPEN), hold timer initialized | Servo rotates to 100° immediately | **PASS** |
| **TC-04** | Auto-Close Timer | Hand removed after trigger, wait 3 seconds | Servo rotates back to 10° (CLOSED) after 3000 ms | Closed accurately after 3.0s elapsed | **PASS** |
| **TC-05** | Rapid Triggering | Hand sensor toggled rapidly (< 500 ms) | Lid stays open smoothly without servo jitter or lockup | Lid held open, timer reset properly | **PASS** |
| **TC-06** | Waste Level 25% | Waste sensor distance = 24.0 cm | Calculated Fill = 25%, Status NORMAL, Green LED ON | Fill: 25%, Green LED ON | **PASS** |
| **TC-07** | Waste Level 50% | Waste sensor distance = 18.0 cm | Calculated Fill = 50%, Status NORMAL, Green LED ON | Fill: 50%, Green LED ON | **PASS** |
| **TC-08** | Waste Level 75% | Waste sensor distance = 12.0 cm | Calculated Fill = 75%, Status NORMAL, Green LED ON | Fill: 75%, Green LED ON | **PASS** |
| **TC-09** | Full Threshold (90%)| Waste sensor distance = 8.4 cm | Calculated Fill = 90%, State switches to CRITICAL | Fill: 90%, State: CRITICAL (FULL) | **PASS** |
| **TC-10** | Overflow Condition | Waste sensor distance = 4.0 cm (< 6.0 cm full) | Calculated Fill constrained to 100%, State CRITICAL | Fill: 100%, Constrained properly | **PASS** |
| **TC-11** | Full-Bin Visual Alert | State = CRITICAL (FULL) | Green LED turns OFF, Red LED turns ON | Green LED OFF, Red LED solidly lit | **PASS** |
| **TC-12** | Full-Bin Audio Alert | State = CRITICAL (FULL) | Active buzzer pulses periodically (100ms on / 2000ms off) | Buzzer emits periodic alarm pulse | **PASS** |
| **TC-13** | Safety Interlock | State = CRITICAL, Hand sensor = 10 cm | Lid remains locked CLOSED at 10° (prevents overflow) | Servo does not open; lid stays closed | **PASS** |
| **TC-14** | Recovery / Emptying| Waste sensor distance changed back to 30 cm | State returns to NORMAL, Red LED OFF, Green LED ON, Buzzer OFF | Immediate recovery to NORMAL (READY) | **PASS** |

---

## Summary Conclusion
All embedded control logic, sensor timing, math algorithms, and safety interlocks have been fully verified under virtual simulation in Wokwi. The system is robust, non-blocking, and production-ready.
