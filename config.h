/*
 * File: config.h
 * Author: Rick Hayes
 * License: MIT
 * Version: 1.3
 * Date: April 05, 2025
 */
#ifndef CONFIG_H
#define CONFIG_H

#include <nlohmann/json.hpp>
#include <fstream>
#include <stdexcept>

using json = nlohmann::json;

class Config {
private:
    json data;
public:
    Config(const std::string& filepath) {
        std::ifstream file(filepath);
        if (!file.is_open()) throw std::runtime_error("Failed to open config file: " + filepath);
        file >> data;
    }
    uint8_t getPin(const std::string& device, const std::string& pinType) {
        return data[device][pinType].get<uint8_t>();
    }
    float getThreshold(const std::string& device) {
        return data[device]["threshold"].get<float>();
    }
};

#endif // CONFIG_H
