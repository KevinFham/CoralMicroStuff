# CoralMicroStuff

Sandboxing stuff w/ the Google Coral Micro

> i hate c++

### Instructions

`cd ~/Arduino`

`git clone https://github.com/KevinFham/CoralMicroStuff.git`

`mv CoralMicroStuff/* .`

### Coral Micro Docs

[Getting Started](https://coral.ai/docs/dev-board-micro/arduino/)

[Arduino API](https://coral.ai/docs/reference/micro/arduino/)

### FreeRTOS Dev in Arduino

Arduino will not have access to certain libs such as `ipc_m4.h` and `ipc_m7.h` after setup. You must insert the libs from the [Coral Micro Source Code](https://github.com/google-coral/coralmicro) into the board's package files

`cp -r coralmicro/libs/base/ ~/.arduino15/packages/coral/hardware/coral_micro/1.0.1/variants/coral_micro/libs` 

# Dependencies

[Coral Arduino Package](https://coral.ai/docs/dev-board-micro/arduino/#2-install-the-coral-package)

[Bolder_Flight_Systems_InvenSense_IMU](https://github.com/bolderflight/invensense-imu) (v3.1.3) by borderflight (for MPU9250)

[VL53L0X](https://github.com/pololu/vl53l0x-arduino) (v1.3.1) by Pololu

[RF24](https://nrf24.github.io/RF24/) (v1.4.8) by TMRh20 (for nRF24L01)


[PCA9685](https://github.com/janelia-arduino/PCA9685) (v3.0.1) by Peter Polidoro

# Issues

### When Coral Micro cannot be found on `lsusb`

https://coral.ai/docs/dev-board-micro/arduino/#troubleshooting

### Uploading Code to the Coral Micro

1. Disable any serial connection to the Coral Micro (including Arduino Serial Monitor)

2. Upload Code (Python flashing or Arduino uploading)

3. Disconnect and reconnect the Coral Micro to USB-C

4. Connect to serial (either through `screen /dev/ttyACM0 115200` or Arduino Serial Monitor)

### TODO

- [ ] Fix nRF24L01 randomly failing to communicate (with [RF24Network by TMRh20](https://nrf24.github.io/RF24Network/) library?)
