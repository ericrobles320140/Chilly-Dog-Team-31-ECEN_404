//Libraries included
#include <Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial bt (8, 9);

//////////////////////////////////// Bluetooth ////////////////////////////////////
String readFromBT() {
  char c = ' ';
  String message = "";

  while (bt.available() > 0) {
    c = bt.read();
    message += c;
    }
  Serial.println(message);
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
  for (pos = 0; pos >= 90; pos -= 1) { // goes from 0 degrees to 180 degrees
     // in steps of 1 degree
     myservoONOFF.write(pos);              // tell servo to go to position in variable 'pos'
     delay(15);                       // waits 15 ms for the servo to reach the position
  }
  for (pos = 90; pos <= 0; pos += 1) { // goes from 180 degrees to 0 degrees
     myservoONOFF.write(pos);              // tell servo to go to position in variable 'pos'
     delay(15);                       // waits 15 ms for the servo to reach the position
  }

  on++;
  //serial.print("On: ");
  //serial.print(on);
  
  
}

//TEMP UP
void PushButtonTEMPUP(){
  for (pos = 0; pos >= 90; pos -= 1) { // goes from 0 degrees to 180 degrees
     // in steps of 1 degree
     myservoTEMPUP.write(pos);              // tell servo to go to position in variable 'pos'
     delay(15);                       // waits 15 ms for the servo to reach the position
  }
  for (pos = 90; pos <= 0; pos += 1) { // goes from 180 degrees to 0 degrees
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
  /////////////////////////////// Serial ////////////////////////////////////////////
  Serial.begin(9600);
  bt.begin(9600);
  //////////////////////////////////////////////////////////////////////////////////
  
  ///////////////////////////// Servo Motors ////////////////////////////////////////
  myservoONOFF.attach(3);  // attaches the servo on pin 2 to the servo object
  myservoTEMPUP.attach(5);  // attaches the servo on pin 4 to the servo object
  myservoTEMPDOWN.attach(6);  // attaches the servo on pin 6 to the servo object
  ///////////////////////////////////////////////////////////////////////////////////

}

void loop() {
  //variables
  String userinputString = "0";
  int userinput = 0;

  //while no user input detected do nothing
  while(bt.available() == 0) {
    //Serial.println("No user input");
  }

   userinputString = secondHalf(readFromBT());
   //Serial.print("user input string: ");
   //Serial.println(userinputString);
  Serial.println(userinputString);
  if (userinputString != "") {
    userinput = userinputString.toInt();
  }
   //Serial.print("user input: ");
   //Serial.println(userinput);


   
    switch(userinput) {
      case 1: //ON
        PushButtonONOFF();
        break;
    }
}
  
