#include <IRremote.h>

#define IR_RECEIVE_PIN 11
#define IR_BUTTON_on 65345
#define IR_BUTTON_off 65344

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN);
}

void loop() {
  if (IrReceiver.decode()) {
    IrReceiver.resume();
    Serial.println(IrReceiver.decodedIRData.command);
  }
}
