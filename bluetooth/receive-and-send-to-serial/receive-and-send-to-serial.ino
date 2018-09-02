/*
 * A bluetooth program that sends back to the serial channel everything it receives
 */

// Bytes pending to be read.
int legth;

// The buffer to store the data read from the serial channel.
byte buffer[64] = {};

void setup() {
  Serial.begin(115200);
}

void loop() {
  int length = Serial.available();
  if (length > 0) {
    // Read from the serial channel.
    Serial.readBytes(buffer, length);

    // Write into the serial channel what has been read.
    Serial.write(buffer, length);
    Serial.println();
  }

  delay(50);
}
