#include "sequence.h"
#include "driver.h"

const int DS    = 2;
const int LATCH = 3;
const int CLOCK = 4;

const int MAX_SEQUENCES = 6;

const int EN1 = 10;
const int IN1 = 9;
const int IN2 = 8;
const int IN3 = 7;
const int IN4 = 6;
const int EN2 = 5;

const int LEFT_REAR_LIGHT  = 11;
const int RIGHT_REAR_LIGHT = 12;

const int FRONT_RIGHT_SIDE_LIGHT = A3;
const int REAR_RIGHT_SIDE_LIGHT  = A2;
const int FRONT_LEFT_SIDE_LIGHT  = A1;
const int REAR_LEFT_SIDE_LIGHT  = A0;

const int MAX_SPEED_PERCENTAGE = 80;

const int DELAY = 75;

const bool DEBUG = false;

void setup() {
  Serial.begin(9600);

  // Led sequencer.
  pinMode(DS, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);

  // Right side motor.
  pinMode(EN1, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  // Left side motor.
  pinMode(EN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Rear lights.
  pinMode(LEFT_REAR_LIGHT, OUTPUT);
  pinMode(RIGHT_REAR_LIGHT, OUTPUT);

  // Right side lights.
  pinMode(FRONT_RIGHT_SIDE_LIGHT, OUTPUT);
  pinMode(REAR_RIGHT_SIDE_LIGHT, OUTPUT);

  // Left side lights.
  pinMode(FRONT_LEFT_SIDE_LIGHT, OUTPUT);
  pinMode(REAR_LEFT_SIDE_LIGHT, OUTPUT);
}

/* 
 * Build the sequences. 
 */
Sequence* sequences[MAX_SEQUENCES] = { new Circular(), new DoubleCircular(), new StarTrek(), 
                                       new KnightRider(), new DoubleKnightRider(), new FillUp() };

int sequenceIndex = 0;
Sequence* sequence = sequences[sequenceIndex];

/* 
 * Build the car. 
 */
Motor* rightMotor = new Motor(EN1, IN1, IN2);
Motor* leftMotor = new Motor(EN2, IN3, IN4);
Driver* driver = new Driver(rightMotor, leftMotor, MAX_SPEED_PERCENTAGE);

const int STOP              = 0;
const int FORWARD           = 1;
const int CLOCKWISE         = 2;
const int BACKWARD          = 3;
const int COUNTER_CLOCKWISE = 4;

void move(int maneuver) {
  switch(maneuver) {
    case STOP:
      driver->stop();
      break;
    case FORWARD:
      driver->moveForward();
      break;
    case CLOCKWISE:
      driver->rotateClockwise();
      break;
    case BACKWARD:
      driver->moveBackward();
      break;
    case COUNTER_CLOCKWISE:
      driver->rotateCounterClockwise();
      break;
    default:
      break;
  }
}

const int MOVE = 0;
const int CHANGE_SEQUENCE = 1;
const int SET_SPEED = 2;

int decodeAndExecute(byte message) {
  int command = (message & 0xC0) >> 6;
  switch(command) {
    case MOVE:
      int maneuver = message & 0x07;
      move(maneuver);
      break;
    case CHANGE_SEQUENCE:
      sequenceIndex += ++sequenceIndex % MAX_SEQUENCES;
      break;
    case SET_SPEED:
      int speed = (message & 0x0F) * 10;
      driver->setSpeed(speed);
      break;
    default:
      break;
  }
}
void loop() {
  if (Serial.available()) {
    byte message = Serial.read();
    decodeAndExecute(message);
  }

  sequence->next();
  delay(DELAY);
}
