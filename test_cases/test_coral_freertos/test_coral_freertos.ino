/*
 Ripped from test_serial.cc in FreeRTOS_apps branch

 - Essentially, this proves that everything in the https://github.com/google-coral/coralmicro libs folder is accessible in Arduino
 - This also proves that multitasking on the m4 and m7 is possible, and that FreeRTOS app development is possible in Arduino
*/
#include <cstdio>

#include "libs/base/led.h"
#include "libs/base/tasks.h"
#include "third_party/freertos_kernel/include/FreeRTOS.h"
#include "third_party/freertos_kernel/include/task.h"

[[noreturn]] void blink_task(void* param) {
  auto led_type = static_cast<coralmicro::Led*>(param);
  bool on = true;
  while (true) {
    on = !on;
    coralmicro::LedSet(*led_type, on);
    printf("Hello world!\r\n");
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}
// extern "C" [[noreturn]] void app_main(void *param) {
//   (void)param;
//   auto user_led = coralmicro::Led::kUser;
//   xTaskCreate(&blink_task, "blink_user_led_task", configMINIMAL_STACK_SIZE,
//               &user_led, coralmicro::kAppTaskPriority, nullptr);

//   printf("wassup\r\n");
//   vTaskSuspend(nullptr);
// }
auto user_led = coralmicro::Led::kUser;

void setup(){
  Serial.begin(115200);
  xTaskCreate(&blink_task, "blink_user_led_task", configMINIMAL_STACK_SIZE,
              &user_led, coralmicro::kAppTaskPriority, nullptr);
}

void loop(){
  Serial.println("loop");
  delay(5000);
}