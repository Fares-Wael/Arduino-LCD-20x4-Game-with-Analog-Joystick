#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 4, 20);
int VRy = A0;
int VRx = A1;
int SW = 2;
byte counter = 0;
byte mc = 0, mr = 0;
byte ac = 2, ar = 0;
int xPosition = 0;
int yPosition = 0;
int SW_state = 0;
int mapX = 0;
int mapY = 0;
byte i = 19;
byte j = 19;
byte monster[] = {
  B01111,
  B01111,
  B01111,
  B11100,
  B11100,
  B00110,
  B01111,
  B01001
};
byte arrow[] = {
  B00011,
  B00110,
  B01100,
  B11000,
  B11000,
  B01100,
  B00110,
  B00011
};
void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP);
  lcd.createChar(0, monster);
  lcd.setCursor(0, 0);
  lcd.write(0);
  lcd.createChar(1, arrow);
}
void loop() {
  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  SW_state = digitalRead(SW);
  mapX = map(xPosition, 0, 1023, 1, -1);
  mapY = map(yPosition, 0, 1023, 1, -1);
  if (mapX) {
    if (mapX == 1) {
      mc++;
      lcd.setCursor(mc - 1, mr);
      lcd.print(" ");
      lcd.setCursor(mc, mr);
      lcd.write(0);
      delay(100);
      if (mc >= 18) mc = 18;
    } else if (mapX == -1) {
      mc--;
      lcd.setCursor(mc + 1, mr);
      lcd.print("  ");
      lcd.setCursor(mc, mr);
      lcd.write(0);
      delay(100);
      if (mc == 255) mc = 0;
    }
  }
  if (mapY) {
    if (mapY == 1) {
      mr++;
      lcd.setCursor(mc, mr - 1);
      lcd.print(" ");
      lcd.setCursor(mc, mr);
      lcd.write(0);
      delay(100);
      if (mr >= 3) mr = 3;
      if (mr == 4) mr = 3;
    } else if (mapY == -1) {
      mr--;
      lcd.setCursor(mc, mr + 1);
      lcd.print("  ");
      lcd.setCursor(mc, mr);
      lcd.write(0);
      delay(100);
      if (mr <= 0) mr = 0;
      if (mr == 255) mr = 0;
    }
  }
  lcd.setCursor(i + 1, ar);
  lcd.print(" ");
  lcd.setCursor(i, ar);
  lcd.write(1);
  delay(100);
  if (i <= 0) i = 0;
  i--;
  if (mc == i && i == 0) {
    if (mr == ar) {
      counter++;
      Serial.println(counter);
      lcd.setCursor(0, ar);
      lcd.print(" ");
      i = 19;
      ar++;
      if (ar == 3) ar = 0;
    }
  }
  if (mc == i && i != 0) {
    if (mr == ar && i != 0) {
      gameover();
    }
  }
  delay(100);
  lcd.setCursor(j + 1, ac);
  lcd.print(" ");
  lcd.setCursor(j, ac);
  lcd.write(1);
  delay(100);
  if (j <= 0) j = 0;
  j--;
  if (mc == j && j == 0) {
    if (mr == ac) {
      counter++;
      Serial.println(counter);
      lcd.setCursor(0, ac);
      lcd.print(" ");
      j = 19;
      ac++;
      if (ac >= 3) ar = 0;
    }
  }
  if (mc == j && j != 0) {
    if (mr == ac && j != 0) {
      gameover();
    }
  }
  delay(100);
}
void gameover() {
  Serial.println("Game Over");
  counter = 0;
  lcd.clear();
  lcd.setCursor(4, 1);
  lcd.print("Game over..!");
  delay(1000);
  lcd.clear();
  delay(1000);
  lcd.setCursor(4, 1);
  lcd.print("Game over..!");
  delay(1000);
  lcd.clear();
  delay(1000);
  lcd.setCursor(4, 1);
  lcd.print("Game over..!");
  delay(1000);
  lcd.clear();
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.write(0);
  mc = 0;
  mr = 0;
  i = 19;
  j = 19;
  ac = 2;
  ar = 0;
}