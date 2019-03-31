#ifndef MOTOR_H
#define MOTOR_H

#include "Arduino.h"

class Motor {
  private:

  byte _en;
  byte _in1;
  byte _in2;
  
  public:

  /*
   * The constructor.
   * 
   * @param en1 The "EN" pin in.
   * @param in1 The first "IN" pin.
   * @param in2 The second "IN" pin.
   * @return An instance of this class.
   */
  Motor(byte en, byte in1, byte in2);

  /*
   * Move the motor forward.
   * 
   * @param power The power the motor will use to move forward.
   */
  void moveForward(byte power);

  /*
   * Move the motor backward.
   * 
   * @param power The power the motor will use to move backward.
   */
  void moveBackward(byte power);

  /*
   * Stop any movement.
   */
  void stop();

  /*
   * Set the power for the motor.
   * 
   * @param power The power, which must range betwen 0 and 255, both included.
   *              It sets the power to 0 if power is lower than 0 and 255 if
   *              it is greater than 255.
   */
  void setSpeed(int power);
  
  private:

  /*
   * Ensures that the power belongs to the [0, 255] range, both included.
   * If the power is lower than 0 then, 0 is returned. If the power is
   * higher that 255 then, 255 is returned.
   *
   * @param power The power value that needs to be sanatised.
   */
  byte sanatisePower(byte power);
};

#endif
