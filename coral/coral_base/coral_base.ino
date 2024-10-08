/*
  Setup

 - nRF24L01, VL53L0X, and MPU9250 require 3.3V
 - I2C1_SCL/I2C1_SDA (Coral)   -   SCL/SDA
 - SPI6_SDI/SPI6_SDO (Coral)   -   MISO/MOSI or CIPO/COPI
 - SPI6_SCK (Coral)            -   SCK
 - A4 (Coral) (alt, D3)        -   nRF "CSN"
 - A3 (Coral) (alt, D2)        -   nRF "CE"
 - D0 (Coral)                  -   VL53L0X_1 "XSHUT"
 - D1 (Coral)                  -   VL53L0X_2 "XSHUT"

  Coral Micro pins: https://coral.ai/docs/reference/micro/pins/
*/
#define VL53L0X1_ADDRESS 0x30
#define VL53L0X2_ADDRESS 0x31
#define SHT_VL53L0X1 D0
#define SHT_VL53L0X2 D1

#include <Wire.h>
#include <VL53L0X.h>
#include "mpu9250.h"  //Bolder_Flight_Systems_invenSense_IMU by bolderflight
#include <RF24Network.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define BAUD_RATE 115200
#define MAP_SIZE_MAX 20

#include <stdint.h>
#include <algorithm>

VL53L0X ir_1;
VL53L0X ir_2;
constexpr int kGpio[] = { D0, D1 };
void setupVL53L0X(){
  for (auto pin : kGpio) { pinMode(pin, OUTPUT); }
  Serial.println("Setting VL53L0X addresses");
  digitalWrite(SHT_VL53L0X1, LOW);    // Shutdown
  digitalWrite(SHT_VL53L0X2, LOW);
  delay(10);
  digitalWrite(SHT_VL53L0X1, HIGH);   // Enable/Reset
  digitalWrite(SHT_VL53L0X2, HIGH);
  delay(10);
  digitalWrite(SHT_VL53L0X1, HIGH);   // Set IR1
  digitalWrite(SHT_VL53L0X2, LOW);
  ir_1.init();
  ir_1.setAddress(VL53L0X1_ADDRESS);
  ir_1.setTimeout(100);
  ir_1.startContinuous();
  digitalWrite(SHT_VL53L0X2, HIGH);   // Set IR2
  ir_2.init();
  ir_2.setAddress(VL53L0X2_ADDRESS);
  ir_2.setTimeout(100);
  ir_2.startContinuous();
}

bfs::Mpu9250 mpu;
void setupMPU9250(){
  mpu.Config(&Wire, bfs::Mpu9250::I2C_ADDR_PRIM);
  if (!mpu.Begin())
    Serial.println("Error initializing communication with IMU");
  else if (!mpu.ConfigSrd(19))
    Serial.println("Error configured SRD");
  else
    Serial.println("MPU9250 is connected");
}

RF24 radio(A3, A4); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};
void setupNRF24L01(){
  radio.begin();
  radio.setPayloadSize(16);       //Maximum size buffer
  radio.setDataRate(RF24_2MBPS);  //Can be set to either RF24_2MBPS, RF24_1MBPS, or RF24_250KBPS (Must be RF24_2MBPS for the Coral)
  radio.setPALevel(RF24_PA_MIN);  //Radio TX power to MIN
  radio.setRetries(15, 15);
  // radio.setCRCLength(RF24_CRC_8);
  radio.setChannel(2);          //Channel least likely to use Wifi, Microwave, etc. (Can also use 2)
  // radio.setAutoAck(false);
  Serial.println((radio.isChipConnected()) ? "nRF24 is connected" : "nRF24 failed to connect");
  Serial.println("Writing on 00002, Reading on 00001");
  radio.openWritingPipe(addresses[1]);
  radio.openReadingPipe(1, addresses[0]);
}
bool sendMessage(String message){
  radio.stopListening();
  char str[32];
  message.toCharArray(str, message.length() + 1);
  Serial.print("Sending: "); Serial.print(message);
  bool success = radio.write(&str, sizeof(str));
  if( success ){ Serial.println(" (Success)"); }
  else{ Serial.println(" (Failed)"); }
  radio.startListening();
  return success;
}

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



BinaryMap binmap;

void setup() {
  Serial.begin(BAUD_RATE);
  Wire.begin();
  Wire.setClock(400000);
  setupVL53L0X();
  setupMPU9250();
  setupNRF24L01();
}

void loop() {
  radio.startListening();
  if (radio.available()){
    char msg[32] = "";
    radio.read(&msg, sizeof(msg));
    Serial.print("Recieved: "); Serial.println(msg);
    radio.flush_rx();

    if (!strcmp(msg, "status")){
      String ir1_status = "IR1 Status: "; ir1_status += (ir_1.timeoutOccurred() ? "Failed" : "OK");
      String ir2_status = "IR2 Status: "; ir2_status += (ir_2.timeoutOccurred() ? "Failed" : "OK");
      String mpu_status = "MPU Status: "; mpu_status += (mpu.Read() ? "OK" : "Failed");
      String nrf_status = "nRF Status: "; nrf_status += (radio.isChipConnected() ? "OK" : "Failed");
      sendMessage(ir1_status); Serial.println(ir1_status);
      sendMessage(ir2_status); Serial.println(ir2_status);
      sendMessage(mpu_status); Serial.println(mpu_status);
      sendMessage(nrf_status); Serial.println(nrf_status);
    }
  }
  delay(1);
}
