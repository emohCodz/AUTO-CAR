#include <LiquidCrystal.h>
#include <Wire.h>
#include <Encoder.h>

/* SENSOR CONNECTIONS */
// LCD
const int rs = 8, en = 9, db7 = 7, db6 = 6, db5 = 5, db4 = 4, backlight = 10;
LiquidCrystal lcd(rs, en, db4, db5, db6, db7);
// Motor Driver
const int IN1 = 1, IN2 = 2, IN3 = 12, IN4 = 13, enA = 3, enB = 11;
// Infrared Sensor
const int rightIR = A2, leftIR = A1;
// Rotary Encoder
const int encoderPin = A3;
const double wheelDiameter = 6.7;
int distance = 0;
volatile int pulseCounter = 0;
// MPU-6050
const int MPU_ADDR = 0x68;
int16_t AccX, AccY, AccZ;

/* E10X PROGRAM MODE */
int runProgram = 0; // Initialize to 0
int rampProgram = 0;
int angle = 0;

/* CAR FUNCTIONS */
// Movement
void moveForward(void);
void turnLeft(void);
void turnRight(void);
void stopCar(void);
void donut(void);
// Measurement

void measureDistance(void);
void measureAngle(void);

void setup() {
  // Setup I/O Pins
  pinMode(rightIR, INPUT);
  pinMode(leftIR, INPUT);
  pinMode(encoderPin, INPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  // Setup MPU-6050
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // Wake up the sensor (out of sleep mode)
  Wire.endTransmission(true);

  // Setup LCD (number of columns and rows).
  lcd.begin(16,2);
  lcd.clear();

  // Print a start up message to the LCD.
  lcd.setCursor(0,0);
  lcd.print("E10X: READY!");
  delay(1000);
  lcd.clear();

}

void loop() {
  // Measure the angle.

  lcd.clear();
  delay(2);
  lcd.setCursor(0,1);
  lcd.print("Angle:");
  lcd.setCursor(7,1);
  lcd.print(angle); 
  lcd.setCursor(9,1);
  lcd.print("      ");

  // Set the SELECT button.
  int x = analogRead(0);
  if (x < 800) {
    runProgram = 1;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("E10X: START!");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("E10X: GO!");
    lcd.clear();
  }

  if (runProgram == 1) {

    // Movement


    do {

    int rightSensor = digitalRead(rightIR);
    int leftSensor = digitalRead(leftIR);

      if((rightSensor == 1) && (leftSensor == 1)) {
            moveForward();
      } else if((rightSensor == 1) && (leftSensor == 0)) {
            turnLeft();
      } else if((rightSensor == 0) && (leftSensor == 1)) {
            turnRight();
      }
      measureAngle();
      if(angle >= 10) {
        stopCar();
        measureAngle();
        delay(1000);
        rampProgram = 1;
      }
    /*
    if (rampProgram == 1) {
              // LCD (Angle and Time Counter)
      lcd.setCursor(0,1);
      lcd.print("Angle:");
      lcd.setCursor(7,1);
      lcd.print(angle);
      lcd.setCursor(9,1);
      lcd.print("      ");
      moveForward();
      delay(800);
      stopCar();
      measureAngle();
      lcd.setCursor(0,1);
      lcd.print("Angle:");
      lcd.setCursor(7,1);
      lcd.print(angle);
      lcd.setCursor(9,1);
      lcd.print("      ");
      delay(900);
      moveForward();
      delay(700);
      stopCar();
      delay(4000);
      donut();
      delay(1130);
      stopCar();
      rampProgram = 0;
    }*/
  } while (runProgram == 1);

  }
}

void moveForward(void) {
  analogWrite(enA, 80);
  analogWrite(enB, 80);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnLeft(void) {
  analogWrite(enA, 130);
  analogWrite(enB, 130);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnRight(void) {
  analogWrite(enA, 130);
  analogWrite(enB, 130);
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

void donut(void) {
  analogWrite(enA, 255);
  analogWrite(enB, 220);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void measureDistance(void) {
  // Setup Encoder
  attachInterrupt(digitalPinToInterrupt(encoderPin), pulseCounter++, RISING);
  // Calculate the distance travelled
  distance = (pulseCounter * (PI * wheelDiameter) / 20) - 1;

}

void measureAngle(void) {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 14, true);
  AccX = Wire.read() << 8 | Wire.read();
  AccY = Wire.read() << 8 | Wire.read();
  AccZ = Wire.read() << 8 | Wire.read();
  int xAng = map(AccX, 265, 402, -90, 90);
  int yAng = map(AccY, 265, 402, -90, 90);
  int zAng = map(AccZ, 265, 402, -90, 90);
  // Calculate incline angle
  angle = 93 - RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);
  delay(300);
}
