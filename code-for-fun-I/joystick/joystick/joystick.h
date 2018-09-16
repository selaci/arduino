#ifndef Joystick_h
#define Joystick_h
#endif

#include "Arduino.h"

#define JOYSTICK_FIRST_QUADRANT 0
#define JOYSTICK_SECOND_QUADRANT 1
#define JOYSTICK_THIRD_QUADRANT 2
#define JOYSTICK_FORTH_QUADRANT 3
#define JOYSTICK_AT_CENTRE 4

#define JOYSTICK_22_5 0.3926991
#define JOYSTICK_45 0.785398
#define JOYSTICK_90 1.5708

class Joystick {
  private:
  float _mPower;
  float _x;
  float _y;
  int _quadrant;
  float _k;
  float _angle;

  public:
  Joystick(int mPower);  
  void setCoordinates(int x, int y);
  int getLeftMotorPower();
  int getRightMotorPower();
  int getQuadrant();

  private:
  float A();
  float B();
  float C();
};
