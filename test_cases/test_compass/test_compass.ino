/*
 Requires MPU9250
*/

#include "mpu9250.h"  //Bolder_Flight_Systems_invenSense_IMU by bolderflight

bfs::Mpu9250 mpu;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000);
  delay(1000);

  mpu.Config(&Wire, bfs::Mpu9250::I2C_ADDR_PRIM);

  if (!mpu.Begin()) {
    Serial.println("Error initializing communication with IMU");
    while (1) {}
  }

  if (!mpu.ConfigSrd(19)) {
    Serial.println("Error configured SRD");
    while (1) {}
  }
}

void loop() {
  if (mpu.Read()) {


    // Serial.print("New data [imu, mag]: ");
    // Serial.print(mpu.new_imu_data()); Serial.print(" ");
    // Serial.print(mpu.new_mag_data()); Serial.print(" ");

    // Acceleration in meters per second^2
    // Serial.print("Accel: ");
    // Serial.print(mpu.accel_x_mps2()); Serial.print(" ");
    // Serial.print(mpu.accel_y_mps2()); Serial.print(" ");
    // Serial.print(mpu.accel_z_mps2()); Serial.print(" ");

    // Gyroscope in radians per second
    // Serial.print("Gyro: ");
    // Serial.print(mpu.gyro_x_radps());
    // Serial.print(" ");
    // Serial.print(mpu.gyro_y_radps());
    // Serial.print(" ");
    // Serial.print(mpu.gyro_z_radps());
    // Serial.print(" ");

    // Magnometer in microTeslas
    // Serial.print("Mag: ");
    // Serial.print(mpu.mag_x_ut());
    // Serial.print(" ");
    // Serial.print(mpu.mag_y_ut());
    // Serial.print(" ");
    // Serial.print(mpu.mag_z_ut());
    // Serial.print(" ");

    // Compass
    Serial.print("Compass: ");
    float heading = (atan2(mpu.mag_y_ut(), mpu.mag_x_ut()) * 180) / PI;
    heading += (heading < 0) ? 360 : 0;
    Serial.print(heading);

    // Thermometer in Celsius
    // Serial.print("Temp: ");
    // Serial.print(mpu.die_temp_c());

    Serial.println();
  }
}

// #include "quaternionFilters.h"
// #include "MPU9250.h"

// #define I2Cclock 400000
// #define I2Cport Wire
// #define MPU9250_ADDRESS MPU9250_ADDRESS_AD0   // Use either this line or the next to select which I2C address your device is using
// // #define MPU9250_ADDRESS MPU9250_ADDRESS_AD1

// MPU9250 myIMU(MPU9250_ADDRESS, I2Cport, I2Cclock);

// void setup(){
//   Serial.begin(115200);
//   Wire.begin();
//   Wire.setClock(400000);
//   delay(1000);
//   myIMU.initMPU9250();
//   myIMU.initAK8963(myIMU.factoryMagCalibration);

//   myIMU.getAres();
//   myIMU.getGres();
//   myIMU.getMres();

// }


// void loop(){
//   myIMU.readAccelData(myIMU.accelCount);

//   myIMU.ax = (float)myIMU.accelCount[0] * myIMU.aRes; // - myIMU.accelBias[0];
//   myIMU.ay = (float)myIMU.accelCount[1] * myIMU.aRes; // - myIMU.accelBias[1];
//   myIMU.az = (float)myIMU.accelCount[2] * myIMU.aRes; // - myIMU.accelBias[2];

//   myIMU.readGyroData(myIMU.gyroCount);  // Read the x/y/z adc values

//   myIMU.gx = (float)myIMU.gyroCount[0] * myIMU.gRes;
//   myIMU.gy = (float)myIMU.gyroCount[1] * myIMU.gRes;
//   myIMU.gz = (float)myIMU.gyroCount[2] * myIMU.gRes;

//   myIMU.readMagData(myIMU.magCount);  // Read the x/y/z adc values

//   myIMU.mx = (float)myIMU.magCount[0] * myIMU.mRes
//               * myIMU.factoryMagCalibration[0] - myIMU.magBias[0];
//   myIMU.my = (float)myIMU.magCount[1] * myIMU.mRes
//               * myIMU.factoryMagCalibration[1] - myIMU.magBias[1];
//   myIMU.mz = (float)myIMU.magCount[2] * myIMU.mRes
//               * myIMU.factoryMagCalibration[2] - myIMU.magBias[2];

//   myIMU.updateTime();

//   myIMU.delt_t = millis() - myIMU.count;

//   Serial.print("X-acceleration: "); Serial.print(1000 * myIMU.ax);
//   Serial.print(" mg ");
//   Serial.print("Y-acceleration: "); Serial.print(1000 * myIMU.ay);
//   Serial.print(" mg ");
//   Serial.print("Z-acceleration: "); Serial.print(1000 * myIMU.az);
//   Serial.println(" mg ");

//   // Print gyro values in degree/sec
//   Serial.print("X-gyro rate: "); Serial.print(myIMU.gx, 3);
//   Serial.print(" degrees/sec ");
//   Serial.print("Y-gyro rate: "); Serial.print(myIMU.gy, 3);
//   Serial.print(" degrees/sec ");
//   Serial.print("Z-gyro rate: "); Serial.print(myIMU.gz, 3);
//   Serial.println(" degrees/sec");

//   // Print mag values in degree/sec
//   Serial.print("X-mag field: "); Serial.print(myIMU.mx);
//   Serial.print(" mG ");
//   Serial.print("Y-mag field: "); Serial.print(myIMU.my);
//   Serial.print(" mG ");
//   Serial.print("Z-mag field: "); Serial.print(myIMU.mz);
//   Serial.println(" mG");

//   myIMU.yaw   = atan2(2.0f * (*(getQ()+1) * *(getQ()+2) + *getQ()
//                 * *(getQ()+3)), *getQ() * *getQ() + *(getQ()+1)
//                 * *(getQ()+1) - *(getQ()+2) * *(getQ()+2) - *(getQ()+3)
//                 * *(getQ()+3));
//   myIMU.pitch = -asin(2.0f * (*(getQ()+1) * *(getQ()+3) - *getQ()
//                 * *(getQ()+2)));
//   myIMU.roll  = atan2(2.0f * (*getQ() * *(getQ()+1) + *(getQ()+2)
//                 * *(getQ()+3)), *getQ() * *getQ() - *(getQ()+1)
//                 * *(getQ()+1) - *(getQ()+2) * *(getQ()+2) + *(getQ()+3)
//                 * *(getQ()+3));
//   myIMU.pitch *= RAD_TO_DEG;
//   myIMU.yaw   *= RAD_TO_DEG;

// myIMU.yaw  -= 8.5;
//     myIMU.roll *= RAD_TO_DEG;

// }