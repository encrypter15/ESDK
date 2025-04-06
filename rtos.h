/*
 * File: rtos.h
 * Author: Rick Hayes
 * License: MIT
 * Version: 1.3
 * Date: April 05, 2025
 */
#ifndef RTOS_H
#define RTOS_H

#ifdef STM32_PLATFORM
#include "FreeRTOS.h"
#include "task.h"
#endif

class RTOSWrapper {
public:
    void createTask(void (*taskFunc)(void*), const char* name, void* param) {
        #ifdef STM32_PLATFORM
        xTaskCreate(taskFunc, name, 512, param, 1, nullptr);
        #endif
        #ifdef RASPI_PLATFORM
        pthread_t thread;
        pthread_create(&thread, nullptr, (void* (*)(void*))taskFunc, param);
        #endif
    }
    void startScheduler() {
        #ifdef STM32_PLATFORM
        vTaskStartScheduler();
        #endif
    }
};

#endif // RTOS_H
