#include <Arduino.h>
#include <PCA9685.h>

// #include "Constants.h"


PCA9685 pca9685;

// PCA9685::DurationMicroseconds servo_pulse_duration;

void setup()
{
  pca9685.setupSingleDevice(Wire, 0x40);

  pca9685.setupOutputEnablePin(2);
  pca9685.enableOutputs(2);

  pca9685.setAllDevicesToFrequency(800);

  // servo_pulse_duration = constants::servo_pulse_duration_min;
}

void loop()
{
  for (int i = 0; i < 100; i++){
    pca9685.setChannelDutyCycle(0, 0.01 * i, 0);
    pca9685.setChannelDutyCycle(1, 0.01 * i, 0);
    Serial.println(i);
    delay(100);
  }
  // if (servo_pulse_duration > constants::servo_pulse_duration_max)
  // {
  //   servo_pulse_duration = constants::servo_pulse_duration_min;
  // }
  // pca9685.setChannelDutyCycle(0, servo_pulse_duration, 0);
  // servo_pulse_duration += constants::servo_pulse_duration_increment;
  // Serial.println(servo_pulse_duration);
  // delay(constants::loop_delay);
}
