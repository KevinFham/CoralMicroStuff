#include "Arduino.h"

int led_pin = PIN_LED_USER;
int button_pin = PIN_BTN;
PinStatus val = LOW;

void setup() {
  Serial.begin(115200);
  // Turn on Status LED to show the board is on.
  pinMode(PIN_LED_STATUS, OUTPUT);
  digitalWrite(PIN_LED_STATUS, HIGH);
  Serial.println("Arduino Button LED!");

  pinMode(led_pin, OUTPUT);
  pinMode(button_pin, INPUT);
}

void loop() {
  val = digitalRead(button_pin);
  digitalWrite(led_pin, val == LOW ? HIGH : LOW);

  Serial.println("Hello World");
  delay(100);
}