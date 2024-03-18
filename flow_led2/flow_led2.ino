void setup() {
  // put your setup code here, to run once:
  for (int i = 2; i <= 7; i++) {
    pinMode(i,OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 2; i <= 4; i++) {
    digitalWrite(i,HIGH);
    digitalWrite(9 - i,HIGH);
    delay(250);
  }
  for (int i = 2; i <= 4; i++) {
    digitalWrite(i,LOW);
    digitalWrite(9 - i,LOW);
    delay(250);
  }
  for (int i = 4; i >= 2; i--) {
    digitalWrite(i,HIGH);
    digitalWrite(9 - i,HIGH);
    delay(250);
  }
  for (int i = 4; i >= 2; i--) {
    digitalWrite(i,LOW);
    digitalWrite(9 - i,LOW);
    delay(250);
  }
}