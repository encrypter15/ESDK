# Embedded Systems Development Kit (ESDK)

![logo] (https://raw.githubusercontent.com/encrypter15/ESDK/refs/heads/main/logo.jpg)

## Overview
The Embedded Systems Development Kit (ESDK) is a comprehensive toolkit for programming IoT devices, drones, and robotics. It includes a hardware abstraction layer (HAL), simulator, and support for STM32 and Raspberry Pi platforms.

## Author
- **Rick Hayes**

## License
- **MIT**

## Version
- **1.4**


## Features
- Hardware Abstraction Layer (HAL) for STM32 and Raspberry Pi
- OTA Firmware Updates
- RTOS Integration (FreeRTOS for STM32, pthreads for Raspberry Pi)
- Sensor Fusion with Kalman Filtering
- Wireless Communication (BLE/Wi-Fi)
- Power Management
- Command-Line Interface (CLI)
- Safety and Fault Tolerance
- Modular Driver Library
- Simulation-to-Hardware Bridging
- Cloud Integration
- Configuration via JSON
- Real-Time Logging
- Graphical Visualization with SFML

## Prerequisites
- **STM32:** STM32Cube HAL, FreeRTOS, arm-none-eabi-g++
- **Raspberry Pi:** wiringPi, wiringPiSPI, libcurl, SFML, bluetooth
- **General:** nlohmann/json, g++

## Compilation
### STM32
```bash
arm-none-eabi-g++ -DSTM32_PLATFORM -mcpu=cortex-m4 -mthumb main.cpp stm32cubemx.c -o esdk.elf -L/path/to/stm32cube/libs -lstm32f4xx_hal -lfreertos
```

### Raspberry Pi
```bash
g++ -DRASPI_PLATFORM main.cpp -o esdk -lwiringPi -lwiringPiSPI -lcurl -lsfml-graphics -lsfml-window -lsfml-system -lbluetooth -lpthread
```

## Usage
1. Configure `config.json` with your pin mappings.
2. Compile for your target platform.
3. Flash (STM32) or run (Raspberry Pi) the binary.

## Notes
- STM32 setup uses ADC1 on PA0 and TIM2 on PA1 for PWM.
- Raspberry Pi uses MCP3008 for ADC and GPIO 18 for PWM.
- Install dependencies before compiling.
