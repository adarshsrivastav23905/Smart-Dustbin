#pragma once

#include <Arduino.h>

// ============================================================
// SMART DUSTBIN - CENTRAL CONFIGURATION
// ============================================================

// -------------------- PIN CONFIGURATION ---------------------

constexpr uint8_t HAND_TRIG_PIN  = 9;
constexpr uint8_t HAND_ECHO_PIN  = 10;

constexpr uint8_t LEVEL_TRIG_PIN = 6;
constexpr uint8_t LEVEL_ECHO_PIN = 7;

constexpr uint8_t SERVO_PIN      = 5;
constexpr uint8_t BUZZER_PIN     = 4;

constexpr uint8_t GREEN_LED_PIN  = 12;
constexpr uint8_t RED_LED_PIN    = 13;


// -------------------- SENSOR SETTINGS ----------------------

constexpr float HAND_DETECTION_DISTANCE_CM = 20.0f;

// Calibration values for the virtual bin
constexpr float EMPTY_BIN_DISTANCE_CM = 30.0f;
constexpr float FULL_BIN_DISTANCE_CM  = 6.0f;


// -------------------- BIN THRESHOLDS -----------------------

constexpr uint8_t WARNING_LEVEL_PERCENT = 80;
constexpr uint8_t FULL_LEVEL_PERCENT    = 90;


// -------------------- SERVO SETTINGS -----------------------

constexpr int LID_CLOSED_ANGLE = 10;
constexpr int LID_OPEN_ANGLE   = 100;


// -------------------- TIMING SETTINGS ----------------------

constexpr unsigned long HAND_SENSOR_INTERVAL_MS  = 120;
constexpr unsigned long LEVEL_SENSOR_INTERVAL_MS = 400;

constexpr unsigned long LID_HOLD_TIME_MS =
    3000;

constexpr unsigned long BUZZER_INTERVAL_MS =
    2000;

constexpr unsigned long STATUS_PRINT_INTERVAL_MS =
    1000;


// -------------------- SERIAL SETTINGS ---------------------

constexpr unsigned long SERIAL_BAUD_RATE = 9600;