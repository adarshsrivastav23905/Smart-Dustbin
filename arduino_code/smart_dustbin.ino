/**
 * ============================================================================
 * PROJECT: Smart Dustbin – Industry-Oriented Embedded System
 * PLATFORM: Arduino UNO / ATmega328P (Fully compatible with Wokwi / Tinkercad)
 * AUTHOR: Adarsh Srivastav
 * REPOSITORY: Smart-Dustbin-Embedded-System
 * ============================================================================
 * 
 * DESCRIPTION:
 * An automated, hygienic, dual-sensor smart waste management system designed
 * for institutional and public deployment. It features:
 * 1. Proximity-based touchless lid actuation (Ultrasonic Sensor 1 + Servo Motor).
 * 2. Real-time internal waste level monitoring (Ultrasonic Sensor 2).
 * 3. 16x2 I2C LCD Display telemetry output.
 * 4. Fill-level percentage calculation and threshold detection.
 * 5. Multi-tier alert management (Green LED, Red LED, Active Buzzer).
 * 6. Full-bin safety interlock (prevents lid opening when bin is 100% full).
 * 7. Non-blocking state management using millis() timers.
 * ============================================================================
 */

#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ============================================================================
// 1. PIN DEFINITIONS & HARDWARE MAPPINGS
// ============================================================================
// Proximity Sensor (Hand Detection)
const uint8_t HAND_TRIG_PIN  = 9;
const uint8_t HAND_ECHO_PIN  = 10;

// Level Sensor (Internal Bin Fill Depth)
const uint8_t LEVEL_TRIG_PIN = 6;
const uint8_t LEVEL_ECHO_PIN = 7;

// Actuator & Acoustic Alert
const uint8_t SERVO_PIN      = 5;
const uint8_t BUZZER_PIN     = 4;

// Visual Indicators
const uint8_t GREEN_LED_PIN  = 12; // Normal operation / Ready
const uint8_t RED_LED_PIN    = 13; // Full-bin warning alert

// ============================================================================
// 2. CALIBRATION CONSTANTS & SYSTEM THRESHOLDS
// ============================================================================
const float HAND_DETECTION_DISTANCE_CM = 20.0f;

const float EMPTY_BIN_DISTANCE_CM = 30.0f;
const float FULL_BIN_DISTANCE_CM  = 6.0f;

const uint8_t FULL_LEVEL_PERCENT  = 90;

const int LID_CLOSED_ANGLE = 10;
const int LID_OPEN_ANGLE   = 100;

const unsigned long HAND_SENSOR_INTERVAL_MS  = 100;
const unsigned long LEVEL_SENSOR_INTERVAL_MS = 400;
const unsigned long LID_HOLD_TIME_MS         = 3000;
const unsigned long BUZZER_BEEP_INTERVAL_MS  = 2000;
const unsigned long LCD_UPDATE_INTERVAL_MS   = 500;
const unsigned long SERIAL_PRINT_INTERVAL_MS = 1000;

// ============================================================================
// 3. GLOBAL OBJECTS & STATE VARIABLES
// ============================================================================
Servo lidServo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

float currentHandDistance  = -1.0f;
float currentWasteDistance = -1.0f;
int   currentFillPercent   = 0;
bool  isBinFull            = false;
bool  isLidOpen            = false;

unsigned long lastHandReadTime   = 0;
unsigned long lastLevelReadTime  = 0;
unsigned long lidAutoCloseTarget = 0;
unsigned long lastBuzzerBeepTime = 0;
unsigned long lastLcdUpdateTime  = 0;
unsigned long lastSerialLogTime  = 0;

// ============================================================================
// 4. HELPER FUNCTION: Read HC-SR04 Ultrasonic Sensor
// ============================================================================
float readUltrasonicDistance(uint8_t trigPin, uint8_t echoPin) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    unsigned long duration = pulseIn(echoPin, HIGH, 30000UL);
    if (duration == 0) return -1.0f;

    float distanceCm = (duration * 0.0343f) / 2.0f;
    if (distanceCm < 2.0f || distanceCm > 400.0f) return -1.0f;

    return distanceCm;
}

// ============================================================================
// 5. HELPER FUNCTION: Calculate Bin Fill Percentage
// ============================================================================
int calculateFillPercentage(float distanceCm) {
    if (distanceCm < 0.0f) return currentFillPercent;

    float percentage = ((EMPTY_BIN_DISTANCE_CM - distanceCm) / 
                        (EMPTY_BIN_DISTANCE_CM - FULL_BIN_DISTANCE_CM)) * 100.0f;

    if (percentage < 0.0f) percentage = 0.0f;
    if (percentage > 100.0f) percentage = 100.0f;

    return (int)(percentage + 0.5f);
}

// ============================================================================
// 6. ACTUATION FUNCTIONS
// ============================================================================
void openLid() {
    lidServo.write(LID_OPEN_ANGLE);
    isLidOpen = true;
    lidAutoCloseTarget = millis() + LID_HOLD_TIME_MS;
}

void closeLid() {
    lidServo.write(LID_CLOSED_ANGLE);
    isLidOpen = false;
}

