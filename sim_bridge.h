/*
 * File: sim_bridge.h
 * Author: Rick Hayes
 * License: MIT
 * Version: 1.3
 * Date: April 05, 2025
 */
#ifndef SIM_BRIDGE_H
#define SIM_BRIDGE_H

#include "hal.h"
#include "simulator.h"

class HardwareSimulatorBridge {
private:
    HardwareAbstractionLayer* hal;
    Simulator* sim;
    bool useSim;
public:
    HardwareSimulatorBridge(HardwareAbstractionLayer* hardware, Simulator* simulator, bool simulate)
        : hal(hardware), sim(simulator), useSim(simulate) {
        if (useSim && sim) sim->start();
    }
    float readAnalog(uint8_t pin) {
        return useSim && sim ? sim->getTemperature() : hal->readAnalog(pin);
    }
    void writePWM(uint8_t pin, uint8_t value) {
        if (!useSim) hal->writePWM(pin, value);
    }
};

#endif // SIM_BRIDGE_H
