#include "joystick.h"

Joystick::Joystick(int mPower) {
  _mPower = mPower;
}

void Joystick::setCoordinates(int x, int y) {
  if (x >= 512 && y >= 512) {
    _quadrant = JOYSTICK_FIRST_QUADRANT;
    _x = x - 512;
    _y = y - 512;
  } else if (x >= 512 && y < 512) {
    _quadrant = JOYSTICK_SECOND_QUADRANT;
    _x = x - 512;
    _y = 512 - y;
  } else if (x < 512 && y < 512) {
    _quadrant = JOYSTICK_THIRD_QUADRANT;
    _x = 512 - x;
    _y = 512 - y;
  } else if (x < 512 && y >= 512) {
    _quadrant = JOYSTICK_FORTH_QUADRANT;
    _x = 512 - x;
    _y = y - 512;
  } else {
    _quadrant = JOYSTICK_AT_CENTRE;
  }
    
  float distance = sqrt(_x * _x + _y * _y);
  _k = _mPower * distance / 512;

  if (distance != 0) {
    _angle = acos(_x / distance);
  } else {
    _angle = 0;
  }
}


int Joystick::getLeftMotorPower() {
  float power;

  switch(_quadrant) {
    case JOYSTICK_FIRST_QUADRANT:
      power = 1;
      break;
    case JOYSTICK_SECOND_QUADRANT:
      power = - 1;
      break;

    case JOYSTICK_THIRD_QUADRANT:
      if (_angle < JOYSTICK_22_5) {
        power = - C();
      } else if (_angle < JOYSTICK_45) {
        power = - B();
      } else {
        power = - A();
      }
      break;

    case JOYSTICK_FORTH_QUADRANT:
      if (_angle < JOYSTICK_22_5) {
        power = C();
      } else if (_angle < JOYSTICK_45) {
        power = B();
      } else {
        power = A();
      }
      break;

    default:
      power = 0;
      break;
  }

  return _k * power;
}

int Joystick::getRightMotorPower() {
  float power;

  switch(_quadrant) {
    case JOYSTICK_FIRST_QUADRANT:
      if (_angle < JOYSTICK_22_5) {
        power = C();
      } else if (_angle < JOYSTICK_45) {
        power = B();
      } else {
        power = A();
      }
      break;
    
    case JOYSTICK_SECOND_QUADRANT:
      if (_angle < JOYSTICK_22_5) {
        power = - C();
      } else if (_angle < JOYSTICK_45) {
        power = - B();
      } else {
        power = - A();
      }
      break;

    case JOYSTICK_THIRD_QUADRANT:
      power = - 1;
      break;

    case JOYSTICK_FORTH_QUADRANT:
      power = 1;
      break;

    default:
      power = 0;
      break;
  }
  return _k * power;
}

float Joystick::A() {
  return (1 - (JOYSTICK_90 - _angle) / JOYSTICK_90);
}

float Joystick::B() {
  return (_angle - JOYSTICK_22_5) / JOYSTICK_45;
}

float Joystick::C() {
  return (_angle - JOYSTICK_22_5) / JOYSTICK_22_5;
}

