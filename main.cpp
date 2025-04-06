/*
 * File: main.cpp
 * Author: Rick Hayes
 * License: MIT
 * Version: 1.3
 * Date: April 05, 2025
 */
#include <iostream>
#include "hal.h"
#include "device.h"
#include "ota.h"
#include "rtos.h"
#include "sensor_fusion.h"
#include "wireless.h"
#include "power.h"
#include "cli.h"
#include "safety.h"
#include "drivers.h"
#include "sim_bridge.h"
#include "cloud.h"
#include "config.h"
#include "logger.h"
#include "visualizer.h"

#ifdef STM32_PLATFORM
extern "C" void STM32CubeMX_Init(void);
STM32HAL hal;
#elif defined(RASPI_PLATFORM)
RaspberryPiGPIO hal;
#else
#error "Define STM32_PLATFORM or RASPI_PLATFORM"
#endif

void sensorTask(void* param) {
    auto* args = static_cast<std::tuple<TemperatureSensor*, SensorFusion*>*>(param);
    TemperatureSensor* sensor = std::get<0>(*args);
    SensorFusion* fusion = std::get<1>(*args);
    while (true) {
        float temp = fusion->update(sensor->readTemperature());
        std::cout << "Fused Temp: " << temp << "°C\n";
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

int main() {
    #ifdef STM32_PLATFORM
    STM32CubeMX_Init();
    #endif

    Config config("config.json");
    Logger logger("esdk.log");
    CloudClient cloud("https://api.example.com/data", "your-api-key");
    Visualizer viz;
    OTAUpdater ota(&hal, &cloud, "https://example.com/firmware.bin");
    RTOSWrapper rtos;
    SensorFusion fusion;
    Wireless wireless(&hal);
    PowerManager power(&hal);
    CLI cli;
    Safety safety(&hal);
    MPU6050Driver* mpu = DriverRegistry::createMPU6050(&hal, 0x68);
    Simulator sim;
    HardwareSimulatorBridge bridge(&hal, &sim, false);

    TemperatureSensor sensor(&hal, config.getPin("temperature_sensor", "analog_pin"));
    MotorController motor(&hal, config.getPin("motor_controller", "pwm_pin"),
                         config.getPin("motor_controller", "direction_pin"));

    safety.enableWatchdog();
    ota.checkAndUpdate();

    auto taskArgs = std::make_tuple(&sensor, &fusion);
    rtos.createTask(sensorTask, "SensorTask", &taskArgs);
    rtos.startScheduler();

    for (int i = 0; i < 10 && viz.isOpen(); ++i) {
        float temp = bridge.readAnalog(0);
        sensor.setIndicator(config.getPin("temperature_sensor", "led_pin"),
                           config.getThreshold("temperature_sensor"));
        bridge.writePWM(config.getPin("motor_controller", "pwm_pin"), temp > 30.0f ? 128 : 0);

        logger.log("Temperature: " + std::to_string(temp) + "°C");
        cloud.uploadData(temp);
        wireless.sendData("Temp: " + std::to_string(temp));
        viz.update(temp);

        cli.processCommand("read_temp", sensor, motor);
        safety.resetWatchdog();
        power.enterSleep();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        power.wakeUp();
    }

    delete mpu;
    return 0;
}
