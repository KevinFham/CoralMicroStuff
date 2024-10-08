// #include "MPU9250.h" //MPU9250 by hideakitai
#include "mpu9250.h" //Bolder_Flight_Systems_invenSense_IMU by bolderflight

bfs::Mpu9250 mpu;

void setup(){
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000);
  delay(2000);
  
  mpu.Config(&Wire, bfs::Mpu9250::I2C_ADDR_PRIM);

  if (!mpu.Begin()) {
    Serial.println("Error initializing communication with IMU");
    while(1) {}
  }

  if (!mpu.ConfigSrd(19)) {
    Serial.println("Error configured SRD");
    while(1) {}
  }
}

void loop(){
  if (mpu.Read()) {
    Serial.print(mpu.new_imu_data());
    Serial.print("\t");
    Serial.print(mpu.new_mag_data());
    Serial.print("\t");
    Serial.print(mpu.accel_x_mps2());
    Serial.print("\t");
    Serial.print(mpu.accel_y_mps2());
    Serial.print("\t");
    Serial.print(mpu.accel_z_mps2());
    Serial.print("\t");
    Serial.print(mpu.gyro_x_radps());
    Serial.print("\t");
    Serial.print(mpu.gyro_y_radps());
    Serial.print("\t");
    Serial.print(mpu.gyro_z_radps());
    Serial.print("\t");
    Serial.print(mpu.mag_x_ut());
    Serial.print("\t");
    Serial.print(mpu.mag_y_ut());
    Serial.print("\t");
    Serial.print(mpu.mag_z_ut());
    Serial.print("\t");
    Serial.print(mpu.die_temp_c());
    Serial.print("\n");
  }
}