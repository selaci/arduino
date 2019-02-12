#include "motor.h"

Motor::Motor(byte en, byte in1, byte in2) {
  _en = en;
  _in1 = in1;
  _in2 = in2;

  pinMode(_en, OUTPUT);
  pinMode(_in1, OUTPUT);
  pinMode(_in2, OUTPUT);
}

void Motor::moveForward(byte power) {
  digitalWrite(_in1, HIGH);
  digitalWrite(_in2, LOW);
  digitalWrite(_en, power);
}

void Motor::moveBackward(byte power) {
  digitalWrite(_in1, LOW);
  digitalWrite(_in2, HIGH);
  digitalWrite(_en, power);
}
