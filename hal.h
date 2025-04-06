/*
 * File: hal.h
 * Author: Rick Hayes
 * License: MIT
 * Version: 1.3
 * Date: April 05, 2025
 */
#ifndef HAL_H
#define HAL_H

#include <cstdint>

#ifdef STM32_PLATFORM
#include "stm32f4xx_hal.h"
#endif
#ifdef RASPI_PLATFORM
#include <wiringPi.h>
#endif

class HardwareAbstractionLayer {
public:
    virtual ~HardwareAbstractionLayer() = default;
    virtual void initialize() = 0;
    virtual void writePin(uint8_t pin, bool value) = 0;
    virtual bool readPin(uint8_t pin) = 0;
    virtual float readAnalog(uint8_t pin) = 0;
    virtual void writePWM(uint8_t pin, uint8_t value) = 0;
    virtual void enterSleep() = 0;
    virtual void wakeUp() = 0;
    virtual void enableWatchdog() = 0;
    virtual void resetWatchdog() = 0;
};

#ifdef STM32_PLATFORM
class STM32HAL : public HardwareAbstractionLayer {
private:
    GPIO_TypeDef* getGPIOBase(uint8_t pin) {
        return (pin < 16) ? GPIOA : GPIOB;
    }
    uint16_t getGPIOPin(uint8_t pin) {
        return 1U << (pin % 16);
    }
public:
    void initialize() override {
        __HAL_RCC_GPIOA_CLK_ENABLE();
        __HAL_RCC_GPIOB_CLK_ENABLE();
        GPIO_InitTypeDef GPIO_InitStruct = {0};
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        for (uint8_t pin = 0; pin < 32; pin++) {
            GPIO_InitStruct.Pin = getGPIOPin(pin);
            HAL_GPIO_Init(getGPIOBase(pin), &GPIO_InitStruct);
        }
    }
    void writePin(uint8_t pin, bool value) override {
        HAL_GPIO_WritePin(getGPIOBase(pin), getGPIOPin(pin), value ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }
    bool readPin(uint8_t pin) override {
        return HAL_GPIO_ReadPin(getGPIOBase(pin), getGPIOPin(pin)) == GPIO_PIN_SET;
    }
    float readAnalog(uint8_t pin) override { return 0.0f; }
    void writePWM(uint8_t pin, uint8_t value) override {}
    void enterSleep() override { HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI); }
    void wakeUp() override { SystemInit(); }
    void enableWatchdog() override {}
    void resetWatchdog() override {}
};
#endif

#ifdef RASPI_PLATFORM
class RaspberryPiGPIO : public HardwareAbstractionLayer {
public:
    void initialize() override {
        if (wiringPiSetup() == -1) throw std::runtime_error("Failed to initialize wiringPi");
        for (uint8_t pin = 0; pin < 40; pin++) pinMode(pin, OUTPUT);
    }
    void writePin(uint8_t pin, bool value) override { digitalWrite(pin, value ? HIGH : LOW); }
    bool readPin(uint8_t pin) override { pinMode(pin, INPUT); return digitalRead(pin) == HIGH; }
    float readAnalog(uint8_t pin) override { return 0.0f; }
    void writePWM(uint8_t pin, uint8_t value) override { pwmWrite(pin, value); }
    void enterSleep() override { system("sudo systemctl suspend"); }
    void wakeUp() override {}
    void enableWatchdog() override {}
    void resetWatchdog() override {}
};
#endif

#endif // HAL_H
