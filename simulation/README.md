
```markdown
# Wokwi Simulation

The project is implemented and validated as a virtual embedded
system using Wokwi.

## Scenario 1 — Normal

Hand sensor: 50 cm
Waste sensor: 30 cm

Expected:

- Lid CLOSED
- Green LED ON
- Red LED OFF
- Status NORMAL

## Scenario 2 — Hand Detection

Hand sensor: 15 cm

Expected:

- Servo moves to OPEN position
- Serial state becomes OPEN

## Scenario 3 — Full Bin

Waste sensor: 8.4 cm or lower

Expected:

- Fill >= 90%
- Red LED ON
- Buzzer active
- Status FULL