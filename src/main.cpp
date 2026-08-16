#include <Arduino.h>

#include "config.h"
#include "sensor_manager.h"
#include "bin_monitor.h"
#include "lid_controller.h"
#include "alert_manager.h"
#include "lcd_manager.h"
#include "diagnostics.h"

SensorManager sensors;
BinMonitor binMonitor;
LidController lidController;
AlertManager alerts;
LCDManager lcdManager;
Diagnostics diagnostics;

void setup()
{
    Serial.begin(SERIAL_BAUD_RATE);

    sensors.begin();
    binMonitor.begin();
    lidController.begin();
    alerts.begin();
    lcdManager.begin();
    diagnostics.begin();

    Serial.println();
    Serial.println(F("=========================================="));
    Serial.println(F(" SMART DUSTBIN EMBEDDED SYSTEM"));
    Serial.println(F(" Virtual Validation Platform"));
    Serial.println(F(" Arduino UNO + PlatformIO + Wokwi + 16x2 LCD"));
    Serial.println(F("=========================================="));
}

void loop()
{
    sensors.update();

    const float handDistance = sensors.getHandDistance();
    const float wasteDistance = sensors.getWasteDistance();

    binMonitor.update(wasteDistance);

    if (!binMonitor.isFull() &&
        handDistance > 0 &&
        handDistance <= HAND_DETECTION_DISTANCE_CM)
    {
        lidController.open();
    }

    if (lidController.shouldClose())
    {
        lidController.close();
    }

    if (binMonitor.isFull())
    {
        lidController.close();
    }

    alerts.update(binMonitor.isFull());

    lcdManager.update(
        binMonitor.getFillPercent(),
        lidController.isOpen(),
        binMonitor.isFull()
    );

    diagnostics.update(
        handDistance,
        wasteDistance,
        binMonitor.getFillPercent(),
        lidController.isOpen(),
        binMonitor.isFull()
    );
}