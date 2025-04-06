/*
 * File: ota.h
 * Author: Rick Hayes
 * License: MIT
 * Version: 1.3
 * Date: April 05, 2025
 */
#ifndef OTA_H
#define OTA_H

#include "hal.h"
#include "cloud.h"
#include <string>

class OTAUpdater {
private:
    HardwareAbstractionLayer* hal;
    CloudClient* cloud;
    std::string firmwareUrl;
public:
    OTAUpdater(HardwareAbstractionLayer* hardware, CloudClient* cloudClient, const std::string& url)
        : hal(hardware), cloud(cloudClient), firmwareUrl(url) {}
    bool checkAndUpdate() {
        #ifdef STM32_PLATFORM
        std::string firmwareData = downloadFirmware();
        if (!firmwareData.empty()) return true;
        #endif
        #ifdef RASPI_PLATFORM
        system(("wget -O /tmp/new_esdk " + firmwareUrl + " && mv /tmp/new_esdk /usr/bin/esdk && reboot").c_str());
        return true;
        #endif
        return false;
    }
private:
    std::string downloadFirmware() { return "firmware_data"; }
};

#endif // OTA_H
