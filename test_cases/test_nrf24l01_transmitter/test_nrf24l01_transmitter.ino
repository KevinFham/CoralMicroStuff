/*
 How to Connect the nRF to Arduino Mega or Uno/Nano: https://howtomechatronics.com/tutorials/arduino/arduino-wireless-communication-nrf24l01-tutorial/

  Requires a secondary nRF24L01 available to receive data and respond (running test_nrf24l01_receiver)
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};   //Channel 00001: Transmitter (Write), Reciever (Read)
                                                  //Channel 00002: Transmitter (Read), Reciever (Write)
unsigned long BAUD_RATE = 115200;
/*
 Setup
*/
void setup() {
  Serial.begin(BAUD_RATE);
  radio.begin();
  radio.setPayloadSize(16);       //32 is the maximum size buffer
  radio.setDataRate(RF24_1MBPS);  //Can be set to either RF24_2MBPS, RF24_1MBPS, or RF24_250KBPS
  radio.setPALevel(RF24_PA_MIN);  //Radio TX power to MIN
  radio.setRetries(15, 15);
  // radio.setCRCLength(RF24_CRC_8);
  radio.setChannel(2);          //Channel least likely to use Wifi, Microwave, etc. (Can also use 2)
  // radio.setAutoAck(false);
  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1, addresses[1]);
  Serial.println((radio.isChipConnected()) ? "nRF24 is connected" : "nRF24 failed to connect");
  Serial.println("Setup Complete");
}
/*
 Loop
*/
void loop() {
  /* Radio Transmissions (Send from Serial) */
  radio.stopListening();
  if (Serial.available()){
    String msg = Serial.readStringUntil(10);
    char str[32];
    msg.toCharArray(str, msg.length() + 1);
    Serial.print("Sending: "); Serial.print(msg);
    if( radio.write(&str, sizeof(str)) ){
      Serial.println(" (Success)");
    }
    else{
      Serial.println(" (Failed)");
    }
  }
  /* Radio Transmissions (Recieve) */
  radio.startListening();
  if (radio.available()) {
    char msg[32] = "";
    radio.read(&msg, sizeof(msg));
    Serial.print("Recieved: "); Serial.println(msg);
    radio.flush_rx();
  }
  delay(1);
}