#include <Arduino.h>

#include "diagnostics.h"
#include "config.h"

void Diagnostics::begin()
{
    lastPrint_ = 0;
}

void Diagnostics::update(
    float handDistance,
    float wasteDistance,
    int fillPercent,
    bool lidOpen,
    bool binFull)
{
    if (millis() - lastPrint_ <
        STATUS_PRINT_INTERVAL_MS)
    {
        return;
    }

    lastPrint_ = millis();

    Serial.print(F("HAND="));

    if (handDistance < 0)
        Serial.print(F("INVALID"));
    else
        Serial.print(handDistance, 1);

    Serial.print(F("cm | WASTE="));

    if (wasteDistance < 0)
        Serial.print(F("INVALID"));
    else
        Serial.print(wasteDistance, 1);

    Serial.print(F("cm | FILL="));
    Serial.print(fillPercent);
    Serial.print(F("% | LID="));

    Serial.print(
        lidOpen ? F("OPEN") : F("CLOSED"));

    Serial.print(F(" | STATE="));

    Serial.println(
        binFull ? F("FULL") : F("NORMAL"));
}