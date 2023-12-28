#include <LiquidCrystal.h>
#include <Wire.h>

/* LCD Pins */
const int rs = 8, en = 9, db7 = 7, db6 = 6, db5 = 5, db4 = 4, backlight = 10;
LiquidCrystal lcd(rs, en, db4, db5, db6, db7);
/* Motor Driver Pins */
const int IN1 = 1, IN2 = 2, IN3 = 12, IN4 = 13, enA = 11, enB = 3;
/* Ultrasonic Sensor Pins */
const int echoPin = A2, trigPin = A1;
long duration;
int objDistance;
/* Program Initializer */
int runProgram = 0;

// Movement functions
void moveForward(void);
void turnLeft(void);
void turnRight(void);
void stopCar(void);
// Detect functions
void detectObstacle(void);

void setup() {
  // Setup I/O pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  // Setup LCD (number of columns and rows).
  lcd.begin(16,2);
  lcd.clear();

  // Print a start up message to the LCD.
  lcd.setCursor(0,0);
  lcd.print("E10X: READY!");
  delay(1200);
  lcd.clear();
  lcd.print("Press <SELECT>");
  lcd.setCursor(0,1);
  lcd.print("To Start E10X");
}

void loop() {
  // Set the SELECT button.
  int x = analogRead(0);
  if (x < 800) {
    runProgram = 1;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("E10X: START!");
    delay(1000);
  }

  // Car starts moving.
  if (runProgram == 1) {
    // LCD (Move Mode Display)
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("E10X: GO!");
    lcd.clear();
    double startTime = millis();

    do {
      moveForward();
      measureDistance();
      detectObstacle();

      lcd.setCursor(0,1);
      lcd.print("Dist:");
      lcd.setCursor(7,1);
      lcd.print(objDistance);

      if (objDistance > 0 && objDistance <= 10) {
        stopCar();
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("OBJECT DETECTED");
        delay(3000);
        turnRight();
        delay(1000);
      }
    } while (runProgram == 1);
  }
}

void moveForward(void) {
  analogWrite(enA, 120);
  analogWrite(enB, 90);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnLeft(void) {
  analogWrite(enA, 120);
  analogWrite(enB, 90);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnRight(void) {
  analogWrite(enA, 90);
  analogWrite(enB, 120);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void stopCar(void) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
}

void detectObstacle(void) {
  // Transmit ultrasonic pulses
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(15);
  digitalWrite(trigPin, LOW);
  // Receive reflected ultrasonic pulses
  duration = pulseIn(echoPin, HIGH);
  // Calculate object distance
  objDistance = duration * 0.034 / 2;
  delay(10);
}
