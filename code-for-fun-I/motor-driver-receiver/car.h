#ifndef CAR_H
#define CAR_H

#include "Arduino.h"
#include "motor.h"

class Car {
  private:

  Motor* _leftMotor;
  Motor* _rightMotor;

  float _lPowerDistribution;
  float _rPowerDistribution;

  public:

  /*
   * The constructor.
   * 
   * @param leftMotor The left motor.
   * @param rightMotor The right motor.
   * @return An instance of this class.
   */
  Car(Motor* leftMotor, Motor* rightMotor);

  /*
   * Move the car forward.
   * 
   * @param power The power the car uses on both motors to move forward.
   */
  void moveForward(byte power);

  /*
   * Move the car backward.
   * 
   * @param power The power the car uses on both motors to move backward.
   */
  void moveBackward(byte power);

  /*
   * Rotate to the left. The rotation occurs by moving the right motor forward
   * and the left motor backward.
   * 
   * @param power The power the motors use to move.
   */
  void rotateToLeft(byte power);

  /*
   * Rotate to the right. The rotation occurs by moving the left motor forward
   * and the right motor backward.
   * 
   * @param power The power the motors use to move.
   */
  void rotateToRight(byte power);

  /*
   * Sets the power distribution between the left and the right motor.
   * This number needs to ranged between [0, 2] for each motor.
   */
  void setDistribution(float left, float right);
};

#endif
