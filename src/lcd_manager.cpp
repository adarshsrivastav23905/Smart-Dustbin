#include "lcd_manager.h"

void LCDManager::begin()
{
    lcd_.init();
    lcd_.backlight();

    lcd_.clear();

    lcd_.setCursor(0, 0);
    lcd_.print("SMART DUSTBIN");

    lcd_.setCursor(0, 1);
    lcd_.print("INITIALIZING...");

    delay(1000);

    lcd_.clear();
}

void LCDManager::update(
    int fillPercent,
    bool lidOpen,
    bool binFull)
{
    if (millis() - lastUpdate_ < 500)
    {
        return;
    }

    lastUpdate_ = millis();

    lcd_.clear();

    if (binFull)
    {
        lcd_.setCursor(0, 0);
        lcd_.print("BIN FULL!");

        lcd_.setCursor(0, 1);
        lcd_.print("FILL: ");
        lcd_.print(fillPercent);
        lcd_.print("%");
    }
    else if (lidOpen)
    {
        lcd_.setCursor(0, 0);
        lcd_.print("LID: OPEN");

        lcd_.setCursor(0, 1);
        lcd_.print("FILL: ");
        lcd_.print(fillPercent);
        lcd_.print("%");
    }
    else
    {
        lcd_.setCursor(0, 0);
        lcd_.print("SMART DUSTBIN");

        lcd_.setCursor(0, 1);
        lcd_.print("FILL: ");
        lcd_.print(fillPercent);
        lcd_.print("% NORMAL");
    }
}