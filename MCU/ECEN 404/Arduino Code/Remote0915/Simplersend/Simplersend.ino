#include <Arduino.h>
#include "PinDefinitionsAndMore.h" // Define macros for input and output pin etc.
#include <IRremote.hpp>

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);

}

void loop() {
   IrSender.sendNEC(0xC7EA, 0x19, 1);

   delay(1000);
}
