/*
 * A simple program to test the 298N bridge.
 */

const int ENA = 10;
const int IN1 = 9;
const int IN2 = 8;

const int IN3 = 7;
const int IN4 = 6;
const int ENB = 5;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  // Motor A forward.
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  
  // Motor B forward.
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void loop() {
  digitalWrite(ENA, 100);
  digitalWrite(ENB, 100);

  delay(1000);
}
