#include"74hc595Digits.h"

int a = 10;
int b = 11;
int c = 5;
int d = 7;
int e = 6;
int f = 9;
int g = 8;
int number = 0;
int button = 12;
int numberState = false;
Digital dice(a,b,c,d,e,f,g);

void setup() {
  // put your setup code here, to run once:
  for (int i = 5; i < 12; i++) {
    pinMode(i,OUTPUT);
    digitalWrite(i,HIGH);
  }
  pinMode(13,OUTPUT);
  pinMode(button,INPUT);
  numberState = 0;
}
void loop() {
  for (int i = 1; i <= 5; i++) {
    dice.select_on(i);
    if (digitalRead(button) == HIGH)numberState = true;
    if (numberState == true) {
      delay(300);
      while(digitalRead(button) == LOW);
      numberState = false;
      delay(200);
    }
    delay(50);
    dice.select_off(i);
  }
}