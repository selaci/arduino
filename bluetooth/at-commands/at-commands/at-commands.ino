#include <SoftwareSerial.h>

// Pin 2 for RX and pin 3 for TX.
SoftwareSerial BTserial(2, 3);

char c;

void setup() {
  Serial.begin(115200);
  BTserial.begin(38400);
  Serial.println("Arduino ready for commands");
  Serial.println("Remember to select Both NL & CR in the serial monitor");
}

void loop() {
  if (BTserial.available()) {
    c = BTserial.read();
    Serial.write(c);
  }

  if (Serial.available()) {
    c = Serial.read();
    Serial.print(c);
    BTserial.write(c);
  }
}
