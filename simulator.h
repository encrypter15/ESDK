/*
 * File: simulator.h
 * Author: Rick Hayes
 * License: MIT
 * Version: 1.3
 * Date: April 05, 2025
 */
#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <iostream>
#include <random>

class Simulator {
private:
    std::mt19937 rng;
    float simulatedTemperature;
public:
    Simulator() : rng(std::random_device{}()), simulatedTemperature(20.0f) {}
    void start() { std::cout << "Simulator started.\n"; }
    void stop() { std::cout << "Simulator stopped.\n"; }
    void update() {
        std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
        simulatedTemperature += dist(rng);
        if (simulatedTemperature < -40.0f) simulatedTemperature = -40.0f;
        if (simulatedTemperature > 85.0f) simulatedTemperature = 85.0f;
    }
    float getTemperature() const { return simulatedTemperature; }
};

#endif // SIMULATOR_H
