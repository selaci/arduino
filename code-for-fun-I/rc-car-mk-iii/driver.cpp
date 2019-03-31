#include "driver.h"

int Driver::determinePower(int percentage) {
  if (percentage > _maxPercentage) {
    percentage = _maxPercentage;
  } else if (percentage < 0) {
    percentage = 0;
  }

    return map(percentage, 0, 100, 0, 255);
}

Driver::Driver(Motor* rightMotor, Motor* leftMotor, int maxPercentage) {
  _rightMotor = rightMotor;
  _leftMotor = leftMotor;

  if (maxPercentage > 100) {
    _maxPercentage = 100;
  } else if (_maxPercentage < 0) {
    _maxPercentage = 0;
  } else {
    _maxPercentage = maxPercentage;
  }

  // It returns roughly 60 out of 255.
  _power = determinePower(24);
}

void Driver::stop() {
  _rightMotor->stop();
  _leftMotor->stop();
}

void Driver::moveForward() {
  _rightMotor->moveForward(_power);
  _leftMotor->moveForward(_power);
}
  
void Driver::rotateClockwise() {
  _rightMotor->moveBackward(_power/2);
  _leftMotor->moveForward(_power/2);
}
  
void Driver::moveBackward() {
  _rightMotor->moveBackward(_power);
  _leftMotor->moveBackward(_power);
}
  
void Driver::rotateCounterClockwise() {
  _rightMotor->moveForward(_power/2);
  _leftMotor->moveBackward(_power/2);
}

void Driver::setSpeed(int percentage) {
  _power = determinePower(percentage);

  _rightMotor->setSpeed(_power);
  _leftMotor->setSpeed(_power);  
}
