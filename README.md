# CoralMicroStuff

Sandboxing stuff w/ the Google Coral Micro

> i hate c++

### Instructions

`cd coralmicro/apps`

`git clone https://github.com/KevinFham/CoralMicroStuff.git`

`mv CoralMicroStuff/* .`

Add these lines in `coralmicro/apps/CMakeLists.txt`
```
add_subdirectory(test_serial)
add_subdirectory(test_VL53L0X)
add_subdirectory(test_MPU9250)
```

### Coral Micro Docs

https://coral.ai/docs/dev-board-micro/get-started/#3-boot-up-for-the-first-time

Note: in scripts/requirements.txt, set `hidapi==0.10.1` to `hidapi==0.11.2`

### FreeRTOS app dev

https://coral.ai/docs/dev-board-micro/freertos/

# Issues

### When Coral Micro cannot be found on `lsusb`

https://coral.ai/docs/dev-board-micro/arduino/#troubleshooting

### Uploading Code to the Coral Micro

1. Disable any serial connection to the Coral Micro (including Arduino Serial Monitor)

2. Upload Code (Python flashing or Arduino uploading)

3. Disconnect and reconnect the Coral Micro to USB-C

4. Connect to serial (either through `screen /dev/ttyACM0 115200` or Arduino Serial Monitor)



