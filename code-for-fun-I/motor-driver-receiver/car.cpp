#include "car.h"

Car::Car(Motor* leftMotor, Motor* rightMotor) {
  _leftMotor = leftMotor;
  _rightMotor = rightMotor;
}

void Car::moveForward(byte power) {
  _leftMotor->moveForward((byte) (power * _lPowerDistribution));
  _rightMotor->moveForward((byte) (power * _rPowerDistribution));
}

void Car::moveBackward(byte power) {
  _leftMotor->moveBackward((byte) (power * _lPowerDistribution));
  _rightMotor->moveBackward((byte) (power * _rPowerDistribution));
}

void Car::rotateToLeft(byte power) {
  _leftMotor->moveBackward((byte) (power * _lPowerDistribution));
  _rightMotor->moveForward((byte) (power * _rPowerDistribution));
}

void Car::rotateToRight(byte power) {
  _leftMotor->moveForward((byte) (power * _lPowerDistribution));
  _rightMotor->moveBackward((byte) (power * _rPowerDistribution));
}

void Car::setDistribution(float left, float right) {
  _lPowerDistribution = left;
  _rPowerDistribution = right;
}
