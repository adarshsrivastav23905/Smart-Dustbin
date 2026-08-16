#include <Arduino.h>

#include "alert_manager.h"
#include "config.h"

void AlertManager::begin()
{
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(GREEN_LED_PIN, OUTPUT);
    pinMode(RED_LED_PIN, OUTPUT);

    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(RED_LED_PIN, LOW);
}

void AlertManager::update(bool binFull)
{
    if (binFull)
    {
        digitalWrite(GREEN_LED_PIN, LOW);
        digitalWrite(RED_LED_PIN, HIGH);

        if (millis() - lastBeep_ >=
            BUZZER_INTERVAL_MS)
        {
            lastBeep_ = millis();

            digitalWrite(BUZZER_PIN, HIGH);
            delay(100);
            digitalWrite(BUZZER_PIN, LOW);
        }
    }
    else
    {
        digitalWrite(GREEN_LED_PIN, HIGH);
        digitalWrite(RED_LED_PIN, LOW);
        digitalWrite(BUZZER_PIN, LOW);
    }
}