#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "Arduino.h"

/*
 * A constant to control output messages. For development purposes.
 */
const bool DEBUG = false;

/*
 * The command to change the LED sequence.
 */
const int CHANGE_LED_SEQUENCE = 16;

/*
 * The commnad to move the vehicle.
 */
const int MOVE = 32;

/*
 * A message to be sent in case the command can not be decoded properly.
 */
const String UNEXPECTED_COMMAND = "Unexpected command";

/*
 * A message to be sent when the command's data can not be decoded properly.
 */
const String UNEXPECTED_DATA = "Unexpected data";

/*
 * 74HC595 pin layout.
 */
const byte DATA = 2;  // DS
const byte LATCH = 3; // ST_CP
const byte SHIFT = 4; // ST_CH

/*
 * Left motor pin layout.
 */

const byte EN2 = 9;
const byte IN4 = 8;
const byte IN3 = 7;

/*
 * Right motor pin layout.
 */

const byte EN1 = 10;
const byte IN1 = 11;
const byte IN2 = 12;


/*
 * The minimum value that will be sent to the motors. If the current value
 * is lower than this minimum then, 0 is delivered.
 */
const byte MINIMUM = 30;

#endif