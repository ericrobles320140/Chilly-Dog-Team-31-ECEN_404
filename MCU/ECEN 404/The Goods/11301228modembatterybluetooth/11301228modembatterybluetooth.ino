//Libraries inlcuded
#include <Servo.h>
#include "DHT.h"
#include <EEPROM.h>
#include <Wire.h> //library allows communication with I2C/TWI devices
#include <Adafruit_ADS1X15.h> //driver for TI's ADS1X15
#include <SparkFun_LTE_Shield_Arduino_Library.h>

//////////////////////////////////// Bluetooth ////////////////////////////////////
String readFromBT() {
  char c = ' ';
  String message = "";

  while (Serial.available() > 0) {
    c = Serial.read();
    message += c;
    }
  return message;
  }


  String secondHalf(String m) {
  String p = "";
  String temp = "temp";
  String utemp = "utemp";
  String emp = "emp";
  String checker = "";
  bool halfFound = false;
  for (int i = 0; i < m.length(); i++) {
    if (m[i] != ':' && halfFound && (checker == utemp || checker == temp || checker == emp)){
      p += m[i];
    } 
    else if (m[i] == ':') {
      halfFound = true;
    }
    else {
      checker += m[i];
      }
  }
  return p;
}
///////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////// Modem ///////////////////////////////////////

LTE_Shield lte;
SoftwareSerial lteSerial(8, 9); //defining pins for software serial
int i = 1;
String number = "17379009086";
String message = "";

///////////////////////////////////////////////////////////////////////////////////

////////////////////////////// Temperature Sensors ////////////////////////////////
//Defining pins
#define Tempin1 2     // Digital pin connected to the DHT sensor
#define Tempin2 4

//Defining temperature sensor type
#define DHTTYPE DHT22 

//Initializing temperature sensors
DHT dht1(Tempin1, DHTTYPE);
DHT dht2(Tempin2, DHTTYPE);

//variables
float h1 = 0; // humidity from sensor 1
float t1 = 0; // temperature from sensor 1 celsius
float f1 = 0; // temperature from sensor 1 Fahrenheit 
float h2 = 0; // humidity from sensor 2
float t2 = 0; // temperature from sensor 2 celsius
float f2 = 0; // temperature from sensor 2 Fahrenheit

//Functions
void ReadTemp() {
    // Wait a few seconds between measurements.
  delay(2000);
  
  //take temperature and load them into variables
  //humidity reading from sensor 1
  h1 = dht1.readHumidity();
  // Read temperature as Celsius (the default)
  t1 = dht1.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  f1 = dht1.readTemperature(true);


  //humidity reading from sensor 2
  h2 = dht2.readHumidity();
  // Read temperature as Celsius (the default)
  t2 = dht2.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  f2 = dht2.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h1) || isnan(t1) || isnan(f1)) {
    
    //Send Modem read DHT sensor 1 failure
    lte.begin(lteSerial, 9600); //must run this before every send
    message = "err:"+String(int(1));
    lte.sendSMS(number, message);
    
    ////serial.println(F("ERROR 1: Failed to read from DHT sensor 1!"));
    //return;
  }

  // Check if any reads failed and exit early (to try again).
  if (isnan(h2) || isnan(t2) || isnan(f2)) {

    //Send Modem read DHT sensor 2 failure
    lte.begin(lteSerial, 9600); //must run this before every send
    message = "err:"+String(int(2));
    lte.sendSMS(number, message);
    
    ////serial.println(F("ERROR 2: Failed to read from DHT sensor 2!"));
    //return;
  }

  //MODEM OUTPUT
  //Send Internal Temperature
  lte.begin(lteSerial, 9600); //must run this before every send
  message = "itemp:"+String(int(floor(f1)));
  lte.sendSMS(number, message);

  //Send External Temperature
  lte.begin(lteSerial, 9600); //must run this before every send
  message = "otemp:"+String(int(floor(f2)));
  lte.sendSMS(number, message);

  //PRINT STATEMENTS
  ////serial.print(F("Humidity1: "));
  ////serial.print(h1);
  //serial.print(F("Temperature1: "));
  //serial.print(t1);
  //serial.print(F("°C "));
  //serial.print(f1);
  //serial.println(F("°F "));
  

  ////serial.print(F("Humidity2: "));
  ////serial.print(h2);
  //serial.print(F("Temperature2: "));
  //serial.print(t2);
  //serial.print(F("°C "));
  //serial.print(f2);
  //serial.println(F("°F "));

  
  //WARNINGS
  //Temperature too high
  //if internal cabin temp is greater than 90 degrees send notification
  if( f1 > 90 ) {

    //Send Modem warning of 90 degrees temp
    lte.begin(lteSerial, 9600); //must run this before every send
    message = "err:"+String(int(10));
    lte.sendSMS(number, message);
    
    ////serial.println("WARNING 10: Cabin is above 90 degrees ferinheight");
  }

  if( f1 > 100 ) {

    //Send Modem warning of 100 degrees temp
    lte.begin(lteSerial, 9600); //must run this before every send
    message = "err:"+String(int(12));
    lte.sendSMS(number, message);
    
    ////serial.println("WARNING 12: Cabin is above 100 degrees ferinheight return to your vehicle immediatley");
  }

  //Temperature too low
  if( f1 < 40) {

    //Send Modem warning of 40 degrees temp
    lte.begin(lteSerial, 9600); //must run this before every send
    message = "err:"+String(int(11));
    lte.sendSMS(number, message);
    
    ////serial.print("WARNING 11: Cabin is below 40 degrees ferinheight");
  }
}

