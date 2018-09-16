#include "joystick.h"

Joystick::Joystick(float radius, int mPower) {
  _radius = radius;
  _mPower = mPower;
}

void Joystick::setCoordinates(int x, int y) {
  if (x > 512 && y > 512) {
    _quadrant = JOYSTICK_FIRST_QUADRANT;
    _x = x - 512;
    _y = y - 512;
  } else if (x > 512 && y < 512) {
    _quadrant = JOYSTICK_SECOND_QUADRANT;
    _x = x - 512;
    _y = 512 - y;
  } else if (x < 512 && y > 512) {
    _quadrant = JOYSTICK_THIRD_QUADRANT;
    _x = 512 - x;
    _y = 512 - y;
  } else {
    _quadrant = JOYSTICK_FORTH_QUADRANT;
    _x = 512 - x;
    _y = y - 512;
  }

  _distance = sqrt(_x * _x + _y * _y);

  _angle = acos(x / _distance);
}

int Joystick::getLeftMotorPower() {
  int power;

  switch (_quadrant) {
  case JOYSTICK_FIRST_QUADRANT:
    power = (int) (_mPower * _distance / _radius);
    break;
  case JOYSTICK_SECOND_QUADRANT:
    power = (int) (_mPower * _distance / _radius);
  case JOYSTICK_THIRD_QUADRANT:
    if (_angle < JOYSTICK_22_5_IN_RAD) {
      power = (int) (-(_mPower * _distance / _radius) * (_angle - JOYSTICK_22_5_IN_RAD) / JOYSTICK_22_5_IN_RAD);
    } else if (_angle < JOYSTICK_45_IN_RAD) {
      power = (int) (-(_mPower * _distance / _radius) * (_angle - JOYSTICK_22_5_IN_RAD) / JOYSTICK_45_IN_RAD);
    } else {
      power = (int) (-(_mPower * _distance / _radius) * (JOYSTICK_90_IN_RAD - _angle) / JOYSTICK_90_IN_RAD);
    }
    break;
  case JOYSTICK_FORTH_QUADRANT:      
    if (_angle < JOYSTICK_22_5_IN_RAD) {
      power = (int) ((_mPower * _distance / _radius) * (_angle - JOYSTICK_22_5_IN_RAD) / JOYSTICK_22_5_IN_RAD);
    } else if (_angle < JOYSTICK_45_IN_RAD) {
      power = (int) ((_mPower * _distance / _radius) * (_angle - JOYSTICK_22_5_IN_RAD) / JOYSTICK_45_IN_RAD);
    } else {
      power = (int) (-(_mPower * _distance / _radius) * (JOYSTICK_90_IN_RAD - _angle) / JOYSTICK_90_IN_RAD);
    }
    break;
  }

  return power;
}

int Joystick::getRightMotorPower() {
  int power;

  switch(_quadrant) {
  case JOYSTICK_FIRST_QUADRANT:
    if (_angle < JOYSTICK_22_5_IN_RAD) {
      power = (int) ( (_mPower * _distance / _radius) * (JOYSTICK_90_IN_RAD - _angle) / JOYSTICK_90_IN_RAD )
    } else if (_angle < JOYSTICK_45_IN_RAD) {
    } else {
    }
    break;
  }
}
