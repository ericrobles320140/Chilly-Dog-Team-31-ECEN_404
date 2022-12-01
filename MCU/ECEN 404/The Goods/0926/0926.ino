
//Libraries inlcuded
#include <Servo.h>
#include "DHT.h"
#include <EEPROM.h>

////////////////////////////// Temperature Sensors ////////////////////////////////
//Defining pins
#define Tempin1 30     // Digital pin connected to the DHT sensor
#define Tempin2 31

//Defining temperature sensor type
#define DHTTYPE DHT22 

//Initializing temperature sensors
DHT dht1(Tempin1, DHTTYPE);
DHT dht2(Tempin2, DHTTYPE);

//variables
float h1 = 0;
float t1 = 0;
float f1 = 0;
float h2 = 0; 
float t2 = 0; 
float f2 = 0;

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
    Serial.println(F("Failed to read from DHT sensor 1!"));
    return;
  }

  // Check if any reads failed and exit early (to try again).
  if (isnan(h2) || isnan(t2) || isnan(f2)) {
    Serial.println(F("Failed to read from DHT sensor 2!"));
    return;
  }

  //PRINT STATEMENTS
  //Serial.print(F("Humidity1: "));
  //Serial.print(h1);
  Serial.print(F("Temperature1: "));
  Serial.print(t1);
  Serial.print(F("°C "));
  Serial.print(f1);
  Serial.println(F("°F "));
  

  //Serial.print(F("Humidity2: "));
  //Serial.print(h2);
  Serial.print(F("Temperature2: "));
  Serial.print(t2);
  Serial.print(F("°C "));
  Serial.print(f2);
  Serial.println(F("°F "));
}

///////////////////////////////////////////////////////////////////////////////////


///////////////////////////// Servo Motors ////////////////////////////////////////

//Initailazing Servo Motors
Servo myservoONOFF;  // create servo object to control a servo
Servo myservoTEMPUP;  // create servo object to control a servo
Servo myservoTEMPDOWN;  // create servo object to control a servo


//Initailizing Variables
int pos = 0;    // variable to store the servo position
int on = 0;

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




void setup() {

  Serial.begin(9600);
  
  ///////////////////////////// Temperature Sensors ////////////////////////////////
  Serial.println(F("DHT22 Sensor 1 and Sensor 2 Test!"));

  //Starting temperature sensors
  dht1.begin();
  dht2.begin();
  //////////////////////////////////////////////////////////////////////////////////


  ///////////////////////////// Servo Motors ////////////////////////////////////////
  myservoONOFF.attach(2);  // attaches the servo on pin 2 to the servo object
  myservoTEMPUP.attach(4);  // attaches the servo on pin 2 to the servo object
  myservoTEMPDOWN.attach(6);  // attaches the servo on pin 2 to the servo object
  ///////////////////////////////////////////////////////////////////////////////////
}

void loop() {

  //variables
  int userinput = 0;

  ////////////////////////////// ESTABLISH CONNECTION ///////////////////////////

  //send message every 30 sec until a response from modem

  ///////////////////////////////////////////////////////////////////////////////


  ////////////////////////////// TEMP READINGS //////////////////////////////////

  //Take temperature every 2 seconds
  ReadTemp();

  //if internal cabin temp is greater than 90 degrees send notification
  if( f1 > 90 ) {
    Serial.println("WARNING: Cabin is above 90 degrees ferinheight");
  }
  
 
  //Temperature too high
  
  
  ////////////////////////////////////////////////////////////////////////////////


  /////////////////////////////// SERVO MOTOR ////////////////////////////////////

  //on/off
  //Raise temperature
  //Lower temperature

  //variables
  int lasttemp = EEPROM.read(0);
  int difference = 0;
  

  
  //Print statements
  Serial.println("Commands:");
  Serial.println("1. ON");
  Serial.println("2. OFF");
  Serial.println("or set a temperature output between 62 and 83");

  Serial.print("Value in EEPROM 0 before: ");
  Serial.println(EEPROM.read(0));

  Serial.print("Value in lasttemp before: ");
  Serial.println(lasttemp);


  //while no user input detected do nothing
  while(Serial.available() == 0) { 
  }

  userinput = Serial.parseInt();


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

        Serial.print("lasttemp - userinput = difference: ");
        Serial.print(lasttemp);
        Serial.print(" - "); 
        Serial.print(userinput);
        Serial.print(" = ");
        Serial.println(difference);

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
        Serial.println("User Input ERROR. Try again");
        Serial.println();
    }
  
  ////////////////////////////////////////////////////////////////////////////////


  

}


/////////////////////////////// NOTES ////////////////////////////////////////////

  //program uses delays which doesnt allow anything to happen until it waits
  //program can only take temp reading after button is pressed
  //user input needs to be set to a different variable setpoint
  
  
//////////////////////////////////////////////////////////////////////////////////
