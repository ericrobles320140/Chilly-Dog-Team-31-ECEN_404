// Code to read temperature from DHT22 without library
#include "Arduino.h"
#define MIN_INTERVAL 2000 //minimum time beetween readings
#define TIMEOUT UINT32_MAX
#define microsecondsToClockCycles(a) ((a) * (SystemCoreClock / 1000000L))

// Function to expect the signal line to be at the specified level for a
// period of time and return a count of loop cycles spent at that level
// if more than a millisecond ellapses without the level changing then
//the call fails with a return of 0
//uint32_t expectPulse(bool level) {
//  uint16_t count = 0; 
//  while (digitalRead(2) == level) {
//    if (count++ >= _maxcycles)  {
//      return TIMEOUT;
//    }
//    return count;
//  }
//}


uint32_t expectPulse(bool level) {
  uint32_t _maxcycles;
  _maxcycles = microsecondsToClockCycles(1000);
  uint16_t count = 0; 
  while (digitalRead(2) == level) {
    if (count++ >= _maxcycles) {
      return TIMEOUT; // Exceeded timeout, fail.
    }
  }
  return count;
}



void setup() {
  Serial.begin(9600);
  long int t1 = micros();
  Serial.println(t1);
  
  Serial.println(F("DHT22 Sensor Test!"));
  
  //////////////////////////////// Hand Shake /////////////////////////////////////
  pinMode(2, INPUT_PULLUP);
  delay(1);
  
  // Arduino pin low for 1ms minimum
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  delayMicroseconds(1100);
  
  // Arduino pin input high for 20-40us
  pinMode(2, INPUT_PULLUP);
  delayMicroseconds(55);

  //disable inturrupts maybe
  //noInterrupts();

  if(expectPulse(LOW == TIMEOUT)){
    Serial.println("Sensor did not send low");
  }

  if(expectPulse(HIGH == TIMEOUT)) {
    Serial.println("Sensor did not send high");
  }
  
//  // Sensor sends low for 80us
//  if (digitalRead(2) != 0){
//    Serial.println("Sensor did not send low for 80us");
//  }
//
//  delayMicroseconds(80);
//
// // Sensor sends high for 80us
//  if (digitalRead(2) != 1){
//    Serial.println("Sensor did not send high for 80us");
//  }
  else {
    Serial.println("Sensor connection sucessful");
  }

  delayMicroseconds(80);
  /////////////////////////////////////////////////////////////////////////////////

  /////////////////////////// Interpreting Pulses /////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////////

}

void loop() {
  // put your main code here, to run repeatedly:

}