// ============================================================================
// 7. ALERT MANAGEMENT FUNCTION
// ============================================================================
void updateAlertSystem(bool binFull) {
    unsigned long now = millis();

    if (binFull) {
        digitalWrite(GREEN_LED_PIN, LOW);
        digitalWrite(RED_LED_PIN, HIGH);

        if (now - lastBuzzerBeepTime >= BUZZER_BEEP_INTERVAL_MS) {
            lastBuzzerBeepTime = now;
            digitalWrite(BUZZER_PIN, HIGH);
            delay(100);
            digitalWrite(BUZZER_PIN, LOW);
        }
    } else {
        digitalWrite(GREEN_LED_PIN, HIGH);
        digitalWrite(RED_LED_PIN, LOW);
        digitalWrite(BUZZER_PIN, LOW);
    }
}

// ============================================================================
// 8. 16x2 LCD DISPLAY MANAGER
// ============================================================================
void updateLCD(unsigned long now) {
    if (now - lastLcdUpdateTime < LCD_UPDATE_INTERVAL_MS) return;
    lastLcdUpdateTime = now;

    lcd.clear();

    if (isBinFull) {
        lcd.setCursor(0, 0);
        lcd.print("BIN FULL! LOCK");
        lcd.setCursor(0, 1);
        lcd.print("FILL: ");
        lcd.print(currentFillPercent);
        lcd.print("% CRIT");
    } else if (isLidOpen) {
        lcd.setCursor(0, 0);
        lcd.print("LID: OPENING...");
        lcd.setCursor(0, 1);
        lcd.print("FILL: ");
        lcd.print(currentFillPercent);
        lcd.print("% READY");
    } else {
        lcd.setCursor(0, 0);
        lcd.print("SMART DUSTBIN");
        lcd.setCursor(0, 1);
        lcd.print("FILL: ");
        lcd.print(currentFillPercent);
        lcd.print("% NORMAL");
    }
}

// ============================================================================
// 9. TELEMETRY & SERIAL DIAGNOSTICS
// ============================================================================
void printTelemetry(unsigned long now) {
    if (now - lastSerialLogTime >= SERIAL_PRINT_INTERVAL_MS) {
        lastSerialLogTime = now;

        Serial.print(F("[TELEMETRY] Hand: "));
        if (currentHandDistance < 0) Serial.print(F("NONE"));
        else { Serial.print(currentHandDistance, 1); Serial.print(F(" cm")); }

        Serial.print(F(" | Waste Depth: "));
        if (currentWasteDistance < 0) Serial.print(F("ERR"));
        else { Serial.print(currentWasteDistance, 1); Serial.print(F(" cm")); }

        Serial.print(F(" | Fill: "));
        Serial.print(currentFillPercent);
        Serial.print(F("% | Lid: "));
        Serial.print(isLidOpen ? F("OPEN   ") : F("CLOSED "));

        Serial.print(F(" | Status: "));
        Serial.println(isBinFull ? F("CRITICAL (FULL)") : F("NORMAL (READY)"));
    }
}

// ============================================================================
// 10. SETUP FUNCTION
// ============================================================================
void setup() {
    Serial.begin(9600);

    pinMode(HAND_TRIG_PIN, OUTPUT);
    pinMode(HAND_ECHO_PIN, INPUT);
    pinMode(LEVEL_TRIG_PIN, OUTPUT);
    pinMode(LEVEL_ECHO_PIN, INPUT);

    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(GREEN_LED_PIN, OUTPUT);
    pinMode(RED_LED_PIN, OUTPUT);

    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(RED_LED_PIN, LOW);

    lidServo.attach(SERVO_PIN);
    closeLid();

    // Initialize 16x2 I2C LCD
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SMART DUSTBIN");
    lcd.setCursor(0, 1);
    lcd.print("INITIALIZING...");
    delay(1000);
    lcd.clear();

    Serial.println();
    Serial.println(F("=========================================================="));
    Serial.println(F("  SMART DUSTBIN - EMBEDDED SYSTEM CONTROL PLATFORM"));
    Serial.println(F("  Architecture: Arduino UNO / ATmega328P + 16x2 I2C LCD"));
    Serial.println(F("=========================================================="));
    Serial.println(F("[SYS] System Initialized Successfully. Running main loop..."));
}

// ============================================================================
// 11. MAIN SUPER-LOOP (Non-Blocking Cooperative Scheduling)
// ============================================================================
void loop() {
    unsigned long now = millis();

    if (now - lastHandReadTime >= HAND_SENSOR_INTERVAL_MS) {
        lastHandReadTime = now;
        currentHandDistance = readUltrasonicDistance(HAND_TRIG_PIN, HAND_ECHO_PIN);
    }

    if (now - lastLevelReadTime >= LEVEL_SENSOR_INTERVAL_MS) {
        lastLevelReadTime = now;
        currentWasteDistance = readUltrasonicDistance(LEVEL_TRIG_PIN, LEVEL_ECHO_PIN);
        currentFillPercent = calculateFillPercentage(currentWasteDistance);
        isBinFull = (currentFillPercent >= FULL_LEVEL_PERCENT);
    }

    if (!isBinFull) {
        if (currentHandDistance > 0.0f && currentHandDistance <= HAND_DETECTION_DISTANCE_CM) {
            openLid();
        }
    } else {
        if (isLidOpen) {
            closeLid();
        }
    }

    if (isLidOpen && ((long)(now - lidAutoCloseTarget) >= 0)) {
        closeLid();
    }

    updateAlertSystem(isBinFull);
    updateLCD(now);
    printTelemetry(now);
}
