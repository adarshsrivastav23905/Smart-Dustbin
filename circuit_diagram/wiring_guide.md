# Complete Circuit Diagram & Wiring Guide

## 1. Pin Interfacing Summary Table

| Peripheral Module | Device Pin | Arduino UNO Pin | Signal Type | Function Description |
|---|---|---|---|---|
| **Hand Proximity Sensor** (HC-SR04 #1) | VCC | 5V | Power | +5V DC Supply Rail |
| | GND | GND | Power | Common System Ground |
| | TRIG | Digital Pin 9 (D9) | Digital Output | 10µs Ultrasonic trigger pulse |
| | ECHO | Digital Pin 10 (D10) | Digital Input | Echo pulse duration return |
| **Waste Level Sensor** (HC-SR04 #2) | VCC | 5V | Power | +5V DC Supply Rail |
| | GND | GND | Power | Common System Ground |
| | TRIG | Digital Pin 6 (D6) | Digital Output | 10µs Ultrasonic trigger pulse |
| | ECHO | Digital Pin 7 (D7) | Digital Input | Echo pulse duration return |
| **Lid Actuator** (Micro Servo SG90) | VCC (Red) | 5V | Power | Servo +5V Power Line |
| | GND (Brown/Black) | GND | Power | Common System Ground |
| | PWM (Orange/Yellow) | Digital Pin 5 (D5) | PWM Output | Servo position pulse (10° closed, 100° open) |
| **Acoustic Alarm** (Active Buzzer 5V) | Positive (+) | Digital Pin 4 (D4) | Digital Output | Logic HIGH activates tone |
| | Negative (-) | GND | Power | Common System Ground |
| **Visual Telemetry** (Normal Green LED) | Anode (+) | Digital Pin 12 (D12)| Digital Output | Via 330Ω Current Limiting Resistor |
| | Cathode (-) | GND | Power | Common System Ground |
| **Visual Telemetry** (Full Red LED) | Anode (+) | Digital Pin 13 (D13)| Digital Output | Via 330Ω Current Limiting Resistor |
| | Cathode (-) | GND | Power | Common System Ground |
| **Optional LCD/OLED** (I2C 16x2 / 0.96") | VCC | 5V | Power | +5V DC Rail |
| | GND | GND | Power | Common Ground |
| | SDA | Pin A4 / SDA | I2C Data | Serial Data Line |
| | SCL | Pin A5 / SCL | I2C Clock | Serial Clock Line |

---

## 2. Resistor Calculations for Status LEDs
Using Ohm's Law ($V = I \times R \implies R = \frac{V_{supply} - V_{forward}}{I_{target}}$):
- $V_{supply} = 5.0\text{ V}$
- Red LED: $V_f \approx 2.0\text{ V}$, $I_f = 10\text{ mA} \implies R = \frac{5.0 - 2.0}{0.010} = 300\Omega \approx \mathbf{330\Omega}$ standard value.
- Green LED: $V_f \approx 2.2\text{ V}$, $I_f = 10\text{ mA} \implies R = \frac{5.0 - 2.2}{0.010} = 280\Omega \approx \mathbf{330\Omega}$ standard value.

---

## 3. Physical & Breadboard Layout Guidelines
1. **Power Rails**: Run red jumper from Arduino `5V` to breadboard red (+) rail; black jumper from Arduino `GND` to breadboard blue (-) rail.
2. **Decoupling**: When using physical servo motors, place a $100\mu\text{F}$ capacitor across 5V and GND close to the servo lead to prevent voltage sagging during servo motor initial acceleration.
3. **Common Ground**: All peripherals must share the identical reference potential (GND).
