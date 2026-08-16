#pragma once

#include <Servo.h>

class LidController
{
public:
    void begin();

    void open();
    void close();

    bool isOpen() const;
    bool shouldClose() const;

private:
    Servo servo_;

    bool open_ = false;
    unsigned long closeTime_ = 0;
};