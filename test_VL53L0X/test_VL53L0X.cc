#include <cstdio>
#include <sstream>

#include "libs/base/check.h"
#include "libs/base/i2c.h"
#include "libs/base/utils.h"
#include "libs/base/led.h"
#include "libs/base/tasks.h"
#include "third_party/freertos_kernel/include/FreeRTOS.h"
#include "third_party/freertos_kernel/include/task.h"

//[[noreturn]] void get_IR(void* param) {
//
//    CHECK(
//        coralmicro::I2cControllerRead()
//    )
//}

extern "C" [[noreturn]] void app_main(void *param) {
  (void)param;

  auto config = I2cGetDefaultConfig(coralmicro::I2c::kI2c1);
  I2cInitController(config);

  std::string serial = coralmicro::GetSerialNumber();
  constexpr int kTargetAddress = 0x29;              //I2C Addr for VL53L0X
  int kTransferSize = serial.length();

  auto buffer = std::vector<uint8_t>(kTransferSize, 0);

  while (true){
    CHECK(
      coralmicro::I2cControllerRead(config, kTargetAddress, buffer.data(), kTransferSize)
    );

    std::stringstream ss;
    for (auto it = buffer.begin(); it != buffer.end(); it++){
        if (it != buffer.begin()){
            ss << " ";
        }
        ss << *it;
    }

    printf("%s", ss.str());       //TODO: print out info somehow
  }

//  auto user_led = coralmicro::Led::kUser;
//  xTaskCreate(&get_IR, "blink_user_led_task", configMINIMAL_STACK_SIZE,
//              &user_led, coralmicro::kAppTaskPriority, nullptr);

  vTaskSuspend(nullptr);
}