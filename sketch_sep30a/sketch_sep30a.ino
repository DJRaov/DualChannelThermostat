void setup() {
  // put your setup code here, to run once:
 pinmode(13, OUTPUT);
 Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.writeln("test");
  delay(500);
}
