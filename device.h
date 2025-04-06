/*
 * File: device.h
 * Author: Rick Hayes
 * License: MIT
 * Version: 1.3
 * Date: April 05, 2025
 */
#ifndef DEVICE_H
#define DEVICE_H

#include "hal.h"

class TemperatureSensor {
private:
    HardwareAbstractionLayer* hal;
    uint8_t analogPin;
public:
    TemperatureSensor(HardwareAbstractionLayer* hardware, uint8_t pin) : hal(hardware), analogPin(pin) {
        hal->initialize();
    }
    float readTemperature() { return hal->readAnalog(analogPin); }
    void setIndicator(uint8_t ledPin, float threshold) {
        float temp = readTemperature();
        hal->writePin(ledPin, temp > threshold);
    }
};

class MotorController {
private:
    HardwareAbstractionLayer* hal;
    uint8_t pwmPin;
    uint8_t directionPin;
public:
    MotorController(HardwareAbstractionLayer* hardware, uint8_t pwm, uint8_t dir)
        : hal(hardware), pwmPin(pwm), directionPin(dir) {
        hal->initialize();
    }
    void setSpeed(float speed) {
        bool direction = speed >= 0;
        hal->writePin(directionPin, direction);
        uint8_t pwmValue = static_cast<uint8_t>(std::abs(speed) * 255);
        hal->writePWM(pwmPin, pwmValue);
    }
};

#endif // DEVICE_H
