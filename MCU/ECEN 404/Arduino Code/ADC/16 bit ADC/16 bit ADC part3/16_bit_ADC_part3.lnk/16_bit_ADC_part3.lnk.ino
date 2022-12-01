#include <Wire.h> //library allows communication with I2C/TWI devices
#include <Adafruit_ADS1X15.h> //driver for TI's ADS1X15

//https://github.com/adafruit/Adafruit_ADS1X15

// need readADC_SingleEnded
// startADCReading
// getLastConversionResults
// read register

Adafruit_ADS1015 ads1115; //initalization for 16 bit ADC conversion

void setup(void)
{
  Serial.begin(9600);
  Serial.println("Hello!");

  ads1115.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  
  Serial.println("Getting single-ended readings from AIN0..3");
  Serial.println("ADC Range: +/- 6.144V (1 bit = 3mV)");
  ads1115.begin(); //ADC set up
}

void loop(void)
{
  int16_t adc0; //variable to store adc conversion

  adc0 = ads1115.readADC_SingleEnded(0); //single ended reading from pin 0

  Serial.print("AIN0: "); Serial.println(adc0);

  Serial.println(" ");
  
  delay(1000);
}
