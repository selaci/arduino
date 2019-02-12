#include "car.h"

Car::Car(Motor* leftMotor, Motor* rightMotor) {
  _leftMotor = leftMotor;
  _rightMotor = rightMotor;
}

void Car::moveForward(byte power) {
  _leftMotor->moveForward(power);
  _rightMotor->moveForward(power);
}

void Car::moveBackward(byte power) {
  _leftMotor->moveBackward(power);
  _rightMotor->moveBackward(power);
}

void Car::rotateToLeft(byte power) {
  _leftMotor->moveBackward(power);
  _rightMotor->moveForward(power);
}

void Car::rotateToRight(byte power) {
  _leftMotor->moveForward(power);
  _rightMotor->moveBackward(power);
}
