// Code to read temperature from DHT22 without library
#include "Arduino.h"
#define MIN_INTERVAL 2000 //minimum time beetween readings
#define TIMEOUT UINT32_MAX

// Function to expect the signal line to be at the specified level for a
// period of time and return a count of loop cycles spent at that level
// if more than a millisecond ellapses without the level changing then
//the call fails with a return of 0

//want it to count the number of cycles it is high or low
uint32_t expectPulse(bool level) {
  uint16_t count = 0; 
  while (digitalRead(2) == level) {
    if (count++ >= 429496729) {
      return TIMEOUT; // Exceeded timeout, fail.
    }
  }
  return count;
}



void setup() {
  Serial.begin(9600);
  uint32_t cycles[80];
  uint8_t data[5];
  bool _lastresult;
  
  Serial.println(F("DHT22 Sensor Test!"));

  
  //////////////////////////////// Hand Shake /////////////////////////////////////
  pinMode(2, INPUT_PULLUP);
  delay(1);
  
  // Arduino pin low for 1ms minimum
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  delayMicroseconds(1100);
  
  { // Timing critical code
    
  // Arduino pin input high for 20-40us
  pinMode(2, INPUT_PULLUP);
  delayMicroseconds(55);

  //disable inturrupts maybe
  //noInterrupts();

//  if(expectPulse(LOW == TIMEOUT)){
//    Serial.println("Sensor did not send low");
//  }
//
//  if(expectPulse(HIGH == TIMEOUT)) {
//    Serial.println("Sensor did not send high");
//  }
  
  // Sensor sends low for 80us
  if (digitalRead(2) != 0){
    Serial.println("Sensor did not send low for 80us");
  }
  if (digitalRead(2) == 0){
    Serial.println("Sensor sent low for 80us!");
  }

  delayMicroseconds(80);

 // Sensor sends high for 80us
  if (digitalRead(2) != 1){
    Serial.println("Sensor did not send high for 80us");
  }
  if (digitalRead(2) == 1){
    Serial.println("Sensor sent low for 80us!");
    Serial.println(expectPulse(LOW));
    Serial.println("Sensor connection sucessful");
  }
  /////////////////////////////////////////////////////////////////////////////////

  /////////////////////////// Interpreting Pulses /////////////////////////////////
  
  for (int i = 0; i < 80; i += 2) {
      cycles[i] = expectPulse(LOW);
      cycles[i + 1] = expectPulse(HIGH);
    }
  } // Timing critical code is now complete.

  for(int loop = 0; loop < 80; loop++) {
      Serial.println(cycles[loop]);
  }

  for (int i = 0; i < 40; ++i) {
    uint32_t lowCycles = cycles[2 * i];
    uint32_t highCycles = cycles[2 * i + 1];
    if ((lowCycles == TIMEOUT) || (highCycles == TIMEOUT)) {
       Serial.println("DHT timeout waiting for pulse.");
      return;
    }
    data[i / 8] <<= 1;
    // Now compare the low and high cycle times to see if the bit is a 0 or 1.
    if (highCycles > lowCycles) {
      // High cycles are greater than 50us low cycle count, must be a 1.
      data[i / 8] |= 1;
    }
    // Else high cycles are less than (or equal to, a weird case) the 50us low
    // cycle count so this must be a zero.  Nothing needs to be changed in the
    // stored data.
  }

  // Check we read 40 bits and that the checksum matches.
  if (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)) {
    Serial.println("DHT checksum is good!");
  } 
  else {
    Serial.println("DHT checksum failure!");
  }

  

  
  /////////////////////////////////////////////////////////////////////////////////

}

void loop() {
  // put your main code here, to run repeatedly:

}
