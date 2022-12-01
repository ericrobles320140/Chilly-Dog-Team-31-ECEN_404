 int age;       //Declare an Int variable to hold your age
 
void setup() {
  Serial.begin(9600);      // Initialize Serial Port
}
 
void loop() {
  Serial.println("How old are you? ");        //Prompt User for input
  while (Serial.available()==0){}             // wait for user input
  age = Serial.parseInt();                    //Read user input and hold it in a variable
 
  // Print well formatted output
  Serial.print("You are ");                 
  Serial.print(age);
  Serial.println(" years old.");
  }
