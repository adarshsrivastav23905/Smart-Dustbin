#pragma once

class AlertManager
{
public:
    void begin();

    void update(bool binFull);

private:
    unsigned long lastBeep_ = 0;
};