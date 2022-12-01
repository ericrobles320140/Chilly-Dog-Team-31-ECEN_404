
//Libraries inlcuded
#include <Servo.h>
#include "DHT.h"

////////////////////////////// Temperature Sensors ////////////////////////////////
//Defining pins
#define Tempin1 30     // Digital pin connected to the DHT sensor
#define Tempin2 31

//Defining temperature sesnor type
#define DHTTYPE DHT22 

//Initializing temperature sensors
DHT dht1(Tempin1, DHTTYPE);
DHT dht2(Tempin2, DHTTYPE);

//Functions
void ReadTemp() {
    // Wait a few seconds between measurements.
  delay(2000);
  
  //take temperature and load them into variables
  //humidity reading from sensor 1
  float h1 = dht1.readHumidity();
  // Read temperature as Celsius (the default)
  float t1 = dht1.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f1 = dht1.readTemperature(true);


  //humidity reading from sensor 2
  float h2 = dht2.readHumidity();
  // Read temperature as Celsius (the default)
  float t2 = dht2.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f2 = dht2.readTemperature(true);

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
Servo myservo;  // create servo object to control a servo


//Initailizing Variables
int pos = 0;    // variable to store the servo position
int on = 0;

//Functions
void PushButton(){
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
     // in steps of 1 degree
     myservo.write(pos);              // tell servo to go to position in variable 'pos'
     delay(15);                       // waits 15 ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
     myservo.write(pos);              // tell servo to go to position in variable 'pos'
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
  myservo.attach(2);  // attaches the servo on pin 2 to the servo object
  ///////////////////////////////////////////////////////////////////////////////////
}

void loop() {

  //variables
  int userinput = "0";

  ////////////////////////////// ESTABLISH CONNECTION ///////////////////////////

  //send message every 30 sec until a response from modem

  ///////////////////////////////////////////////////////////////////////////////


  ////////////////////////////// TEMP READINGS //////////////////////////////////

  
  
  ////////////////////////////////////////////////////////////////////////////////


  /////////////////////////////// SERVO MOTOR ////////////////////////////////////

  //on/off
  //Raise temperature
  //Lower temperature

  
  //Print statements
  Serial.println("Commands:");
  Serial.println("1. ON");
  Serial.println("2. OFF");
  Serial.println("or set a temperature output between 62 and 83");


  //while no user input detected do nothing
  while(Serial.available() == 0) { 
  }

  userinput = Serial.parseInt();

    switch(userinput) {
      case 1:
        PushButton();
      case 2: 
        PushButton();
      case 62:
        PushButton();
      case 63:
        PushButton();
     default: 
        Serial.println("User Input ERROR. Try again");
        Serial.println();
    }
  
  ////////////////////////////////////////////////////////////////////////////////


  

}


/////////////////////////////// NOTES ////////////////////////////////////////////

  //program uses delays which doesnt allow anything to happen until it waits
  //program can only take temp reading after button is pressed
  //its doign everything twice for some reason
  
  
//////////////////////////////////////////////////////////////////////////////////
