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
    digitalWrite(i + 3,HIGH);
    delay(300);
  }
  for (int i = 2; i <= 4;  i++) {
    digitalWrite(i,LOW);
    digitalWrite(i + 3,LOW);
    delay(300);
  }
  for (int i = 4; i >= 2; i--) {
    digitalWrite(i,HIGH);
    digitalWrite(i + 3,HIGH);
    delay(300);
  }
  for (int i = 4; i >= 2;  i--) {
    digitalWrite(i,LOW);
    digitalWrite(i + 3,LOW);
    delay(300);
  }
}
