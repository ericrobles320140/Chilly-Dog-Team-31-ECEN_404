int ifread;

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);

}

void loop() {
  ifread = analogRead(A0);

  Serial.println(ifread);
}
