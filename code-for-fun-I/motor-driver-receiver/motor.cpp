#include "motor.h"

Motor::Motor(byte en, byte in1, byte in2) {
  _en = en;
  _in1 = in1;
  _in2 = in2;

  pinMode(_en, OUTPUT);
  pinMode(_in1, OUTPUT);
  pinMode(_in2, OUTPUT);
}

byte Motor::sanatisePower(byte power) {
  if (power < 0) {
    return 0;
  } else if (power > 255) {
    return 255;
  } else {
    return power;
  }
}
void Motor::moveForward(byte power) {
  digitalWrite(_in1, HIGH);
  digitalWrite(_in2, LOW);

  power = sanatisePower(power);
  analogWrite(_en, power);
}

void Motor::moveBackward(byte power) {
  digitalWrite(_in1, LOW);
  digitalWrite(_in2, HIGH);

  power = sanatisePower(power);
  analogWrite(_en, power);
}
