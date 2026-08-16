#include <Arduino.h>
#include "lid_controller.h"
#include "config.h"

void LidController::begin()
{
    servo_.attach(SERVO_PIN);

    servo_.write(LID_CLOSED_ANGLE);

    open_ = false;
}

void LidController::open()
{
    servo_.write(LID_OPEN_ANGLE);

    open_ = true;

    closeTime_ =
        millis() + LID_HOLD_TIME_MS;
}

void LidController::close()
{
    servo_.write(LID_CLOSED_ANGLE);

    open_ = false;
}

bool LidController::isOpen() const
{
    return open_;
}

bool LidController::shouldClose() const
{
    if (!open_)
        return false;

    return static_cast<long>(
        millis() - closeTime_) >= 0;
}