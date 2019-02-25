#include "car.h"
#include "constants.h"

Car::Car(Motor* leftMotor, Motor* rightMotor) {
  _leftMotor = leftMotor;
  _rightMotor = rightMotor;
}

void Car::moveForward(byte power) {
  if (DEBUG) {
    byte leftPower = power * _lPowerDistribution;
    byte rightPower = power * _rPowerDistribution;

    Serial.print("_leftMotor->moveForward(");
    Serial.print(leftPower);
    Serial.print(") _rightMotor->moveForward(");
    Serial.print(rightPower);
    Serial.println(")");
  }
  
  _leftMotor->moveForward((byte) (power * _lPowerDistribution));
  _rightMotor->moveForward((byte) (power * _rPowerDistribution));
}

void Car::moveBackward(byte power) {
  _leftMotor->moveBackward((byte) (power * _lPowerDistribution));
  _rightMotor->moveBackward((byte) (power * _rPowerDistribution));

  if (DEBUG) {
    byte leftPower = power * _lPowerDistribution;
    byte rightPower = power * _rPowerDistribution;

    Serial.print("_leftMotor->moveBackward(");
    Serial.print(leftPower);
    Serial.print(") _rightMotor->moveForward(");
    Serial.print(rightPower);
    Serial.println(")");
  }
}

void Car::rotateToLeft(byte power) {
  _leftMotor->moveBackward((byte) (power * _lPowerDistribution));
  _rightMotor->moveForward((byte) (power * _rPowerDistribution));

  if (DEBUG) {
    byte leftPower = power * _lPowerDistribution;
    byte rightPower = power * _rPowerDistribution;

    Serial.print("_leftMotor->moveBackward(");
    Serial.print(leftPower);
    Serial.print(") _rightMotor->moveForward(");
    Serial.print(rightPower);
    Serial.println(")");
  }
}

void Car::rotateToRight(byte power) {
  _leftMotor->moveForward((byte) (power * _lPowerDistribution));
  _rightMotor->moveBackward((byte) (power * _rPowerDistribution));

  if (DEBUG) {
    byte leftPower = power * _lPowerDistribution;
    byte rightPower = power * _rPowerDistribution;

    Serial.print("_leftMotor->moveForward(");
    Serial.print(leftPower);
    Serial.print(") _rightMotor->moveBackward(");
    Serial.print(rightPower);
    Serial.println(")");
  }
}

void Car::setDistribution(float left, float right) {
  _lPowerDistribution = left;
  _rPowerDistribution = right;
}
