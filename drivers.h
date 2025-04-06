/*
 * File: drivers.h
 * Author: Rick Hayes
 * License: MIT
 * Version: 1.3
 * Date: April 05, 2025
 */
#ifndef DRIVERS_H
#define DRIVERS_H

#include "hal.h"

class MPU6050Driver {
private:
    HardwareAbstractionLayer* hal;
    uint8_t i2cAddress;
public:
    MPU6050Driver(HardwareAbstractionLayer* hardware, uint8_t addr) : hal(hardware), i2cAddress(addr) {}
    void initialize() {}
    float readAccelX() { return 0.0f; }
};

class DriverRegistry {
public:
    static MPU6050Driver* createMPU6050(HardwareAbstractionLayer* hal, uint8_t addr) {
        return new MPU6050Driver(hal, addr);
    }
};

#endif // DRIVERS_H
