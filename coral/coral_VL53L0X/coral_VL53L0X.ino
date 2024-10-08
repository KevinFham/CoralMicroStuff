/*
 Setup

 - VL53L0X requires 3.3V
 - SCL/SDA on Coral I2C1_SCL/I2C1_SDA
 - VL53L0X_1 "XSHUT" to Coral pin D0
 - VL53L0X_2 "XSHUT" to Coral pin D1

 Help from: https://robojax.com/learn/arduino/?vid=robojax_VL53L0X_multiple
 Coral Micro pins: https://coral.ai/docs/reference/micro/pins/
*/
#define VL53L0X1_ADDRESS 0x30
#define VL53L0X2_ADDRESS 0x31
#define SHT_VL53L0X1 D0
#define SHT_VL53L0X2 D1

#include <Wire.h>
#include <VL53L0X.h>

VL53L0X ir_1;
VL53L0X ir_2;

constexpr int kGpio[] = {
  D0, D1, D2, D3,
};
bool high = true;

void setup()
{
  Serial.begin(115200);
  Wire.begin();
  Serial.println("Initializing GPIO");
  for (auto pin : kGpio) {
    pinMode(pin, OUTPUT);
  }
  Serial.println("Setting VL53L0X addresses");
  digitalWrite(SHT_VL53L0X1, LOW);
  digitalWrite(SHT_VL53L0X2, LOW);
  delay(10);
  digitalWrite(SHT_VL53L0X1, HIGH);
  digitalWrite(SHT_VL53L0X2, HIGH);
  delay(10);
  //Set IR1 first
  digitalWrite(SHT_VL53L0X1, HIGH);
  digitalWrite(SHT_VL53L0X2, LOW);
  ir_1.init();
  ir_1.setAddress(VL53L0X1_ADDRESS);
  ir_1.setTimeout(100);
  ir_1.startContinuous();
  //Set IR2 next
  digitalWrite(SHT_VL53L0X2, HIGH);
  ir_2.init();
  ir_2.setAddress(VL53L0X2_ADDRESS);
  ir_2.setTimeout(100);
  ir_2.startContinuous();
}
void loop()
{
  Serial.print("IR1:"); Serial.print(ir_1.readRangeContinuousMillimeters());
  if (ir_1.timeoutOccurred()) { Serial.print("TIMEOUT"); }
  Serial.print(" IR2:"); Serial.print(ir_2.readRangeContinuousMillimeters());
  if (ir_2.timeoutOccurred()) { Serial.print("TIMEOUT"); }
  Serial.println();
}