/*
 TODO: Port Multicore model Cascade to verify that m4 and m7 interprocess comms works
        Note down that the coralmicro/libs/base folder was copied into ~/.arduino15/packages/coral/hardware/coral_micro/1.0.1/variants/coral_micro/libs 
 https://coral.ai/docs/dev-board-micro/get-started/#6-try-multi-core-model-cascading
 https://coral.ai/docs/dev-board-micro/multicore/#define-an-m4-program-with-cmake
*/
#include "libs/base/filesystem.h"
#include "libs/base/ipc_m4.h"
#include "libs/base/led.h"
#include "libs/base/main_freertos_m4.h"
#include "libs/camera/camera.h"
#include "libs/tensorflow/utils.h"
#include "third_party/freertos_kernel/include/FreeRTOS.h"
#include "third_party/freertos_kernel/include/task.h"
#include "third_party/freertos_kernel/include/timers.h"
#include "third_party/tflite-micro/tensorflow/lite/micro/micro_error_reporter.h"
#include "third_party/tflite-micro/tensorflow/lite/micro/micro_interpreter.h"
#include "third_party/tflite-micro/tensorflow/lite/micro/micro_mutable_op_resolver.h"
#include "third_party/tflite-micro/tensorflow/lite/schema/schema_generated.h"


#include "libs/base/filesystem.h"
#include "libs/base/http_server_handlers.h"
#include "libs/base/ipc_m7.h"
#include "libs/base/led.h"
#include "libs/base/mutex.h"
#include "libs/base/network.h"
#include "libs/base/reset.h"
#include "libs/base/strings.h"
#include "libs/base/watchdog.h"
#include "libs/camera/camera.h"
#include "libs/libjpeg/jpeg.h"
#include "libs/rpc/rpc_http_server.h"
#include "libs/tensorflow/posenet.h"
#include "libs/tpu/edgetpu_manager.h"
#include "third_party/freertos_kernel/include/FreeRTOS.h"
#include "third_party/freertos_kernel/include/semphr.h"
#include "third_party/freertos_kernel/include/task.h"
#include "third_party/mjson/src/mjson.h"
#include "third_party/tflite-micro/tensorflow/lite/micro/micro_interpreter.h"

#include <cstdio>
#include <cstring>
#include <memory>
#include <utility>
#include <vector>

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
