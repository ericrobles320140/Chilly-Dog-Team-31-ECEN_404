#define TIMEOUT UINT32_MAX

uint32_t expectPulse(bool level) {
  uint16_t count = 0; 
  while (digitalRead(2) == level) {
    count++;
    Serial.println(count);
  }
  Serial.println(count);
  return count;
}

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHT22 Sensor Test!"));

  pinMode(2, INPUT_PULLUP);
  delay(1);
  
  // Arduino pin low for 1ms minimum
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  delayMicroseconds(1100);

  {
    // Arduino pin input high for 20-40us
    pinMode(2, INPUT_PULLUP);
    delayMicroseconds(55);

    expectPulse(LOW);
    expectPulse(HIGH);
  }
  

}

void loop() {
  // put your main code here, to run repeatedly:

}
