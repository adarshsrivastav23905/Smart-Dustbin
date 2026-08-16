#pragma once

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

class LCDManager
{
public:
    void begin();
    void update(int fillPercent, bool lidOpen, bool binFull);

private:
    LiquidCrystal_I2C lcd_{0x27, 16, 2};
    unsigned long lastUpdate_ = 0;
};
