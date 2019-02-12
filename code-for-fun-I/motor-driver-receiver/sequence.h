#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "Arduino.h"

/*
 * An abstract class that defines the contract each LED sequence must implement.
 *
 * Each sequence is supposed to upate the current sequence at a certain intervals.
 * The LED is controlled by a 74HC595 shift register. So the sequence returns an
 * integer. In this case the integer must range from 0 to 255.
 */
class Sequence {
public:

  /*
   * The next integer in the sequence. It can actually be any value, even the same
   * one in case the sequence does not change for whatever reason.
   */
  virtual int next() = 0;
};

/*
 * A sequence that moves from left to right and then back from right to left.
 */
class Horizontal: public Sequence {
private:

  int sequence[8] = {1, 2, 4, 8, 16, 32, 64, 128};
  int length = 8;
  int index = -1;
  bool increasing = true;

public:

  int next();

private:

  bool isIncreasing();

  int nextToRight() {
    index++;
    if (index == length - 1) {
      increasing = false;
    }

    return sequence[index];
  }

  int nextToLeft() {
    index--;
    if (index == 0) {
      increasing = true;
    }

    return sequence[index];
  }
};

/*
 * A random sequencer.
 */
class Random: public Sequence {
  int next();
};

#endif
