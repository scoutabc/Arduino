int rowpins[4] = {3,4,5,6};
int datapin = 0;
int clockpin = 1;
int latchpin = 2;

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(rowpins[i],INPUT);
    digitalWrite(rowpins[i],HIGH);
  }
  pinMode(datapin,OUTPUT);
  pinMode(clockpin,OUTPUT);
  pinMode(latchpin,OUTPUT);
}

void display(int x, int y) {
  digitalWrite(latchpin,LOW);
  shiftOut(datapin,clockpin,MSBFIRST,pow(2,y));
  digitalWrite(latchpin,HIGH);
  pinMode(rowpins[x],OUTPUT);
  digitalWrite(rowpins[x],LOW);
  digitalWrite(latchpin,LOW);
  shiftOut(datapin,clockpin,MSBFIRST,0);
  digitalWrite(latchpin,HIGH);
  pinMode(rowpins[x],INPUT);
  digitalWrite(rowpins[x],HIGH);
}

void loop() {
  display(1,2);
}
