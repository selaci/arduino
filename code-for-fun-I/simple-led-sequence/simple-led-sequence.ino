/*
 * LED pin layout
 * 
 * "pinMode" and "digitalWrite"
 */

const byte LED1 = 0;
const byte LED2 = 1;
const byte LED3 = 2;
const byte LED4 = 3;
const byte LED5 = 4;
const byte LED6 = 5;
const byte LED7 = 6;
const byte LED8 = 7;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(LED7, OUTPUT);
  pinMode(LED8, OUTPUT);
}

int i = 0;

void loop() {
  if (i == 0) {
    digitalWrite(LED8, LOW);
    digitalWrite(LED1, HIGH);
  } else if (i == 1) {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
  } else if (i == 2) {
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, HIGH);
  } else if (i == 3) {
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, HIGH);
  } else if (i == 4) {
    digitalWrite(LED4, LOW);
    digitalWrite(LED5, HIGH);
  } else if (i == 5) {
    digitalWrite(LED5, LOW);
    digitalWrite(LED6, HIGH);
  } else if (i == 6) {
    digitalWrite(LED6, LOW);
    digitalWrite(LED7, HIGH);    
  } else if (i == 7) {
    digitalWrite(LED7, LOW);
    digitalWrite(LED8, HIGH);
  }
  
  i = ++i % 8;
  delay(100);
}
