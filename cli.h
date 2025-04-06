/*
 * File: cli.h
 * Author: Rick Hayes
 * License: MIT
 * Version: 1.3
 * Date: April 05, 2025
 */
#ifndef CLI_H
#define CLI_H

#include "device.h"
#include <string>
#include <iostream>

class CLI {
public:
    void processCommand(const std::string& cmd, TemperatureSensor& sensor, MotorController& motor) {
        if (cmd == "read_temp") {
            std::cout << "Temperature: " << sensor.readTemperature() << "°C\n";
        } else if (cmd.substr(0, 9) == "set_speed") {
            float speed = std::stof(cmd.substr(10));
            motor.setSpeed(speed);
            std::cout << "Motor speed set to: " << speed << "\n";
        }
    }
};

#endif // CLI_H
