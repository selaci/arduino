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
};

#endif
