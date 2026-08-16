#pragma once

#include <Arduino.h>

class SensorManager
{
public:
    void begin();
    void update();

    float getHandDistance() const;
    float getWasteDistance() const;

private:
    float readDistance(uint8_t trigPin, uint8_t echoPin);

    float handDistance_ = -1.0f;
    float wasteDistance_ = -1.0f;

    unsigned long lastHandRead_ = 0;
    unsigned long lastWasteRead_ = 0;
};