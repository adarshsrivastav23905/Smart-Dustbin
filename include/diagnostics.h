#pragma once

class Diagnostics
{
public:
    void begin();

    void update(
        float handDistance,
        float wasteDistance,
        int fillPercent,
        bool lidOpen,
        bool binFull
    );

private:
    unsigned long lastPrint_ = 0;
};