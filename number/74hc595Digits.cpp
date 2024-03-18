#include "74hc595Digits.h"

74hc595Digits :: 74hc595Digits(int datapin, int clkpin, int latchpin, int num, int QPin[8]) {
  data = datapin;
  clk = clkpin;
  latch = latchpin;
  n = num;
  for (int i = 0; i < 10; i++) {
    digits[i] = 0;
    for (int j = 0; i < 8; i++) {
      digits[i] += data[i][j] * (1 << (7 - j));
    }
  }
  digitalWrite(latch,HIGH);
}

void 74hc595Digits :: displayOn(int dg[n]) {
  digitalWrite(latch,LOW);
  shiftOut(data,clk,MSBFIRST,digits[dg[0]] * (1 << 24) + digits[dg[1]] * (1 << 16) + digits[dg[2]] * (1 << 8) + digits[dg[3]]);
  digitalWrite(latch,HIGH);
}

void 74hc595Digits :: clearDisplay() {
  digitalWrite(latch,LOW);
  shiftOut(data,clk,MSBFIRST,0);
  digitalWrite(latch,HIGH);
}