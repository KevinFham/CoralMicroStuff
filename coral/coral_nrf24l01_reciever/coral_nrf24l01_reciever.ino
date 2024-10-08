/*
 Setup

 - nRF24L01 requires 3.3V
 - MISO/MOSI or CIPO/COPI on Coral SPI6_SDI/SPI6_SDO
 - SCK on Coral SPI6_SCK
 - nRF "CSN" to Coral pin A4 (alternatively, D3)
 - nRF "CE" to Coral pin A3 (alternatively, D2) (For some reason not necessary?)

  Requires a secondary nRF24L01 available to send data
*/

#include <RF24Network.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(A3, A4); // CE, CSN
// RF24 radio(D2, D3); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};   //Channel 00001: Transmitter (Write), Reciever (Read)
                                                  //Channel 00002: Transmitter (Read), Reciever (Write)
unsigned long BAUD_RATE = 115200;
/*
 Setup
*/
void setup() {
  Serial.begin(BAUD_RATE);
  radio.begin();
  radio.setPayloadSize(16);       //Maximum size buffer
  radio.setDataRate(RF24_2MBPS);  //Can be set to either RF24_2MBPS, RF24_1MBPS, or RF24_250KBPS (Must be RF24_2MBPS for the Coral)
  radio.setPALevel(RF24_PA_MIN);  //Radio TX power to MIN
  radio.setRetries(15, 15);
  // radio.setCRCLength(RF24_CRC_8);
  radio.setChannel(2);          //Channel least likely to use Wifi, Microwave, etc. (Can also use 2)
  // radio.setAutoAck(false);
  radio.openWritingPipe(addresses[1]);
  radio.openReadingPipe(1, addresses[0]);
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

// void loop() {
//   /* Radio Transmissions (Constant repeat message) */
//   radio.stopListening();
//   String msg = "penis cock balls";
//   char str[32];
//   msg.toCharArray(str, msg.length() + 1);
//   Serial.print("Sending: "); Serial.println(msg);
//   radio.write(&str, sizeof(str));
//   delay(1000);
// }