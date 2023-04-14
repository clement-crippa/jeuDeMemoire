#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 

int ledPins[] = {8, 9, 10};  
int buttonPins[] = {A0, A1, A2};  

int sequence[10];  
int niveau = 1;  
int score = 0;  

void setup() {
  lcd.begin(16, 2);
  pinMode(ledPins[0], OUTPUT);
  pinMode(ledPins[1], OUTPUT);
  pinMode(ledPins[2], OUTPUT);
  pinMode(buttonPins[0], INPUT);
  pinMode(buttonPins[1], INPUT);
  pinMode(buttonPins[2], INPUT);
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Niveau: ");
  lcd.print(niveau);
  lcd.setCursor(0, 1);
  lcd.print("Score: ");
  lcd.print(score);
  delay(1000);
  lcd.clear();
  generateSequence();  
  digitalWrite(ledPins[0], LOW);  
  displaySequence(); 
  if (playSequence()) { 
    niveau++;  
    score++;  
  } else {
    niveau = 1;  
    score = 0; 
    lcd.setCursor(0, 0);
    lcd.print("Perdu !");
    delay(250);
    digitalWrite(ledPins[0], LOW);
    digitalWrite(ledPins[1], LOW);
    digitalWrite(ledPins[2], LOW);
    delay(250);
    tone(7, 2000, 1000);
    delay(3000);
    lcd.clear();
  }
}


void generateSequence() {
  for (int i = 0; i < niveau; i++) {
    sequence[i] = random(0, 3);
  }
}

void displaySequence() {
  for (int i = 0; i < niveau; i++) {
    digitalWrite(ledPins[sequence[i]], HIGH);  
    delay(500);  
    digitalWrite(ledPins[sequence[i]], LOW);  
    delay(250);  
  }
}

bool playSequence() {
  for (int i = 0; i < niveau; i++) {
    int buttonPressed = -1;
    while (buttonPressed == -1) {
      for (int j = 0; j < 3; j++) {
        if (digitalRead(buttonPins[j]) == HIGH) {
          buttonPressed = j;  
          digitalWrite(ledPins[j], HIGH);
        }
      }
    }
    if (buttonPressed != sequence[i]) { 
      return false;
    }
  digitalWrite(ledPins[buttonPressed], HIGH);  
  delay(500); 
  digitalWrite(ledPins[buttonPressed], LOW); 
    delay(250);
  }
  return true; 
}
