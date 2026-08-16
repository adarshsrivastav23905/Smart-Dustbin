# Engineering Limitations and Failure Modes Analysis

## 1. Physical & Sensor Limitations
1. **Ultrasonic Acoustic Dispersion**:
   - Soft or porous waste (fabrics, sponges, paper) absorbs ultrasonic waves rather than reflecting them sharply, leading to occasional false high distance readings.
   - Irregular surface topography inside the bin can reflect ultrasonic echoes at oblique angles, causing pulse timeout.
   - *Mitigation*: Software clipping, non-linear rolling average filters, and minimum timeout thresholds.

2. **Sensor Dead Band (Blind Zone)**:
   - HC-SR04 ultrasonic sensors cannot reliably measure distances less than $2\text{ cm}$. If waste comes within $< 2\text{ cm}$ of the sensor face, the receiver triggers immediately or times out.
   - *Mitigation*: Mounting the sensor recessed at a minimum standoff distance of $4\text{ to }6\text{ cm}$ above the maximum fill height.

3. **Servo Mechanical Load & Current Spikes**:
   - Standard hobby servos (SG90) draw up to $500\text{ mA}$ under mechanical stall. When powered directly from an Arduino UNO 5V regulator, inductive voltage dips (brownouts) can reset the microcontroller.
   - *Mitigation*: Separate dedicated 5V power supply rail for servo motors with common ground and decoupling capacitors ($100\mu\text{F} - 470\mu\text{F}$) in real hardware setups.

## 2. Environmental Constraints
- **Temperature Dependence of Sound**: The speed of sound varies with ambient temperature ($v \approx 331.3 + 0.606 \times T\text{ m/s}$). For uncalibrated systems at extreme temperatures ($0^\circ\text{C}$ vs $40^\circ\text{C}$), depth calculation drift is approx $\pm 3.5\%$.
- **Moisture & Condensation**: Internal bin humidity may condense on ultrasonic transducer mesh in wet waste bins. Sealed waterproof ultrasonic sensors (such as JSN-SR04T) are recommended for industrial wet waste production deployments.

## 3. Simulation vs Hardware Parity
| Feature | Virtual Simulation (Wokwi / Tinkercad) | Real Hardware Deployment |
|---|---|---|
| Sensor Noise | Ideal geometric distance sliders | Jitter, acoustic bounce, ambient reflections |
| Power Delivery | Infinite ideal 5V rail | Brownout risks under servo surge load |
| Mechanical Wear | Frictionless instant movement | Gear backlash, stall current, mechanical jam |
| Latency | Microsecond deterministic | Interrupt latency, supply voltage variation |
