# Sensor Calibration

## Empty Bin

Measure the distance from the waste-level sensor to the
bottom of the bin with no waste present.

Configured demo value:

30 cm

## Full Bin

Define the distance at which the bin should be considered
100% full.

Configured demo value:

6 cm

## Formula

Fill Percentage =

((Empty Distance - Measured Distance) /
 (Empty Distance - Full Distance)) × 100

## Important

The values above are simulation/demo calibration values.
They must be measured again if physical hardware is used.