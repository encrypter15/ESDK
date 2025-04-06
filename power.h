/*
 * File: power.h
 * Author: Rick Hayes
 * License: MIT
 * Version: 1.3
 * Date: April 05, 2025
 */
#ifndef POWER_H
#define POWER_H

#include "hal.h"

class PowerManager {
private:
    HardwareAbstractionLayer* hal;
public:
    PowerManager(HardwareAbstractionLayer* hardware) : hal(hardware) {}
    void enterSleep() { hal->enterSleep(); }
    void wakeUp() { hal->wakeUp(); }
};

#endif // POWER_H
