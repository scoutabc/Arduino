#include <LedControl.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <stdio.h>
class exercise {
  public:
    char practise[15];
    char result[10];
    void init() {
      randomSeed(analogRead(0));
      int n[50];
      int num = get_primes(n);
      int index = (int)random(0,num + 1);
      int a = 0,b = 0;
      while (a == b) {
        a = (int)random(1,100 / n[index] + 1);
        b = (int)random(1,100 / n[index] + 1);
      }
      int first = a * n[index];
      int second = b * n[index];
      int y = get_result(first,second);
      if (first / 10 == 0 && second / 10 == 0) {
        sprintf(practise," %d/ %d=",first,second);
      }else if (first / 10 == 0) {
        sprintf(practise," %d/%d=",first,second);
      }else if (second / 10 == 0) {
        sprintf(practise,"%d/ %d=",first,second);
      }else {
        sprintf(practise,"%d/%d=",first,second);
      }
      first /= y;
      second /= y;
      sprintf(result,"%d#%d",first,second);
    }
  private:
    bool is_prime(int n) {
      for (int i = 2; i < (int)sqrt(n); i++) {
        if (n % i == 0) {
          return false;
        }
      }
      return true;
    }
    int get_primes(int n[]) {
      int index = 0;
      for (int i = 2; i < 50; i++) {
        if (is_prime(i)) {
          n[index] = i;
          index++;
        }
      }
      return index + 1;
    }
    int get_result(int a,int b) {
      if (a == 0 || b == 0) {
        return a > b ? a : b;
      }
      int x = a > b ? a : b;
      int n = a < b ? a : b;
      int r = x % n;
      return get_result(n,r);
    }
};
exercise ex;

int quesnum = 4;
int randoms[16];
int jump_a = -1;
int jump_b = -1;
int is_a = true;
int button1 = 2;
int button2 = 3;
int diceButton = 12;
int ax = 0;
int ay = 7;
int bx = 4;
int by = 7;
int steps = 4;

int din = 11;
int cs = 10;
int clk = 13;
int xy = 0;
LedControl lc = LedControl(din, clk, cs, 1);

LiquidCrystal_I2C lcd(0x27, 20, 4);

