#include <Arduino.h>

#include "bin_monitor.h"
#include "config.h"

void BinMonitor::begin()
{
    fillPercent_ = 0;
    full_ = false;
}

void BinMonitor::update(float distanceCm)
{
    if (distanceCm < 0.0f)
    {
        return;
    }

    fillPercent_ =
        calculateFillPercent(distanceCm);

    full_ =
        fillPercent_ >= FULL_LEVEL_PERCENT;
}

int BinMonitor::calculateFillPercent(float distanceCm)
{
    const float percentage =
        ((EMPTY_BIN_DISTANCE_CM - distanceCm) /
         (EMPTY_BIN_DISTANCE_CM - FULL_BIN_DISTANCE_CM))
        * 100.0f;

    if (percentage <= 0.0f)
    {
        return 0;
    }

    if (percentage >= 100.0f)
    {
        return 100;
    }

    return static_cast<int>(percentage + 0.5f);
}

int BinMonitor::getFillPercent() const
{
    return fillPercent_;
}

bool BinMonitor::isFull() const
{
    return full_;
}