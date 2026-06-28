#include <LiquidCrystal.h>

// LCD: RS, EN, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int sensor = A0;
int airValue = 0;

// LEDs
int greenLED = 6;
int redLED   = 7;

// Buzzer
int buzzer = 8;

void setup()
{
  Serial.begin(9600);

  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(buzzer, OUTPUT);

  lcd.begin(16, 2);

  // Welcome Screen
  lcd.setCursor(0, 0);
  lcd.print("Welcome To");

  lcd.setCursor(0, 1);
  lcd.print("Tanuja's AMS");

  delay(3000);

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Air Monitoring");

  lcd.setCursor(0, 1);
  lcd.print("System");

  delay(2000);

  lcd.clear();
}

void loop()
{
  airValue = analogRead(sensor);

  Serial.print("Air Quality Value: ");
  Serial.println(airValue);

  // FRESH AIR
  if (airValue < 350)
  {
    digitalWrite(greenLED, HIGH);
    digitalWrite(redLED, LOW);
    noTone(buzzer);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Fresh Air");

    lcd.setCursor(0, 1);
    lcd.print("AQ:");
    lcd.print(airValue);
  }

  // POOR AIR
  else if (airValue < 700)
  {
    digitalWrite(greenLED, LOW);
    digitalWrite(redLED, HIGH);
    noTone(buzzer);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Poor Air");

    lcd.setCursor(0, 1);
    lcd.print("AQ:");
    lcd.print(airValue);
  }

  // VERY POOR AIR
  else
  {
    digitalWrite(greenLED, LOW);
    digitalWrite(redLED, HIGH);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Avoid Going Out");

    lcd.setCursor(0, 1);
    lcd.print("AQ:");
    lcd.print(airValue);

    tone(buzzer, 1000);
    delay(300);
    noTone(buzzer);
  }

  delay(1000);
}