///////////////////////////////////////////////////////////////////////////////////


///////////////////////////// Servo Motors ////////////////////////////////////////

//Initailazing Servo Motors
Servo myservoONOFF;  // create servo object to control a servo
Servo myservoTEMPUP;  // create servo object to control a servo
Servo myservoTEMPDOWN;  // create servo object to control a servo


//Initailizing Variables
int pos = 0;    // variable to store the servo position
int on = 0;     //variable to determine on off status of AC

//Functions
//ON/OFF
void PushButtonONOFF(){
  for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
     // in steps of 1 degree
     myservoONOFF.write(pos);              // tell servo to go to position in variable 'pos'
     delay(15);                       // waits 15 ms for the servo to reach the position
  }
  for (pos = 90; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
     myservoONOFF.write(pos);              // tell servo to go to position in variable 'pos'
     delay(15);                       // waits 15 ms for the servo to reach the position
  }

  on++;
  //serial.print("On: ");
  //serial.print(on);
  
  
}

//TEMP UP
void PushButtonTEMPUP(){
  for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
     // in steps of 1 degree
     myservoTEMPUP.write(pos);              // tell servo to go to position in variable 'pos'
     delay(15);                       // waits 15 ms for the servo to reach the position
  }
  for (pos = 90; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
     myservoTEMPUP.write(pos);              // tell servo to go to position in variable 'pos'
     delay(15);                       // waits 15 ms for the servo to reach the position
  }
}

//TEMP DOWN
void PushButtonTEMPDOWN(){
  for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
     // in steps of 1 degree
     myservoTEMPDOWN.write(pos);              // tell servo to go to position in variable 'pos'
     delay(15);                       // waits 15 ms for the servo to reach the position
  }
  for (pos = 90; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
     myservoTEMPDOWN.write(pos);              // tell servo to go to position in variable 'pos'
     delay(15);                       // waits 15 ms for the servo to reach the position
  }
}


///////////////////////////////////////////////////////////////////////////////////

/////////////////////////// Battery Percentage ////////////////////////////////////

//variables
int ADCsensorpin = A0; // input pin for ADC
int digitalvalue = 0; // variable to store ADC conversion

//Functions
float DigitaltoAnalog(int digitalValue) {
  float analogVoltage = 0.00;
  analogVoltage = digitalValue * (5/1023);
  return(analogVoltage);
}

void ReadBattery(void) {
  digitalvalue = analogRead(ADCsensorpin); // read the value from the ADC
  int batterypercentage = 0;

  //serial.println();
  //serial.println("------- BATTERY PERCENTAGE --------");
  //serial.println();
  //serial.println("Digital Value: ");
  //serial.println(digitalvalue);

  // Battery is 100% charged
  if(digitalvalue <= 853 && digitalvalue > 823) { //if 4.211V >= Vin > 4.064V
    batterypercentage = 100;
    //serial.println("100%");
  }

  // Battery is 75% charged
  if(digitalvalue <= 823 && digitalvalue > 794) { //if 4.064V >= Vin > 3.919V
    batterypercentage = 75;
    //serial.println("75%");
  }

  // Battery is 50% charged
  if(digitalvalue <= 794 && digitalvalue > 764) { //if 3.919V >= Vin > 3.773V
    batterypercentage = 50;
    //serial.println("50%");
  }

  // Battery is 25% charged
  if(digitalvalue <= 764 && digitalvalue > 746) { //if 3.773V >= Vin > 3.686V
    batterypercentage = 25;

    //Send Modem low battery warning 25%
    lte.begin(lteSerial, 9600); //must run this before every send
    message = "err:"+String(int(14));
    lte.sendSMS(number, message);
    
    //serial.println("25%");
  }

    // Battery is 10% charged
  if(digitalvalue <= 746 && digitalvalue > 740) { //if 3.686V >= Vin > 3.657V
    batterypercentage = 10;

    //Send Modem low battery warning 10%
    lte.begin(lteSerial, 9600); //must run this before every send
    message = "err:"+String(int(15));
    lte.sendSMS(number, message);
    
    ////serial.println("10%");
  }

    // Battery is dead
  if(digitalvalue <= 740 && digitalvalue > 0) { //if 3.657V >= Vin > 0V
    batterypercentage = 0;

    //Send Modem warning of 10 percent battery
    lte.begin(lteSerial, 9600); //must run this before every send
    message = "err:"+String(int(13));
    lte.sendSMS(number, message);
    
    ////serial.println("WARNING 13: Chilly Dog battery is LOW. Return to your car immediately");
  }

    //Battery out of range
  if(isnan(digitalvalue) || digitalvalue > 853) {

    //Send Modem battery percentage read error
    lte.begin(lteSerial, 9600); //must run this before every send
    message = "err:"+String(int(3));
    lte.sendSMS(number, message);
    
    ////serial.println("ERROR 3: Cannot read Battery Percentage");
  }

  //serial.println();

  // MODEM MESSAGE
    lte.begin(lteSerial, 9600); //must run this before every send
    message = "bat:"+String(int(floor(batterypercentage)));
    lte.sendSMS(number, message);
}



