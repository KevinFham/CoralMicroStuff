#include <cstdio>

#include "libs/base/check.h"
#include "libs/base/i2c.h"
#include "libs/base/utils.h"
#include "libs/base/led.h"
#include "libs/base/tasks.h"
#include "third_party/freertos_kernel/include/FreeRTOS.h"
#include "third_party/freertos_kernel/include/task.h"

[[noreturn]] void get_IR(void* param) {

}

extern "C" [[noreturn]] void app_main(void *param) {
  (void)param;

  auto config = I2cGetDefaultConfig(coralmicro::I2c::kI2c1);
  I2cInitController(config);

  std::string serial = coralmicro::GetSerialNumber();
  constexpr int kTargetAddress = 0x68;              //I2C Addr for MPU9250

//  auto user_led = coralmicro::Led::kUser;
//  xTaskCreate(&get_IR, "blink_user_led_task", configMINIMAL_STACK_SIZE,
//              &user_led, coralmicro::kAppTaskPriority, nullptr);

  vTaskSuspend(nullptr);
}