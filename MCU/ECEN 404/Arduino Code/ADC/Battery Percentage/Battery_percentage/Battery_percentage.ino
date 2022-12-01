#include <Wire.h> //allows connection with I2C devices
#include <Adafruit_ADS1X15.h> // 16-bit ADC library

Adafruit_ADS1015 ads1115; //iniate 16-bit ADC

/////////////////////////// Battery Percentage ////////////////////////////////////

//variables

///////////////////////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(9600); //set baud rate

  //initial message
  Serial.println("Hello!");
  Serial.println("Getting single-ended readings from AIN0..3");
  Serial.println("ADC Range:(1 bit = 3mV)");
  
  ads1115.begin();
}

void loop() {
  int16_t adc0;

  adc0 = ads1115.readADC_SingleEnded(0);

  Serial.print("AIN0: "); Serial.println(adc0);

  Serial.println(" ");
  
  delay(1000);

}
