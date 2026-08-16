# Test Plan

| ID | Scenario | Input | Expected Result |
|---|---|---|---|
| TC01 | Normal | Hand 50 cm | Lid closed |
| TC02 | Hand detected | Hand 15 cm | Lid opens |
| TC03 | Timeout | Hand removed | Lid closes |
| TC04 | Empty bin | Waste 30 cm | 0% |
| TC05 | 25% | Waste 24 cm | ~25% |
| TC06 | 50% | Waste 18 cm | ~50% |
| TC07 | 75% | Waste 12 cm | ~75% |
| TC08 | Full threshold | Waste 8.4 cm | FULL |
| TC09 | Full bin | Waste 6 cm | 100% + alert |
| TC10 | Invalid input | No echo | Previous valid state retained |

## Validation

All tests are executed in the Wokwi virtual environment.