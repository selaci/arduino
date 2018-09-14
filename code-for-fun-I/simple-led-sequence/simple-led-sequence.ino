/*
 * LED pin layout
 * 
 * "pinMode" and "digitalWrite"
 */

const byte LED1 = 13;
const byte LED2 = 12;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

int i = 0;

void loop() {
  if (i == 0) {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
  } else if (i == 1) {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
  }  

  i = ++i % 2;
  delay(200);  
}
