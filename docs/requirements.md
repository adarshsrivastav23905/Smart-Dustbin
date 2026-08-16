# System Requirements

## Functional Requirements

FR-01: Detect an approaching hand/object.

FR-02: Open the lid automatically when the object is
within the configured detection distance.

FR-03: Close the lid automatically after the configured
hold period.

FR-04: Measure waste level using an ultrasonic sensor.

FR-05: Convert sensor distance to a 0–100% fill estimate.

FR-06: Enter FULL state when the configured threshold is reached.

FR-07: Activate visual and audible alerts in FULL state.

FR-08: Provide serial diagnostics.

## Non-Functional Requirements

NFR-01: Modular source code.

NFR-02: Configurable thresholds.

NFR-03: Invalid sensor readings must not crash the system.

NFR-04: Project must be reproducible using PlatformIO and Wokwi.

NFR-05: Project must be version controlled with Git.