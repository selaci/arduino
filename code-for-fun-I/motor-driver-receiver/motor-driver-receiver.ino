#include "constants.h"
#include "sequence.h"
#include "car.h"

/*
 * A motor driver receiver with additional LED sequence.
 *
 * This program reads data from the serial channel and decodes it
 * into commands.
 */


/*
 * An array of sequences.
 */
int lengthSequences = 2;
Sequence* sequences[2] = { new Horizontal(), new Random() };

/* An index to keep track of the sequence number. */
int i = 0;


/*
 * The mega CAR!
 */
Car* car;

/*
 * The variable to boost or slow down the left motor based on the
 * distribution of power between the left and the right motor.
 */
float lPowerDistribution = 1;

/*
 * The variable to boost or slow down the right motor based on the
 * distribution of power between the left and the right motor.
 */
float rPowerDistribution = 1;

void setup() {
  // Initialise serial channel.
  Serial.begin(9600);

  // Build the car instance.
  Motor* leftMotor = new Motor(EN2, IN3, IN4);
  Motor* rightMotor = new Motor(EN1, IN1, IN2);

  car = new Car(leftMotor, rightMotor);

  // Set the 74HC595 pins.
  pinMode(DATA, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(SHIFT, OUTPUT);
}

/*
 * Rotate the car to the left or to the right.
 * 
 * @param h The horizontal division number. "h" should never be equal 
 *          to the neutral division number. If that happens then,
 *          there is bug in the code.
 */
void rotate(int h) {
  int power;
  if (h > NEUTRAL_DIVISION_NUMBER) {
    if (h > MAX_DIVISION_NUMBER) { 
      h = MAX_DIVISION_NUMBER;
    }
    power = map(h, NEUTRAL_DIVISION_NUMBER, MAX_DIVISION_NUMBER, 0, MAX_POWER);
    car->rotateToRight(power / 2);
    if (DEBUG) {
      Serial.print("car->rotateToRight(");
      Serial.print(power);
      Serial.println(")");
    }
  } else {
    if (h < 0) {
      h = 0;
    }
    power = map(h, 0, NEUTRAL_DIVISION_NUMBER, MAX_POWER, 0);
    car->rotateToLeft(power / 2);
    if (DEBUG) {
      Serial.print("car->rotateToLeft(");
      Serial.print(power);
      Serial.println(")");
    }
  }
}

/*
 * Move the car along the vertical axis. Either forward or backward.
 * 
 * @param v The vertical division number. "v" should never be equal 
 *          to the neutral division number. If that happens then,
 *          there is bug in the code.
 */
void moveStraight(int v) {
  int power;
  if (v < NEUTRAL_DIVISION_NUMBER) {
    if (v < 0) {
      v = 0;
    }
    
    power = map(v, NEUTRAL_DIVISION_NUMBER, 0, 0, MAX_POWER);
    car->moveForward(power);

    if (DEBUG) {
      Serial.print("car->moveForward(");
      Serial.print(power);
      Serial.println(")");
    }
  } else {
    if (v > MAX_DIVISION_NUMBER) { 
      v = MAX_DIVISION_NUMBER;
    }
    power = map(v, NEUTRAL_DIVISION_NUMBER, MAX_DIVISION_NUMBER, 0, MAX_POWER);
    car->moveBackward(power);
    if (DEBUG) {
      Serial.print("car->moveBackward(");
      Serial.print(power);
      Serial.println(")");
    }
  }
}
/*
 * Move the car according to the message.
 * 
 * @param message The encoded message that contains the vertical 
 *                and horizontal values.
 */
void move(byte message) {
  int h = (message & 0x38) >> 3;

  if (h !=  NEUTRAL_DIVISION_NUMBER) {
    rotate(h);
  } else {
    int v = message & 0x07;  
    moveStraight(v); // Either forward or backward.
  }
}

void processMessage(byte message) {
  byte command = message & 0xC0;

  if (command == MOVE_COMMAND) {
    move(message);
    
  } else if (command == CHANGE_LED_SEQUENCE_COMMAND) {
    if (DEBUG) {
      Serial.print("Change LED Sequence");
    }
    
    i = (i + 1) % lengthSequences;
  } else { // DISTRIBUTION
    
    byte distribution = message & 0x7F;
    lPowerDistribution = 2 - (2 * distribution) / 100.0;
    rPowerDistribution = 2 - lPowerDistribution;

    car->setDistribution(lPowerDistribution, rPowerDistribution);

    if (DEBUG) {
      Serial.print("Distribution: ");
      Serial.print(distribution);
      Serial.print(", lPowerDistribution: ");
      Serial.print(lPowerDistribution);
      Serial.print(", rPowerDistribution: ");
      Serial.println(rPowerDistribution);
    }
  }
}

void loop() {
  // Read and process all serial data.
  while(Serial.available()) {
    int message = Serial.read();

    // Print the message that has been received.
    if (DEBUG) {
      Serial.println(message, BIN);
    }
    
    processMessage(message);
  }

  // Update the LEDs.
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, SHIFT, MSBFIRST, sequences[i]->next());
  digitalWrite(LATCH, HIGH);

  // Sleep. ZZZzzzZZZzzz ...
  delay(75);
}
