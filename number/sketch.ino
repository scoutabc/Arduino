#include <LedControl.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int din = 11;
int cs = 10;
int clk = 13;
LedControl lc = LedControl(din,clk,cs,1);

LiquidCrystal_I2C lcd(0x27,16,2);

void turn_on(int x,int y);
void turn_off(int x,int y);
void setObstacle();

void setup() {
  //lc.shutdown(0,false);
  //lc.setIntensity(0,8);
  //randomSeed(analogRead(0));
  //setObstacle();
  lcd.init();
  lcd.backlight();
}

void loop() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Arduino");
  delay(2000);
}

void turn_on(int x, int y) {
  lc.setLed(0,x,y,true);
}

void turn_off(int x, int y) {
  lc.setLed(0,x,y,false);
}

void setObstacle() {
  for (int i = 0; i < 8; i++) {
    lc.setLed(0,i,random(1,8),true);
  }
}