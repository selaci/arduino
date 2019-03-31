#ifndef DRIVER_H
#define DRIVER_H

#include "motor.h"

class Driver {
private:
  Motor* _rightMotor;
  Motor* _leftMotor;
  int _maxPercentage;
  int _power;

  int determinePower(int percentage);

public:
  /*
   * The onstructor.
   * 
   * @param right, the motor located at the right side of the car.
   * @param left, the motor located at the left side of the car.
   * @maxPercentage , a constant that ranges between 0 and 100. It's
   *                  the percentage of maximum speed to be applied
   *                  to the motors. For example, 50, would be 50%
   *                  of the maximum speed.
   */
  Driver(Motor* right, Motor* left, int maxPercentage);

  /*
   * Stops all motors.
   */
  void stop();

  /*
   * Sets all motors to move forward.
   */
  void moveForward();

  /*
   * Reverse the right motor and set the left one forward.
   */
  void rotateClockwise();

  /*
   * Sets all motors in reverse mode.
   */
  void moveBackward();

  /*
   * Reverse the left motor and set the right one forward.
   */
  void rotateCounterClockwise();

  /*
   * Set the speed of the motors.
   * 
   * @param percentage , a constant that ranges between 0 and 100. It's
   *                     the percentage of maximum speed to be applied
   *                     to the motors. For example, 50, would be 50%
   *                     of the maximum speed.
   */
  void setSpeed(int percentage);
};

#endif
