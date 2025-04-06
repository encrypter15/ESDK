/*
 * File: wireless.h
 * Author: Rick Hayes
 * License: MIT
 * Version: 1.3
 * Date: April 05, 2025
 */
#ifndef WIRELESS_H
#define WIRELESS_H

#include "hal.h"
#include <string>

class Wireless {
private:
    HardwareAbstractionLayer* hal;
public:
    Wireless(HardwareAbstractionLayer* hardware) : hal(hardware) {}
    void sendData(const std::string& data) {
        #ifdef STM32_PLATFORM
        #endif
        #ifdef RASPI_PLATFORM
        system(("echo \"" + data + "\" | bluetoothctl").c_str());
        #endif
    }
    std::string receiveData() {
        #ifdef STM32_PLATFORM
        return "";
        #endif
        #ifdef RASPI_PLATFORM
        return "received_data";
        #endif
    }
};

#endif // WIRELESS_H