int latch = 5;
int hcclk = 6;
int data = 4;
byte digits[5] = {
  B01100000,
  B11011010,
  B11110010,
  B01100110,
  B10110110,
};
int randomsidA = 0;
int randomsidB = 8;
int rows = 4;
int cols = 4;
char keys[4][4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[4] = {7, 8, 9, 1};
byte colPins[4] = {0, A1, A2, A3};
Keypad customKeypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

void turn_on(int x, int y);
void turn_off(int x, int y);
void setObstacle();
void blink(int x, int y);
void succes(bool aOrb);
void displayNumber(int n);
int dice();
void is_prime(int n);
void get_prime(int n[]);
bool is_correct();
void print_information();
void print_first();

void setup() {
  pinMode(data, OUTPUT);
  pinMode(hcclk, OUTPUT);
  pinMode(latch, OUTPUT);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(diceButton, INPUT);
  ex.init();
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  randomSeed(analogRead(0));
  turn_on(ax, ay);
  turn_on(bx, by);
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void loop() {
  print_first();
  setObstacle(randoms);
  print_information();
  steps = dice();
  while (1) {
    if (is_a) {
      if (digitalRead(button1) == HIGH) {
        turn_off(ax, ay);
        if (ay == 6 && ax == 3) {
          turn_on(ax, ay + 1);
          succes(true);
        } else if ((ay == 0 && jump_a == -1) || (ay == 7 && jump_a == 1)) {
          ax += 1;
          randomsidA += 1;
          turn_on(ax, ay);
          jump_a *= (-1);
          steps -= 1;
          lcd.clear();
          print_information();
        } else if ((ay == 4 && jump_a == -1) || (ay == 3 && jump_a == 1)) {
          randomsidA += 1;
          ay += jump_a;
          turn_on(ax, ay);
          steps -= 1;
          lcd.clear();
          print_information();
        }else {
          ay += jump_a;
          turn_on(ax, ay);
          steps -= 1;
          lcd.clear();
          print_information();
        }
        if (ay == randoms[randomsidA]) {
          if (is_correct()) {
            steps += 2;
          }else {
            steps = 0;
          }
        }
        if (steps == 0) {
          is_a = false;
          steps = dice();
          lcd.clear();
          print_information();
        }
        delay(300);
      }
    } else {
      if (digitalRead(button2) == HIGH) {
        turn_off(bx, by);
        if (by == 6 && bx == 7) {
          turn_on(bx, by + 1);
          succes(false);
        } else if ((by == 0 && jump_b == -1) || (by == 7 && jump_b == 1)) {
          bx += 1;
          randomsidB += 1;
          turn_on(bx, by);
          jump_b *= (-1);
          steps -= 1;
          lcd.clear();
          print_information();
        } else if ((by == 3 && (bx == 5 || bx == 7)) || (by == 4 && (bx == 4 || bx == 6))) {
            randomsidB += 1;
            by += jump_b;
            turn_on(bx,by);
            steps -= 1;
            lcd.clear();
            print_information();
        }else {
          by += jump_b;
          turn_on(bx, by);
          steps -= 1;
          lcd.clear();
          print_information();
        }
        if (by == randoms[randomsidB]) {
          if (is_correct()) {
            steps += 2;
          }else {
            steps = 0;
          }
        }
        if (steps == 0) {
          is_a = true;
          steps = dice();
          lcd.clear();
          print_information();
        }
        delay(300);
      }
    }
  }
}

void turn_on(int x, int y) {
  lc.setLed(0, x, y, true);
}

void turn_off(int x, int y) {
  lc.setLed(0, x, y, false);
}

void setObstacle(int randoms[16]) {
  if (quesnum == 2) {
    for (int i = 0; i < 4; i++) {
      int j = random(0,4);
      if (j == 0) {
        randoms[4 * i] = random(4,7);
        turn_on(i * 2,randoms[4 * i]);
        randoms[4 * i + 1] = 9;
        randoms[4 * i + 2] = 9;
        randoms[4 * i + 3] = 9;
      }else if (j == 1) {
        randoms[4 * i] = 9;
        randoms[4 * i + 1] = random(1,4);
        turn_on(i * 2,randoms[4 * i + 1]);
        randoms[4 * i + 2] = 9;
        randoms[4 * i + 3] = 9; 
      }else if (j == 2) {
        randoms[4 * i] = 9;
        randoms[4 * i + 1] = 9;
        randoms[4 * i + 2] = random(1,4);
        turn_on(i * 2 + 1,randoms[4 * i + 2]);
        randoms[4 * i + 3] = 9; 
      }else if (j == 3) {
        randoms[4 * i] = 9;
        randoms[4 * i + 1] = 9;
        randoms[4 * i + 2] = 9;
        randoms[4 * i + 3] = random(4,7); 
        turn_on(i * 2 + 1,randoms[4 * i + 3]);
      }
    }
  }else if (quesnum == 4) {
    for (int i = 0; i < 4; i++) {
      int j1 = random(0,2);
      int j2 = random(0,2);
      if (j1 == 0) {
        randoms[4 * i] = random(4,7);
        turn_on(2 * i,randoms[4 * i]);
        printf("%d\n", randoms[4 * i]);
        randoms[4 * i + 1] = 9;
      }else if (j1 == 1) {
        randoms[4 * i] = 9;
        randoms[4 * i + 1] = random(1,4);
        turn_on(2 * i,randoms[4 * i + 1]);
        printf("%d\n", randoms[4 * i + 1]);
      }
      if (j2 == 0) {
        randoms[4 * i + 2] = random(1,4);
        turn_on(2 * i + 1,randoms[4 * i + 2]);
        randoms[4 * i + 3] = 9;
        printf("%d\n", randoms[4 * i + 2]);
      }else if (j2 == 1) {
        randoms[4 * i + 2] = 9;
        randoms[4 * i + 3] = random(4,7);
        turn_on(2 * i + 1,randoms[4 * i + 3]);
        printf("%d\n", randoms[4 * i + 3]);
      }
    }
  }else if (quesnum == 8) {
    for (int i = 0; i < 4; i++) {
      randoms[4 * i] = random(4,7);
      turn_on(2 * i,randoms[4 * i]);
      randoms[4 * i + 1] = random(1,4);
      turn_on(2 * i,randoms[4 * i + 1]);
      randoms[4 * i + 2] = random(1,4);
      turn_on(2 * i + 1,randoms[4 * i + 2]);
      randoms[4 * i + 3] = random(4,7);
      turn_on(2 * i + 1,randoms[4 * i + 3]);
    }
  }
}

void blink(int x, int y) {
  lc.setLed(0, x, y, true);
  delay(100);
  lc.setLed(0, x, y, false);
  delay(100);
}
void print_exercise(char exercise[]) {
  lcd.setCursor(4, 2);
  lcd.print(exercise);
}
void succes(bool aOrb) {
  if (aOrb) {
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("The WINNER is...");
    delay(5000);
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("The WINNER is Player A!!!");
  }else {
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("The WINNER is...");
    delay(5000);
    lcd.setCursor(0,1);
    lcd.print("The WINNER is Player B!!!");
  }
}
void displayNumber(int n) {
  digitalWrite(latch, LOW);
  shiftOut(data, hcclk, LSBFIRST, digits[n - 1]);
  digitalWrite(latch, HIGH);
}
int dice() {
  int numberState = false;
  for (int i = 1; i <= 5; i++) {
    displayNumber(i);
    if (digitalRead(diceButton) == HIGH) numberState = true;
    if (numberState == true) {
      delay(300);
      return i;
    }
    if (i == 5) {
      i = 0;
    }
    delay(50);
  }
}
bool is_correct() {
  lcd.clear();
  print_information();
  ex.init();
  print_exercise(ex.practise);
  char customKey;
  char customKeys[100];
  int index =  0;
  while(1) {
    customKey = customKeypad.getKey();
    if (customKey) {
      if (customKey != 'C' && customKey != 'A') {
        lcd.print(customKey);
        customKeys[index] = customKey;
        index++;
      }else if (customKey == 'A') {
        customKeys[index] = '\0';
        if (strcmp(customKeys,ex.result) == 0) {
          lcd.clear();
          print_information();
          lcd.setCursor(6,2);
          lcd.print("Correct!");
          return true;
        }else {
          lcd.clear();
          lcd.setCursor(6,1);
          lcd.print("Wrong! ");
          char all[20];
          sprintf(all,"not %s,it's %s",customKeys,ex.result);
          lcd.setCursor(0,2);
          lcd.print(all);
          return false;
        }
      }else if (customKey == 'C') {
        if (index != 0) {
          customKeys[index - 1] = '\0';
          index--;
          lcd.clear();
          print_information();
          char all[150];
          strcpy(all,ex.practise);
          strcat(all,customKeys);
          print_exercise(all);
        }
      }
    }
  }
}
void print_information() {
  char information[25];
  sprintf(information,"A:(%d,%d) B:(%d,%d)",ax,7 - ay,bx,7 - by);
  lcd.setCursor(0,0);
  lcd.print(information);
  lcd.setCursor(0,1);
  if(is_a) {
    lcd.print("Now it's A turn");
  }else {
    lcd.print("Now it's B turn");
  }
}
void print_first() {
  lcd.setCursor(0,1);
  lcd.print("      WELCOME");
  lcd.setCursor(0,2);
  lcd.print("to play this game!!!");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Easy ---- A");
  lcd.setCursor(0,1);
  lcd.print("Normal ---- B");
  lcd.setCursor(0,2);
  lcd.print("Difficult ---- C");
  char customKey;
  while(1) {
    customKey = customKeypad.getKey();
    if (customKey) {
      if (customKey == 'A') {
        quesnum = 2;
        break;
      }else if (customKey == 'B') {
        break;
      }else if (customKey == 'C') {
        quesnum = 8;
        break;
      }
    }
  }
  lcd.clear();
}