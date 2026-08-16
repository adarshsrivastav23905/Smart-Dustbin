#pragma once

class BinMonitor
{
public:
    void begin();

    void update(float distanceCm);

    int getFillPercent() const;

    bool isFull() const;

private:
    int fillPercent_ = 0;
    bool full_ = false;

    int calculateFillPercent(float distanceCm);
};