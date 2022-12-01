#include <EEPROM.h>

void setup() {
  Serial.begin(9600);

}

void loop() {

  int userinput = 0;

  //Print statements
  Serial.println("Type a number between 0 and 255 to store in EPPROM:");
  
  while(Serial.available() == 0) { 
  }

  userinput = Serial.parseInt();


  Serial.print("Value in EEPROM 0 before: ");
  Serial.println(EEPROM.read(0));

  EEPROM.write(0,userinput); //put the value of memory into EEPROM adress 0

  Serial.print("Value in EEPROM 0 after: ");
  Serial.println(EEPROM.read(0));

}
