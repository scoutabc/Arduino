byte digits[5] = {
  B01100000,
  B11011010,
  B11110010,
  B01100110,
  B10110110,
};
int data = 4;
int latch = 5;
int clk = 6;

void setup() {
  pinMode(data,OUTPUT);
  pinMode(latch,OUTPUT);
  pinMode(clk,OUTPUT);
}

void writeDigits(int digit) {
  digitalWrite(latch,LOW);
  shiftOut(data,clk,LSBFIRST,digits[digit - 1]);
  digitalWrite(latch,HIGH);
}

void loop() {
  digitalWrite(latch,LOW);
  shiftOut(data,clk,LSBFIRST,B11111100);
  digitalWrite(latch,HIGH);
  delay(1000);
}