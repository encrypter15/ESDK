/*
 * File: logger.h
 * Author: Rick Hayes
 * License: MIT
 * Version: 1.3
 * Date: April 05, 2025
 */
#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>

class Logger {
private:
    std::ofstream logFile;
public:
    Logger(const std::string& filepath) {
        logFile.open(filepath, std::ios::app);
        if (!logFile.is_open()) throw std::runtime_error("Failed to open log file: " + filepath);
    }
    ~Logger() { if (logFile.is_open()) logFile.close(); }
    void log(const std::string& message) {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        logFile << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S") << " - " << message << std::endl;
    }
};

#endif // LOGGER_H
