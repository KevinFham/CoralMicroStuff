/*
 Setup

 - MPU9250 and VL53L0X requires 3.3V
 - SCL/SDA on Coral I2C1_SCL/I2C1_SDA
*/
#include <Wire.h>
#include <VL53L0X.h>
#include "mpu9250.h"  //Bolder_Flight_Systems_invenSense_IMU by bolderflight

#include <stdint.h>
#include <algorithm>

const int MAP_SIZE_MAX = 20;

/*
* Mapping
*/
class BinaryMap {
  private:
    uint8_t binary_map[MAP_SIZE_MAX][MAP_SIZE_MAX] = { 0 };
    float pos_X;
    float pos_Y;
  public:
    BinaryMap(){
      
    }
    void recordIR(int irReading, float compassHeading_rad){
      int record_Y = MAP_SIZE_MAX / 2; 
      int record_X = MAP_SIZE_MAX / 2; 
      if(irReading < MAP_SIZE_MAX){
        record_Y += round(irReading * cos(compassHeading_rad));
        record_X += round(irReading * sin(compassHeading_rad));
        binary_map[record_Y][record_X] = 1;
      }
      // Serial.print("x,y: "); Serial.print(record_X); Serial.print(" "); Serial.println(record_Y);
    }
    void clearMap(){
      memset(binary_map, 0, sizeof(binary_map));
    }
    void printMap(){
      for(int i = 0; i < MAP_SIZE_MAX; i++){
        for(int j = 0; j < MAP_SIZE_MAX; j++){
          Serial.print(binary_map[i][j]);
        }
        Serial.println();
      }
      clearMap();
    }
};


/*
* Main
*/
bfs::Mpu9250 mpu;
VL53L0X ir;
BinaryMap binmap;
void setup()
{
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000);
  mpu.Config(&Wire, bfs::Mpu9250::I2C_ADDR_PRIM);
  if (!mpu.Begin()) {
    Serial.println("Error initializing communication with IMU");
    while (1) {}
  }
  if (!mpu.ConfigSrd(19)) {
    Serial.println("Error configured SRD");
    while (1) {}
  }
  ir.init();
  ir.setTimeout(100);
  ir.startContinuous();   //Start continuous back-to-back mode
}

void loop()
{
  float irReading = ir.readRangeContinuousMillimeters() / 25.4;
  float heading;
  Serial.print(irReading);
  if (ir.timeoutOccurred()) { Serial.print("TIMEOUT"); }
  Serial.println();
  if (mpu.Read()) {
    Serial.print("Compass: ");
    heading = atan2(mpu.mag_y_ut(), mpu.mag_x_ut());
    heading += (heading < 0) ? 2 * PI : 0;
    Serial.print(heading * 180 / PI);
    Serial.println();
  }

  binmap.recordIR((int)irReading, heading);
  binmap.printMap();

  
  delay(100);
}