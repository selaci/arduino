#ifndef Joystick_h
#define Joystick_h
#endif

#include "Arduino.h"

#define JOYSTICK_FIRST_QUADRANT 0
#define JOYSTICK_SECOND_QUADRANT 1
#define JOYSTICK_THIRD_QUADRANT 2
#define JOYSTICK_FORTH_QUADRANT 3
#define JOYSTICK_22_5_IN_RAD 0.3926991f
#define JOYSTICK_45_IN_RAD 0.785398f
#define JOYSTICK_90_IN_RAD 1.5708f

class Joystick {
  private:
  float _radius;
  int _mPower;
  int _x;
  int _y;
  int _quadrant;
  float _distance;
  float _angle;

  public:
  Joystick(float radius, int mPower);  
  void setCoordinates(int x, int y);
  int getLeftMotorPower();
  int getRightMotorPower();
  int getQuadrant();
};
