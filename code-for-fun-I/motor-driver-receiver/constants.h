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
const byte CHANGE_LED_SEQUENCE_COMMAND = 0x00;


/*
 * The commnad to move the vehicle.
 */
const byte MOVE_COMMAND = 0x40;

/*
 * The command to distribute power between the motors.
 */
const byte DISTRIBUTION_COMMAND = 0x80;

/*
 * The number of divisions. From 0 to (max -1)
 */
const int MAX_DIVISION_NUMBER = 6;

/*
 * The division number that acts as a neural position or
 * in other words that indicates that no power should be
 * applied.
 */
const int NEUTRAL_DIVISION_NUMBER = 3;

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
const byte IN4 = 7;
const byte IN3 = 8;

/*
 * Right motor pin layout.
 */

const byte EN1 = 10;
const byte IN1 = 11;
const byte IN2 = 12;

/*
 * The maximum power that will be delivered to the motors.
 * I use this in order to limit the speed. Otherwise the car
 * may get a bit out of control.
 */
const byte MAX_POWER = 170;

#endif
