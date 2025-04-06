/*
 * File: safety.h
 * Author: Rick Hayes
 * License: MIT
 * Version: 1.3
 * Date: April 05, 2025
 */
#ifndef SAFETY_H
#define SAFETY_H

#include "hal.h"

class Safety {
private:
    HardwareAbstractionLayer* hal;
public:
    Safety(HardwareAbstractionLayer* hardware) : hal(hardware) {}
    void enableWatchdog() { hal->enableWatchdog(); }
    void resetWatchdog() { hal->resetWatchdog(); }
};

#endif // SAFETY_H
