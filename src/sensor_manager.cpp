#include <Arduino.h>

#include "sensor_manager.h"
#include "config.h"

void SensorManager::begin()
{
    pinMode(HAND_TRIG_PIN, OUTPUT);
    pinMode(HAND_ECHO_PIN, INPUT);

    pinMode(LEVEL_TRIG_PIN, OUTPUT);
    pinMode(LEVEL_ECHO_PIN, INPUT);
}

void SensorManager::update()
{
    const unsigned long now = millis();

    if (now - lastHandRead_ >= HAND_SENSOR_INTERVAL_MS)
    {
        lastHandRead_ = now;

        handDistance_ =
            readDistance(HAND_TRIG_PIN, HAND_ECHO_PIN);
    }

    if (now - lastWasteRead_ >= LEVEL_SENSOR_INTERVAL_MS)
    {
        lastWasteRead_ = now;

        wasteDistance_ =
            readDistance(LEVEL_TRIG_PIN, LEVEL_ECHO_PIN);
    }
}

float SensorManager::readDistance(
    uint8_t trigPin,
    uint8_t echoPin)
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);

    digitalWrite(trigPin, LOW);

    const unsigned long duration =
        pulseIn(echoPin, HIGH, 30000UL);

    if (duration == 0)
    {
        return -1.0f;
    }

    const float distance =
        duration * 0.0343f / 2.0f;

    if (distance < 2.0f ||
        distance > 400.0f)
    {
        return -1.0f;
    }

    return distance;
}

float SensorManager::getHandDistance() const
{
    return handDistance_;
}

float SensorManager::getWasteDistance() const
{
    return wasteDistance_;
}