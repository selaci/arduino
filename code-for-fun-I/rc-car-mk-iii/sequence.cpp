#include "sequence.h"

unsigned int Sequence::next() {
  return 0;
}

Sequence::~Sequence() {}

unsigned int Circular::next() {
  unsigned long number = ((_number << 1) % 65536);

  if (number == 0) {
    _number = 1;
  } else {
    _number = (unsigned int) number;
  }

  return _number;
}

unsigned int DoubleCircular::next() {
    _index = (_index + 1) % 8;
  return _sequence[_index];
}

unsigned int StarTrek::next() {
    _index = (_index + 1) % 4;
  return _sequence[_index];
}

unsigned int KnightRider::next() {
    _index = (_index + 1) % 14;
  return _sequence[_index];
}

unsigned int DoubleKnightRider::next() {
  _index = (_index + 1) % 14;
  return _sequence[_index];
}

unsigned int FillUp::next() {
  if (_max == 0) {
    _number = 0;
    _max = 32768;
    _cumulated = 0;
  }

  if (_number == 0) {
    _number = 1;
  } else {
    _number = _number << 1;
  }

  if (_number == _max) {
    _max >>= 1;
    _cumulated += _number;
    _number = 0;
  }

  return _cumulated + _number;
}
