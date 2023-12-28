// Starting of Program
int m1a = 9;
int m1b = 10;
int m2a = 11;
int m2b = 12;
char val;
int enA = 5;
int enB = 6;


void setup() 
{
pinMode(enA, OUTPUT);
pinMode(enB, OUTPUT); 
pinMode(m1a, OUTPUT);  // Digital pin 10 set as output Pin
pinMode(m1b, OUTPUT);  // Digital pin 11 set as output Pin
pinMode(m2a, OUTPUT);  // Digital pin 12 set as output Pin
pinMode(m2b, OUTPUT);  // Digital pin 13 set as output Pin
Serial.begin(9600);
}

void loop()
{
  while (Serial.available() > 0)
  {
  val = Serial.read();
  Serial.println(val);
  }

  if( val == 'F') // Forward
    {
      analogWrite(enA, 100);
      analogWrite(enB, 100);
      digitalWrite(m1a, LOW);
      digitalWrite(m1b, HIGH);
      digitalWrite(m2a, HIGH);
      digitalWrite(m2b, LOW);  
    }
  else if(val == 'B') // Backward
    {
      analogWrite(enA, 100);
      analogWrite(enB, 100);
      digitalWrite(m1a, HIGH);
      digitalWrite(m1b, LOW);
      digitalWrite(m2a, LOW);
      digitalWrite(m2b, HIGH); 
    }
  
    else if(val == 'L') //Left
    {
    analogWrite(enA, 150);
    analogWrite(enB, 100);
    digitalWrite(m1a, LOW);
    digitalWrite(m1b,  HIGH);
    digitalWrite(m2a, LOW);
    digitalWrite(m2b, HIGH);
    }
    else if(val == 'R') //Right
    {
    analogWrite(enA, 100);
    analogWrite(enB, 150);
    digitalWrite(m1a, HIGH);
    digitalWrite(m1b, LOW);
    digitalWrite(m2a, HIGH);
    digitalWrite(m2b, LOW); 
    }
    
  else if(val == 'S') //Stop
    {
    analogWrite(enA, 100);
    analogWrite(enB, 100);
    digitalWrite(m1a, LOW);
    digitalWrite(m1b, LOW);
    digitalWrite(m2a, LOW);
    digitalWrite(m2b, LOW); 
    }
  else if(val == 'I') //Forward Right
    {
      analogWrite(enA, 100);
      analogWrite(enB, 100);
    digitalWrite(m1a, HIGH);
    digitalWrite(m1b, LOW);
    digitalWrite(m2a, LOW);
    digitalWrite(m2b, LOW);
    }
  else if(val == 'J') //Backward Right
    {
      analogWrite(enA, 100);
      analogWrite(enB, 100);
    digitalWrite(m1a, LOW);
    digitalWrite(m1b, HIGH);
    digitalWrite(m2a, LOW);
    digitalWrite(m2b, LOW);
    }
   else if(val == 'G') //Forward Left
    {
      analogWrite(enA, 100);
      analogWrite(enB, 100);
    digitalWrite(m1a, LOW);
    digitalWrite(m1b, LOW);
    digitalWrite(m2a, HIGH);     digitalWrite(m2b, LOW);
    }
  else if(val == 'H') //Backward Left
    {
      analogWrite(enA, 100);
      analogWrite(enB, 100);
    digitalWrite(m1a, LOW);
    digitalWrite(m1b, LOW);
    digitalWrite(m2a, LOW);
    digitalWrite(m2b, HIGH); 
    }
}