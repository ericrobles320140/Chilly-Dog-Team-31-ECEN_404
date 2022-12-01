#include <Arduino.h>
#include "PinDefinitionsAndMore.h" // Define macros for input and output pin etc.
#include <IRremote.hpp>

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);

}

void loop() {
   //IrSender.sendSamsung(0x4185, 0xFF41, 0); //turn on
   IrSender.sendSamsung(0x4085, 0xFF40, 3); //turn off
   

   delay(1000);

}