///////////////////////////////////////////////////////////////////////////////////

void setup() {

  Serial.begin(9600);

  ///////////////////////////////////// Modem //////////////////////////////////////
  //set baud rate for UART communiacation
  lte.begin(lteSerial, 9600);
  

  //////////////////////////////////////////////////////////////////////////////////
  
  ///////////////////////////// Temperature Sensors ////////////////////////////////
  //serial.println(F("DHT22 Sensor 1 and Sensor 2 Test!"));

  //Starting temperature sensors
  dht1.begin();
  dht2.begin();
  //////////////////////////////////////////////////////////////////////////////////


  ///////////////////////////// Servo Motors ////////////////////////////////////////
  myservoONOFF.attach(3);  // attaches the servo on pin 2 to the servo object
  myservoTEMPUP.attach(5);  // attaches the servo on pin 4 to the servo object
  myservoTEMPDOWN.attach(6);  // attaches the servo on pin 6 to the servo object
  ///////////////////////////////////////////////////////////////////////////////////
}

void loop() {

  //variables
  String userinputString = "";
  int userinput = 0;

  ////////////////////////////// ESTABLISH CONNECTION ///////////////////////////

  //send message every 30 sec until a response from modem

  ///////////////////////////////////////////////////////////////////////////////


  ////////////////////////////// TEMP READINGS //////////////////////////////////
  
  
  ////////////////////////////////////////////////////////////////////////////////

  ///////////////////////// BATTERY PERCENTAGE ///////////////////////////////////

  
  ////////////////////////////////////////////////////////////////////////////////


  /////////////////////////////// SERVO MOTOR ////////////////////////////////////

  //on/off
  //Raise temperature
  //Lower temperature

  //variables
  int lasttemp = EEPROM.read(0);
  int difference = 0;
  
  
  //Print statements
  //serial.println();
  //serial.println("Commands:");
  //serial.println("1. ON");
  //serial.println("2. OFF");
  //serial.println("or set a temperature output between 62 and 83");
  //serial.println();

  ////serial.print("Value in EEPROM 0 before: ");
  ////serial.println(EEPROM.read(0));

  ////serial.print("Value in lasttemp before: ");
  ////serial.println(lasttemp);
  ////serial.println();


  //while no user input detected do nothing
  while(Serial.available() == 0) {
    ReadTemp();
    ReadBattery();
  }

  userinputString = secondHalf(readFromBT());

  if (userinputString != "") {
    userinput = userinputString.toInt();
  }

  
  //Serial.parseInt();


    switch(userinput) {
      case 1: //ON
        PushButtonONOFF();
        break;
      case 2: //OFF
        PushButtonONOFF();
        break;
      case 62:
      case 63:
      case 64:
      case 65:
      case 66:
      case 67:
      case 68:
      case 69: 
      case 70:
      case 71:
      case 72: 
      case 73:
      case 74: 
      case 75:
      case 76:
      case 77:
      case 78:
      case 79:
      case 80:
      case 81: 
      case 82:
      case 83:
        
        //determine difference of setpoint and last temp
        difference = lasttemp - userinput;

        //update EEPROM with userinput
        EEPROM.write(0,userinput);

        //update lasttemp with userinput
        lasttemp = EEPROM.read(0);

        //serial.print("lasttemp - userinput = difference: ");
        //serial.print(lasttemp);
        //serial.print(" - "); 
        //serial.print(userinput);
        //serial.print(" = ");
        //serial.println(difference);

        if(difference < 0) {
          difference = abs(difference);
          for( int i = 0 ; i < difference ; i++){
            PushButtonTEMPUP();
          }
        }

        if(difference > 0) {
          for( int i = 0 ; i < difference ; i++){
            PushButtonTEMPDOWN();
          }
        }
        break;
     default: 
     
        //Send Modem User Input Error
        lte.begin(lteSerial, 9600); //must run this before every send
        message = "err:"+String(int(4));
        lte.sendSMS(number, message);
     
        ////serial.println("ERROR 4: User Input error. Try again");
        ////serial.println();
    }
  
  ////////////////////////////////////////////////////////////////////////////////


  

}


/////////////////////////////// NOTES ////////////////////////////////////////////

  //program uses delays which doesnt allow anything to happen until it waits
  //notifications
  
//////////////////////////////////////////////////////////////////////////////////
