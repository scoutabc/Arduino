#include<Arduino.h>
#define Q0 0
#define Q1 1
#define Q2 2
#define Q3 3
#define Q4 4
#define Q5 5
#define Q6 6
#define Q7 7
byte data[10][8] ={
  {1,1,1,1,1,1,0,0},
  {0,1,1,0,0,0,0,0},
  {1,1,0,1,1,0,1,0},
  {1,1,1,1,0,0,1,0},
  {0,1,1,0,0,1,1,0},
  {1,0,1,1,0,1,1,0},
  {1,0,1,1,1,1,1,0},
  {1,1,1,0,0,0,0,0},
  {1,1,1,1,1,1,1,0},
  {1,1,1,1,0,1,1,0}
};

class 74hc595Digits {
  public:
    74hc595Digits(int datapin,int clkpin,int latchpin,int num,int QPin[8]);
    void displayOn(int dg[n]);
    void clearDisplay();
  private:
    byte digits[10];
    int data,clk,latch,n;
};